SRC=find-points-ps.c

OBJ=${SRC:.c=}

#=====================================================================
.c:
	cc -Wall -O $< -o $* -lm

all: ${OBJ}

clean:
	rm -f *~ sim.? sim.??
	rm -f ${OBJ}
