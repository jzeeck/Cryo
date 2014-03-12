compile:
	gcc -Wall rc.c -o cryo

run: compile
	./cryo plaintext
