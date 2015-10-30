// unifier.h -- Implements a unifier class to performs unification on a symbol table.
// Created by Anqi Zhang, Yu Xiao.
//
#include "stdafx.h"
#include <iostream>
#include "Unifier.h"

Unifier::Unifier(SymbolTable& st) :
	st_(st)
{}

void Unifier::unify_all() {
	// if succeed :
	// (1) printing out the original versions of the predicates
	// (2) the list of substitutions (if any) that were needed to unify the predicates
	// (3) (a single copy of) the resulting transformed unified version of the predicate(s) (with all of the substitutions applied)
	st_.start_map_iteration();
	while(st_.map_has_next()) {
		/* get predicates with same name */
		std::vector<PredicateST>& same_name_preds = st_.map_next();
		/* iterate through each predicate */
		for (std::vector<PredicateST>::iterator it = same_name_preds.begin(); it != same_name_preds.end(); ++it) {
			PredicateST &current = *it;
			/* iterate through each predicate behind current */
			for (decltype(it) after_it = it + 1; after_it != same_name_preds.end(); ++after_it) {
				PredicateST &follow = *after_it;
				/* unify two predicate */
				try {
					unify(current, follow);
					/* print result */
					print_result(*it, *after_it);
				}
				catch (std::runtime_error& e) {
					std::cerr << e.what() << " : " << *it << " <--> " << *after_it << std::endl << std::endl;
				}
				subs_v_.clear();
			}
		}
	}
}

void Unifier::unify(const PredicateST& cur, const PredicateST& fol) {
	if (cur.symbols.size() != fol.symbols.size()) {
	    throw std::runtime_error("symbol length mismatched");
	}

	// working copies
	cur_copy_ = std::make_shared<PredicateST>(cur);
	fol_copy_ = std::make_shared<PredicateST>(fol);

	// Point at first Token in two working copies
	std::vector<Token*>::iterator cur_it = cur_copy_->symbols.begin();
	std::vector<Token*>::iterator fol_it = fol_copy_->symbols.begin();

	// Compare each symbol in predicates
	for (; cur_it != cur_copy_->symbols.end(); ++cur_it, ++fol_it) {
		Token** cur_token = &*cur_it;
		Token** fol_token = &*fol_it;
		compare_sub(cur_token, fol_token);
	}
}

void Unifier::compare_sub(Token** cur, Token** fol) {
	if (**cur == **fol) { return; }

	if (**cur == Token::NUMBER && **fol == Token::NUMBER) { // different constants
        throw std::runtime_error(
            "constant mismatched (" +
            std::string(**cur) +
            " <--> " +
            std::string(**fol) +
            ")"
        );
	}

    bool is_succ = false; // check if any substitution succeed.
    Token *src, *dst;

	if (**cur == Token::LABEL && **fol == Token::LABEL) { // different variables
        src = *cur;
        dst = *fol;
	}
	else { // one is constant and one is label
		src = (**cur == Token::NUMBER) ? *cur : *fol;
		dst = (**cur == Token::NUMBER) ? *fol : *cur;
	}

    is_succ |= substitute(cur_copy_->symbols, dst, src); // substitute on current copy
    is_succ |= substitute(fol_copy_->symbols, dst, src); // substitute on following copy

    if (is_succ) {
        subs_v_.push_back(std::make_pair(*src, *dst)); // records this substitution action.
    }
}

void Unifier::substitute(Token** dst, Token** src) {
    *dst = *src;
}

bool Unifier::substitute(std::vector<Token*>& dst_v, Token* dst, Token* src) {
    bool is_substituted = false; // check if is substituted.
    for (size_t i = 0; i < dst_v.size(); ++i) {
		if (*dst_v[i] == *dst) { // token in container matches the dst token
			Token** dst_ptr = &dst_v[i];
			Token** src_ptr = &src;
			substitute(dst_ptr, src_ptr);
            is_substituted = true;
		}
	}
    return is_substituted;
}

void Unifier::print_result(PredicateST const& cur, PredicateST const& fol) {
	std::cout << "original : " << cur << " -- " << fol << std::endl;
	std::cout << "unified  : " << *cur_copy_ << " -- " << *fol_copy_ << std::endl;
	std::cout << "substitution :" << " ";
	for (auto token_token_pair : subs_v_) {
		std::cout << "{" << std::string(token_token_pair.first) << " -> " << std::string(token_token_pair.second) << "}" << " ";
	}
	std::cout << std::endl << std::endl;
}
