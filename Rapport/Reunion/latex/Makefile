all: 2018-03-27_Reunion_1.pdf 2018-04-12_Reunion_2.pdf 2018-04-16_Reunion_3.pdf 2018-04-19_Reunion_4.pdf 2018-05-07_Reunion_5.pdf
%.pdf: %.tex
	latexmk -f -lualatex -silent $^
	find . -iname `echo $< | rev | cut -d '.' -f 2 | rev`."*" ! -iname "*.pdf" ! -iname "*.tex" -print -delete
.PHONY: clean
clean:
	rm -f *.pdf
	find . -maxdepth 1 -type f ! -iname "*.pdf" ! -iname "*.tex"  ! -iname "Makefile" -print -delete
