#include <stdio.h>
#include <stdlib.h>

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

int main(int argc, char** argv) {
	//Version and exit info
	puts("Lispy Version 0.0.1.1");
	puts("Press Ctrl+c to Exit\n");
	
	//Infinite loop
	while (1) {
		//Will intelligently choose the available readline for the user's platform
		char* input = readline("lispy> ");
		add_history(input);
		printf("No you're a %s\n", input);
		free(input);
	}
	//End
	return 0;
}
