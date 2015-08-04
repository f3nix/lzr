

.PHONY: all
all: liblzr lzrd


.PHONY: liblzr
liblzr:
	$(MAKE) -C liblzr/


.PHONY: lzrd
lzrd:
	$(MAKE) -C lzrd/


.PHONY: install
install:
	# $(MAKE) -C lzrd/ install


.PHONY: clean
clean:
	$(MAKE) -C liblzr/ clean
	$(MAKE) -C lzrd/ clean
