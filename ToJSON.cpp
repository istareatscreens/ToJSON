#include "ToJSON.h"

ToJSON::ToJSON(const unsigned int length)
{
    json.reserve(length);
}

ToJSON::ToJSON():json(""){}

ToJSON &ToJSON::addObject(const string &key, const ToJSON &object)
{
    json = addKey(key) + (object.isEmpty()? "{}": object.getJSON());
    return *this;
}

string ToJSON::getJSON() const
{
    return "{" + json + "}";
}

bool ToJSON::isEmpty() const
{
    return json.empty();
}

string ToJSON::formatValue(const string &input)
{
    std::stringstream stream;
    stream<<"\""<<input<<"\"";
    return stream.str();
}

string ToJSON::formatValue(const bool &input)
{
    if(input)
    {
        return "true";
    }
    else
    {
        return "false";
    }
}

string ToJSON::formatValue(const char &input)
{
    return formatValue(string{input});
}

string ToJSON::formatValue(const ToJSON &input)
{
    return formatValue(input.getJSON());
}
