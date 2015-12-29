SRC=1d-disp.c

OBJ=${SRC:.c=}

#=====================================================================
.c:
	cc -Wall -O $< -o $* -lm

all: ${OBJ}

clean:
	rm -f *~ sim.? sim.?? junk* ${OBJ}
