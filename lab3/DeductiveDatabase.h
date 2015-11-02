#ifndef DEDUCTIVE_DATABASE_H
#define DEDUCTIVE_DATABASE_H
#include "Visitor.h"
#include <vector>
#include "PredicateEntry.h"
#include "SymbolTable.h"

struct HornclauseDatabaseEntry;

class DeductiveDatabase : public Visitor {
public:

    DeductiveDatabase(SymbolTable& symbol_table);

    void FillHornclauseFromTree(std::shared_ptr<RootNode>);

    void AddHornclauseEntry(const HornclauseDatabaseEntry&);

    void Display(std::ostream&, const unsigned& offset, const unsigned& num_entries = 0) const;

    size_t size() const;

    virtual void OnPreVisit(HornclauseNode*) override;
    virtual void OnPostVisit(HornclauseNode*) override;
    virtual void OnPreVisit(HeadNode*) override;
    virtual void OnPostVisit(HeadNode*) override;
    virtual void OnPreVisit(BodyNode*) override;
    virtual void OnPostVisit(BodyNode*) override;
    virtual void OnVisit(PredicateNode*) override;
    
private:
    SymbolTable& symbol_table_;

    std::vector<HornclauseDatabaseEntry> hornclause_entries_;

    HornclauseDatabaseEntry* hornclause_buffer_ptr_;

    std::vector<PredicateEntry*> predicate_buffer_;
};

struct HornclauseDatabaseEntry {
    std::vector<PredicateEntry *> head;
    std::vector<PredicateEntry *> body;

    friend std::ostream& operator<<(std::ostream& os, const HornclauseDatabaseEntry& entry);
};

#endif

