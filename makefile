default: compile

compile:
	g++ -g -o executable.out main.cpp -l raylib

clean:
	rm executable.out

run: compile
	ulimit -c unlimited
	./executable.out
