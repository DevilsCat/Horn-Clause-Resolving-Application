// DeductiveDatabase.h -- This file declares a DeductiveDatabase and HornclauseDatabaseEntry classes
// used to store, retrieve display horn clauses.
// Created by Anqi Zhang, Yu Xiao, copyright preserved.
//
#ifndef DEDUCTIVE_DATABASE_H
#define DEDUCTIVE_DATABASE_H
#include "Visitor.h"
#include <vector>
#include "PredicateEntry.h"
#include "SymbolTable.h"

struct HornclauseDatabaseEntry;

// Stores stores, retrieves and displays the horn clauses. It can parse a
// horn clause AST tree and insert horn clauses into itself.
//
// Since every entry inside database should be formed by predicates in
// exist symbol table, make sure update {SymbolTable} object first.
//
// Usage Example:
//      // ... Updates a {SymbolTable} object symbol_table.
//      DeductiveDatabase database(symbol_table);
//      // ... Obtains a tree from "process" or "assert" commands.
//      database.FillHornclauseFromTree(root);
//      database.Display();
class DeductiveDatabase : public Visitor {
public:
    static std::shared_ptr<DeductiveDatabase> instance();

    static void init(SymbolTable& symbol_table);

    DeductiveDatabase(const DeductiveDatabase&) = delete;
    DeductiveDatabase& operator= (const DeductiveDatabase&) = delete;

    void FillHornclauseFromTree(std::shared_ptr<RootNode>);

    void AddHornclauseEntry(HornclauseDatabaseEntry&);

    bool RetrieveHornclauseEntry(HornclauseDatabaseEntry& result, const unsigned& idx);

    int Display(const unsigned& offset, const unsigned& num_entries = 0) const;

    size_t size() const;

    virtual void OnPreVisit(HornclauseNode*) override;
    virtual void OnPostVisit(HornclauseNode*) override;
    virtual void OnPreVisit(HeadNode*) override;
    virtual void OnPostVisit(HeadNode*) override;
    virtual void OnPreVisit(BodyNode*) override;
    virtual void OnPostVisit(BodyNode*) override;
    virtual void OnVisit(PredicateNode*) override;
    
private:
    // Takes a reference to a symbol
    DeductiveDatabase(SymbolTable& symbol_table);

    bool IsHornclauseEntryDup(const HornclauseDatabaseEntry&) const;

    SymbolTable& symbol_table_;

    std::vector<HornclauseDatabaseEntry> hornclause_entries_;

    HornclauseDatabaseEntry* hornclause_buffer_ptr_;

    std::vector<std::shared_ptr<PredicateEntry>> predicate_buffer_;

    static std::shared_ptr<DeductiveDatabase> deductive_database_;
};

struct HornclauseDatabaseEntry {
    typedef std::vector<std::shared_ptr<PredicateEntry>>::iterator PredicateEntryIterator;

    std::vector<std::shared_ptr<PredicateEntry>> head;
    std::vector<std::shared_ptr<PredicateEntry>> body;

    void operator= (const HornclauseDatabaseEntry&);

    bool IsFact() const;

    PredicateEntryIterator EraseBodyAt(const unsigned& idx);

    void InsertBodyAt(const unsigned& idx, PredicateEntryIterator first, PredicateEntryIterator last);

    bool EqualsTo(const HornclauseDatabaseEntry&) const;

    friend std::ostream& operator<<(std::ostream& os, const HornclauseDatabaseEntry& entry);
};

#endif

