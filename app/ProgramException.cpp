// ProgramException.cpp -- This files defines a ProgramException class.
// Created by Yu Xiao, Anqi Zhang, all right reserved.
//
#include "stdafx.h"
#include "ProgramException.h"

ProgramException::ProgramException(const std::string& _Message, const ExceptionCode& _Code): 
    runtime_error(_Message), code_(_Code) 
{}

ProgramException::ProgramException(const char* _Message, const ExceptionCode& _Code): 
    runtime_error(_Message), code_(_Code)
{}

int ProgramException::code() const {
    return code_;
}
