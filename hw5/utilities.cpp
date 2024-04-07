#include "utilities.hpp"
#include "bp.hpp"
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


void init_llvm(){
    CodeBuffer &codeBuffer = CodeBuffer.instance();
    codeBuffer.emit("define i32 @main(){");
    codeBuffer.emit("%stack = alloca [50 x i32]");
    codeBuffer.emit("declare i32 @scanf(i8*, ...)");
    codeBuffer.emit("declare i32 @printf(i8*, ...)");
    codeBuffer.emit("declare void @exit(i32)");
    codeBuffer.emit("@.DIV_BY_ZERO_ERROR = internal constant [23 x i8] c\"Error division by zero\\00\"");
    codeBuffer.emit("@.int_specifier_scan = constant [3 x i8] c"%d\00"");
    codeBuffer.emit("@.int_specifier = constant [4 x i8] c"%d\0A\00"");
    codeBuffer.emit("@.str_specifier = constant [4 x i8] c"%s\0A\00"");

    codeBuffer.emit("define i32 @readi(i32) {");
    codeBuffer.emit("%ret_val = alloca i32");
    codeBuffer.emit("%spec_ptr = getelementptr [3 x i8], [3 x i8]* @.int_specifier_scan, i32 0, i32 0");
    codeBuffer.emit("call i32 (i8*, ...) @scanf(i8* %spec_ptr, i32* %ret_val)");
    codeBuffer.emit("%val = load i32, i32* %ret_val");
    codeBuffer.emit("ret i32 %val");
    codeBuffer.emit("}");

    codeBuffer.emit("define void @printi(i32) {");
    codeBuffer.emit("%spec_ptr = getelementptr [4 x i8], [4 x i8]* @.int_specifier, i32 0, i32 0");
    codeBuffer.emit("call i32 (i8*, ...) @printf(i8* %spec_ptr, i32 %0)");
    codeBuffer.emit("ret void");
    codeBuffer.emit("}");

    codeBuffer.emit("define void @print(i8*) {");
    codeBuffer.emit("%spec_ptr = getelementptr [4 x i8], [4 x i8]* @.str_specifier, i32 0, i32 0");
    codeBuffer.emit("call i32 (i8*, ...) @printf(i8* %spec_ptr, i8* %0)");
    codeBuffer.emit("ret void");
    codeBuffer.emit("}");
}