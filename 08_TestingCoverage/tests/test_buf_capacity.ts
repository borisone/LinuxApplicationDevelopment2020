#include "buf.h"

#suite Test buf_capacity
#test test_buf_capacity
    float *a = 0;
    ck_assert_int_eq(buf_capacity(a), 0);
