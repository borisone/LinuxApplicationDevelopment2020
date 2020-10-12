CFLAGS = -fPIC
GENERATES = prog prog-a prog-so liboutput.so
TRASH = *.o *.err *.out liboutput_static.a

run-%: %
	LD_LIBRARY_PATH='.' ./$< > $^.0.out 2> $^.0.err 
	LD_LIBRARY_PATH='.' ./$< 1 > $^.1.out 2> $^.1.err 
	LD_LIBRARY_PATH='.' ./$< 1 2 3 > $^.3.out 2> $^.3.err 

test: run-prog run-prog-a run-prog-so
	for i in 0 1 3; do \
		cmp prog.$$i.out prog-a.$$i.out ; \
		cmp prog.$$i.out prog-so.$$i.out ; \
		cmp prog-a.$$i.out prog-so.$$i.out ; \
		cmp prog.$$i.err prog-a.$$i.err ; \
		cmp prog.$$i.err prog-so.$$i.err ; \
		cmp prog-a.$$i.err prog-so.$$i.err ; \
	done

prog-so: prog.o liboutput.so
	cc $(CFLAGS) -L. prog.o -loutput -o prog-so

prog-a: prog.o liboutput_static.a
	cc $(CFLAGS) -L. prog.o -loutput_static -o prog-a

prog: const.o fun.o prog.o
	cc const.c fun.c prog.c -o prog

liboutput.so: fun.o const.o
	cc -shared $(CFLAGS) fun.o const.o -o liboutput.so

liboutput_static.a: const.o fun.o
	ar -rcs liboutput_static.a const.o fun.o

const.o: const.c
	cc const.c -c -o const.o

fun.o: fun.c
	cc fun.c $(CFLAGS) -c -o fun.o

prog.o: prog.c
	cc prog.c -c -o prog.o

clean:
	rm -f $(TRASH)

distclean:
	rm -f $(GENERATES)
