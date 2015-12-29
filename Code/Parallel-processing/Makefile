SRC=serial-example.c threads-example1.c\
	threads-example2.c threads-example3.c\
	threads-example4.c

EXE=${SRC:.c=}

all: ${EXE}

.SUFFIXES: .c

.c:
	gcc -Wall -O $< -o $* -D_THREAD_SAFE -lpthread

clean:
	rm ${EXE}
