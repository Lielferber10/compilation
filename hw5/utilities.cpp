#include "utilities.hpp"

using namespace std;

Var::Var()
{
    reg1 = 0;
    reg2 = 0;
}


string Var::freshVar(){
    return "%t_" + to_string(reg1++);
}

string Var::freshStringVar(){
    return "%q" + to_string(reg2++);
};