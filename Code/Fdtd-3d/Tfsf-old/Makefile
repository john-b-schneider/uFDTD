SRC=3d-ez-tfsf.c

OBJ=${SRC:.c=}

#=====================================================================
all: ${OBJ}

abc-3d.o: abc-3d.c
	cc -Wall -c $<

tfsf-3d-ez.o: tfsf-3d-ez.c
	cc -Wall -c $<

3d-ez-tfsf: 3d-ez-tfsf.c abc-3d.o tfsf-3d-ez.o
	cc -Wall -O $< -o 3d-ez-tfsf abc-3d.o tfsf-3d-ez.o -lm

.c:
	cc -Wall -O $< -o $* -lm

clean:
	rm -f *~ junk* sim.* *.o ${OBJ}
