#pragma once

#include <cstddef>

template <typename T, typename F>
void iter(T *arr_add,const size_t length, F func)
{
    if (!arr_add || !func)
        return;
    for (size_t i = 0; i < length; i++)
    {
        func(arr_add[i]);
    }
}
