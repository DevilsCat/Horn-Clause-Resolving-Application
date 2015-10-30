// scanner.h : Declares scanner class extracting string from ifstream and interpreting it as semantic token struct
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#include "stdafx.h"
#include "scanner.h"
#include "Label.h"
#include "Number.h"
#include <regex>

#define REG_LABEL       "^[a-zA-Z]*$"
#define REG_NUMBER      "^[0-9]*$"
#define REG_LEFTPAREN   "^[(]$"
#define REG_RIGHTPAREN  "^[)]$"

scanner::scanner(std::ifstream& ifs) : 
	ifs_(std::move(ifs)) 
{}

scanner::operator bool() const{
	return !ifs_.eof();
}
scanner& scanner::operator>> (std::shared_ptr<Token> &ptr){
	if (*this){

		std::string token_label;
		ifs_ >> token_label;

		// setup patterns of regular expression
		std::regex label(REG_LABEL);
		std::regex number(REG_NUMBER);
		std::regex leftparen(REG_LEFTPAREN);
		std::regex rightparen(REG_RIGHTPAREN);

		// regular expression matches and create Token object
		if (std::regex_match(token_label, label)){
			ptr =std::make_shared<Label>(Label(token_label));
		}
		else if (std::regex_match(token_label, number)){
			ptr = std::make_shared<Number>(Number(token_label));
		}
		else if (std::regex_match(token_label, leftparen)){
			ptr = std::make_shared<Token>(Token(Token::LEFTPAREN, token_label));
		}
		else if (std::regex_match(token_label, rightparen)){
			ptr = std::make_shared<Token>(Token(Token::RIGHTPAREN, token_label));
		}

	}
	return *this;
}

void scanner::move_ifs(std::ifstream&& ifs) {
	ifs_ = std::move(ifs);
}