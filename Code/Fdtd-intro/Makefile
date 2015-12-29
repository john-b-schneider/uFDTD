SRC=1DbareBones.c 1Dadditive.c 1Dtfsf.c 1Ddielectric.c\
	1Dlossy.c 1Dmatched.c

EXE=${SRC:.c=}

#=====================================================================
.c:
	cc -Wall -O $< -o $* -lm

all: ${EXE}

clean:
	rm -f *~ sim.? sim.?? junk* ${EXE}
