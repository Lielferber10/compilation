%{
#include "output.hpp"
#include <string.h>
#include "parser.tab.hpp"


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
stringWithoutEscapes         ([\t\x20-\x21\x23-\x5B\x5D-\x7E])*



%x STRINGMODE
%x STRINGMODEAFTERNULLTERMINATOR


numericEscape (\\x[2-6]([0-9]|[a-f]|[A-F])|\\x7([0-9]|[a-e]|[A-E])|\\x09|\\x0[dD]|\\x0[aA])
escape ({numericEscape}|(\\[tnr\"\\]))
failedNumericEscape (\\x[^\n\r\"]?[^\n\r\"]?)
failedEscape ((\\.)|{failedNumericEscape})

%%

void                            {return VOID;}
int                             {return INT;}
byte                            {return BYTE;}
b                               {return B;}
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
\"                              {BEGIN(STRINGMODE);return STRING;}

<STRINGMODE>{escape}                    return 36;
<STRINGMODE>{stringWithoutEscapes}      return STRING;
<STRINGMODE>\\0                         {BEGIN(STRINGMODEAFTERNULLTERMINATOR); return 38; }

<STRINGMODE>(\")                        { BEGIN(INITIAL); return 37; }

<STRINGMODEAFTERNULLTERMINATOR>({escape}|\\0|[\t\x20-\x21\x23-\x5B\x5D-\x7E])*            {}

<STRINGMODEAFTERNULLTERMINATOR>\"        {BEGIN(INITIAL); return 39;}

 /* string errors */

<STRINGMODEAFTERNULLTERMINATOR><<EOF>>    { printf("Error unclosed string\n"); return 40; }

<STRINGMODEAFTERNULLTERMINATOR>\\?[\n\r]   { printf("Error unclosed string\n"); return 40; }

<STRINGMODEAFTERNULLTERMINATOR>{failedEscape}                   {
          printf("Error undefined escape sequence %s\n",yytext+1);
          return 40;
        }



<STRINGMODE><<EOF>>    { printf("Error unclosed string\n"); exit(0); }

<STRINGMODE>\\?[\n\r]   { printf("Error unclosed string\n"); exit(0); }

<STRINGMODE>{failedEscape}                   {
          printf("Error undefined escape sequence %s\n",yytext+1);
          exit(0);
        }

<STRINGMODE,STRINGMODEAFTERNULLTERMINATOR>.            {printf("Error %s\n", yytext); exit(0);}

[\r\n\x20\t]                      {}
.                               {printf("Error %s\n", yytext); exit(0);}

%%