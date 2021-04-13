all:
	cd Serial && $(MAKE)
	cd OpenMP && $(MAKE)

Ball-serial: clean
	cd Serial && $(MAKE)

Ball-common:
	cd Common && $(MAKE)

Ball-openmp:
	cd OpenMP && $(MAKE)

clean:
	cd Serial && $(MAKE) clean
	cd Common && $(MAKE) clean
	cd OpenMP && $(MAKE) clean