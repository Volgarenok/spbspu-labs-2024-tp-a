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
            return return arr[h1]->translation;
        h1 = (h1 + h2) % buffer_size;
        ++i;
    }
    return 'NotFound';
};

void feofanova::FindRE(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
    int i = 0;
    int h1 = Hash(value, buffer_size, buffer_size - 1);
    int h2 = Hash(value, buffer_size, buffer_size + 1);
    while (arr[h1] != nullptr && i < buffer_size)
    {
        if (arr[h1]->value == value)
            return arr[h1]->translation;
        h1 = (h1 + h2) % buffer_size;
        ++i;
    }
    return 'NotFound';
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

unordered_map<string, pair<string, string>> feofanova::Flip(const unordered_map<string, pair<string, string>>& russianDict) 
{
    unordered_map<string, pair<string, string>> englishDict;

    for (const auto& entry : russianDict) {
        const string& russianWord = entry.first;
        const string& partOfSpeech = entry.second.first;
        const string& englishTranslation = entry.second.second;

        if (englishDict.find(englishTranslation) == englishDict.end()) {
            englishDict[englishTranslation] = make_pair(partOfSpeech, russianWord);
        }
    }
    return englishDict;
}


unordered_map<string, pair<string, string>> feofanova::Filter(const unordered_map<string, pair<string, string>>& russianDict, string PoS)
{
    unordered_map<string, pair<string, string>> englishDict;

    for (const auto& entry : russianDict) {
        const string& russianWord = entry.first;
        const string& partOfSpeech = entry.second.first;
        const string& englishTranslation = entry.second.second;

        if (entry.second.word==PoS) {
            englishDict[russianWord] = make_pair(partOfSpeech, englishTranslation);
        }
    }
    return englishDict;
}

bool feofanova::FullCompare(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
    std::string result = "";
    std::string dict1Name = "";
    std::string dict2Name = "";
    in >> result >> dict1Name >> dict2Name;
    auto dict1 = dicts.find(dict1Name);
    auto dict2 = dicts.find(dict2Name);
    if (dict1 == dicts.end() || dict2 == dicts.end())
    {
        throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    std::map< std::string, size_t > unionDict = dict1->second;
    for (int i = 0; i < buff_size; ++i)
    {
        if (! dict2.find(dict[i])) { return false; }
    }
    return true;
}

void feofanova::PartCompare(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out, std::stringPoS)
{
    std::string result = "";
    std::string dict1Name = "";
    std::string dict2Name = "";
    in >> result >> dict1Name >> dict2Name;
    auto dict1 = dicts.find(dict1Name);
    auto dict2 = dicts.find(dict2Name);
    if (dict1 == dicts.end() || dict2 == dicts.end())
    {
        throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    std::map< std::string, size_t > unionDict = dict1->second;
    for (int i = 0; i < buff_size; ++i)
    {
        if (!dict2.find(dict[i]) && dict[i]->SpeechPart==PoS) { return false; }
    }
    return true;
}

void feofanova::doUnion(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
    std::string result = "";
    std::string dict1Name = "";
    std::string dict2Name = "";
    in >> result >> dict1Name >> dict2Name;
    auto dict1 = dicts.find(dict1Name);
    auto dict2 = dicts.find(dict2Name);
    if (dict1 == dicts.end() || dict2 == dicts.end())
    {
        throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    std::map< std::string, size_t > unionDict = dict1->second;
    std::for_each(dict2->second.begin(), dict2->second.end(), std::bind(unionWord, std::ref(unionDict), std::placeholders::_1));
    dicts[result] = std::move(unionDict);
    out << "- Dictionary <" << result << "> created by union of <" << dict1Name << "> and <" << dict2Name << ">.\n";
}

void feofanova::doCross(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{
    std::string result = "";
    std::string dict1Name = "";
    std::string dict2Name = "";
    in >> result >> dict1Name >> dict2Name;
    auto dict1 = dicts.find(dict1Name);
    auto dict2 = dicts.find(dict2Name);
    if (dict1 == dicts.end() || dict2 == dicts.end())
    {
        throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    std::map< std::string, size_t > intersectDict;
    std::for_each(dict1->second.begin(), dict1->second.end(), std::bind(intersectWord, std::ref(intersectDict), std::placeholders::_1, std::ref(dict2->second)));
    dicts[result] = std::move(intersectDict);
    out << "- Dictionary <" << result << "> created by intersecting <" << dict1Name << "> and <" << dict2Name << ">.\n";
}

void feofanova::doExtend(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{}

void feofanova::doReduce(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out)
{}

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