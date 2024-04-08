#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Var
{
    int reg1;
    int reg2;
    int reg3;
    
    public:
        Var();
        std::string freshVar();
        std::string freshStringVar();
        std::string freshLabel();
};

void init_llvm();

#endif