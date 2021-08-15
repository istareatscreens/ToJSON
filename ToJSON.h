#ifndef TOJSON_H
#define TOJSON_H

#include <string>
#include <sstream>
#include <type_traits>

namespace ToJSON
{
    using std::string;

    class ToJSON
    {
    private:
        string json;
        template <typename T>
        string format_value(const T &input)
        {
            std::stringstream stream;
            if (std::is_arithmetic<T>::value)
            {
                stream << input;
            }
            else
            {
                stream << "\"" << input << "\"";
            }
            return stream.str();
        };

        string format_value(const bool &input);
        string format_value(const char &input);
        string format_value(const ToJSON &input);
        string format_value(const string &input);

        inline string add_key(const string &key)
        {
            return ((is_empty()) ? "" : json + ", ") + //check if empty
                   format_value(key) + " : ";
        };

    public:
        ToJSON();
        ToJSON(const unsigned int length);
        template <typename... T>
        ToJSON &addPropertyArray(const string &key, const T &...values)
        {
            json = add_key(key) + "[";
            std::stringstream stream;
            for (const auto value : {format_value(values)...})
            {
                stream << "," << value;
            }
            json += (stream.str().empty() ? "" : stream.str().substr(1)) + "]";
            return *this;
        };

        template <typename T>
        ToJSON &add_property_value(const string &key, const T &value)
        {
            json = add_key(key) + format_value(value);
            return *this;
        };

        ToJSON &add_object(const string &key, const ToJSON &object);
        string to_string() const;
        bool is_empty() const;
    };

    ToJSON::ToJSON(const unsigned int length)
    {
        json.reserve(length);
    }

    ToJSON::ToJSON() : json("") {}

    ToJSON &ToJSON::add_object(const string &key, const ToJSON &object)
    {
        json = add_key(key) + (object.is_empty() ? "{}" : object.to_string());
        return *this;
    }

    string ToJSON::to_string() const
    {
        return "{" + json + "}";
    }

    bool ToJSON::is_empty() const
    {
        return json.empty();
    }

    string ToJSON::format_value(const string &input)
    {
        std::stringstream stream;
        stream << "\"" << input << "\"";
        return stream.str();
    }

    string ToJSON::format_value(const bool &input)
    {
        if (input)
        {
            return "true";
        }
        else
        {
            return "false";
        }
    }

    string ToJSON::format_value(const char &input)
    {
        return format_value(string{input});
    }

    string ToJSON::format_value(const ToJSON &input)
    {
        return format_value(input.to_string());
    }
}
#endif