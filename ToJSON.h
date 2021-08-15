#ifndef TOJSON_H
#define TOJSON_H
#include <string>
#include <sstream>
#include <type_traits>

namespace ToJSON
{
    using std::string;

    class IToString
    {
    public:
        virtual string to_string() const = 0;
    };

    class ToJSON : public IToString
    {

    private:
        string json;

        inline string add_key(const string &key)
        {
            return (json.empty() ? "" : ",") + format_value(key) + ":";
        };

    protected:
        template <typename T>
        string format_value(const T &input)
        {
            std::stringstream stream;
            if (std::is_arithmetic<T>::value)
            {
                stream << input;
                return stream.str();
            }
            return "\"" + input + "\"";
        };

        string format_value(const bool &input);
        string format_value(const char &input);
        string format_value(const string &input);
        string format_value(const IToString &input);

    public:
        ToJSON();
        ToJSON(const unsigned int length);

        template <typename... T>
        ToJSON &add_array(const string &key, const T &...values)
        {
            json += add_key(key) + "[";
            string array = "";
            for (const auto value : {format_value(values)...})
            {
                array += "," + value;
            }
            json += (array.empty() ? "" : array.substr(1)) + "]";
            return *this;
        };

        template <typename T>
        ToJSON &add(const string &key, const T &value)
        {
            json += add_key(key) + format_value(value);
            return *this;
        };

        ToJSON &add_object(const string &key, const ToJSON &object);
        string to_string() const override;
        bool empty() const;
    };

    ToJSON::ToJSON() : json("") {}

    ToJSON::ToJSON(const unsigned int length)
    {
        json.reserve(length);
        json = "";
    }

    ToJSON &ToJSON::add_object(const string &key, const ToJSON &object)
    {
        json += add_key(key) + object.to_string();
        return *this;
    }

    string ToJSON::to_string() const
    {
        return "{" + json + "}";
    }

    bool ToJSON::empty() const
    {
        return json.empty();
    }

    string ToJSON::format_value(const string &input)
    {
        return "\"" + input + "\"";
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

    string ToJSON::format_value(const IToString &input)
    {
        return input.to_string();
    }

    class ToArray : public IToString
    {
    private:
        string array;

        inline string add_comma()
        {
            return array.empty() ? "" : ",";
        };

    public:
        ToArray();
        ToArray(const unsigned int length);

        template <typename T>
        ToArray &add(const T &value)
        {
            array += add_comma() + format_value(value);
            return *this;
        };

        template <typename... T>
        ToArray &add_multiple(const T &...values)
        {
            array += add_comma();
            string concat = "";
            for (const auto value : {ToJSON::format_value(values)...})
            {
                concat += "," + value;
            }
            add(concat.substr(1));
            return *this;
        };

        bool empty() const;
        string to_string() const override;

        friend class ToJSON;
    };

    ToArray::ToArray(const unsigned int length)
    {
        array.reserve(length);
        array = "";
    }

    ToArray::ToArray() : array("") {}

    bool ToArray::empty() const
    {
        return array.empty();
    }

    string ToArray::to_string() const
    {
        return "[" + array + "]";
    }
}
#endif