# Horn-Clause-Resolving-Application

##Objective
This Win32 console Application intends to broaden the experience with programming language features and design approaches in C++, and with expression parsing, representation, matching, and transformation techniques (using Horn clauses from logic programming), including:
* Parse and store representations of Horn clauses;
* Unify predicates within the context of a copy of a pair of Horn clauses that are to be resolved;
* Perform resolution of the two Horn clauses to produce another Horn clause that is added to the deductive database.

##Installation
Clone or download the zip of the whole visual studio 2013 solution, build and run the console application.

##Command Description
The program receives user input to execute each of the following commands as they are given:
* **process \<filename\>** -- loads and parses a file of Horn clauses;
* **assert \<Horn clause\> \{\<Horn clause\>\}** -- parses the rest of the line following the assert keyword to identify one or more well formed Horn clauses;
* **up \[lines\]** -- scrolls up a full screen if no number is given following the command, or scrolls up the number of lines given if a number was given;
* **resolve \<Hron_clause_number\> \<Horn_clause_number\>** -- resolves the Horn clause whose numbers in the list are given in the command;
* **randomize \<variable\> \[\<max\>\]** -- generates a randomized value for a bound varialbe;
* **set \<variable\> \<value\>** -- sets a bound variable to the given value;
* **print** -- prints out the contents of the symbol table including both predicates and bound variables.

##References
* This application is the [final lab](http://www.cse.wustl.edu/~cdgill/courses/cse425/lab3/) for CSE 425 Programming Systems and Languages from Washington Unversity in St. Louis.
* [Horn clause](https://en.wikipedia.org/wiki/Horn_clause) format used in the application

```
 horclause -> LEFTPAREN head [body] RIGHTPAREN
 head -> predicate
 body -> LEFTPAREN predicate {predicate} RIGHTPAREN
 predicate -> LEFTPAREN name {symbol} RIGHTPAREN
 name -> LABEL
 symbol -> UNBOUND | NUMBER | BOUND 
```

##Screen Shot
![Image](https://github.com/DevilsCat/Horn-Clause-Resolving-Application/blob/master/app/files/lab3-screenshot.png)

##Contributors
[Archzzz](https://github.com/Archzzz) & [DevilsCat](https://github.com/DevilsCat), all rights reserved.
