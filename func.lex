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
%%

int yywrap() { return EOF; }
