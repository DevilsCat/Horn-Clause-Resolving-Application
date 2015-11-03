#pragma once
#include <system_error>

class ProgramException : public std::runtime_error {
public:
    enum ExceptionCode {
        kInvalidNumber = -1,
        kInvalidVariable = -2,
        kNumberArgsMisMatch = -3,
        kInvalidHornclauseIndex = -4,
        kFatalError = -100
    };

    explicit ProgramException(const std::string& _Message, const ExceptionCode& _Code);

    explicit ProgramException(const char* _Message, const ExceptionCode& _Code);

    int code();

private:
    ExceptionCode code_;
};
