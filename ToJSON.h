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
    class To;

    class Null
    {
    protected:
        static constexpr const char *null{"null"};
    };

    namespace detail
    {
        class To : public Null
        {
        protected:
            template <typename T>
            inline string format_value(const T &input)
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

            inline string format_value(const bool &input);
            inline string format_value(const char &input);
            inline string format_value(const string &input);
            inline string format_value(const ToJSON &input);
            inline string format_value(const ToArray &input);
            inline string format_value(const Null &input);
        };
    }

    class ToArray : public detail::To
    {

    private:
        string array;

        inline string insert_comma()
        {
            return array.empty() ? "" : ",";
        };

    public:
        ToArray();
        ToArray(const unsigned int length);

        template <typename T>
        ToArray &insert(const T &value)
        {
            array += insert_comma() + format_value(value);
            return *this;
        };

        template <typename... T>
        ToArray &insert_multiple(const T &...values)
        {
            array += insert_comma();
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
    };

    inline ToArray::ToArray(const unsigned int length)
    {
        array.reserve(length);
        array = "";
    }

    inline ToArray::ToArray() : array("") {}

    inline bool ToArray::empty() const
    {
        return array.empty();
    }

    inline string ToArray::str() const
    {
        return "[" + array + "]";
    }

    class ToJSON : public detail::To
    {

    private:
        string json;

        inline string insert_key(const string &key)
        {
            return (json.empty() ? "" : ",") + format_value(key) + ":";
        };

    public:
        ToJSON();
        ToJSON(const unsigned int length);

        template <typename... T>
        ToJSON &insert_array(const string &key, const T &...values)
        {
            json += insert_key(key) + "[";
            string array = "";
            for (const auto value : {format_value(values)...})
            {
                array += "," + value;
            }
            json += array.substr(1) + "]";
            return *this;
        };

        ToJSON &insert_array(const string &key);

        template <typename T>
        ToJSON &insert(const string &key, const T &value)
        {
            json += insert_key(key) + format_value(value);
            return *this;
        };

        string str() const;
        bool empty() const;
    };

    inline ToJSON::ToJSON() : json("") {}

    inline ToJSON::ToJSON(const unsigned int length)
    {
        json.reserve(length);
        json = "";
    }

    inline string ToJSON::str() const
    {
        return "{" + json + "}";
    }

    inline bool ToJSON::empty() const
    {
        return json.empty();
    }

    inline ToJSON &ToJSON::insert_array(const string &key)
    {
        json += insert_key(key) + "[]";
        return *this;
    }

    inline string detail::To::format_value(const string &input)
    {
        return "\"" + input + "\"";
    }

    inline string detail::To::format_value(const bool &input)
    {
        return input ? "true" : "false";
    }

    inline string detail::To::format_value(const char &input)
    {
        return format_value(string{input});
    }

    inline string detail::To::format_value(const ToJSON &input)
    {
        return input.str();
    }

    inline string detail::To::format_value(const Null &input)
    {
        return string{input.null};
    }

    inline string detail::To::format_value(const ToArray &input)
    {
        return input.str();
    }

}
#endif