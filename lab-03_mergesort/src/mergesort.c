#include"mergesort.h"

int merge(
    void *array,
    size_t left, size_t mid, size_t right,
    int (*comparator)(const void *, const void *)
)
{
    char** tmp_array = malloc(sizeof(char*) * (right - left));
    if (tmp_array == NULL)
        return -1;
    for (size_t i = 0; i < (right - left); ++i)
        *(tmp_array + i) = *((char**)array + left + i);

    size_t it1 = 0;
    size_t it2 = 0;
    size_t cur_pos = 0;
    while (it1 < mid - left || it2 < right - mid)
    {
        if (it1 == mid - left)
        {
            *((char**)array + cur_pos + left) = *(tmp_array + it2 + (mid - left));
            it2++;
        }
        else if (it2 == right - mid)
        {
            *((char**)array + cur_pos + left) = *(tmp_array + it1);
            it1++;
        }
        else
        {
            if (comparator(*(tmp_array + it1), *(tmp_array + it2 + (mid - left))) < 0)
            {
                *((char**)array + cur_pos + left) = *(tmp_array + it1);
                it1++;
            }
            else
            {
                *((char**)array + cur_pos + left) = *(tmp_array + it2 + (mid - left));
                it2++;
            }
        }
        cur_pos++;
    }
    free(tmp_array);
    return 0;
}

int mergesortRecursive(
    void *array,
    size_t left, size_t right,
    int (*comparator)(const void *, const void *)
)
{
    int is_dead = 0;
    if (left + 1 >= right)
        return 0;
    size_t mid = (left + right) / 2;
    is_dead = mergesortRecursive(array, left, mid, comparator);
    if (is_dead == -1)
        return is_dead;
    is_dead = mergesortRecursive(array, mid, right, comparator);
    if (is_dead == -1)
        return is_dead;
    return merge(array, left, mid, right, comparator);
}
int mergesort(
    void *array,
    size_t elements, size_t element_size,
    int (*comparator)(const void *, const void *)
)
{
    element_size++;
    return mergesortRecursive(array, 0, elements, comparator);
}
