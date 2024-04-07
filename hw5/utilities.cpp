#include "utilities.hpp"

using namespace std;

Var::Var()
{
    reg = 0;
}

//Var &Var::getInstance(){
//    Var instance;
//    return instance;
//}

string Var::freshVar(){
    return "%t_" + to_string(reg++);
}