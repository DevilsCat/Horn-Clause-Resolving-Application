// Scanner.h : Declares Scanner class extracting string from ifstream and interpreting it as semantic token struct
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef SCANNER_H
#define SCANNER_H

#include <istream>
#include <memory>
#include "BaseToken.h"
#include <deque>

class Scanner {
    const size_t kMaxQueueSize = 2;

public:
    explicit Scanner(std::istream& is);

	//
	// operator bool()
	// A public type conversion operator to bool that returns true as long as the input file stream its member variable 
	// references remains valid for reading, and otherwise returns false
	//
	operator bool() const;

    std::shared_ptr<BaseToken> Peek() const;
    std::shared_ptr<BaseToken> Peek(const size_t& idx) const;

    std::shared_ptr<BaseToken> NextToken();

	//
	// is_good()
	// Determines if the file inside this Scanner is good or not
	//
    bool is_good() const;

private:
    // 
    // operator>>
    // An extraction operator (operator>>) that takes a reference to a token object and returns a reference to the Scanner 
    // class object on which the extraction operator was invoked.*/
    //
    Scanner& operator>> (std::shared_ptr<BaseToken>& ptr);

    std::shared_ptr<BaseToken> PopFromTokenQueue_();
    void PushToTokenQueue_(std::shared_ptr<BaseToken> t);

    // A file stream to extract Token from.
    std::istream& is_;

    // token queue for caching certain numbers {kMaxQueueSize} of elements
    std::deque<std::shared_ptr<BaseToken>> token_queue_;
};

#endif