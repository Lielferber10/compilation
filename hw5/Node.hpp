#ifndef NODE
#define NODE

#include "hw3_output.hpp"
#include "utilities.hpp"
#include <vector>
#include <string>
#include <iostream>


using namespace std;
using namespace output;

extern int yylineno;

typedef enum {
    TINT,TBYTE,TBOOL,TVOID,TSTRING,TFUNCTION,TNONE
}   Types;

class Node {
    public:
    int lineno;
    string text;
    string var;
    Types type;
    
    Node()
    {
        lineno = -1;
        text = "";
        var= "";
        type=TNONE; 
    }
    Node(int line){
        lineno=line;
        text="";
        var= "";
        type=TNONE; 
    };

    Node(int line, string txt){
        lineno=line;
        text=txt;
        var= "";
        type=TNONE; 
    };

    Node(int line, string txt, Types type){
        lineno=line;
        text=txt;
        var= "";
        this->type=type; 
    };

    bool is_num(){
        if(type==TINT || type==TBYTE)
            return true;
        return false;
    }

    void printNode()
    {
        std::cout << "line: " << lineno << "  text: " << text << "  type: " << type << endl;
    }
};

#define YYSTYPE Node*

class Int : public Node {
    public:
    Int(int line, string txt) : Node(line,txt)
    {
        type=TINT;
    };
};

class Byte : public Node {
    public:
    Byte(int line, string txt) : Node(line,txt)
    {
        type=TBYTE;
    };
};


class Bool : public Node {
    public:
    Bool(int line, string txt) : Node(line,txt)
    {
        type=TBOOL;
    };
};

class Void : public Node {
    public:
    Void(int line, string txt) : Node(line,txt)
    {
        type=TVOID;
    };
};

class String : public Node {
    public:
    String(int line, string txt) : Node(line,txt)
    {
        type=TSTRING;
    };
};

class Add :public Node {
    public:
    Add(Node *a, Node *b)
    {
        if ((a->type != TINT)&&(a->type != TBYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }

        if ((b->type != TINT)&&(b->type != TBYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }
        if(a->type==TINT || b->type == TINT) {
            type = TINT;
        } else type= TBYTE;
        lineno=yylineno;
        text="";
        var="";
    };

    
};


class Sub :public Node {
    public:
    Sub(Node *a,Node *b)
    {
        if ((a->type != TINT)&&(a->type != TBYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }

        if ((b->type != TINT)&&(b->type != TBYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }
        if(a->type==TINT || b->type == TINT) {
            type = TINT;
        } else type= TBYTE;
        lineno=yylineno;
        text="";
        var="";
    }; 
};

class Mul :public Node {
    public:
    Mul(Node *a,Node *b)
    {
        if ((a->type != TINT)&&(a->type != TBYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }

        if ((b->type != TINT)&&(b->type != TBYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }
        if(a->type==TINT || b->type == TINT) {
            type = TINT;
        } else type= TBYTE;
        lineno=yylineno;
        text="";
        var="";
    };
};

class Dev :public Node {
    public:
    Dev(Node *a,Node *b)
    {
        if ((a->type != TINT)&&(a->type != TBYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }

        if ((b->type != TINT)&&(b->type != TBYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }
        if(a->type==TINT || b->type == TINT) {
            type = TINT;
        } else type= TBYTE;
        lineno=yylineno;
        text="";
        var="";
    };
};


class Exp : public Node{
    public:
    Exp(Node *new_type,Node *exp,int line) //explicit cast
    {
        if(!exp->is_num()||!new_type->is_num())
        {
            errorMismatch(line);
            exit(0);
        }
        type=new_type->type;
        lineno=line;
        text=std::move(exp->text);
        var="";

    };

    Exp (Node* type, Node* id, Node* exp, int line)
    {
        bool valid = false;
        if(type->type == exp->type) valid = true;
        else if (type->type == TINT && exp->type == TBYTE) valid = true;

        if (!valid)
        {
            errorMismatch(line);
            exit(0);
        }
        this->type=type->type;
        lineno=line;
        text = id->text;
        var="";
    };
    
    Exp (Types type, Node* id, Node* exp, int line)
    {
        bool valid=false;
        if(type==exp->type) valid=true;
        else if (type == TINT && exp->type == TBYTE) valid=true;
        
        if (!valid)
        {
            errorMismatch(line);
            exit(0);
        }
        this->type=type;
        lineno=line;
        text = id->text;
        var="";
    }
    
};























#endif
