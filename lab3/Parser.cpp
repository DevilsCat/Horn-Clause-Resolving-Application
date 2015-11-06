// parser.cpp : Implments a Parser class performing parsing for one layer formatted output horn clause
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#include "stdafx.h"
#include "parser.h"
#include <string>
#include "Utils.h"

Parser::Parser(std::istream& is):
	is_(is), scanner_(is_), root_(new RootNode())
{}

int Parser::Parse(){
	if (!scanner_.is_good()){ // error check
		return errno;
	}

	scanner_ >> token_ptr_;
	while (scanner_){
		try {
			root_->AddNode(ParseHornclause());
		}
		catch(std::invalid_argument &e){
            output_handler.LogError(e.what());
			//std::cerr << e.what() << std::endl;
		} catch (std::bad_alloc& e) { // make_shared might failed.
            output_handler.LogError(e.what());
			//std::cerr << e.what() << std::endl;
			throw; // re-throw this exception. Main function should handle (possibly force quit).
		}
	}

	return 0;
}

std::shared_ptr<RootNode> Parser::root() {
	return root_;
}

std::shared_ptr<BaseToken> Parser::match(BaseToken::TokenType type){
	if (*token_ptr_ != type) {
		throw std::invalid_argument("Unexpected token [" + token_ptr_->label + "]");
	}
	std::shared_ptr<BaseToken> res = NextToken();
	return res;
}

std::shared_ptr<BaseToken> Parser::NextToken(){
	std::shared_ptr<BaseToken> res = token_ptr_;
	scanner_ >> token_ptr_;
	return res;
}

std::shared_ptr<HornclauseNode> Parser::ParseHornclause(){
	if (*token_ptr_ != TokenType::LEFTPAREN){ // error check at first beging, and make sure a token discard.
		throw std::invalid_argument("Unexpected token [" + NextToken()->label + "]");
	}
    
    HornclauseNode hornclause;

	match(TokenType::LEFTPAREN);
	hornclause.AddNode(ParseHead()); // parse head.
	if (*token_ptr_ == TokenType::LEFTPAREN){
		hornclause.AddNode(ParseBody()); // parse body.
	}
	match(TokenType::RIGHTPAREN);

    return std::make_shared<HornclauseNode>(hornclause);
}
std::shared_ptr<HeadNode> Parser::ParseHead(){
	HeadNode head;
	head.AddNode(ParsePredicate()); // parse predicate
	return std::make_shared<HeadNode>(head);
}

std::shared_ptr<BodyNode> Parser::ParseBody(){
	BodyNode body;
	match(TokenType::LEFTPAREN);
	do{		
		body.AddNode(ParsePredicate());
	} while (*token_ptr_ == TokenType::LEFTPAREN); // may have multiple predicates
	match(TokenType::RIGHTPAREN);
	return std::make_shared<BodyNode>(body);
}

std::shared_ptr<PredicateNode> Parser::ParsePredicate(){
    PredicateNode predicate;
    match(TokenType::LEFTPAREN);
    predicate.AddNode(ParseName());
    if (*token_ptr_ != TokenType::RIGHTPAREN){ // may have no symbol.
        do {
            predicate.AddNode(ParseSymbol());
        } while (*token_ptr_ != TokenType::RIGHTPAREN);
    }
    match(TokenType::RIGHTPAREN);
    return std::make_shared<PredicateNode>(predicate);
}

std::shared_ptr<SymbolNode> Parser::ParseSymbol(){
    SymbolNode symbol(
        match(TokenType(TokenType::BOUND | TokenType::NUMBER | TokenType::UNBOUND)) // Warning: still return Label, but generate Unbound/bound automatically.
    );
	return std::make_shared<SymbolNode>(symbol);
}



std::shared_ptr<NameNode> Parser::ParseName() {
    NameNode name(
        std::dynamic_pointer_cast<LabelToken>(match(TokenType::LABEL))
    );
    return std::make_shared<NameNode>(name);
}