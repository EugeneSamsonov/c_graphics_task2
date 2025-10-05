#include "edu_search.h"

#include <stdio.h>
#include <stdlib.h>

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "[ERROR] function %s is unimplemented\n", __func__); \
        abort(); \
    } while (0)

#define UNUSED(x) (void)(x)

size_t edu_linear_search(const void *ptr, size_t count, size_t size, const void *key, edu_cmp cmp) {
    if (!ptr || !key || !cmp || count == 0) return count;

    const unsigned char *pos = (const unsigned char *)ptr;
    for (size_t i = 0; i < count; ++i) {
        if (cmp(pos + i * size, key) == 0) {
            return i;
        }
    }
    return count;
    // UNUSED(ptr);
    // UNUSED(count);
    // UNUSED(size);
    // UNUSED(key);
    // UNUSED(cmp);
    // UNIMPLEMENTED;
}


size_t edu_binary_search(const void *ptr, size_t count, size_t size, const void *key, edu_cmp cmp) {
    if (count <= 0) return 0;

    const char *charptr = (const char *)ptr;
    size_t mid, left = 0, right = count - 1;

    while (right >= left)
    {
        mid = left + (right - left) / 2;

        if (cmp(charptr + (mid * size), key) == 0) return mid;

        else if (cmp(charptr + (mid * size), key) > 0) right = mid - 1;

        else left = mid + 1;
    }

    return count;
    // UNUSED(ptr);
    // UNUSED(count);
    // UNUSED(size);
    // UNUSED(key);
    // UNUSED(cmp);
    // UNIMPLEMENTED;
}
