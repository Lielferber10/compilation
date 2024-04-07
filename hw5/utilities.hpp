#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Var
{
    int reg;
    
    public:
        Var();
        //Var &getInstance();
        std::string freshVar();
};

void init_llvm();

#endif