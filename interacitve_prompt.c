#include <stdio.h>
#include <stdlib.h>

#include "mpc/mpc.h"

/**For Windows systems **/
#ifdef _WIN32
#include <string.h>

static char buffer[2048];

//Custom readline function
char* readline(char* prompt) { 
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(stflen(buffer)+1);
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0';
	return cpy;
}

//Fake add_history function
void add_history(char* unused) {}

/** Other computer systems **/
#else 
#include <editline/readline.h>
#include <editline/history.h>
//End preprocessor commands
#endif

long eval_op(long x, char* op, long y)
{
	if(strcmp(op, "+") == 0) { return x + y; }
	if(strcmp(op, "-") == 0) { return x - y; }
	if(strcmp(op, "*") == 0) { return x * y; }
	if(strcmp(op, "/") == 0) { return x / y; }
	return 0;
}

long eval(mpc_ast_t* t){
	/* If number return directly */
	if (strstr(t->tag, "number")) {
		return atoi(t->contents);
	}
	
	//operator is always the second
	char* op = t->children[1]->contents;
	
	//Third child stored as X
	long x = eval(t->children[2]);
	
	//Iterate through the rest of the children
	int i = 3;
	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		i++;   
	}
	return x;
}


int main(int argc, char** argv) {
	//Initialise the parser
	/* Creating parser */
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");
	
	/* Define the parsers */
	mpca_lang(MPCA_LANG_DEFAULT, 
	 "																										\
		number		:  /-?[0-9]+/ ;														\
		operator	: '+' | '-' | '*' | '/' ;									\
		expr			: <number> | '(' <operator> <expr>+ ')' ;	\
		lispy			: /^/ <operator> <expr>+ /$/ ;						\
	 ",
	 Number, Operator, Expr, Lispy );
	//Version and exit info
	puts("Krispy Version 0.0.1.2");
	puts("Press Ctrl+c to Exit\n");
	
	//Infinite loop
	while (1) {
		//Will intelligently choose the available readline for the user's platform
		char* input = readline("krispy> ");
		add_history(input);
		
		//Handling the user input
		mpc_result_t r;
		if (mpc_parse("<stdin>", input, Lispy, &r)) {
			long result = eval(r.output);
			printf("%li\n", result);
			mpc_ast_delete(r.output);
		} else {
			//Error handling
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		
		free(input);
	}
	//Cleaning up my closet
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	//End
	return 0;
}
