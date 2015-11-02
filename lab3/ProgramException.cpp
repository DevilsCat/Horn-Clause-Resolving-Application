#include "stdafx.h"
#include "ProgramException.h"

ProgramException::ProgramException(const std::string& _Message, const ExceptionCode& _Code): 
    runtime_error(_Message), code_(_Code) 
{}

ProgramException::ProgramException(const char* _Message, const ExceptionCode& _Code): 
    runtime_error(_Message), code_(_Code)
{}

int ProgramException::code() {
    return code_;
}