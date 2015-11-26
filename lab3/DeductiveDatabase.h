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
// exist symbol table, make sure initialize and update {SymbolTable} singleton first.
//
// Usage Example:
//      SymbolTable::init();
//      DeductiveDatabase::init(*SymbolTable::instance());
//      // ... Obtains a tree from "process" or "assert" commands.
//      // ... updates a {SymbolTable} singleton.
//      DeductiveDatabase::instance()->FillHornclauseFromTree(root);
//      DeductiveDatabase::instance()->Display();
class DeductiveDatabase : public Visitor {
public:
    // Returns the singleton of this class.
    static std::shared_ptr<DeductiveDatabase> instance();

    // Takes reference of the SymbolTable singleton and initializes this singleton. 
    static void init(SymbolTable& symbol_table);

    // Deletes copy constructor and operator.
    DeductiveDatabase(const DeductiveDatabase&) = delete;
    DeductiveDatabase& operator= (const DeductiveDatabase&) = delete;

    // Takes a horn clause tree and adds all horn clause to database.
    void FillHornclauseFromTree(std::shared_ptr<RootNode>);

    // Takes a reference of {HornclauseDatabaseEntry} and adds to database.
    void AddHornclauseEntry(HornclauseDatabaseEntry&);

    // Retrieves database entry to passed in result given index. Returns true if retrieve
    // success (means index is in bound).
    bool RetrieveHornclauseEntry(HornclauseDatabaseEntry& result, const unsigned& idx);

    // Print horn clause entries in the database given offset and numbers of entries to
    // print. Prints from offset to the rest entries if the size of database is less than
    // offset plus numbers of entries to print.
    //
    // Returns actual printed numbers of entries.
    int Display(const unsigned& offset, const unsigned& num_entries = 0) const;

    // Returns the numbers of horn clause entries in database.
    size_t size() const;

    // Traverses the horn clause AST tree and stores horn clause.
    //
    // Allocates a {HornclauseDatabaseEntry} to fill in.
    // Should release the allocated resource manually. 
    virtual void OnPreVisit(HornclauseNode*) override;
    // Adds a copy of filled {HornclauseDatabaseEntry} to database, and release
    // allocated buffer.
    virtual void OnPostVisit(HornclauseNode*) override;
    // Clears the predicate temporary buffer.
    virtual void OnPreVisit(HeadNode*) override;
    // Copies the predicate temporary buffer to head of {HornclauseDatabaseEntry}.  
    virtual void OnPostVisit(HeadNode*) override;
    // Clears the predicate temporary buffer.
    virtual void OnPreVisit(BodyNode*) override;
    // Copies the predicate temporary buffer to body of {HornclauseDatabaseEntry}.
    virtual void OnPostVisit(BodyNode*) override;
    // Stores the {PredicateEntry} reference from {SymbolTable} singleton.
    virtual void OnVisit(PredicateNode*) override;
    
private:
    // Takes a reference to a SymbolTable singleton, and initalizes this singleton.
    DeductiveDatabase(SymbolTable& symbol_table);

    // Returns true if given hornclause already exists in this database.
    bool IsHornclauseEntryDup_(const HornclauseDatabaseEntry&) const;

    // Stores the reference to {SymbolTable} singleton.
    SymbolTable& symbol_table_;

    // Stores all horn clauses entries in this database.
    std::vector<HornclauseDatabaseEntry> hornclause_entries_;

    // Temporarily stores newly allocated horn clause entry to fill in. 
    // Being deleted after stores its copy to database.
    HornclauseDatabaseEntry* new_hornclause_;

    // Temporaily stroes newly occurred predicates, being cleared
    // before {Visitor} visiting {HeadNode} and {BodyNode}.
    std::vector<std::shared_ptr<PredicateEntry>> predicate_buffer_;

    // Stores the singleton of this class.
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

