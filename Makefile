compile_flags = -g

evalutation: evaluation.o arraylist.o moves.o board.o
	gcc evaluation.o arraylist.o moves.o board.o $(compile_flags) -o evaluation 

evaluation.o: evaluation.c
	gcc -c -I/evaluation.h evaluation.c

arraylist.o: arraylist.c
	gcc -c -I/arraylist.h arraylist.c

moves.o: moves.c
	gcc -c -I/moves.h moves.c

board.o: board.c
	gcc -c -I/board.h board.c
