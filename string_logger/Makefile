.PHONY: all clean build test

all: build
clean:
	@echo "***************[bazel clean]**************"
	bazel clean
	@echo

build:
	@echo "***************[bazel build]**************"
	bazel build ...
	@echo

test:
	@echo "***************[bazel test]**************"
	bazel test --test_output=all ...
	@echo
