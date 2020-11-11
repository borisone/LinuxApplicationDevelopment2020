CFLAGS += -Wall

if COND_GCOV
   CFLAGS += -fprofile-arcs -ftest-coverage -O0 -g
endif

lib_LTLIBRARIES = libbuf.la

# bin_PROGRAMS = libbuf
buf_LDADD = libbuf.la
libbuf_la_SOURCES = buf.c

gcov:
	gcov .libs/libbuf -t -j -k
