// parser.cpp : Implments a parser class performing parsing for one layer formatted output horn clause
// Created by Anqi Zhang (439754), and Yu Xiao (439734)
//
#include "stdafx.h"
#include "parser.h"
#include <string>

parser::parser(std::string& filename):
	filename_(filename), ifs_(filename), scanner_(ifs_), root(new TokenRoot())
{}

int parser::parse(){
	if (!scanner_.is_good()){ // error check
		int error_code = errno;
		std::cerr << "File " + filename_ + " open failed." << std::endl;
		return error_code;
	}

	buffer.clear();
	scanner_ >> token_ptr;
	while (scanner_){
		try {
			parse_hornclauses();
			root->addNode(std::make_shared<Hornclause>(buffer));
		}
		catch(std::invalid_argument &e){
			std::cerr << e.what() << std::endl;
		} catch (std::bad_alloc& e) { // make_shared might failed.
			std::cerr << e.what() << std::endl;
			throw; // re-throw this exception. Main function should handle (possibly force quit).
		}
		buffer.clear();
	}

	return 0;
}

std::shared_ptr<TokenRoot> parser::get_token_tree() {
	return root;
}

std::shared_ptr<Token> parser::match(Token::token_t type){
	if (*token_ptr != type) {
		throw std::invalid_argument("Unexpected token [" + token_ptr->label + "]");
	}
	std::shared_ptr<Token> res = next_token();
	return res;
}

std::shared_ptr<Token> parser::next_token(){
	std::shared_ptr<Token> res = token_ptr;
	scanner_ >> token_ptr;
	return res;
}

void parser::parse_hornclauses(){
	if (*token_ptr != Type::LEFTPAREN){ // error check at first beging, and make sure a token discard.
		throw std::invalid_argument("Unexpected token [" + next_token()->label + "]");
	}

	match(Type::LEFTPAREN);
	buffer.addNode(parse_head()); // parse head.
	if (*token_ptr == Type::LEFTPAREN){
		buffer.addNode(parse_body()); // parse body.
	}
	match(Type::RIGHTPAREN);

}
std::shared_ptr<Head> parser::parse_head(){
	Head head;
	head.addNode(parse_predicate()); // parse predicate
	return std::make_shared<Head>(head);
}

std::shared_ptr<Body> parser::parse_body(){
	Body body;
	match(Type::LEFTPAREN);
	do{		
		body.addNode(parse_predicate());
	} while (*token_ptr == Type::LEFTPAREN); // may have multiple predicates
	match(Type::RIGHTPAREN);
	return std::make_shared<Body>(body);
}

std::shared_ptr<Symbol> parser::parse_symbol(){
	Symbol symbol;
	while (*token_ptr != Type::RIGHTPAREN){
		if (*token_ptr == Type::NUMBER){
			symbol.addNode(match(Type::NUMBER));
		}
		else {
			symbol.addNode(match(Type::LABEL));
		}
	}
	return std::make_shared<Symbol>(symbol);
}

std::shared_ptr<Predicate> parser::parse_predicate(){
	Predicate predicate;
	match(Type::LEFTPAREN);
	predicate.addNode(match(Type::LABEL));
	if (*token_ptr != Type::RIGHTPAREN){ // may have no symbol.
		predicate.addNode(parse_symbol());
	}
	match(Type::RIGHTPAREN);
	return std::make_shared<Predicate>(predicate);
}
