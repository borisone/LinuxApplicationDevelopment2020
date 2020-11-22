```
$ autoreconf -fisv
$ ./configure
$ make
$ ./guess
$ make doxygen-doc # documentation
$ python3 -m http.server -d doxygen-doc/html/ PORT # to run server
```
