%{
#include "output.hpp"
#include "Node.hpp"
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

int                             {yylval = new Int(yylineno,yytext); return INT;}
byte                            {yylval = new Byte(yylineno,yytext); return BYTE;}
b                               {yylval = new Byte(yylineno,yytext); return B;}
bool                            {yylval = new Bool(yylineno,yytext); return BOOL;}
and                             {yylval = new Node(yylineno,yytext); return AND;}
or                              {yylval = new Node(yylineno,yytext); return OR;}
not                             {yylval = new Node(yylineno,yytext); return NOT;}
true                            {yylval = new Bool(yylineno,yytext); return TRUE;}
false                           {yylval = new Bool(yylineno,yytext); return FALSE;}
return                          {yylval = new Node(yylineno,yytext); return RETURN;}
if                              {yylval = new Node(yylineno,yytext); return IF;}
else                            {yylval = new Node(yylineno,yytext); return ELSE;}
while                           {yylval = new Node(yylineno,yytext); return WHILE;}
break                           {yylval = new Node(yylineno,yytext); return BREAK;}
continue                        {yylval = new Node(yylineno,yytext); return CONTINUE;}
{identifier}                    {yylval = new Node(yylineno,yytext); return ID;}
;                               {yylval = new Node(yylineno,yytext); return SC;}
\(                              {yylval = new Node(yylineno,yytext); return LPAREN;}
\)                              {yylval = new Node(yylineno,yytext); return RPAREN;}
\{                              {yylval = new Node(yylineno,yytext); return LBRACE;}
\}                              {yylval = new Node(yylineno,yytext); return RBRACE;}
=                               {yylval = new Node(yylineno,yytext); return ASSIGN;}
{highPriorityRelation}          {yylval = new Node(yylineno,yytext); return HRELOP;}
{lowPriorityRelation}           {yylval = new Node(yylineno,yytext); return LRELOP;}
\+                              {yylval = new Node(yylineno,yytext); return PLUS;}
\-                              {yylval = new Node(yylineno,yytext); return MINUS;}
\*                              {yylval = new Node(yylineno,yytext); return MULT;}
\/                              {yylval = new Node(yylineno,yytext); return DEV;}
{number}                        {yylval = new Int(yylineno,yytext); return NUM;}
{string}                        {yylval = new String(yylineno,yytext); return STRING;}
([\r\n\x20\t]|{comment})        {}
.                               {output::errorLex(yylineno); exit(0);}

%%