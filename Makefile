compile:
	gcc -Wall cryo.c rc.c -o cryo

run: compile
	./cryo plaintext

clean:
	rm cryo