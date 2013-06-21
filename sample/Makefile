all: $(patsubst %.c,%.out,$(wildcard *.c))

.c.out:
	gcc -I../include $< ../build/host/lib/libmruby.a -lm -o $@

clean:
	rm *.out

.PHONY: all clean
