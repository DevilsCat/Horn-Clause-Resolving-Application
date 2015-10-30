// scanner.h : Declares scanner class extracting string from ifstream and interpreting it as semantic token struct
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <memory>
#include "TokenRoot.h"

class scanner {
private:
	// A file stream to extract Token from.
	std::ifstream ifs_;
public:
	scanner() {}

	explicit scanner(std::ifstream& ifs);

	//
	// operator bool()
	// A public type conversion operator to bool that returns true as long as the input file stream its member variable 
	// references remains valid for reading, and otherwise returns false
	//
	operator bool() const;

	// 
	// operator>>
	// An extraction operator (operator>>) that takes a reference to a token object and returns a reference to the scanner 
	// class object on which the extraction operator was invoked.*/
	//
	scanner& operator>> (std::shared_ptr<Token> &ptr);

	//
	// move_ifs()
	// Get(Move) ifstream after initialization
	//
	void move_ifs(std::ifstream&& ifs);

	//
	// is_good()
	// Determines if the file inside this scanner is good or not
	//
	bool is_good(){ return ifs_.is_open(); }
};

#endif