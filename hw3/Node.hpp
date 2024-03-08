#ifndef NODE
#define NODE

#include "hw3_output.hpp"
#include <vector>
#include <string>

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
    Types type;
    
    Node()
    {
        lineno = -1;
        text = "";
        type=TNONE; 
    }
    Node(int line){
        lineno=line;
        text="";
        type=TNONE; 
    };

    Node(int line, string txt){
        lineno=line;
        text=txt;
        type=TNONE; 
    };

    bool is_num(){
        if(type==TINT || type==TBYTE)
            return true;
        return false;
    }
    //virtual ~Node();
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
    Add(Node *a,Node *b)
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
        if (new_type->type == TBYTE && exp->type == TINT && std::stoi(exp->text) >= 256)
        {
            errorByteTooLarge(std::stoi(new_type->text),std::to_string(line));
        }
        type=new_type->type;
        lineno=line;
        text=std::move(exp->text);

    };

    Exp (Node* type, Node* id, Node* exp, int line)
    {
        bool valid = false;
        if(type->type == exp->type)
            valid = true;
        else if (type->type == TINT && exp->type == TBYTE)
            valid = true;
        
        if (type->type == TBYTE && exp->type == TINT && std::stoi(exp->text) >= 256)
        {
            errorByteTooLarge(std::stoi(type->text),std::to_string(line));
        }

        if (!valid)
        {
            errorMismatch(line);
            exit(0);
        }
        this->type=type->type;
        lineno=line;
        text = id->text;
        
    };
    
    Exp (Types type, Node* id, Node* exp, int line)
    {
        bool valid=false;
        if(type==exp->type) valid=true;
        else if (type == TINT && exp->type == TBYTE) valid=true;
        
        if (type == TBYTE && exp->type == TINT && std::stoi(exp->text) < 256)
        {

        }
            valid=true;

        if (!valid)
        {
            errorMismatch(line);
            exit(0);
        }
        this->type=type;
        lineno=line;
        text = id->text;
        
        
    }

};























#endif
