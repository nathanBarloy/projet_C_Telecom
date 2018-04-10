all: Rapport.pdf
%.pdf: %.tex
	latexmk -lualatex -silent $^
	find . -iname `echo $< | rev | cut -d '.' -f 2 | rev`."*" ! -iname "*.pdf" ! -iname "*.tex" -print -delete
.PHONY: clean
clean:
	rm -f *.pdf
	find . -maxdepth 1 -type f ! -iname "*.pdf" ! -iname "*.tex"  ! -iname "Makefile" -print -delete
