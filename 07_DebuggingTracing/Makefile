GENERATES = *.so *~ *FIX*

all:
	cc -shared -fPIC fakeunlinkat.c -ldl -o fakeunlinkat.so

clean:
	rm -rf $(GENERATES)

