#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i;
    
    for (i = 0; i < element_count; ++i) {
        if (numbers[i] == num) {
            return i;
        }
    }

    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i;
    
    for (i = element_count; i > 0; --i) {
        if (numbers[i - 1] == num) {
            return i - 1;
        }
    }

    return -1;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    size_t i;
    int max = numbers[0];
    int max_index = 0;

    if (element_count == 0) {
        return -1;
    }
    for (i = 1; i < element_count; ++i) {
        if (numbers[i] > max) {
            max = numbers[i];
            max_index = i;
        }
    }

    return max_index;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    size_t i;
    int min = numbers[0];
    int min_index = 0;

    if (element_count == 0) {
        return -1;
    }
    for (i = 1; i < element_count; ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
            min_index = i;
        }
    }

    return min_index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    size_t i;
    if (element_count == 0) {
        return 0;
    }

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] <= 0) {
            return 0;
        }
    }

    return 1;
}

int has_even(const int numbers[], const size_t element_count)
{
    size_t i;

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] % 2 == 0) {
            return 1;
        }
    }

    return 0;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    size_t i;

    if (pos == element_count) {
        numbers[pos] = num;
        return 1;
    }
    if (pos > element_count) {
        return 0;
    }
    
    for (i = element_count; i > pos; --i) {
        numbers[i] = numbers[i - 1];
    }
    numbers[pos] = num;
    return 1;
}
    
int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    size_t i;

    if (index >= element_count) {
        return 0;
    }
    for (i = index; i < element_count; ++i) {
        numbers[i] = numbers[i + 1];
    }
    
    return 1;
}
