#include "commands.hpp"



void zolotukhin::create(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string newSetName;
    inp >> newSetName;
    if (Sets.find(newSetName) == Sets.end())
    {
        Set tmp;
        Sets.insert(std::pair<std::string, Set>(newSetName, tmp));
    }
    else
    {
        out << "SET ALREADY EXIST";
    }
}

void zolotukhin::addWord(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string setName;
    std::string word;
    std::string lineNum;
    inp >> setName >> word >> lineNum;
    if (Sets.find(setName) == Sets.end())
    {
        out << "SET NOT FOUND";
    }
    else
    {
        if (Sets.find(setName)->second.set_.find(word) == Sets.find(setName)->second.set_.end())
        {
            std::vector<std::string> tmp;
            tmp.push_back(lineNum);
            Sets.find(setName)->second.set_.insert(std::pair<std::string, std::vector<std::string>>(word, tmp));
        }
        else
        {
            if (std::find(Sets.find(setName)->second.set_.find(word)->second.begin(), Sets.find(setName)->second.set_.find(word)->second.end(), lineNum) != Sets.find(setName)->second.set_.find(word)->second.end())
            {
                out << "WORD AT THIS LINE ALREADY EXIST";
            }
            else
            {
                Sets.find(setName)->second.set_.find(word)->second.push_back(lineNum);
            }
        }
    }
}

void zolotukhin::removeWord(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string setName;
    std::string word;
    inp >> setName >> word;
    if (Sets.find(setName) == Sets.end())
    {
        out << "SET NOT FOUND";
    }
    else
    {
        if (Sets.find(setName)->second.set_.find(word) == Sets.find(setName)->second.set_.end())
        {
            out << "NO WORD";
        }
        else
        {
            Sets.find(setName)->second.set_.erase(word);
        }
    }
}

void zolotukhin::search(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string setName;
    std::string word;
    inp >> setName >> word;
    if (Sets.find(setName) == Sets.end())
    {
        out << "SET NOT FOUND";
    }
    else
    {
        if (Sets.find(setName)->second.set_.find(word) == Sets.find(setName)->second.set_.end())
        {
            out << "NO WORD";
        }
        else
        {
            out << word << ": ";
            std::copy(Sets.find(setName)->second.set_.find(word)->second.cbegin(), Sets.find(setName)->second.set_.find(word)->second.cend(), std::ostream_iterator< const std::string& >(out, " "));
            out << '\n';
        }
    }
}

void zolotukhin::display(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string setName;
    inp >> setName;
    auto it = Sets.find(setName);

    if (it == Sets.end()) {
        out << "<SET NOT FOUND>\n";
        return;
    }

    const Set& set = it->second;

    if (set.set_.empty()) {
        out << "<DATA STRUCTURE IS EMPTY>\n";
        return;
    }

    for (const auto& s : set.set_) {
        out << s.first << ": ";
        for (const auto& line : s.second) {
            out << line << " ";
        }
        out << "\n";
    }
}



void zolotukhin::countWords(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string setName;
    inp >> setName;
    if (Sets.find(setName) == Sets.end())
    {
        out << "SET NOT FOUND";
    }
    else
    {
        out << Sets.find(setName)->second.set_.size();
    }
}

void zolotukhin::clearSet(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string setName;
    inp >> setName;
    if (Sets.find(setName) == Sets.end())
    {
        out << "SET NOT FOUND";
    }
    else
    {
        Set t;
        Sets.find(setName)->second = t;
    }
}

void zolotukhin::mergeSets(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string set1;
    std::string set2;
    std::string setRes;
    inp >> set1 >> set2 >> setRes;
    if (Sets.find(set1) == Sets.end() || Sets.find(set2) == Sets.end())
    {
        out << "SET NOT FOUND";
    }
    if (Sets.find(setRes) != Sets.end())
    {
        out << "RESULT SET ALREADY EXISTS\n";
        return;
    }
    else
    {
        Set tmp;
        tmp.set_.insert(Sets.find(set1)->second.set_.begin(), Sets.find(set1)->second.set_.end());
        tmp.set_.insert(Sets.find(set2)->second.set_.begin(), Sets.find(set2)->second.set_.end());
        Sets.insert(std::pair<std::string, Set>(setRes, tmp));
    }
}

void zolotukhin::intersectSets(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out)
{
    std::string set1;
    std::string set2;
    std::string setRes;
    inp >> set1 >> set2 >> setRes;
    if (Sets.find(set1) == Sets.end() || Sets.find(set2) == Sets.end())
    {
        out << "SET NOT FOUND";
    }
    if (Sets.find(setRes) != Sets.end())
    {
        out << "RESULT SET ALREADY EXISTS\n";
        return;
    }
    else
    {
        Set tmp;
        const Set& setA = Sets.find(set1)->second;
        const Set& setB = Sets.find(set2)->second;
        std::set_intersection(
            setA.set_.begin(), setA.set_.end(),
            setB.set_.begin(), setB.set_.end(),
            std::inserter(tmp.set_, tmp.set_.begin())
        );
        Sets.insert({ setRes, tmp });
    }
}


