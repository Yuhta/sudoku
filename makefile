.PHONY:	compile install clean

compile:
	cd src && $(MAKE) && $(RM) *.o

install:
	if [[ ! -d bin ]]; then mkdir bin; fi
	cp src/sudoku bin/

clean:
	cd src && $(MAKE) clean
	$(RM) -r bin
