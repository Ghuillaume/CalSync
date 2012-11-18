#include "cardparser.h"
#include <assert.h>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>

#ifndef TRUE 
#define FALSE 0
#define TRUE -1
#endif

/************************ 
Test
*/

typedef struct TUserData
{
	int indent;
	int inBegin, inEnd, startData;
	char *cardType;

} TUserData;

void OutChar(int n, char ch)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%c", ch);
};

void PropHandler(void *userData, const CARD_Char *propName, const CARD_Char **params)
{
	TUserData *ud = (TUserData *) userData;
    char *pname = NULL;
    const CARD_Char **p = NULL;
	
    assert(ud != NULL);

	ud->inBegin = FALSE;
	ud->inEnd = FALSE;
	ud->startData = TRUE;

	if (strcmpi(propName, "BEGIN") == 0)
	{
		/* begin: vcard/vcal/whatever */
		ud->inBegin = TRUE;
		ud->indent++;
	}
	else if (strcmpi(propName, "END") == 0)
	{
		/* end: vcard/vcal/whatever */
        free(ud->cardType);
        ud->cardType = NULL;
		ud->inEnd = TRUE;
		ud->indent--;
	}
	else
	{
		OutChar(ud->indent * 4, ' ');

		pname = strdup(propName);
		strupr(pname);
		printf("%s:\n", pname);
        free(pname);

		p = params;
		while (p[0])
		{
            OutChar(ud->indent * 4, ' ');
            printf(" * %s", p[0]);

			if (p[1])
                printf("=\"%s\"", p[1]);

			printf("\n");
			p += 2;
		};
	};
};


void DataHandler(void *userData, const CARD_Char *data, int len)
{
	TUserData *ud = (TUserData *) userData;
    int i;
	assert(ud != NULL);

	if (ud->inBegin)
	{
		/* accumulate begin data */
		if (len > 0)
		{
            ud->cardType = realloc(ud->cardType, len + 1);
            memcpy(ud->cardType, data, len);
            ud->cardType[len] = 0;
		}
		else
		{
			strupr(ud->cardType);
			OutChar(ud->indent * 4 - 4, ' ');
            printf("[%s]\n", ud->cardType);
		};
	}
	else if (ud->inEnd)
	{
		if (len > 0)
		{
            ud->cardType = realloc(ud->cardType, len + 1);
            memcpy(ud->cardType, data, len);
            ud->cardType[len] = 0;
		}
        else if (ud->cardType)
        {
            OutChar(ud->indent * 4, ' ');
            printf("EOF [%s]\n", ud->cardType);
            free(ud->cardType);
            ud->cardType = NULL;
        };
	}
	else
	{
		if (ud->startData)
        {
			OutChar(ud->indent * 4, ' ');
            printf(" Data = {");
		    ud->startData = FALSE;
        };

		if (len == 0)
			printf("}\n");
		else
		{
			/* output printable data */
			for (i = 0; i < len; i++)
			{
				CARD_Char c = data[i];
				if (c == '\r')
					printf("\\r");
				else if (c == '\n')
					printf("\\n");
				else if (c >= ' ' && c <= '~')
					printf("%c", c);
			};
		};
	};
};

int main(int argc, char *argv[])
{
    const char *fname = argv[1];
	TUserData userData;
    CARD_Parser vp = NULL;
    FILE *f = NULL;
	int parseErr = FALSE;
    int len, rc;
	char buf[512];

    memset(&userData, 0, sizeof(userData));

	printf("Test vCard parser\n");
    printf("Parser version = %s\n", CARD_ParserVersion());

    if (argc <= 1)
    {
        printf("usage:\n  test <vcardfilename>\n");
        return 0;
    };

    if (access(fname, 0) != 0)
    {
        printf("unable to access <%s>\n", fname);
        return -1;
    };

	/* open test */
    f = fopen(fname, "r+b");
	if (! f)
	{
		printf("Unable to open test card %s\n", fname);
		return 0;
	};


	/* allocate parser */
	vp = CARD_ParserCreate(NULL);

	/* initialise */
	CARD_SetUserData(vp, &userData);
	CARD_SetPropHandler(vp, PropHandler);
	CARD_SetDataHandler(vp, DataHandler);

	/* parse */
    len = fread(buf, 1, sizeof(buf), f); 
	while (len > 0)
	{
		rc = CARD_Parse(vp, buf, len, FALSE);
		if (rc == 0)
		{
			parseErr = TRUE;
			printf("Error parsing vcard\n");
			break;
		};

		len = fread(buf, 1, sizeof(buf), f); 
	};
    fclose(f);

	/* finalise parsing */
	if (! parseErr)
		CARD_Parse(vp, NULL, 0, TRUE);

	/* free parser */
	CARD_ParserFree(vp);

	/* done */
	printf("Done.\n");

    /* free up any remaining user data buffers */
    free(userData.cardType);

	return 0;
};
