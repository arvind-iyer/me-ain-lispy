#include <stdio.h>

/*Declare a 2048 char buffer */
static char input[2048];

int main(int argc, char** argv){
	//Print Version and Exit information
	puts("Lispy Version 0.0.1a");
	puts("Press Ctrl+c to Exit\n");
	
	//Infinite loop
	while (1) {
		//Output prompt
		fputs("lispy> ", stdout);
		
		//Read a line of user input
		fgets(input, 2048, stdin);
		
		//Echo input as output
		printf("No you're a %s", input);
	}
	
	//End
	return 0;
}
