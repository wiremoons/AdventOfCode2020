## +++ DEFAULT MAKE OUTPUT +++ :
## Set default 'make' rule to run if no argument is given
.PHONY: default
default: all ;

all: d1 d2 d3 d4 d5 d6 d7

clean: d1-clean d2-clean d3-clean d5-clean d5-clean d6-clean d7-clean

d1:
	make -C ./Day-01/

d2:
	make -C ./Day-02

d3:
	make -C ./Day-03

d4:
	make -C ./Day-04

d5:
	make -C ./Day-05

d6:
	make -C ./Day-06

d7:
	make -C ./Day-07

# run make clean for each day
d1-clean:
	make -C ./Day-01 clean

d2-clean:
	make -C ./Day-02 clean

d3-clean:
	make -C ./Day-03 clean

d4-clean:
	make -C ./Day-04 clean	

d5-clean:
	make -C ./Day-05 clean

d6-clean:
	make -C ./Day-06 clean

d7-clean:
	make -C ./Day-07 clean