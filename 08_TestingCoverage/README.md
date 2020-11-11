```
$ autoreconf -fisv
$ ./configure --enable-gcov
$ make
$ make check # to run tests
```

To check the code coverage run the following commands
```
$ cd src
$ gcov .libs/buf -t -j -k
```
