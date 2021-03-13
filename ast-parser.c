/**
 * Solution to Q3: Implement the AST parser here. Note that this
 * is essentially an extension of the solutions to Q2, so you 
 * may wish to copy and paste your solutions and extend that.
 * 
 * Add helper functions/code as you wish.
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"
#include "tree.h"

//////////////////////////////////////////////////

// global variables

int symb;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

//////////////////////////////////////////////////

// HELPER FUNCTIONS
//----------------------------------------------//


/**
 * Similar to showSimp from the lecture notes. 
 */
char *getSymb(int s)
{  switch(s)
   {  
      case  ID: return "ID";
      case  INT: return "INT";
      /**
	   * add cases for more FUNC tokens here
	   */
      case EOF: return "EOF";
      default: 
         printf("bad symbol: %d",s);
         return NULL;
   }
}

void error(char * rule, char * message)
{  printf("%s: found %s\n", rule, getSymb(symb));
   printf("%s: %s\n", rule, message);
   exit(0);
}




//-------------YOUR CODE BELOW THIS LINE----------------------//

/**
 *  This is where parser execution begins: it's the method for parsing programs.
 *  It corresponds to the top level, start symbol of FUNC grammars.
 */ 
struct node *program()
{

	/* 
	 * YOUR CODE HERE
	 */
   return NULL;
}

/**
 * 
 * YOUR CODE HERE
 * 
 * Add methods corresponding to the non-terminals in the FUNC grammar, and other code below here.
 * 
 */




/**
 * Execution starts here
 */
int main(int argc, char **argv)
{
	// open the file to be parsed, if possible
	if ((yyin = fopen(argv[1], "r")) == NULL)
	{
		printf("can't open %s\n", argv[1]);
		exit(0);
	}

	struct node *progtree = program();
	if (progtree == NULL)
	{
		printf("program() returned null. Methods unimplemented?\n");
		return -1;
	}
	printTree(progtree);
	fclose(yyin);
}