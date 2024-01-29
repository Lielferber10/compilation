#include "tokens.hpp"
#include <iostream>
#include <vector>


char const tokenNames[29][10] = {
	"empty",
	"VOID",
	"INT",
	"BYTE",
	"B",
	"BOOL",
	"AND",
	"OR",
	"NOT",
	"TRUE",
	"FALSE",
	"RETURN",
	"IF",
	"ELSE",
	"WHILE",
	"BREAK",
	"CONTINUE",
	"SC",
	"LPAREN",
	"RPAREN",
	"LBRACE",
	"RBRACE",
	"ASSIGN",
	"RELOP",
	"BINOP",
	"COMMENT",
	"ID",
	"NUM",
	"STRING"};

//functions to deal with '/xFF' chars
int Dehex(char c) {
    if( c >= '0' && c <= '9')
        return c - '0';
    if( c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if( c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    printf("error :(\n"); exit(1);
}
int StringToHex(char str[2])
{
    int hexnum = Dehex(str[0])*16 + Dehex(str[1]);
    return hexnum;
}

void StringMode(int token)
{
	std::vector<std::string> string_vec;
	//std::cout<<yylineno<<" STRING ";
	for( token = yylex(); token != 37;token = yylex()){

		if(token==28){
			//std::cout<<yytext;
			string_vec.push_back(yytext);
		}
		if (token == 36){
			if(yytext[1]=='n'){
				//std::cout<<std::endl;
				string_vec.push_back("\n");
			}
			if(yytext[1]=='r'){
				//std::cout<<"\r";
				string_vec.push_back("\r");
			}
			if(yytext[1]=='t'){
				//std::cout<<"	";
				string_vec.push_back("\t");
			}
			if(yytext[1]=='\\'){
				//std::cout<<"	";
				string_vec.push_back("\\");
			}
			if(yytext[1]=='\"'){
				//std::cout<<"	";
				string_vec.push_back("\"");
			}
			/*if(yytext[1]=='0'){
				//std::cout<<"	";
				string_vec.push_back("\0");
			}*/
			if(yytext[1]=='x'){
				char tmp[2];
				tmp[0]=yytext[2];
				tmp[1]=yytext[3];
						//     std::cout<<"tmp: "<<StringToHex(tmp)<<std::endl;
				//printf("%c",StringToHex(tmp));
				char c=StringToHex(tmp);
				std::string str(1,c);
				string_vec.push_back(str);

			}

					//std::cout<<"l1 "<<yytext[1]<<std::endl;
		}
				

				//if (token == 37) break;
	}
	std::cout<<yylineno<<" STRING ";
	std::vector<std::string>::iterator iter;
	iter=string_vec.begin();
	for(;iter!=string_vec.end();iter++){
		std::cout<<*iter;
	}
	string_vec.clear();
	std::cout<<std::endl;

}

void CommentMode(int token)
{
	std::cout<< yylineno <<" " <<tokenNames[token] << " //"  << std::endl;
}

int main()
{
	int token;
	while (token = yylex())
	{
		if (token== 25){// comment
			CommentMode(token);
			continue;
		}

		if (token== 28) { // begin string mode

			StringMode(token);
			continue;
		}
		std::cout << yylineno <<" " <<tokenNames[token]<< " " <<yytext << std::endl; // default
	}
	return 0;
}

int main2()
{
    int token;
	while (token = yylex())
	{
        std::cout<<yylineno<<" txt: "<<yytext<<" token: "<<token<<std::endl;
       

    }

    return 0;

}