#pragma once

#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP


namespace kumekova
{
    struct DataStruct
    {
        unsigned long long key1;
        std::complex<double> key2;
        std::string key3;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct ComplexDoubleIO
    {
        std::complex<double>& ref;
    };

    struct ULLOCTIO
    {
        unsigned long long& ref;
    };

    struct DoubleIO
    {
        double& num;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct LabelIO
    {
        std::string exp;
    };

    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios<char>& s);
        ~iofmtguard();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::ios::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, ComplexDoubleIO&& dest);
    std::istream& operator>>(std::istream& in, ULLOCTIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second);
}

#endif
