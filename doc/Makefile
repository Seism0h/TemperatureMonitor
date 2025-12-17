PANDOC = pandoc --pdf-engine=xelatex --filter mermaid-filter
LATEX = pdflatex

C_MD = ../c/doc/call_sequence.md
C_PDF = ../c/doc/call_sequence.pdf

CPP_MD = ../cpp/doc/structure.md
CPP_PDF = ../cpp/doc/structure.pdf

MAIN_TEX = documentation.tex
MAIN_PDF = documentation.pdf

.PHONY: all clean clean_artifacts

all: clean $(C_PDF) $(CPP_PDF) $(MAIN_PDF)

clean_artifacts:
	@rm -f *.toc *.aux *.log *.fls *.fdb_latexmk *.out *.err *.synctex.gz

$(C_PDF): $(C_MD)
	$(PANDOC) $< -o $@
	pdfcrop $@ $@

$(CPP_PDF): $(CPP_MD)
	$(PANDOC) $< -o $@
	pdfcrop $@ $@

# Build the main PDF twice to ensure TOC is updated
$(MAIN_PDF): $(MAIN_TEX) $(C_PDF) $(CPP_PDF)
	$(LATEX) -interaction=nonstopmode $(MAIN_TEX)
	$(LATEX) -interaction=nonstopmode $(MAIN_TEX)
	$(MAKE) clean_artifacts

clean:
	$(MAKE) clean_artifacts
	@rm -f $(C_PDF) $(CPP_PDF) $(MAIN_PDF)