#include "buf.h"

#suite Test buf_push
#test test_buf_push
    float *a = 0;
    buf_push(a, 1.3f);
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
