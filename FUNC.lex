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
"begin"         { return BEGIN;}
"endmethod"     { return ENDMETHOD;}
"vars"          { return VARS;}
"return"        { return RETURN;}
"read"          { return READ;}
"write"         { return WRITE;}
"if"            { return IF;}
"then"          { return THEN;}
"else"          { return ELSE;}
"endif"         { return ENDIF;}
"while"         { return WHILE;}
"endwhile"      { return ENDWHILE;}
"less"          { return LESS;}
"lessEq"        { return LESSEQ;}
"eq"            { return EQ;}
"nEq"           { return NEQ;}
","             { return COMMA;}
";"             { return SEMI;}
":="            { return ASSIGN;}
"("             { return LBRA;}
")"             { return RBRA;}
{DIGIT}+        { return INT;}
{IDENT}         { return ID;}
<<EOF>>         { return EOF;}
%%

int yywrap() { return EOF; }
