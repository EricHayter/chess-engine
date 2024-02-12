compile_flags = -g

evalutation: evaluation.o arraylist.o moves.o board.o
	gcc evaluation.o arraylist.o moves.o board.o $(compile_flags) -o evaluation 

evaluation.o: evaluation.c
	gcc -c -I/evaluation.h $(compile_flags) evaluation.c 

arraylist.o: arraylist.c
	gcc -c -I/arraylist.h $(compile_flags) arraylist.c

moves.o: moves.c
	gcc -c -I/arraylist.h -I/moves.h $(compile_flags) moves.c

board.o: board.c
	gcc -c -I/board.h $(compile_flags) board.c
