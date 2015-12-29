SRC=code-liner.c oneThird.c rootTest.c

OBJ=${SRC:.c=}

#=====================================================================
.c:
	cc -Wall -O $< -o $* -lm

all: ${OBJ}

clean:
	rm -f *~ junk* ${OBJ}
