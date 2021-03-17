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

//-------------YOUR CODE BELOW THIS LINE----------------------//

/**
 *  This is where parser execution begins: it's the method for parsing programs.
 */

void methods();
void method();
void args();
void statements();
void statement();
void rw();
void assign();
void ifCond();
voif whileCond();
void cond();
void bop();
void exps();
void expression();

void program()
{
  methods();
}

 void methods()
 {
   method();
   if(symb != SEMI)
    error("methods", "; expected\n");

   if(symb == METHOD)
    methods();
 }

 void method()
 {
   if(symb != METHOD)
    error("method", "method expected\n");
   if(symb != ID)
    error("method", "identifier expected\n");
   if(symb != LBRA)
    error("method", "( expected\n");
   if(symb != RBRA)
    error("method", ") expected\n");

   if(symb == ID)
    yylex();
    args();
   if(symb == VARS)
    yylex();
    args();

   if(symb != BEGIN)
    error("method", "begin expected\n");

    switch(symb)
    {
      case ASSIGN:
      case IF:
      case WHILE:
      case READ:
      case WRITE: yylex();
                  statements();
                  return;
    }

    if(symb == RETURN)
      yylex();
      if(symb != ID)
        error("method", "expected identifier\n");

    if(symb != ENDMETHOD)
      error("method", "endmethod expected\n");

 }

 void args()
 {
   yylex();
   if(symb != ID)
    error("args", "identifier expected\n");

   if(symb == COMMA)
    args();
 }

 void statements()
 {
   statement();
   if(symb != SEMI)
    error("statements", "; expected\n");

   switch(symb)
   {
     case ASSIGN:
     case IF:
     case WHILE:
     case READ:
     case WRITE: yylex();
                 statements();
                 return;
   }
 }

 void statement()
 {
   switch(symb)
   {
     case ASSIGN:
      yylex();
      assign();
      return;
     case IF:
      yylex();
      ifCond();
      return;
     case WHILE:
      yylex();
      whileCond();
      return;
     case READ:
     case WRITE:
                 rw();
                 yylex();
                 return;

     default:
      error("statement", "statement expected\n");
   }
 }

 void rw()
 {
   switch(symb)
   {
     case READ:
      if(symb != ID)
        error("rw", "identifier expected\n");
      yylex();
      return;
     case WRITE:
      yylex();
      expression();
      return;

     default:
      error("rw", "read or write operator expected\n");
   }
 }

 void assign()
 {
   yylex();
   if(symb != ASSIGN)
    error("assign", ":= expected\n");
   yylex();
   expression();
 }

 void ifCond()
 {
   cond();
   if(symb != THEN)
    error("if", "then expected\n");
   yylex();
   statements();
   if(symb == ELSE)
    yylex();
    statements();
   if(symb != ENDIF)
    error("if", "endif expected\n");
 }

 void whileCond()
 {
   cond();
   if(symb != BEGIN)
    error("while", "begin expected\n");
   yylex();
   statements();
   if(symb != ENDWHILE)
    error("while", "endwhile expected\n");
 }

 void cond()
 {
   bop();
   if(symb != LBRA)
    error("cond", "( expected\n");
   yylex();
   exps();
   if(symb != RBRA)
    error("cond", ") expected\n");
 }

 void bop()
 {
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

 void exps()
 {
  expression();
  if(symb == COMMA)
    yylex();
    exps();
 }

 void expression()
 {
   switch(symb)
   {
     case ID:
      yylex();
      if(symb == LBRA)
      {
        yylex();
        exps();
      }
      else
      {
        error("expression", "( expected\n");
      }

      if(symb ==  RBRA)
      {
        yylex();
        return;
      }
      else
      {
        error("expression", ") expected\n");
      }
      return;

     case INT:
      yylex();
      return;

     default:
      error("expression", "expression expected\n");
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

	program(1);
	fclose(yyin);
}
