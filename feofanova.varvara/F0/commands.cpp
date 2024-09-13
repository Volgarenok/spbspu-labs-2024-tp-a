#include "commands.h"

void feofanova::CreateER(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
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

void feofanova::CreateER(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
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

void feofanova::FindER(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
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

void feofanova::FindRE(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
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

void feofanova::DeleteER(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
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

void feofanova::DeleteER(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
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

void feofanova::FullPrint(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
    Node<T>* temp;
    out << "Dictionary Hash Table:" << std::endl;
    out << "--------------------------" << std::endl;
    for (int x = 0; x < buffer_size; x++)
    {
        temp = arr[x];
        if (temp != NULL && temp->state == 1)
        {
            out << "Word: " << temp->value << std::endl;
            out << " -part of speech: " << temp->SpeechPart << "- ";
            out << "Translation(s): ";
            &(temp->translation)[0];
            temp->PrintTranslations();
            out << std::endl << std::endl;
        }
    }
};

void feofanova::PartPrint(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
    std::string PoS;
    in >> PoS;
    Node<T>* temp;
    out << "Dictionary Hash Table of "<< PoS << std::endl;
    out << "--------------------------" << std::endl;
    for (int x = 0; x < buffer_size; x++)
    {
        temp = arr[x];
        if (temp != NULL && temp->state == 1 && temp->SpeechPart==PoS)
        {
            out << "Word: " << temp->value << std::endl;
            out << "Translation(s): ";
            &(temp->translation)[0];
            temp->PrintTranslations();
            out << std::endl << std::endl;
        }
    }
};