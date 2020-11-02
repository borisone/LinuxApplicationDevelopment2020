make
touch test-wrapper-FIX.c
touch test-wrapper.c

LD_PRELOAD=`pwd`/fakeunlinkat.so rm test-wrapper-FIX.c
LD_PRELOAD=`pwd`/fakeunlinkat.so rm test-wrapper.c
