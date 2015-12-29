SRC=fdtd-1d.c fdtd-1d-die.c

OBJ=${SRC:.c=}

#=====================================================================
.c:
	cc -Wall -O $< -o $* -lm

all: ${OBJ}

clean:
	rm -f *~ sim.? sim.?? ${OBJ}
