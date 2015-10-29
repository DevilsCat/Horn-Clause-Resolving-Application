﻿#include "stdafx.h"
#include "CommandProcessor.h"
#include <iostream>

CommandProcessor::CommandProcessor() {}

CommandProcessor::~CommandProcessor() {}

void CommandProcessor::Process(const std::string& filename) {
    std::cout << "Process Command with " << filename << std::endl;
}

void CommandProcessor::Assert(const std::string& hornclauses) {
    std::cout << "Assert Command with " << hornclauses << std::endl;
}

void CommandProcessor::Up(const unsigned& nlines) {
    std::cout << "Up Command with " << nlines << std::endl;
}

void CommandProcessor::Down(const unsigned& nlines) {
    std::cout << "Down Command with " << nlines << std::endl;
}

void CommandProcessor::Resolve(const unsigned& num_first_hornclause, const unsigned& num_second_hornclause) {
    std::cout << "Resolve Command with " << "{" << num_first_hornclause << "," << num_second_hornclause << "}" << std::endl;
}

void CommandProcessor::Randomize(const std::string& variable, const unsigned& max) {
    std::cout << "Randomize Command with " << variable << " with maximum " << max << std::endl;
}

void CommandProcessor::Set(const std::string& variable, const int& value) {
    std::cout << "Set Command with " << variable << " with value " << value << std::endl;
}

void CommandProcessor::Print() {
    std::cout << "Print Command" << std::endl;
}