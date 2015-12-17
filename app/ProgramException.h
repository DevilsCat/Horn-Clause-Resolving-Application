// ProgramException.h -- This files declares a ProgramException class.
// Created by Yu Xiao, Anqi Zhang, all right reserved.
//
#ifndef PROGRAM_EXCEPTION_H
#define PROGRAM_EXCEPTION_H
#include <system_error>

// Describes the Costomized program error with unique Excpetion Code.
// It's used pretty much the same as c++ exception
// Sample Usage:
//      void foo() {
//          throw ProgramException("Error description", ProgramException::ExcpetionCode);
//      }
//      ...
//      // In other caller scope
//      try {
//          foo();
//      } throw (ProgramException& e) {
//          std::cerr << e.what() << " " << e.code() << std::endl;
//      }
class ProgramException : public std::runtime_error {
public:
    // Declares possible error type with unique negative error code.
    enum ExceptionCode {
        kInvalidNumber = -1,
        kInvalidVariable = -2,
        kNumberArgsMisMatch = -3,
        kInvalidHornclauseIndex = -4,
        kFatalError = -100
    };

    // Conctructs with Message (std::string) and error code.
    explicit ProgramException(const std::string& _Message, const ExceptionCode& _Code);

    // Conctructs with Message (char*) and error code.
    explicit ProgramException(const char* _Message, const ExceptionCode& _Code);

    // Returns unique error code.
    int code() const;

private:
    // Stores the error code.
    ExceptionCode code_;
};

#endif
