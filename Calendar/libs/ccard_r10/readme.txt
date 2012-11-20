CARD Parser 1.0 Release
Lindsay Mathieson
Email : <blackpaw@users.sourceforge.net>

This is prelimanary stuff - feel free to email with suggestions &/or patches.

Built & tested with MS Visual C++ 6.0 & DevStudio

Licensing : All code is under the Mozilla Public License 1.1 (MPL 1.1) as specified in 
license.txt

Features:
=========
- generic for any card sytax, e.g vCard & vCal
- reports errors in sytax
- Event orientated (ie reentrant & stream orientated)
- Handles line folding
- Automatic decoding of params
- Handles quoted-printable and base64 decoding


Does NOT:
---------
- Generate cards (parser *only*)
- verify overall card structure - ie if required properties are missing - tough.


Vague Documentation
===================

Purpose:
--------
Card parser is for the general parsing of card (doh!) objects, aka vCards & vCals.
It is a event orientated parser designed to be used in a similar manner to expat (a XML
parser).

In general:
-----------

1. Create a card parser
   - CARD_ParserCreate

2. Init the parser:
   - CARD_SetUserData
   - CARD_SetPropHandler
   - CARD_SetDataHandler

3. Feed it Data
   - CARD_Parse
   - Handle the parse events in the callbacks specified in 2.
   - Keep feeding it data in as large and small chunks as you like

4. Free the card parser
   - CARD_ParserFree


Reference:
----------
//////////////////////////////////////////////////
// setup & parsing
CARD_Parser CARD_ParserCreate(CARD_Char *encoding);
* Returns
  a CARD Parser Object
* Params
  encoding (Acscii/Unicode/etc) - not implememnted yet, ascii only

void CARD_ParserFree(CARD_Parser p);
* Params
  p = Card parser object
* deallocates the card parser object

int CARD_Parse(CARD_Parser p, const char *s, int len, int isFinal);
* Returns
  0 - a parse error occurred
* Params
  p			= Card parser object
  s			= pointer to data stream to parse   
  len		= length of data chunk (pointed to by s)
  isFinal	= non zero if last chunk of data


//////////////////////////////////////////////////
// user data
void CARD_SetUserData(CARD_Parser p, void *userData);
* Params
  p = Card parser object
  userData = any user defined void *

void *CARD_GetUserData(CARD_Parser p);
* Returns
  The user dpecfied data for a card parser object
* Params
  p = Card parser object


//////////////////////////////////////////////////
// handler prototypes
typedef void (*CARD_PropHandler)(void *userData, const CARD_Char *propname, const CARD_Char **params);
* Desc     Called when a property & its params is fully parsed
* Params
  userData = user data specified for the card parser
  propName = name of property for this event
  params   = null terminated list of param name/value pairs
             params[0] = param name
			 params[1] = params value (can be null)
			 ...
			 params[n] = 0

typedef void (*CARD_DataHandler)(void *userData, const CARD_Char *data, int len);
* Desc     Called when a data chunk for a property is decoded
* Params
  userData = user data specified for the card parser
  data     = pointer to decoded data for a parameter (data = NULL = eod)
  len	   = len of data (len = 0 indicates eod)


//////////////////////////////////////////////////
// Set Handlers
void CARD_SetPropHandler(CARD_Parser p, CARD_PropHandler cardProp);
* Params
  p			= Card parser object
  cardProp	= function pointer for prop event handler

void CARD_SetDataHandler(CARD_Parser p, CARD_DataHandler cardData);
* Params
  p			= Card parser object
  cardProp	= function pointer for data event handler

