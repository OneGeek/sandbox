#pragma once

#include <vector>

using namespace std;

template <class T>
void remove(T item, vector<T>& items) {
    for (auto iter=items.begin(); iter != items.end(); iter++)
    {
        if (item == *iter)
        {
            items.erase(iter);
            break;
        }
    }
}

