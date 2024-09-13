#include "hash_table.h"
#include "commands.h"

template <typename T>
int hash_table<T>::Hash(const std::string& s, int table_size, const int key)
{
    int hash_result = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        hash_result = (key * hash_result + s[i]) % table_size;
    }
    hash_result = (hash_result * 2 + 1) % table_size;
    return hash_result;
};


template<typename T>
void hash_table<T>::Rehash()
{
    size = 0;
    Node<T>** arr2 = new Node<T> *[buffer_size];
    for (int i = 0; i < buffer_size; ++i)
        arr2[i] = nullptr;
    std::swap(arr, arr2);
    for (int i = 0; i < buffer_size; ++i)
    {
        if (arr2[i] && arr2[i]->state)
        {
            Add(arr2[i]->value, *arr2[i]->translation[0]);
            for (int x = 1; x < arr[i]->translation_count; x++)
            {
                Add(arr2[i]->value, *arr2[i]->translation[x]);
            }
        }
    }
    for (int i = 0; i < buffer_size; ++i)
        if (arr2[i])
            delete arr2[i];
    delete[] arr2;
};


