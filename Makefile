compile_flags = -g

evalutation: evaluation.o moves.o board.o
	gcc evaluation.o moves.o board.o $(compile_flags) -o evaluation 

evaluation.o: evaluation.c
	gcc -c -I/evaluation.h $(compile_flags) evaluation.c 

moves.o: moves.c
	gcc -c -I/moves.h $(compile_flags) moves.c

board.o: board.c
	gcc -c -I/board.h $(compile_flags) board.c

movelist.o: movelist.c
	gcc -c -I/movelist.h -I/moves.h $(compile_flags) movelist.c

movegen.o: movegen.c
	gcc -c $(compile_flags) movegen.c

clean:
	rm *.o
