#include "commands.h"

template <typename T>
void feofanova::Print()
{
    Node<T>* temp;
    std::cout << "Dictionary Hash Table:" << std::endl;
    std::cout << "--------------------------" << std::endl;
    for (int x = 0; x < buffer_size; x++)
    {
        temp = arr[x];
        if (temp != NULL && temp->state == 1)
        {
            std::cout << "Word: " << temp->value << std::endl;
            std::cout << "Translation(s): ";
            &(temp->translation)[0];
            temp->PrintTranslations();
            std::cout << std::endl << std::endl;
        }
    }
};


template <typename T>
bool feofanova:Find(const T& value)
{
    int i = 0;
    int h1 = Hash(value, buffer_size, buffer_size - 1);
    int h2 = Hash(value, buffer_size, buffer_size + 1);
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->value == value)
            return true;
        h1 = (h1 + h2) % buffer_size;
        ++i;
    }
    return false;
};

template <typename T>
bool feofanova::Remove(const T& value)
{
    int h1 = Hash(value, buffer_size, buffer_size - 1);
    int i = 0;
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->value == value && arr[h1]->state)
        {
            std::cout << value << " deleted" << std::endl;
            arr[h1]->state = false;
            --size;
            return true;
        }
        h1 = (h1) % buffer_size;
        ++i;
    }
    return false;
}

template <typename T>
bool feofanova::Add(const T& value, const T& translation)
{
    if (size > 2 * buffer_size)
        Rehash();
    int h1 = Hash(value, buffer_size, buffer_size - 1);
    int h2 = Hash(value, buffer_size, buffer_size + 1);
    int i = 0;
    int first_deleted = -1;
    int IsWordNew = 0;
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->value == value)
        {
            std::cout << "Новый перевод добавлен" << std::endl;
            Node<T>* n = arr[h1];
            n->AddTranslation(translation);
            IsWordNew = 1;
        }
        if (!arr[h1]->state && first_deleted == -1)
            first_deleted = h1;
        h1 = (h1 + h2) % buffer_size;
        ++i;
    }
    if (first_deleted == -1 && IsWordNew == 0)
    {
        arr[h1] = new Node<T>(value, translation);
        int h1 = Hash(value, buffer_size, buffer_size - 1);
        arr[h1] = new Node<T>(value, translation);
        std::cout << "Новое слово добавлено!" << std::endl;
    }
    ++size;
    return true;
};