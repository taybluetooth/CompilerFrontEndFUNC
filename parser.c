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
{
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
  lex();

  if(symb == METHOD)
    methods();
}

void method()
{
  if(symb != METHOD)
    error("method", "method expected\n");
  lex();
  if(symb != ID)
    error("method", "identifier expected\n");
  lex();
  if(symb != LBRA)
    error("method", "( expected\n");
  lex();

  if(symb == ID) {
    args();
  }

  if(symb != RBRA)
    error("method", ") expected\n");
  lex();

  if(symb == VARS) {
    lex();
    args();
  }

  if(symb != BEGIN)
    error("method", "begin expected\n");
  lex();

  switch(symb)
  {
    case ID:
    case IF:
    case WHILE:
    case READ:
    case WRITE: statements();//
                break;
  }

  if(symb == RETURN) {
    lex();
    if(symb != ID) error("method", "identifier expected\n");
    lex();
    if(symb != SEMI) error("method", "semi expected\n");
    lex();
  }

  if(symb != ENDMETHOD)
    error("method", "endmethod expected\n");
  lex();
}

 void args()
 {
  if(symb != ID)
    error("args", "identifier expected\n");
  lex();

  if(symb == COMMA) {
    lex();
    args();
  }
 }

 void statements()
 {
   statement();
   if(symb != SEMI)
    error("statements", "; expected\n");
   lex();

   switch(symb)
   {
     case ID:
     case IF:
     case WHILE:
     case READ:
     case WRITE:
                 statements();
                 break;
   }
 }

 void statement()
 {
   switch(symb)
   {
     case ID:
      assign();
      break;
     case IF:
      lex();
      ifCond();
      break;
     case WHILE:
      lex();
      whileCond();
      break;
     case READ:
     case WRITE:
                 rw();
                 break;

     default:
      error("statement", "statement expected\n");
   }
 }

 void rw()
 {
   if(symb == READ) {
     lex();
     if(symb != ID) error("rw", "identifier expected\n");
     lex();
   }
   else if(symb == WRITE) {
     lex();
     expression();
   }
   else error("rw", "expected READ or WRITE\n");
 }

 void assign()
 {
   if(symb != ID)
    error("assign", "identifier expected\n");
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
   if(symb == ELSE) {
    lex();
    statements();
   }
   if(symb != ENDIF)
    error("if", "endif expected\n");
   lex();
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
   lex();
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
   lex();
 }

 void bop()
 {
   switch(symb)
   {
     case LESS:
     case LESSEQ:
     case EQ:
     case NEQ: lex();
               break;

     default:
      error("bop", "boolean operator expected\n");
   }
 }

 void exps()
 {
  expression();
  if(symb == COMMA) {
    lex();
    exps();
  }
 }

 void expression()
 {
   if(symb == ID) {
     lex();
     if(symb == LBRA) {
       lex();
       exps();
       if(symb != RBRA) error ("exp", ") expected\n");
       lex();
     }
   } else if (symb == INT) {
     lex();
   } else error("exp", "identifier or integer expected\n");
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
  lex();
	program();
	fclose(yyin);
}
