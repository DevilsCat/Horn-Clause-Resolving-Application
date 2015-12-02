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

Test cases:

1.Test commands:
	(1) Well formed commands
		
		Input: 
			process files\sample.txt
		Output:
			1: ( ( ascending 1 2 ) )
			2: ( ( ascending 1 2 ) ( ( ascending A B ) ) )
			3: ( ( ascending 2 3 ) )
			4: ( ( ascending x Z ) ( ( ascending x Y ) ( ascending Y Z ) ) )
			5: ( ( ascending 4 5 ) ( ( ascending 1 U ) ) )

		Input:
			assert ( ( test 1 2 ) )
		Output:
			1: ( ( ascending 1 2 ) )
			2: ( ( ascending 1 2 ) ( ( ascending A B ) ) )
			3: ( ( ascending 2 3 ) )
			4: ( ( ascending x Z ) ( ( ascending x Y ) ( ascending Y Z ) ) )
			5: ( ( ascending 4 5 ) ( ( ascending 1 U ) ) )
			6: ( ( test 1 2 ) )

		Input:
			randomize a 
			randomize b 100
			print
		Output:
			Bound Label :
			a{28433} b{92}

		Input:
			set x 1
			set a 100
			print
		Output:
			Bound Label :
			a{100} b{92} x{1}
			
	(2) Badly formed commands
		Input: 
			process
			assert
			resolve
			randomize
			randomize X 
			set 
			set x
			set X 1
		Output:
			Process Command Error: Argument Numbers Mismatch.
			Assert Command Error: Not Enough Arguments.
			Resolve Command Error: Unexpeted Numberic Input.
			Randomized Command Error: Not Enough Arguments.
			//
			Set Command Error: Arguments Number Mismatch.
			Set Command Error: Arguments Number Mismatch.
			//

	(3) Existing and missing files
		Input: 
		process sample.txt
		Output:
		Parsing File Failed

2. Test well/badly formed horn clauses
	Input:
		( ( same a a ) )                                
		( ( same 1 b ) )
		( ( same c 2 ) )                                
		( ( sametoo 1 2 ) )
		( ( sametoo 2 2 ) )                                
		( ( sametoo q q ) )                                
		( predP x y ) ( ( predP x z ) ( predP z y ) ) )      
		( ( lesser x y ) ( ( lesser x z ) ( lesser z y ) ) )  
		( ( predQ x y ) ( ( predQ x z ) ( predQ z y ) )      
		x                                              
		( ( lesser z 3 ) )      
		GIBBERISH! qwer5ty8(*&#@RY@#R* 
		( ( unifyme one two ) ( ( unifyme 1 2 ) ) )                  
		(    ( foo a b c ) ( ( foo1a b ) ) )
		( ( notsame a 1 ) )                                
		( ( notsame 2 b ) )
		( ( notsame c 3 ) )   		
	Output:
			=============================Horn Clause Database===================
			1: ( ( same a a ) )
			2: ( ( same 1 b ) )
			3: ( ( same c 2 ) )
			4: ( ( sametoo 1 2 ) )
			5: ( ( sametoo 2 2 ) )
			6: ( ( sametoo q q ) )
			7: ( ( lesser x y ) ( ( lesser x z ) ( lesser z y ) ) )
			8: ( ( lesser z 3 ) )
			9: ( ( unifyme 1 2 ) )
			10: ( ( notsame a 1 ) )
			11: ( ( notsame 2 b ) )
			12: ( ( notsame c 3 ) )
			General Error=======================================================
			Unexpected token [predP]
			Unexpected token [predP]
			Unexpected token [x]
			Unexpected token [y]
			Unexpected token [)]
			Unexpected token [predP]
			Unexpected token [predP]
			Unexpected token [z]
			Unexpected token [y]
			Unexpected token [)]
			Unexpected token [)]
			Unexpected token [)]
			Unexpected token [x]
			Unexpected token [x]
			Unexpected token [GIBBERISH!]
			Unexpected token [qwer5ty8(*&#@RY@#R*]
			Unexpected token [one]
			Unexpected token [one]
			Unexpected token [two]
			Unexpected token [)]
			Unexpected token [)]
			Unexpected token [foo1a]
			Unexpected token [foo1a]
			Unexpected token [b]
			Unexpected token [)]
			Unexpected token [)]
			Unexpected token [)]

