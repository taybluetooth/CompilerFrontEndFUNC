/*
 *This is where you specify the rules for your FUNC lexical analyser. Once you have completed
 * it, you will need to use FLEX to generate a lexical analyser from this file.
 */

%{
#include "tokens.h"
%}

DIGIT [0-9]
IDENT [a-zA-Z][A-Za-z0-9]*

%%
"method"        { return METHOD;}
";"             { return SEMI;}
":="            { return ASSIGN;}
"IF"            { return IF;}
"THEN"          { return THEN;}
"ELSE"          { return ELSE;}
"BEGIN"         { return TBEGIN;}
"END"           { return END;}
"WHILE"         { return WHILE;}
"DO"            { return DO;}
"+"             {return PLUS;}
"-"             { return MINUS;}
"INPUT“         { return INPUT;}
"PRINT"         { return PRINT;}
"VAR"           { return VAR;}
"*"             { return STAR;}
"/"             { return SLASH;}
"("             { return LBRA;}
")"             { return RBRA;}
"<"             { return LT;}
"<="            { return LTE;}
"=="            { return EQ;}
"!="            { return NEQ;}
">"             { return GT;}
">="            { return GTE;}
{DIGIT}+        {return INT;}
{IDENT}         {return ID;}
<<EOF>>         {return EOF;}

%%

int yywrap() { return EOF; }
