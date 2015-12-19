#include <stdio.h>
#include <stdlib.h>

//Using editline to allow editting the buffer
#include <editline/readline.h>
#include <editline/history.h>

int main(int argc, char** argv){
	//Print Version and Exit information
	puts("Lispy Version 0.0.1a");
	puts("Press Ctrl+c to Exit\n");
	
	//Infinite loop
	while (1) {
		//Output prompt and get input 
		char* input = readline("lispy> ");

		//Add input to history
		add_history(input);
		
		//Echo input as output
		printf("No you're a %s\n", input);
		
		//Free input
		free(input);
	}
	
	//End
	return 0;
}
