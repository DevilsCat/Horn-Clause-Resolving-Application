// symbol_table.h -- Declares a Symbol Table class that stores variables, constants and predicates showing up
// in the input file.
// Created by Yu Xiao, Anqi Zhang
//
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <set>
#include <map>
#include <vector>
#include <memory>
#include "Visitor.h"
#include "TokenOperator.h"
#include "NumberToken.h"
#include "BoundToken.h"
#include "UnBoundToken.h"
#include "PredicateEntry.h"
#include <list>

//
// class SymbolTable
// Sample Usage:
//   SymbolTable st; // Create a symbol table
//   ...
//   std::shared_ptr<TokenRoot> tree; // Some how you will have a Token tree like this ... 
//   ...
//   st.fill(tree);
//   st.print();
//
class SymbolTable : Visitor {
    typedef std::map<std::string, std::list<struct PredicateEntry>> MapType;
    friend class DeductiveDatabase;
public:
	//
	// Default constructor and deconstructor.
	//
	SymbolTable();

	~SymbolTable();

	// Semantically, Symbol Table should be unique. Thus does not allow
	// copy constructor and assignment operator.
	void operator= (const SymbolTable&) = delete;
	SymbolTable(const SymbolTable&) = delete;

	//
	// fill()
	// Fills The symbol table with Token tree.
	//
	void FillEntriesFromTree(std::shared_ptr<RootNode> root);
	
	//
	// print() 
	// Traverse the symbol table and print a seprate line for each predicate by printing its name attribute followed
	// by the attributes of the symbols to which it points.
	//
	void PrintSt() const;

    PredicateEntry* FindPredicateEntryByNode(const PredicateNode&);
    PredicateEntry* FindPredicateEntryByPredicateEntry(const PredicateEntry&);

    virtual void OnPreVisit(PredicateNode*) override;
    virtual void OnVisit(SymbolNode*) override;
    virtual void OnPostVisit(SymbolNode*) override;
    virtual void OnVisit(NameNode*) override;
    virtual void OnPostVisit(PredicateNode*) override;

	bool CheckBound(const std::string&);
	void SetBound(std::string&, int);
	void AddBound(std::string&, int = 0);

private:

	//
	// insert_symbol()
	// Inserts the symbol into the symbol table. Note that it should only
	// be either Token::Label or Token::Number, other cases will be ignored.
	//
	void InsertIdentifier(const BaseToken&);
	//
	// insert_predicate()
	// Inserts PredicateST into the symbol table.
	//
	PredicateEntry& InsertPredicate(const PredicateEntry&);

	//
	// find_identity()
	// Returns pointer to the identity (Constant or Variable) inside local symbol table.
	//
	const BaseToken& FindIdentifierByToken(BaseToken&);

	//
	// is_pred_dup()
	// Returns true if two predicates are duplicated, which is used to eliminate duplication.
	//
	bool ISPredicateEntryDup(const PredicateEntry &p);

    // A distinct-element container to stores unique bound labels.
    std::set<BoundToken, TokenComparator> bounds_;

    // A distinct-element container to stroes unique unbound labels.
    std::set<UnBoundToken, TokenComparator> unbounds_;

    // A distinct-element container to stores unique constants.
    std::set<NumberToken, TokenComparator> constants_;

    // A chained-map container to store predicates (might have the same key)
    MapType preds_map_;

    std::shared_ptr<PredicateEntry> entry_buffer_pointer_;

    std::vector<const PredicateEntry*> predicates_trace_;

};

#endif