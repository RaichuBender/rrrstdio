main:			src/main.o src/rrrstdio.o
	$(CC) $^ -Iinclude -O2 -s -o $@
src/%.o:		src/%.c
	$(CC) $^ -Iinclude -O2 -c -o $@
.PHONY:			clean
clean:
	@-rm -vf main src/main.o src/rrrstdio.o
