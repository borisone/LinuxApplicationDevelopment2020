#include "buf.h"

#suite Test buf_size
#test test_buf_size
    float *a = 0;
    ck_assert_int_eq(buf_size(a), 0);

