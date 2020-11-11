TESTS = test test_buf_capacity test_buf_size test_buf_push test_buf_clear test_buf_clear test_buf_pop
check_PROGRAMS = test test_buf_capacity test_buf_size test_buf_push test_buf_clear test_buf_clear test_buf_pop
CFLAGS = @CHECK_CFLAGS@ -I ../src
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
