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

        for (size_t j = i + 1; j < count; ++j) 
            if (cmp(arr + j * size, arr + min_idx * size) < 0) 
                min_idx = j; 
        

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
            if (cmp(arr + (j - 1) * size, arr + j * size) > 0) 
                edu_swap(arr + (j - 1) * size, arr + j * size, size);
            
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

static void quick_sort_recursive(unsigned char *base, size_t size, long left, long right, edu_cmp cmp) {
    if (left >= right) return;

    long i = left;
    long j = right;
    unsigned char *pivot_buf = malloc(size);
    if (!pivot_buf) return;

    // Копируем значение опорного элемента в отдельный буфер
    memcpy(pivot_buf, base + ((left + right) / 2) * size, size);

    while (i <= j) {
        while (cmp(base + i * size, pivot_buf) < 0) i++;
        while (cmp(base + j * size, pivot_buf) > 0) j--;

        if (i <= j) {
            edu_swap(base + i * size, base + j * size, size);
            i++;
            j--;
        }
    }

    free(pivot_buf);

    if (left < j)
        quick_sort_recursive(base, size, left, j, cmp);
    if (i < right)
        quick_sort_recursive(base, size, i, right, cmp);
}

void edu_quick_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    if (ptr == NULL || count < 2 || size == 0 || cmp == NULL)
        return;

    quick_sort_recursive((unsigned char *)ptr, size, 0, (long)count - 1, cmp);
    // UNUSED(ptr);
    // UNUSED(count);
    // UNUSED(size);
    // UNUSED(cmp);
    // UNIMPLEMENTED;
}

static void heapify(void *base, size_t n, size_t size, size_t root, edu_cmp cmp) {
    unsigned char *bytes = (unsigned char *)base;
    size_t largest = root;

    while (1) {
        size_t left = 2 * root + 1;
        size_t right = 2 * root + 2;

        if (left < n && cmp(bytes + left * size, bytes + largest * size) > 0)
            largest = left;
        if (right < n && cmp(bytes + right * size, bytes + largest * size) > 0)
            largest = right;

        if (largest != root) {
            edu_swap(bytes + root * size, bytes + largest * size, size);
            root = largest;  // продолжаем вниз по дереву
        } else {
            break; // свойство кучи восстановлено
        }
    }
}

void edu_heap_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    if (ptr == NULL || count < 2 || size == 0 || cmp == NULL) return;

    unsigned char *bytes = (unsigned char *)ptr;

    for (size_t i = count / 2; i > 0; i--) {
        heapify(bytes, count, size, i - 1, cmp);
    }

    for (size_t i = count; i > 1; i--) {
        edu_swap(bytes, bytes + (i - 1) * size, size);

        heapify(bytes, i - 1, size, 0, cmp);
    }
    // UNUSED(ptr);
    // UNUSED(count);
    // UNUSED(size);
    // UNUSED(cmp);
    // UNIMPLEMENTED;
}

static long long get_int_value(const void *ptr, size_t size) {
    switch (size) {
        case 1: return *(const signed char *)ptr;
        case 2: return *(const short *)ptr;
        case 4: return *(const int *)ptr;
        case 8: return *(const long long *)ptr;
        default:
            fprintf(stderr, "Unsupported integer size: %zu\n", size);
            exit(EXIT_FAILURE);
    }
}

static void set_int_value(void *ptr, size_t size, long long value) {
    switch (size) {
        case 1: *(signed char *)ptr = (signed char)value; break;
        case 2: *(short *)ptr = (short)value; break;
        case 4: *(int *)ptr = (int)value; break;
        case 8: *(long long *)ptr = (long long)value; break;
        default:
            fprintf(stderr, "Unsupported integer size: %zu\n", size);
            exit(EXIT_FAILURE);
    }
}

void edu_counting_sort(void *ptr, size_t count, size_t size, edu_counting_sort_order_e order) {
    if (ptr == NULL || count == 0) return;

    unsigned char *bytes = (unsigned char *)ptr;

    long long min = get_int_value(bytes, size);
    long long max = min;

    for (size_t i = 1; i < count; i++) {
        long long val = get_int_value(bytes + i * size, size);
        if (val < min) min = val;
        if (val > max) max = val;
    }

    size_t range = (size_t)(max - min + 1);

    size_t *counts = (size_t *)calloc(range, sizeof(size_t));
    if (!counts) {
        perror("calloc failed");
        return;
    }

    for (size_t i = 0; i < count; i++) {
        long long val = get_int_value(bytes + i * size, size);
        counts[val - min]++;
    }

    size_t index = 0;
    if (order == EDU_COUNTING_SORT_ASC) {
        for (size_t i = 0; i < range; i++) {
            while (counts[i]--) {
                set_int_value(bytes + index * size, size, (long long)(i + min));
                index++;
            }
        }
    } else {
        for (size_t i = range; i-- > 0;) {
            while (counts[i]--) {
                set_int_value(bytes + index * size, size, (long long)(i + min));
                index++;
            }
        }
    }

    free(counts);
    // printf("max = %ld\n", max);
    // UNUSED(ptr);
    // UNUSED(count);
    // UNUSED(size);
    // UNUSED(order);
    // UNIMPLEMENTED;
}
