#pragma once

#include <cstddef>

template <typename T, typename F>
void iter(T *arr,const size_t length, F func)
{
    if (!arr || !func)
        return;
    for (size_t i = 0; i < length; i++)
        func(arr[i]);
}
