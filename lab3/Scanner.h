// Scanner.h : Declares Scanner class extracting string from ifstream and interpreting it as semantic token struct
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef SCANNER_H
#define SCANNER_H

#include <istream>
#include <memory>
#include "BaseToken.h"

class Scanner {
public:
    explicit Scanner(std::istream& is);

	//
	// operator bool()
	// A public type conversion operator to bool that returns true as long as the input file stream its member variable 
	// references remains valid for reading, and otherwise returns false
	//
	operator bool() const;

	// 
	// operator>>
	// An extraction operator (operator>>) that takes a reference to a token object and returns a reference to the Scanner 
	// class object on which the extraction operator was invoked.*/
	//
	Scanner& operator>> (std::shared_ptr<BaseToken>& ptr);

	//
	// is_good()
	// Determines if the file inside this Scanner is good or not
	//
    bool is_good();

private:
    // A file stream to extract Token from.
    std::istream& is_;
};

#endif