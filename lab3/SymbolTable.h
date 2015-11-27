// SymbolTable.h -- Declares a Symbol Table class that stores variables, constants and predicates showing up
// in the input file.
// Created by Yu Xiao, Anqi Zhang, copyright preserved.
//
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <set>
#include <map>
#include <vector>
#include <memory>
#include "Visitor.h"
#include "HornclauseTokens.h"
#include "PredicateEntry.h"
#include <list>

// Stores bounded/unbounded/constant and predicates of "processed" horn calauses.
// Sample Usage:
//   SymbolTable::init();
//   ...
//   std::shared_ptr<TokenRoot> tree; // Some how you will have a Token tree like this ... 
//   ...
//   SymbolTable::instance()->FillEntriesFromTree(tree);
//   SymbolTable::Print();
//
class SymbolTable : public Visitor {
    typedef std::map<std::string, std::list<struct PredicateEntry>> MapType;
    friend class HornclauseDatabase;
public:
    // Returns singleton of this class.
    static std::shared_ptr<SymbolTable> instance();

    // Initializes singleton of this class.
    static void init();
    
    ~SymbolTable();

    // Semantically, SymbolTable should be unique. Thus does not allow
    // copy constructor and assignment operator.
    void operator= (const SymbolTable&) = delete;
    SymbolTable(const SymbolTable&) = delete;

    // Fills The symbol table with Token tree.
    void FillEntriesFromTree(std::shared_ptr<RootNode> root);
    
    // Traverse the symbol table and print a seprate line for each predicate by printing its name attribute followed
    // by the attributes of the symbols to which it points.
    void Print() const;

    // Returns a point of {PredicateEntry} stores in this symble table given a {PredicateNode}.
    PredicateEntry* FindPredicateEntryByNode(const PredicateNode&);

    // Returns a point of {PredicateEntry} stores in this symble table given a {PredicateEntry}.
    PredicateEntry* FindPredicateEntryByPredicateEntry(const PredicateEntry&);

    // Implement Visitor pattern to traverse horn clause tree and store predicates and unbounded varaible.
    //
    // Allocates a new {PredicateEntry}.
    virtual void OnPreVisit(PredicateNode*) override;

    // Stores unbounded/bounded/constants to identifier container from {SymbolNode}.
    virtual void OnVisit(SymbolNode*) override;

    // Stores idenfiers from this symbol table to {PredicateEntry}.
    virtual void OnPostVisit(SymbolNode*) override;

    // Stores the name to {PredicateEntry}.
    virtual void OnVisit(NameNode*) override;

    // Stores filled Predicate to predicate container in this symbol table.
    virtual void OnPostVisit(PredicateNode*) override;

    // Returns true of if the string is represent a bounded variable in this
    // symbol table.
    bool CheckBound(const std::string&);

    // Updates the bounded variable's value, you should not call this without
    // checking if the bound exists.
    void SetBound(std::string&, int);

    // Adds a new bounded varialbe to this symbol table.
    void AddBound(std::string&, int = 0);

private:
    // Privates it for the sake of Singleton Pattern.
    SymbolTable();

    // Inserts the symbol into the symbol table. Note that it should only
    // be either BaseToken::BOUND, BaseToken::UNBOUND, BaseToken::NUMBER
    // other types will be ignored.
    void InsertIdentifier(const BaseToken&);

    // Inserts PredicateEntry into the symbol table.
    PredicateEntry& InsertPredicate(const PredicateEntry&);

    // Returns pointer to the identity (Constant or Variable) inside local symbol table.
    const BaseToken& FindIdentifierByToken(BaseToken&);

    // Returns true if two predicates are duplicated, which is used to eliminate duplication.
    bool ISPredicateEntryDup(const PredicateEntry &p);

    // A distinct-element container to stores unique bound labels.
    std::set<BoundToken, TokenComparator> bounds_;

    // A distinct-element container to stroes unique unbound labels.
    std::set<UnBoundToken, TokenComparator> unbounds_;

    // A distinct-element container to stores unique constants.
    std::set<NumberToken, TokenComparator> constants_;

    // A chained-map container to store predicates (might have the same key)
    MapType preds_map_;

    // Stores the new allocated empty {PredicateEntry} to fill in.
    std::shared_ptr<PredicateEntry> new_pred_entry_;

    // Stores Predicates in chronical sequence.
    std::vector<const PredicateEntry*> predicates_trace_;

    // Sotres singleton of this class.
    static std::shared_ptr<SymbolTable> symbol_table_;
};

#endif