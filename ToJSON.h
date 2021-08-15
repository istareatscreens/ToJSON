#ifndef TOJSON_H
#define TOJSON_H
#include <string>
#include <sstream>
#include <type_traits>

namespace ToJSON
{
    using std::string;
    class ToJSON;
    class ToArray;

    namespace detail
    {
        class To
        {
        protected:
            template <typename T>
            static string format_value(const T &input)
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

            static string format_value(const bool &input);
            static string format_value(const char &input);
            static string format_value(const string &input);
            static string format_value(const ToJSON &input);
            static string format_value(const ToArray &input);
        };
    }

    class ToArray : public detail::To
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
            for (const auto value : {format_value(values)...})
            {
                concat += "," + value;
            }
            array += array.empty() ? concat.substr(1) : concat;
            return *this;
        };

        bool empty() const;
        string str() const;

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

    string ToArray::str() const
    {
        return "[" + array + "]";
    }

    class ToJSON : public detail::To
    {

    private:
        string json;

        inline string add_key(const string &key)
        {
            return (json.empty() ? "" : ",") + format_value(key) + ":";
        };

    protected:
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
            json += array.substr(1) + "]";
            return *this;
        };

        ToJSON &add_array(const string &key);

        template <typename T>
        ToJSON &add(const string &key, const T &value)
        {
            json += add_key(key) + format_value(value);
            return *this;
        };

        string str() const;
        bool empty() const;
    };

    ToJSON::ToJSON() : json("") {}

    ToJSON::ToJSON(const unsigned int length)
    {
        json.reserve(length);
        json = "";
    }

    string ToJSON::str() const
    {
        return "{" + json + "}";
    }

    bool ToJSON::empty() const
    {
        return json.empty();
    }

    ToJSON &ToJSON::add_array(const string &key)
    {
        json += add_key(key) + "[]";
        return *this;
    }

    string detail::To::format_value(const string &input)
    {
        return "\"" + input + "\"";
    }

    string detail::To::format_value(const bool &input)
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

    string detail::To::format_value(const char &input)
    {
        return format_value(string{input});
    }

    string detail::To::format_value(const ToJSON &input)
    {
        return input.str();
    }

    string detail::To::format_value(const ToArray &input)
    {
        return input.str();
    }

}
#endif