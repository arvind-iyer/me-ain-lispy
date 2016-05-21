#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>
static char buffer[2048];

/* Fake readline */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add history */
void add_history(char* unused) {}

#else

// Include editline
#include <editline/readline.h>

#endif

int main(int argc, char**  argv) {
  /* Print version and how to exit */
  puts("Toxic Version 0.0.1");
  puts("Press Ctrl+c to Exit\n");

  /* Infinite Loop */
  while (1) {
    /* Output prompt and get input */
    char* input = readline("toxic>");

    /* Add input to history */
    add_history(input);

    /*Echo back to user*/
    printf("No you're a %s\n", input);

    /* Free retrieved input after use */
    free(input);
  }
  return 0;
}
