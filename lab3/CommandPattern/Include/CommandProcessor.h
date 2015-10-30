#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H
#include <string>

class CommandProcessor {
public:
    explicit CommandProcessor();

    virtual ~CommandProcessor();

    CommandProcessor(const CommandProcessor&) = delete;
    CommandProcessor& operator= (const CommandProcessor&) = delete;

    void Process(const std::string& filename);

    void Assert(const std::string& hornclauses);

    void Up(const unsigned& nlines = 0);

    void Down(const unsigned& nlines = 0);

    void Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause);

    void Randomize(const std::string& variable, const unsigned& max = 0);

    void Set(const std::string& variable, const int& value);

    void Print();
};

#endif
