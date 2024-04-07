#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Var
{
    int reg1;
    int reg2;
    
    public:
        Var();
        std::string freshVar();
        std::string freshStringVar();
};

void init_llvm();

#endif