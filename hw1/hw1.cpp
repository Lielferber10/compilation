#include "tokens.hpp"
#include <iostream>

extern char* aString;

int main()
{
	int token;
	while(token = yylex())
	{
		char* s;
		if(token == 1)
		{
			s = (char*)"VOID";
		}
		else if(token == 2)
		{
			s = (char*)"INT";
		}
		else if(token == 3)
		{
			s = (char*)"BYTE";
		}
		else if(token == 4)
		{
			s = (char*)"B";
		}
		else if(token == 5)
		{
			s = (char*)"BOOL";
		}
		else if(token == 6)
		{
			s = (char*)"AND";
		}
		else if(token == 7)
		{
			s = (char*)"OR";
		}
		else if(token == 8)
		{
			s = (char*)"NOT";
		}
		else if(token == 9)
		{
			s = (char*)"TRUE";
		}
		else if(token == 10)
		{
			s = (char*)"FALSE";
		}
		else if(token == 11)
		{
			s = (char*)"RETURN";
		}
		else if(token == 12)
		{
			s = (char*)"IF";
		}
		else if(token == 13)
		{
			s = (char*)"ELSE";
		}
		else if(token == 14)
		{
			s = (char*)"WHILE";
		}
		else if(token == 15)
		{
			s = (char*)"BREAK";
		}
		else if(token == 16)
		{
			s = (char*)"CONTINUE";
		}
		else if(token == 17)
		{
			s = (char*)"SC";
		}
		else if(token == 18)
		{
			s = (char*)"LPAREN";
		}
		else if(token == 19)
		{
			s = (char*)"RPAREN";
		}
		else if(token == 20)
		{
			s = (char*)"LBRACE";
		}
		else if(token == 21)
		{
			s = (char*)"RBRACE";
		}
		else if(token == 22)
		{
			s = (char*)"ASSIGN";
		}
		else if(token == 23)
		{
			s = (char*)"RELOP";
		}
		else if(token == 24)
		{
			s = (char*)"BINOP";
		}
		else if(token == 25)
		{
			s = (char*)"COMMENT";
		}
		else if(token == 26)
		{
			s = (char*)"ID";
		}
		else if(token == 27)
		{
			s = (char*)"NUM";
		}
		else if(token == 28)
		{
			s = (char*)"STRING";
		}
		else if(token == -1)
		{
			s = (char*)"error";
		}
		else if(token == -2)
		{
			s = (char*)"error (inside string)";
		}
		else if(token == -3)
		{
			s = (char*)"incorrect use of a byte number!";
		}
		
	
		


		
	}	
	free(aString);
	return 0;
}