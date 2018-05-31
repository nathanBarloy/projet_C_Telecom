all: clean Rapport.pdf
SD=sd/sd.tex sd/dynamic.tex sd/static.tex
NETWORK=network/network.tex
FCT=fct/fct.tex fct/gui.tex fct/cli.tex fct/server.tex
BDPLUS=bdplus/bdplus.tex
COLLAB_REC=collab_rec/collab_rec.tex
ETAT_ART=etat_art/data.tex etat_art/similarite.tex 
%.pdf: %.tex
	latexmk -f -lualatex -silent $^
	find . -iname `echo $< | rev | cut -d '.' -f 2 | rev`."*" ! -iname "*.pdf" ! -iname "*.tex" -print -delete
.PHONY: clean
clean:
	rm -f *.pdf
	find . -maxdepth 1 -type f ! -iname "*.pdf" ! -iname "*.tex"  ! -iname "Makefile" -print -delete
