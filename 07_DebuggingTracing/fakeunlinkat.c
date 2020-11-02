#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

// typedef int (*randtype)(void);
typedef int (*unlinkat_type)(int, const char *, int);

int unlinkat(int dirfd, const char *pathname, int flags) {
    if(strstr(pathname, "FIX")) {
        return EPERM;
    }
    // printf("Fake unlinkat\n");
    unlinkat_type true_unlinkat = dlsym(RTLD_NEXT, "unlinkat");
    return true_unlinkat(dirfd, pathname, flags);
}
