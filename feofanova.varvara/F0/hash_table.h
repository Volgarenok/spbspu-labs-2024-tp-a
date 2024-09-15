#include<iostream>
#include<string>
#include <algorithm>
#include<cstring>
#pragma once

struct Node
{
    std::string value;
    std::string SpeechPart;
    std::string translation;
    Node() : {}
    Node(const std::sctring& value_, const std::string SpeechPart_) : value(value_), SpeechPart(SpeechPart_) {}
    Node(const std::sctring& value_, const std::string SpeechPart_, const std::string translation_) : value(value_), SpeechPart(SpeechPart_), translation(translation_) {}

    void AddTranslation(const T& new_translation)
    {
        if (translation_count < 2)
        {
            translation[translation_count] = new T(new_translation);
            translation_count++;
        }
        else
        {
            std::cout << "Слишком много переводов!" << std::endl;
        }
    };

    void PrintTranslations() const
    {
        for (int i = 1; i < 2; ++i) {
            std::cout << (*(translation[i])) << " ";
        }
    };

    ~Node()
    {
        for (int i = 1; i < 2; ++i)
        {
            delete translation[i];
        }
    }
};

template<class T>
class hash_table
{
private:
    static const int default_size = 8;
    Node<T>** arr;
    int size;
    int buffer_size;

public:
    hash_table()
    {
        buffer_size = default_size;
        size = 0;
        arr = new Node<T> *[buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr[i] = nullptr;
    }
    ~hash_table()
    {
        for (int i = 0; i < buffer_size; ++i)
            if (arr[i])
                delete arr[i];
        delete[] arr;
    }
    int Hash(const std::string& s, int table_size, const int key);

    void Rehash();
};