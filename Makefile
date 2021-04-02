subsystem:
	cd Serial && $(MAKE)
	cd OpenMP && $(MAKE)
	
clean:
	cd Serial && $(MAKE) clean
	cd OpenMP && $(MAKE) clean