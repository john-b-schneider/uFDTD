SRC=code-liner.c

OBJ=${SRC:.c=}

#=====================================================================
.c:
	cc -Wall -O $< -o $* -lm

all: ${OBJ}

clean:
	rm -f *~ sim.? sim.?? junk* ${OBJ}
	cd Fdtd-abc;           make clean; cd ..
	cd Fdtd-improved-code; make clean; cd ..
	cd Fdtd-dimensionless; make clean; cd ..
	cd Fdtd-dispersion;    make clean; cd ..
	cd Fdtd-intro;         make clean; cd ..
	cd Fdtd-spectral;      make clean; cd ..
	cd Numerical-issues;   make clean; cd ..
	cd Fdtd-multidimensional; make clean; cd ..
	cd Fdtd-3d;            make clean; cd ..
	cd Postscript-primer;  make clean; cd ..
