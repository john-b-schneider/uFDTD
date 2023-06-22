texfiles=sisyphus.tex
chapters=numerical-issues.tex em-review.tex fdtd-intro.tex\
	fdtd-improved-code.tex\
	fdtd-dimensionless.tex fdtd-abc.tex fdtd-spectral.tex\
	fdtd-dispersion.tex fdtd-multidimensional.tex\
	fdtd-3d.tex\
	fdtd-acoustics.tex fdtd-dispersive-material.tex\
	fdtd-pml.tex fdtd-near-to-far.tex\
	parallel-processing.tex\
	mom-intro.tex appendices.tex postscript-primer.tex

num_chapters=chap1.pdf chap2.pdf chap3.pdf chap4.pdf chap5.pdf chap6.pdf\
	chap7.pdf chap8.pdf chap9.pdf chap10.pdf chap11.pdf chap12.pdf\
	chap13.pdf chap14.pdf appendices.pdf bibliography.pdf

DATE=$(shell date +%m.%d.%Y)

#=====================================================================

sisyphus.pdf: sisyphus.tex ${chapters} commands.tex

.SUFFIXES: .tex .pdf

.tex.pdf:
	pdflatex $*
        bibtex $*
	pdflatex $*
	pdflatex $*

chapters: ${num_chapters}

# 1 numerical stuff
chap1.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=7 -dLastPage=12 -sOutputFile=chap1.pdf sisyphus.pdf
# 2 EM review
chap2.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=13 -dLastPage=32 -sOutputFile=chap2.pdf sisyphus.pdf
# 3 FDTD intro
chap3.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=33 -dLastPage=74 -sOutputFile=chap3.pdf sisyphus.pdf
# 4 improved code
chap4.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=75 -dLastPage=114 -sOutputFile=chap4.pdf sisyphus.pdf
# 5 scaling to any freq. (dimensionless)
chap5.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=115 -dLastPage=144 -sOutputFile=chap5.pdf sisyphus.pdf
# 6 diff. eq. based ABC's
chap6.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=145 -dLastPage=160 -sOutputFile=chap6.pdf sisyphus.pdf
# 7 dispersion
chap7.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=161 -dLastPage=180 -sOutputFile=chap7.pdf sisyphus.pdf
# 8 2D FDTD
chap8.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=181 -dLastPage=240 -sOutputFile=chap8.pdf sisyphus.pdf
# 9 3D
chap9.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=241 -dLastPage=288 -sOutputFile=chap9.pdf sisyphus.pdf
# 10 dispersive media
chap10.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=289 -dLastPage=306 -sOutputFile=chap10.pdf sisyphus.pdf
# 11 PML
chap11.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=307 -dLastPage=322 -sOutputFile=chap11.pdf sisyphus.pdf
# 12 acoustics
chap12.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=323 -dLastPage=330 -sOutputFile=chap12.pdf sisyphus.pdf
# 13 parallel
chap13.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=331 -dLastPage=350 -sOutputFile=chap13.pdf sisyphus.pdf
# 14 NTFF
chap14.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=351 -dLastPage=376 -sOutputFile=chap14.pdf sisyphus.pdf
# MoM
#chap15.pdf: sisyphus.pdf
#	dvips sisyphus -Ppdf -p =369 -n22 -o chap15.pdf

appendices.pdf: sisyphus.pdf
	gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=377 -dLastPage=402 -sOutputFile=appendices.pdf sisyphus.pdf

bibliography.pdf: sisyphus.pdf
        gs -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -dSAFER -dFirstPage=403 -dLastPage=403 -sOutput\
File=bibliography.pdf sisyphus.pdf

all: ${psfiles}

pdf: ${pdffiles}

index:
	makeindex sisyphus

clean:
	rm -f *.dvi *.log *.aux *~

veryclean:
	rm -f *.dvi *.log *.aux *~ *.ps *.pdf
	cd Code; make clean; cd ..

distro:
	cd ..; tar cvzf /tmp/uFDTD-${DATE}.tgz uFDTD

publish:
	cp chap*.pdf appendices.pdf bibliography.pdf ~/public_html/ufdtd
	cp sisyphus.pdf  ~/public_html/ufdtd/ufdtd.pdf
