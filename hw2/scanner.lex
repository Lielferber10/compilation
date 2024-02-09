%{
#include "output.hpp"
#include <string.h>
#include "parser.tab.hpp"


%}

%option yylineno
%option noyywrap


highPriorityRelation        [<>]=|[<>]
lowPriorityRelation         [=!]=
comment                     \/\/[^\r\n]*[\r|\n|\r\n]?
identifier                  [a-zA-Z][a-zA-Z0-9]*
number                      0|[1-9][0-9]*
string                      \"([^\n\r\"\\]|\\[rnt"\\])+\"




%%

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
{highPriorityRelation}          {return HRELOP;}
{lowPriorityRelation}           {return LRELOP;}
\+                              {return PLUS;}
\-                              {return MINUS;}
\*                              {return MULT;}
\/                              {return DEV;}
{comment}                       {return COMMENT;}
{number}                        {return NUM;}
{string}                        {return STRING;}
[\r\n\x20\t]                    {}
.                               {output::errorLex(yylineno); exit(0);}

%%