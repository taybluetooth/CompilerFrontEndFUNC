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
      case  METHOD: return "METHOD";
      case  BEGIN: return "BEGIN";
      case  ENDMETHOD: return "ENDMETHOD";
      case  VARS: return "VARS";
      case  RETURN: return "RETURN";
      case  READ: return "READ";
      case  WRITE: return "WRITE";
      case  IF: return "IF";
      case  THEN: return "THEN";
      case  ELSE: return "ELSE";
      case  ENDIF: return "ENDIF";
      case  WHILE: return "WHILE";
      case  ENDWHILE: return "ENDWHILE";
      case  LESS: return "LESS";
      case  LESSEQ: return "LESSEQ";
      case  EQ: return "EQ";
      case  NEQ: return "NEQ";
      case  COMMA: return "COMMA";
      case  SEMI: return "SEMI";
      case  ASSIGN: return "ASSIGN";
      case  LBRA: return "LBRA";
      case  RBRA: return "RBRA";
      case  EOF: return "EOF";
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

void rule(char * name, int depth)
{ int i;
  for(i = 0; i < depth; i++)
    printf(" ");
    printf("%s\n",name);
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

 void methods()
 {
   printf("Parser unimplemented!");
 }

 void method()
 {
   printf("Parser unimplemented!");
 }

 void args()
 {
   printf("Parser unimplemented!");
 }

 void statements()
 {
   printf("Parser unimplemented!");
 }

 void statement(int depth)
 {
   rule("statement", depth);
   switch(symb)
   {
     case ASSIGN:
      yylex();
      assign(depth+1);
      return;
     case IF:
      yylex();
      ifCond(depth+1);
      return;
     case WHILE:
      yylex();
      whileCond(depth+1);
      return;
     case READ:
     case WRITE: yylex();
                 return;

     default:
      error("statement", "statement expected\n")
   }
 }

 void rw(int depth)
 {
   rule("rw", depth);
   switch(symb)
   {
     case READ:
      if(symb != ID)
        error("rw", "identifier expected\n");
      yylex();
      return;
     case WRITE:
      yylex();
      exp(depth+1);
      return;

     default:
      error("rw", "read or write operator expected\n")
   }
 }

 void assign(int depth)
 {
   rule("assign", depth);
   yylex();
   if(symb != ASSIGN)
    error("assign", ":= expected\n");
   yylex();
   expr(depth+1);
 }

 void ifCond(int depth)
 {
   rule("if", depth);
   cond(depth+1);
   if(symb != THEN)
    error("if", "then expected\n");
   yylex();
   statements(depth+1);
   if(symb == ELSE)
    yylex();
    statements(depth+1);
   if(symb != ENDIF)
    error("if", "endif expected\n");
 }

 void whileCond(int depth)
 {
   rule("while", depth);
   cond(depth+1);
   if(symb != BEGIN)
    error("while", "begin expected\n");
   yylex();
   statements(depth+1);
   if(symb != ENDWHILE)
    error("while", "endwhile expected\n");
 }

 void cond(int depth)
 {
   rule("cond", depth);
   bop(depth+1);
   if(symb != LBRA)
    error("cond", "( expected\n")
   yylex();
   exps(depth+1);
   if(symb != RBRA)
    error("cond", ") expected\n")
 }

 void bop(int depth)
 {
   rule("bop", depth);
   switch(symb)
   {
     case LESS:
     case LESSEQ:
     case EQ:
     case NEQ: yylex();
               return;

     default:
      error("bop", "boolean operator expected\n");
   }
 }

 void exps(int depth)
 {
  rule("exps", depth);
  exp(depth+1);
  if(symb == COMMA)
    yylex();
    exps(depth+1);
 }

 void exp(int depth)
 {
   rule("exp", depth);
   switch(symb)
   {
     case ID:
      yylex();
      if(symb == LBRA)
      {
        yylex();
        exps(depth+1);
      }
      else
      {
        error("exp", "( expected\n");
      }

      if(symb ==  RBRA)
      {
        yylex();
        return;
      }
      else
      {
        error("exp", ") expected\n");
      }
      return;

     case INT:
      yylex();
      return;

     default:
      error("exp", "expression expected\n");
   }
 }



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
