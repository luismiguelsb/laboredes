CC = gcc
FLAGS = -Wall 

all: testesrv testecli

testesrv: testesrv.cpp
	$(CC) testesrv.cpp -lc -o testesrv $(FLAGS) 

testecli: testecli.cpp
	$(CC) testecli.cpp -lc -o testecli $(FLAGS) 

clean:
	rm testecli testesrv 
