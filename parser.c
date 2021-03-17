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
extern int lex(void);
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

lex()
{ printSymb();
  symb = yylex();
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
void whileCond();
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
    lex();
    args();
   if(symb == VARS)
    lex();
    args();

   if(symb != BEGIN)
    error("method", "begin expected\n");

    switch(symb)
    {
      case ASSIGN:
      case IF:
      case WHILE:
      case READ:
      case WRITE: lex();
                  statements();
                  return;
    }

    if(symb == RETURN)
      lex();
      if(symb != ID)
        error("method", "expected identifier\n");

    if(symb != ENDMETHOD)
      error("method", "endmethod expected\n");

 }

 void args()
 {
   lex();
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
     case WRITE: lex();
                 statements();
                 return;
   }
 }

 void statement()
 {
   switch(symb)
   {
     case ASSIGN:
      lex();
      assign();
      return;
     case IF:
      lex();
      ifCond();
      return;
     case WHILE:
      lex();
      whileCond();
      return;
     case READ:
     case WRITE:
                 rw();
                 lex();
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
      lex();
      return;
     case WRITE:
      lex();
      expression();
      return;

     default:
      error("rw", "read or write operator expected\n");
   }
 }

 void assign()
 {
   lex();
   if(symb != ASSIGN)
    error("assign", ":= expected\n");
   lex();
   expression();
 }

 void ifCond()
 {
   cond();
   if(symb != THEN)
    error("if", "then expected\n");
   lex();
   statements();
   if(symb == ELSE)
    lex();
    statements();
   if(symb != ENDIF)
    error("if", "endif expected\n");
 }

 void whileCond()
 {
   cond();
   if(symb != BEGIN)
    error("while", "begin expected\n");
   lex();
   statements();
   if(symb != ENDWHILE)
    error("while", "endwhile expected\n");
 }

 void cond()
 {
   bop();
   if(symb != LBRA)
    error("cond", "( expected\n");
   lex();
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
     case NEQ: lex();
               return;

     default:
      error("bop", "boolean operator expected\n");
   }
 }

 void exps()
 {
  expression();
  if(symb == COMMA)
    lex();
    exps();
 }

 void expression()
 {
   switch(symb)
   {
     case ID:
      lex();
      if(symb == LBRA)
      {
        lex();
        exps();
      }
      else
      {
        error("expression", "( expected\n");
      }

      if(symb ==  RBRA)
      {
        lex();
        return;
      }
      else
      {
        error("expression", ") expected\n");
      }
      return;

     case INT:
      lex();
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