3.Test Unification: 
    (1) A numeric constant (indicated by a NUMBER token) can be substituted 
	for any bound variable(indicated by a BOUND token) whose value is the same 
	as the constant's value;

        Input: 
        ( ( test 1 3 ) ( ( test x z ) ) )
        ( ( test x Y ) ( ( test x z ) ( test x y ) ) ) 
        set x 1
		set y 2
        set z 3

        Output: 
        ( ( test 1 Y ) ( ( test 1 3 ) ( test 1 y ) ) )
		Unification failed: head cannot be unified with body.

    (2) A numeric constant (indicated by a NUMBER token) can be substituted for 
	any unbound variable(indicated by an UNBOUND token) that either is not 
	subject to any previous substitutions during that resolution attempt, or for 
	which the cumulative substitutions so far produce the same value as the 
	constant's value;

        Input:
        ( ( test 1 3 1 ) ( ( test X z ) ) )
        ( ( test x Y ) ( ( test X Y X ) ( test X Y Y ) ) ) 

        Output:
        ( ( test x 3 ) ( ( test 1 z ) ( test 1 3 3 ) ) )
		Unification failed: head cannot be unified with body.

    (3) A bound variable may be substituted for any unbound variable that is not 
	subject to any previous substitutions (other than renaming to another unbound 
	variable) during that resolution attempt;
		
		Input:
		( ( test x y ) ( ( test X Y ) ) )
		( ( test x y ) ( ( test X Y ) ( test Y X ) (test X X ) ) )

		Output:
		( ( test x y ) ( ( test x y ) ( test y x ) ( test x x ) ) )
		( ( test x y ) ( ( test y x ) ( test y x ) ( test y y ) ) )
		Unification failed: head cannot be unified with body.

	(4) An unbound variable may be substituted for any other unbound variable 
	that is not subject to any substitutions (that is to say, an unbound variable 
	may be renamed to another unbound variable unless the one being renamed already 
	has had a bound variable or a numeric constant substituted for it);

		Input:
		( ( test x y 1 ) ( ( test A B C ) ) )
		( ( test x y ) ( ( test A B C ) ( test A B A ) ( test A A C ) ) )
		
		Output:
		( ( test x y ) ( ( test x y 1 ) ( test x y x ) ( test x x 1 ) ) )
		Unification failed: head cannot be unified with body.
		Unification failed: head cannot be unified with body.

	(5) A (bound or unbound) variable may not be substituted for a numeric constant; 
	and no other (bound or unbound) variable may be substituted for a bound variable.
			
		Input:
		( ( test x Y ) ( ( test X Y ) ) )
		( ( test x y ) ( ( test 1 2 ) ( test a b ) ) )
		
		Output:
		Unification failed: head cannot be unified with body.
		Unification failed: head cannot be unified with body.
	
	(6) Error message
		Input:
			resolve 100 1 
			resolve 1 1
		Output:
			Cannot Retrieve Hornclause Given Index.
			Same number is given twice.

		Input: 
			( ( test 1 2 ) )
			( ( test 1 2 ) )
			( ( test 1 2 ) ( ( test 2 3 ) ) )
			( ( test 1 2 ) ( ( test 2 3 ) ) )
		Output:
			Unificaiton failed: Two horn clauses are identical.
			Unificaiton failed: Two horn clauses are identical.

3. Test extra credit:
	Input:
	    ( ( ( test 1 3 1 ) ( test x y ) ( test x Y ) ) ( ( test X z ) ) )
        ( ( test x Y ) ( ( test X Y X ) ( test X Y Y ) ( test X Y ) ( test Y X ) ( test 1 2 ) ( test a b ) ) ) 
	Output:
		=============================Horn Clause Database==============================
		1: ( ( ( test 1 3 1 ) ( test x y ) ( test x Y ) ) ( ( test X z ) ) )
		2: ( ( test x Y ) ( ( test X Y X ) ( test X Y Y ) ( test X Y ) ( test Y X ) ( test 1 2 ) ( test a b ) ) )
		3: ( ( test x 3 ) ( ( test 1 z ) ( test 1 3 3 ) ( test 1 3 ) ( test 3 1 ) ( test 1 2 ) ( test a b ) ) )
		4: ( ( test x y ) ( ( test x y x ) ( test x y y ) ( test x z ) ( test y x ) ( test 1 2 ) ( test a b ) ) )
		5: ( ( test x x ) ( ( test y x y ) ( test y x x ) ( test y x ) ( test y z ) ( test 1 2 ) ( test a b ) ) )
		6: ( ( test x Y ) ( ( test x Y x ) ( test x Y Y ) ( test x z ) ( test Y x ) ( test 1 2 ) ( test a b ) ) )
		7: ( ( test x x ) ( ( test x x x ) ( test x x x ) ( test x x ) ( test x z ) ( test 1 2 ) ( test a b ) ) )
		General Error==================================================================
		Unification failed: head cannot be unified with body.
		Unification failed: head cannot be unified with body.
		Unification failed: head cannot be unified with body.
		Unification failed: head cannot be unified with body.
		Unification failed: head cannot be unified with body.

/////////////////////////////////////////////////////////////////////////////