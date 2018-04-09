all: 2018-03-27_Reunion_1.pdf
%.pdf: %.tex
	latexmk -lualatex $^
	find . -iname `echo $< | rev | cut -d '.' -f 2 | rev`."*" ! -iname "*.pdf" ! -iname "*.tex" -print -delete
.PHONY: clean
clean:
	rm -f *.pdf
