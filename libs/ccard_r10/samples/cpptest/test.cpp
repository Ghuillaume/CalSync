#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <stack>
#include <sstream>
using namespace std;

#include "cardparser.h"
#include <assert.h>
#include <io.h>

#define TOUPPER(s) transform(s.begin(), s.end(), s.begin(), toupper)

///////////////////////////////////////////////
// Test
class TUserData
{
public:
	bool inBegin, inEnd, startData;
	string cardType;

	TUserData() : inBegin(true), inEnd(false), startData(true) {}
};

typedef stack<TUserData> TUserDataStack;

// globals
TUserDataStack  dataStack;

#define INDENT (dataStack.size())
#define INDENTSTR1 string(INDENT * 4 - 4, ' ')
#define INDENTSTR2 string(INDENT * 4, ' ')
#define INDENTSTR3 string(INDENT * 4 + 4, ' ')

extern "C" void PropHandler(void *userData, const CARD_Char *propName, const CARD_Char **params)
{
	if (strcmpi(propName, "BEGIN") == 0)
	{
		// begin: vcard/vcal/whatever
        dataStack.push(TUserData());
        return;
	};

    if (dataStack.empty())
    {
        cout << "ERROR:Property encountered with no BEGIN:" << endl;
        return;
    };

	if (strcmpi(propName, "END") == 0)
	{
		// end: vcard/vcal/whatever
		dataStack.top().inEnd = true;
	}
	else
	{
		cout << INDENTSTR2;

		string pname = propName;
		TOUPPER(pname);
		cout << pname << ":" << endl;

		const CARD_Char **p = params;
		while (p[0])
		{
			cout << INDENTSTR2 << "* " << p[0];

			if (p[1])
				cout << "=" << '\"' << p[1] << '\"' ;

			cout << endl;
			p += 2;
		};
	};
};


extern "C" void DataHandler(void *userData, const CARD_Char *data, int len)
{
    if (dataStack.empty())
    {
        cout << "ERROR:data encountered with no BEGIN:" << endl;
        return;
    };

	if (dataStack.top().inBegin)
	{
		// accumulate begin data
		ostringstream os;
		if (len > 0)
		{
			os.write(data, len);
			dataStack.top().cardType += os.str();
		}
		else
		{
			TOUPPER(dataStack.top().cardType);
			cout 
				<< INDENTSTR1 
				<< "[" << dataStack.top().cardType << "]" << endl;
            dataStack.top().inBegin = false;
		};
	}
	else if (dataStack.top().inEnd)
	{
		if (len == 0)
        {
			cout << INDENTSTR1 << "EOF [" << dataStack.top().cardType << "]" << endl;
            dataStack.pop();
        };
	}
	else
	{
		if (dataStack.top().startData)
			cout << INDENTSTR3;
		dataStack.top().startData = false;

		if (len == 0)
        {
			cout <<  endl;
            dataStack.top().startData = true;
        }
		else
		{
			// output printable data
            // do some arbitary wrapping
            int col = 0;
			for (int i = 0; i < len; i++)
			{
				CARD_Char c = data[i];
                if (col >= (75 - int(INDENT) * 4 - 4))
                {
					cout << endl << INDENTSTR3;
                    col = 0;
                };
				if (c == '\n')
                {
					cout << endl << INDENTSTR3;
                    col = 0;
                }
				else if (c >= ' ' && c <= '~')
                {
					cout << c;
                    col++;
                };
			};

            // debug
            // write to file
            /* 
            ofstream os("e:\\test\\test.jpg", ios::binary | ios::ate);
            os.write(data, len);
            os.close();
            */
		};
	};
};

int main(int argc, char *argv[])
{
	cout << "Test vCard parser" << endl;
    cout << "Parser version = " << CARD_ParserVersion() << endl;

    if (argc <= 1)
    {
        cout 
            << "usage:" << endl
            << "  test <vcardfilename>" << endl;
        return 0;
    };

    const char *fname = argv[1];

    if (access(fname, 0) != 0)
    {
        cout << "unable to access <" << fname << ">" << endl;
        return -1;
    };

	// open test
	ifstream is(fname, ios::binary);
	if (! is)
	{
		cout << "Unable to open test card " << fname << endl;
		return 0;
	};

	// allocate parser
	CARD_Parser vp = CARD_ParserCreate(NULL);

	// initialise
	CARD_SetPropHandler(vp, PropHandler);
	CARD_SetDataHandler(vp, DataHandler);

	// parse
	bool parseErr = false;
	char buf[512];
	is.read(buf, sizeof(buf));
	while (is.gcount() > 0)
	{
		int len = is.gcount();
		int rc = CARD_Parse(vp, buf, len, false);
		if (rc == 0)
		{
			parseErr = true;
			cout << "Error parsing vcard" << endl;
			break;
		};

		is.read(buf, sizeof(buf));
	};

	// finalise parsing
	if (! parseErr)
		CARD_Parse(vp, NULL, 0, true);

	// free parser
	CARD_ParserFree(vp);

	// done
	cout << "Done." << endl;

	return 0;
};
