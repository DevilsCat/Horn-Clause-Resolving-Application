// scanner.h : Declares scanner class extracting string from ifstream and interpreting it as semantic token struct
// Created by Anqi Zhang (439754), and Yu Xiao (439734) copyright preserved.
//
#include "stdafx.h"
#include "scanner.h"
#include "HornclauseTokens.h"
#include <regex>

#define REG_LABEL       "^[a-zA-Z]*$"
#define REG_UNBOUND     "[[:upper:]]"
#define REG_BOUND       "[[:lower:]]"
#define REG_NUMBER      "^[0-9]*$"
#define REG_LEFTPAREN   "^[(]$"
#define REG_RIGHTPAREN  "^[)]$"

Scanner::Scanner(std::istream& is) : 
    is_(is) 
{
    for (size_t i = 0; i < kMaxQueueSize; ++i) {  // pre-scan the {istream} and obtains two tokens.
        if (*this) {
            std::shared_ptr<BaseToken> token;
            *this >> token;
            PushToTokenQueue_(token);
        }
    }
}

Scanner::operator bool() const{
    return !is_.eof();
}

std::shared_ptr<BaseToken> Scanner::Peek() const {
    return Peek(0);
}

std::shared_ptr<BaseToken> Scanner::Peek(const size_t& idx) const {
    if (idx >= kMaxQueueSize) { return nullptr; }
    return token_queue_.at(idx);
}

std::shared_ptr<BaseToken> Scanner::NextToken() {
    std::shared_ptr<BaseToken> res = PopFromTokenQueue_();
    std::shared_ptr<BaseToken> tmp;
    *this >> tmp;
    PushToTokenQueue_(tmp);
    return res;
}

bool Scanner::is_good() const { return is_.good(); }

Scanner& Scanner::operator>> (std::shared_ptr<BaseToken>& ptr){
    if (*this){  // {istream} still has tokens left.

        std::string token_str;
        is_ >> token_str;

        // setup patterns of regular expression
        std::regex label(REG_LABEL);
        std::regex unbound(REG_UNBOUND);
        std::regex bound(REG_BOUND);
        std::regex number(REG_NUMBER);
        std::regex leftparen(REG_LEFTPAREN);
        std::regex rightparen(REG_RIGHTPAREN);

        // regular expression matches and create Token object
        if (std::regex_match(token_str, unbound)) {
            ptr = std::make_shared<UnBoundToken>(token_str);
        }
        else if (regex_match(token_str, bound)) {
            ptr = std::make_shared<BoundToken>(token_str);
        }
        else if (regex_match(token_str, label)) {
            ptr = std::make_shared<LabelToken>(token_str);
        }
        else if (regex_match(token_str, number)){
            ptr = std::make_shared<NumberToken>(token_str);
        }
        else if (regex_match(token_str, leftparen)){
            ptr = std::make_shared<BaseToken>(BaseToken::LEFTPAREN, token_str);
        }
        else if (regex_match(token_str, rightparen)){
            ptr = std::make_shared<BaseToken>(BaseToken::RIGHTPAREN, token_str);
        }
        else {
            ptr = std::make_shared<BaseToken>(BaseToken::UNKNOWN, token_str);
        }
    }
    return *this;
}

std::shared_ptr<BaseToken> Scanner::PopFromTokenQueue_() {
    std::shared_ptr<BaseToken> res = token_queue_.front();
    token_queue_.pop_front();
    return res;
}

void Scanner::PushToTokenQueue_(std::shared_ptr<BaseToken> t) {
    token_queue_.push_back(t);
}
