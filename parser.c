/**
 * Solutions to Q2: Implement your Recursive Decent Parser here.
 * Note here you do not need to produce an AST as output.
 * 
 * Add helper functions/code as you wish.
 */

#include <stdio.h>
#include <stdlib.h>
#include "tokens.h"

//////////////////////////////////////////////////

// global variables

int symb;
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

//////////////////////////////////////////////////

// 
//----------------HELPER FUNCTIONS------------//
/**
 * Similar to showSymb() from the lecture notes. 
 */
char * getSymb(int s)
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
{  printf("%s: found %s\n",rule,getSymb(symb));
   printf("%s: %s\n",rule,message);
   exit(0);
}





//-------------YOUR CODE BELOW THIS LINE----------------------//

/**
 *  This is where parser execution begins: it's the method for parsing programs.
 */ 
void program()
{
	/* 
	 * YOUR CODE HERE
    * Remove the following line of code when done.
	 */

   printf("Parser unimplemented!");
}

/**
 * 
 * YOUR CODE HERE
 * Add methods corresponding to the Non-terminals in the FUNC grammar below here
 * 
 */



//////////////////////////////////////////////////



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

	program();
	fclose(yyin);
}