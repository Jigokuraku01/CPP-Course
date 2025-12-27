#pragma once
#include <stdio.h>
#include<string.h>
#include<stddef.h>
#include<stdlib.h>
int mergesort(
    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *)
);
