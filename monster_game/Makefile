DIRS= lib bin


all: libs

libs:
	@(for d in $(DIRS); do $(MAKE) -C $$d || exit $?; done)

.PHONY: clean test
clean:
	@(for d in $(DIRS); do $(MAKE) -C $$d $@ ; done)

test:
	@for testdir in `find . -type d -name "unit_tests*"`; \
	do \
		echo "Running unit tests in : $$testdir"; \
		$(MAKE) -C $$testdir test; \
	done

