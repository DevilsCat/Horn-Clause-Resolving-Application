// HornclauseDatabase.h -- This file declares a HornclauseDatabase and Entry classes
// used to store, retrieve display horn clauses.
// Created by Anqi Zhang, Yu Xiao, copyright preserved.
//
#ifndef HORNCLAUSE_DATABASE_H
#define HORNCLAUSE_DATABASE_H
#include "Visitor.h"
#include <vector>
#include "PredicateEntry.h"
#include "SymbolTable.h"

// Stores stores, retrieves and displays the horn clauses. It can parse a
// horn clause AST tree and insert horn clauses into itself.
//
// Since every entry inside database should be formed by predicates in
// exist symbol table, make sure initialize and update {SymbolTable} singleton first.
//
// Usage Example:
//      SymbolTable::init();
//      HornclauseDatabase::init(*SymbolTable::instance());
//      // ... Obtains a tree from "process" or "assert" commands.
//      // ... updates a {SymbolTable} singleton.
//      HornclauseDatabase::instance()->FillHornclauseFromTree(root);
//      HornclauseDatabase::instance()->Display();
class HornclauseDatabase : public Visitor {
public:
    // Represents a horn clause entry in {HornclauseDatabase}, encapsulate attribute function
    // such as determining if is fact horn clause, or if two entries are equal.
    struct Entry {
        typedef std::vector<std::shared_ptr<PredicateEntry>>::iterator PredicateEntryIterator;

        // Stores predicates of horn clause head.
        std::vector<std::shared_ptr<PredicateEntry>> head;

        // Stores predicates of horn clause body.
        std::vector<std::shared_ptr<PredicateEntry>> body;

        // Deeply copies from passed in Entry.
        Entry& operator= (const Entry&);

        // Returns true if this horn clause entry is a fact (only contains head).
        bool IsFact() const;

        // Returns true if this horn clause entry euqals to passed in horn clause.
        bool EqualsTo(const Entry&) const;

        // Erases the predicate at given index position in body. Returns iterator pointing to 
        // erased position plus one. 
        PredicateEntryIterator EraseBodyAt(const unsigned& idx);

        // Inserts ranges of {PredicateEntry}s from first to last {PredicateEntryIterator} at
        // given index position.
        void InsertBodyAt(const unsigned& idx, PredicateEntryIterator first, PredicateEntryIterator last);
        
        // Prints this horn clause entry.
        friend std::ostream& operator<<(std::ostream& os, const Entry& entry);
    };

    // Returns the singleton of this class.
    static std::shared_ptr<HornclauseDatabase> instance();

    // Takes reference of the SymbolTable singleton and initializes this singleton. 
    static void init(SymbolTable& symbol_table);

    // Deletes copy constructor and operator.
    HornclauseDatabase(const HornclauseDatabase&) = delete;
    HornclauseDatabase& operator= (const HornclauseDatabase&) = delete;

    // Takes a horn clause tree and adds all horn clause to database.
    void FillHornclauseFromTree(std::shared_ptr<RootNode>);

    // Takes a reference of {Entry} and adds to database.
    void AddHornclauseEntry(Entry&);

    // Retrieves database entry to passed in result given index. Returns true if retrieve
    // success (means index is in bound).
    bool RetrieveHornclauseEntry(Entry& result, const unsigned& idx);

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
    // Allocates a {Entry} to fill in.
    // Should release the allocated resource manually. 
    virtual void OnPreVisit(HornclauseNode*) override;
    // Adds a copy of filled {Entry} to database, and release
    // allocated buffer.
    virtual void OnPostVisit(HornclauseNode*) override;
    // Clears the predicate temporary buffer.
    virtual void OnPreVisit(HeadNode*) override;
    // Copies the predicate temporary buffer to head of {Entry}.  
    virtual void OnPostVisit(HeadNode*) override;
    // Clears the predicate temporary buffer.
    virtual void OnPreVisit(BodyNode*) override;
    // Copies the predicate temporary buffer to body of {Entry}.
    virtual void OnPostVisit(BodyNode*) override;
    // Stores the {PredicateEntry} reference from {SymbolTable} singleton.
    virtual void OnVisit(PredicateNode*) override;
    
private:
    // Takes a reference to a SymbolTable singleton, and initalizes this singleton.
    HornclauseDatabase(SymbolTable& symbol_table);

    // Returns true if given hornclause already exists in this database.
    bool IsHornclauseEntryDup_(const Entry&) const;

    // Stores the reference to {SymbolTable} singleton.
    SymbolTable& symbol_table_;

    // Stores all horn clauses entries in this database.
    std::vector<Entry> hornclause_entries_;

    // Temporarily stores newly allocated horn clause entry to fill in. 
    // Being deleted after stores its copy to database.
    Entry* new_hornclause_;

    // Temporaily stroes newly occurred predicates, being cleared
    // before {Visitor} visiting {HeadNode} and {BodyNode}.
    std::vector<std::shared_ptr<PredicateEntry>> predicate_buffer_;

    // Stores the singleton of this class.
    static std::shared_ptr<HornclauseDatabase> deductive_database_;
};

#endif

