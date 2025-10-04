#include "edu_sort.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "[ERROR] function %s is unimplemented\n", __func__); \
        abort(); \
    } while (0)

#define UNUSED(x) (void)(x)

static void edu_swap(void *a, void *b, size_t size) {
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void edu_bubble_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    int swapped = 1;

    while (swapped) {
        swapped = 0;
        for (size_t i = 0; i < count - 1; ++i) {
            void *val1 = (char *) ptr + i * size;
            void *val2 = (char *) ptr + (i + 1) * size;
            if (cmp(val1, val2) > 0) {
                edu_swap(val1, val2, size);
                swapped = 1;
            }
        }
        --count;
    }
}

void edu_selection_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    char *arr = (char *) ptr;

    for (size_t i = 0; i < count - 1; ++i) {
        size_t min_idx = i;

        for (size_t j = i + 1; j < count; ++j) {
            if (cmp(arr + j * size, arr + min_idx * size) < 0) min_idx = j; 
        }

        if (min_idx != i) edu_swap(arr + i * size, arr + min_idx * size, size); 
    }
    // UNUSED(ptr);
    // UNUSED(count);
    // UNUSED(size);
    // UNUSED(cmp);
    // UNIMPLEMENTED;
}

void edu_insertion_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    char *arr = (char *) ptr;

    for (size_t i = 1; i < count; ++i) {
        for (size_t j = i; j > 0; --j) {
            if (cmp(arr + (j - 1) * size, arr + j * size) > 0) {
                edu_swap(arr + (j - 1) * size, arr + j * size, size);
            }
            else break;
        }
    }
    // UNUSED(ptr);
    // UNUSED(count);
    // UNUSED(size);
    // UNUSED(cmp);
    // UNIMPLEMENTED;
}

void edu_shell_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    char *arr = (char *) ptr;
        
    for (size_t gap = count / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < count; ++i) {
            for (size_t j = i; j >= gap; --j) {
                if (cmp(arr + (j - 1) * size, arr + j * size) > 0)
                    edu_swap(arr + (j - 1) * size, arr + j * size, size);
                
                else break;
            }
        }
    }
    // UNUSED(ptr);
    // UNUSED(count);
    // UNUSED(size);
    // UNUSED(cmp);
    // UNIMPLEMENTED;
}

void edu_quick_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    UNUSED(ptr);
    UNUSED(count);
    UNUSED(size);
    UNUSED(cmp);
    UNIMPLEMENTED;
}

void edu_heap_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    UNUSED(ptr);
    UNUSED(count);
    UNUSED(size);
    UNUSED(cmp);
    UNIMPLEMENTED;
}

void edu_counting_sort(void *ptr, size_t count, size_t size, edu_counting_sort_order_e order) {
    UNUSED(ptr);
    UNUSED(count);
    UNUSED(size);
    UNUSED(order);
    UNIMPLEMENTED;
}
