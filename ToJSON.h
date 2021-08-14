#include <string>
#include <sstream>
#include <type_traits>

#ifndef TOJSON_H
#define TOJSON_H

using std::string;

class ToJSON
{
private:
    string json;
    template<typename T>
    string formatValue(const T &input)
    {
        std::stringstream stream;
        if(std::is_arithmetic<T>::value)
        {
            stream<<input;
        }
        else
        {
            stream<<"\""<<input<<"\"";
        }
        return stream.str();
    };

    string formatValue(const bool &input);
    string formatValue(const char &input);
    string formatValue(const ToJSON &input);
    string formatValue(const string &input);


    inline string addKey(const string &key)
    {
        return ((isEmpty()) ? "" : json + ", ") + //check if empty
                formatValue(key) + " : ";
    };

public:
    ToJSON();
    ToJSON(const unsigned int length);
    template<typename ...T>
    ToJSON &addPropertyArray(const string &key, const T& ... values)
    {
        json = addKey(key) + "[";
        std::stringstream stream;
        for(const auto value: {formatValue(values)...})
        {
            stream<<","<<value;
        }
        json += (stream.str().empty()? "" : stream.str().substr(1)) + "]";
        return *this;
    };

    template<typename T>
    ToJSON &addPropertyValue(const string &key, const T &value)
    {
        json = addKey(key) + formatValue(value);
        return *this;
    };

    ToJSON &addObject(const string &key, const ToJSON &object);
    string getJSON() const;
    bool isEmpty() const;
};

#endif
