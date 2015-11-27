========================================================================
    CSE 425 Lab 3: Resolving Horn Clauses in C++
    Team Members: Anqi Zhang(zhanganqi@wustl.edu), Yu Xiao(xiao.y@wustl.edu)
========================================================================

This lab is intended to continue to broaden your experience with programming 
language features and design approaches in C++, and with expression parsing, 
representation, matching, and transformation techniques (again using Horn 
clauses from logic programming as a specific example), including:
    (1) Again parsing and storing representations of Horn clauses;
    (2) Again unifying predicates but this time doing so based on bound and 
        unbound variables as well as numeric constants, this time within the 
        context of a copy of a pair of Horn clauses that are to be resolved;
    (3) Performing resolution of the two Horn clause copies to produce 
        another Horn clause that is added to the deductive database (in 
        addition to the previously existing Horn clauses, which should remain 
        in the deductive databased unmodified).

/////////////////////////////////////////////////////////////////////////////
Design Choices:

1. Restricts Argument for Numbers of Database Entries to Display be Positive.
    The program accepts argv[1] to be a positive number ranging from (0, 
    MAX_UNSIGNED). Otherwise a usage print out and program exits.

2. Allows Duplicate Horn Clause Database Entries.
    This means when excecuting i.e. "process files\sample.txt" twice, the
    program will print double entries for each horn clause.

3. Print Parsing & Unification error to General Error Section
    The program will print out these error temporary on the screen, however
    if you execute other commands, these information will disapear. Other more
    trivial errors will display in Hint Section on the console.

4. Widly Usage of Singleton Pattern
    The InputHanlder, OutputHandler, SymbolTable, HornclauseDatabase,
    CommandProcessor applies this pattern to ensure their uniqueness in program.

/////////////////////////////////////////////////////////////////////////////
Project Hiarchy and Standard Files
1. Command Processor Pattern
    (1) CommandProcessor.h, CommandProcessor.cpp
        These files contain CommandProcessor class which passively process
        command that passes to it.
    
    (2) Commands.h, Commands.cpp
        These files contain Command class family, which can execute on
        CommandProcessor.

    (3) InputHandler.h, InputHandler.cpp
        These files contain a InputHandler class, which receives, validates
        and parses user input and make Command class family.

2. Deductive Database
    (1) HornclauseDatabase.h, HornclauseDatabase.cpp
        These files contain a HornclauseDatabase class can parse a horn 
        clause AST tree and insert horn clauses into itself.

3. Symbol Table
    (1) SymbolTable.h, SymbolTable.cpp
        These files contain a Symbol Table class that stores variables, 
        constants and predicates showing up in the input file.

    (2) PredicateEntry.h, PredicateEntry.cpp
        These files contain a PredicateEntry class that stores inside the 
        Symbol Table.

4. Unifier
    (1) Unifier.h, Unifier.cpp
        These files contain a Unifier class to perform unification given
        two database entries.

5. Horn Clause AST Tree
    (1) Visitor Pattern
        1) Visitor.h, Visitor.cpp
           These files contain a Visitor class which delcares interface for 
           traversing horn clause AST tree.
        
        2) PrintVisitor.h, PrintVisitor.cpp
           These files contain a PrintVisitor prints the contents of horn
           clause AST tree.

    (2) HornclauseASTNodes.h, HornclauseASTNodes.cpp
        These files contain ASTNode family classes used to represent a horn
        clause AST tree.

    (3) HornclauseToken.h, HornclauseToken.cpp
        These files contain horn clause token class family.

    (4) Parser.h, Parser.cpp
        These files contain a Parser class performing parsing for one layer 
        formatted output horn clause.

    (5) Scanner.h, Scanner.cpp
        These files contain Scanner class extracting string from ifstream and 
        interpreting it as semantic token struct.

6. Utils
    (1) OutputHandler.h, OutputHandler.cpp
        These files contain a OutputHandler class to handle the console output.

    (2) ProgramException.h, ProgramException.cpp
        These files contain a ProgramException class that costomizes program 
        error with unique Excpetion Code. It's used pretty much the same as 
        c++ exception.

    (3) Utils.h, Utils.cpp
        These files contains utility functions used in this program.

/////////////////////////////////////////////////////////////////////////////


