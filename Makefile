all:
	cd Serial && $(MAKE) && $(MAKE) move
	cd OpenMP && $(MAKE) && $(MAKE) move
	cd MPI && $(MAKE) && $(MAKE) move

Ball-serial: clean
	cd Serial && $(MAKE) && $(MAKE) move

Ball-common:
	cd Common && $(MAKE)

Ball-openmp:
	cd OpenMP && $(MAKE) && $(MAKE) move

Ball-mpi:
	cd MPI && $(MAKE) && $(MAKE) move

clean:
	cd Serial && $(MAKE) clean
	cd Common && $(MAKE) clean
	cd OpenMP && $(MAKE) clean
	cd MPI && $(MAKE) clean
	rm -f ballAlg
	rm -f ballAlg-omp
	rm -f ballAlg-mpi