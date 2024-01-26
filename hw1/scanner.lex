%{
#include "tokens.hpp"
#include <string.h>

char* aString = (char*)malloc(1025);
%}

%option yylineno
%option noyywrap


printable       [\x20-\x7E\x0D\x0A\x09]
escapeSequence  \\[abefnrtv\\'\?"0]
byteValue       [0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]
relation        [=!<>]=|[<>]
binOp           [\+\-\*\/]
comment         \/\/([^\r\n\x0D\x0A])*
identifier      [a-zA-Z][a-zA-Z0-9]*
number          0|[1-9][0-9]*
byteNumber      0|1[0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]
byteSuccesors   [\x20\a\b\e\f\n\r\t\v]*
stringWithoutNull          (([\x20-\x21\x23-\x5B\x5D-\x7E])*(\\\\|\\\"|\\n|\\r|\\t|(\\x[0-9]|\\x[0-9A-Fa-f][0-9A-Fa-f]))*)*
stringWithNull          (([\x20-\x21\x23-\x5B\x5D-\x7E])*(\\\\|\\\"|\\n|\\r|\\t|\\0|(\\x[0-9]|\\x[0-9A-Fa-f][0-9A-Fa-f]))*)*

%x INSTRING
%x STRINGEND
%x BYTENUMBER
%x INSTRINGAFTERNULLTERMINATOR

%%

void                            {return VOID;}
int                             {return INT;}
byte                            {return BYTE;}
bool                            {return BOOL;}
and                             {return AND;}
or                              {return OR;}
not                             {return NOT;}
true                            {return TRUE;}
false                           {return FALSE;}
return                          {return RETURN;}
if                              {return IF;}
else                            {return ELSE;}
while                           {return WHILE;}
break                           {return BREAK;}
continue                        {return CONTINUE;}
{identifier}                    {return ID;}
{byteNumber}                    {BEGIN(BYTENUMBER); return NUM;}
<BYTENUMBER>b                   {BEGIN(INITIAL); return B;}
<BYTENUMBER>{byteSuccesors}     {BEGIN(INITIAL); return 0;/*do nothing*/}
<BYTENUMBER>{number}            {BEGIN(INITIAL); return NUM;} /*we reach here iff the last lexeme is 0*/
<BYTENUMBER>.                   {BEGIN(INITIAL); return -3;}
;                               {return SC;}
\(                              {return LPAREN;}
\)                              {return RPAREN;}
\{                              {return LBRACE;}
\}                              {return RBRACE;}
=                               {return ASSIGN;}
{relation}                      {return RELOP;}
{binOp}                         {return BINOP;}
{comment}                       {return COMMENT;}
{number}                        {return NUM;}
\"                              BEGIN(INSTRING);

<INSTRING>{stringWithoutNull}                       {BEGIN(INSTRINGAFTERNULLTERMINATOR); strcpy(aString, yytext);}
<INSTRING>.|[\r\n]                                  {BEGIN(INITIAL); return -2;}
<INSTRINGAFTERNULLTERMINATOR>{stringWithNull}       BEGIN(STRINGEND);
<INSTRINGAFTERNULLTERMINATOR>\"                     {BEGIN(INITIAL); return STRING;}
<INSTRINGAFTERNULLTERMINATOR>.|[\r\n]               {BEGIN(INITIAL); return -2;}
<STRINGEND>\"                                       {BEGIN(INITIAL); return STRING;}
<STRINGEND>.|[\r\n]                                 {BEGIN(INITIAL); return -2;}
[\r\n\x20]                      {return 0;}
.                               {return -1;}

%%