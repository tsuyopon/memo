.PHONY: all
all: exec test

exec: exec.c
	gcc exec.c -o exec

test: test.c
	gcc test.c -o test

clean:
	rm -f exec test
