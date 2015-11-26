// Scanner.h : Declares Scanner class extracting string from ifstream and interpreting it as semantic token struct
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#ifndef SCANNER_H
#define SCANNER_H

#include <istream>
#include <memory>
#include <deque>
#include "HornclauseTokens.h"

// Support recognizing tokens from input stream and peeking next to
// tokens.
class Scanner {
    // Declares that this Scanner is LL(2) scanner.
    const size_t kMaxQueueSize = 2;
public:
    // Takes a reference of {istream} which supports operator>>.
    explicit Scanner(std::istream& is);

	// A public type conversion operator to bool that returns true as long as the input file stream its member variable 
	// references remains valid for reading, and otherwise returns false
	operator bool() const;

    // Peeks the next tokens in the {istream}.
    std::shared_ptr<BaseToken> Peek() const;

    // Peeks the next one or two tokens in the {istream}.
    // Returns nullptr if idx greater than {kMaxQueueSize}.
    std::shared_ptr<BaseToken> Peek(const size_t& idx) const;

    // Returns the first tokens in the token queue and points to next token.
    std::shared_ptr<BaseToken> NextToken();

	// Determines if the file inside this Scanner is good or not
    bool is_good() const;

private:
    // An extraction operator (operator>>) that takes a reference to a token object and returns a reference to the Scanner 
    // class object on which the extraction operator was invoked.*/
    Scanner& operator>> (std::shared_ptr<BaseToken>& ptr);

    // Pops a token from quue.
    std::shared_ptr<BaseToken> PopFromTokenQueue_();
    
    // Push a token into queue.
    void PushToTokenQueue_(std::shared_ptr<BaseToken> t);

    // A file stream to extract Token from.
    std::istream& is_;

    // token queue for caching certain numbers {kMaxQueueSize} of elements
    std::deque<std::shared_ptr<BaseToken>> token_queue_;
};

#endif