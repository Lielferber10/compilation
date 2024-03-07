#ifndef NODE
#define NODE

#include "hw3_output.hpp"
#include <vector>
#include <string>

using namespace std;
using namespace output;

extern int yylineno;

typedef enum {
    INT,BYTE,BOOL,VOID,STRING,FUNCTION,NONE
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
        type=NONE; 
    }
    Node(int line){
        lineno=line;
        text="";
        type=NONE; 
    };

    Node(int line, string txt){
        lineno=line;
        text=txt;
        type=NONE; 
    };

    bool is_num(){
        if(type==INT || type==BYTE)
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
        type=INT;
    };
};

class Byte : public Node {
    public:
    Byte(int line, string txt) : Node(line,txt)
    {
        type=BYTE;
    };
};


class Bool : public Node {
    public:
    Bool(int line, string txt) : Node(line,txt)
    {
        type=BOOL;
    };
};

class Void : public Node {
    public:
    Void(int line, string txt) : Node(line,txt)
    {
        type=VOID;
    };
};

class String : public Node {
    public:
    String(int line, string txt) : Node(line,txt)
    {
        type=STRING;
    };
};

class Add :public Node {
    public:
    Add(Node *a,Node *b)
    {
        if ((a->type != INT)&&(a->type != BYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }

        if ((b->type != INT)&&(b->type != BYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }
        if(a->type==INT || b->type == INT) {
            type = INT;
        } else type= BYTE;
        lineno=yylineno;
        text="";
    };

    
};


class Sub :public Node {
    public:
    Sub(Node *a,Node *b)
    {
        if ((a->type != INT)&&(a->type != BYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }

        if ((b->type != INT)&&(b->type != BYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }
        if(a->type==INT || b->type == INT) {
            type = INT;
        } else type= BYTE;
        lineno=yylineno;
        text="";
    }; 
};

class Mul :public Node {
    public:
    Mul(Node *a,Node *b)
    {
        if ((a->type != INT)&&(a->type != BYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }

        if ((b->type != INT)&&(b->type != BYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }
        if(a->type==INT || b->type == INT) {
            type = INT;
        } else type= BYTE;
        lineno=yylineno;
        text="";
    };
};

class Dev :public Node {
    public:
    Dev(Node *a,Node *b)
    {
        if ((a->type != INT)&&(a->type != BYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }

        if ((b->type != INT)&&(b->type != BYTE))
        {
          errorMismatch(yylineno);
          exit(0);  
        }
        if(a->type==INT || b->type == INT) {
            type = INT;
        } else type= BYTE;
        lineno=yylineno;
        text="";
    };
};


class Exp :public Node{
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

    };

    Exp (Node * type,Node *id,Node* exp,int line)
    {
        bool valid =false;
        if(type->type == exp->type)
            valid = true;
        else if (type->type == INT && exp->type == BYTE)
            valid = true;
        
        if (!valid)
        {
            errorMismatch(line);
            exit(0);
        }
        this->type=type->type;
        lineno=line;
        text = id->text;
        
    };
    
    Exp (Types type,Node *id,Node *exp,int line)
    {
        bool valid=false;
        if(type==exp->type) valid=true;
        else if (type == INT && exp->type == BYTE) valid=true;
        
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
