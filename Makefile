all: clean hello prompt parsing eval err sexp qexp var
hello:
	gcc -std=c99 -Wall hello.c -o hello
prompt:
	gcc -std=c99 -Wall prompt.c -ledit -o prompt
parsing:
	gcc -std=c99 -Wall parsing.c mpc.c -ledit -lm -o parsing
eval:
	gcc -std=c99 -Wall evaluation.c mpc.c -ledit -lm -o eval
err:
	gcc -std=c99 -Wall error_handling.c mpc.c -ledit -lm -o err
sexp:
	gcc -std=c99 -Wall s_expressions.c mpc.c -ledit -lm -o sexp
qexp:
	gcc -std=c99 -Wall q_expressions.c mpc.c -ledit -lm -o qexp
var:
	gcc -std=c99 -Wall variables.c mpc.c -ledit -lm -o var
clean:
	rm -f hello prompt parsing eval err sexp qexp var
