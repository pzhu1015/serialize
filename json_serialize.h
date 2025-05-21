#pragma once
#include <string>
#include <vector>
#include <list>
#include <set>
#include <memory>
#include <iostream>
#include <picojson.h>
#include "reflection.h"
#define JSON_PRETY true

#define JSON_SERIALIZE_PTR(name, nick) JsonSerialize::Serialize(entity->name, nick, json);
#define JSON_DESERIALIZE_PTR(name, nick) JsonSerialize::DeSerialize(entity->name, nick, json); 

#define JSON_SERIALIZE(name, nick) JsonSerialize::Serialize(entity.name, nick, json);
#define JSON_DESERIALIZE(name, nick) JsonSerialize::DeSerialize(entity.name, nick, json); 

#define JSON_SERIALIZE_ITEM(x) JSON_SERIALIZE(EXTRACT_MEMBER(x), EXTRACT_NICK(x))
#define JSON_DESERIALIZE_ITEM(x) JSON_DESERIALIZE(EXTRACT_MEMBER(x), EXTRACT_NICK(x))

#define JSON_SERIALIZE_ITEM_PTR(x) JSON_SERIALIZE_PTR(EXTRACT_MEMBER(x), EXTRACT_NICK(x))
#define JSON_DESERIALIZE_ITEM_PTR(x) JSON_DESERIALIZE_PTR(EXTRACT_MEMBER(x), EXTRACT_NICK(x))

#define REGIST_CLASS_JSON(T) \
namespace serialize \
{\
    template<>\
	class JsonSerializer<T>\
	{\
	public:\
		static std::string ToString(const std::shared_ptr<T> &entity) \
		{\
            return entity->ToString();\
        }\
		static std::string ToString(const T &entity) \
		{\
            return entity.ToString();\
		}\
		static Json ToJson(const std::shared_ptr<T> &entity) \
		{\
            return Json(entity->ToString());\
		}\
		static Json ToJson(const T &entity) \
		{\
            return Json(entity.ToString());\
		}\
		static std::shared_ptr<T> FromStringPtr(const std::string &str) \
		{\
		    return std::make_shared<T>(str);\
		}\
		static T FromString(const std::string &str) \
		{\
		    return T(str);\
		}\
		static std::shared_ptr<T> FromJsonPtr(const Json &json) \
		{\
		    return std::make_shared<T>(json.get<std::string>());\
		}\
		static T FromJson(const Json &json) \
		{\
		    return T(json.get<std::string>());\
		}\
	};\
}

#define REGIST_MEMBER_JSON(T, ...) \
namespace serialize \
{\
	template<>\
	class JsonSerializer<T>\
	{\
	public:\
		static std::string ToString(const std::shared_ptr<T> &entity) \
		{\
            Json json;\
            json.set<picojson::object>(picojson::object());\
            FOREACH(JSON_SERIALIZE_ITEM_PTR, __VA_ARGS__);\
            return json.serialize(JSON_PRETY);\
        }\
		static std::string ToString(const T &entity) \
		{\
            Json json;\
            json.set<picojson::object>(picojson::object());\
            FOREACH(JSON_SERIALIZE_ITEM, __VA_ARGS__);\
            return json.serialize(JSON_PRETY);\
		}\
		static Json ToJson(const std::shared_ptr<T> &entity) \
		{\
            Json json;\
            json.set<picojson::object>(picojson::object());\
            FOREACH(JSON_SERIALIZE_ITEM_PTR, __VA_ARGS__);\
            return json;\
		}\
		static Json ToJson(const T &entity) \
		{\
            Json json;\
            json.set<picojson::object>(picojson::object());\
            FOREACH(JSON_SERIALIZE_ITEM, __VA_ARGS__);\
            return json;\
		}\
		static std::shared_ptr<T> FromStringPtr(const std::string &str) \
		{\
            auto entity = std::make_shared<T>();\
            Json json;\
            auto err = picojson::parse(json, str);\
            if (!err.empty()) return entity;\
            FOREACH(JSON_DESERIALIZE_ITEM_PTR, __VA_ARGS__);\
            return entity;\
		}\
		static T FromString(const std::string &str) \
		{\
            T entity;\
            Json json; \
            auto err = picojson::parse(json, str); \
            if (!err.empty()) return entity; \
            FOREACH(JSON_DESERIALIZE_ITEM, __VA_ARGS__);\
            return entity;\
		}\
		static std::shared_ptr<T> FromJsonPtr(const Json &json) \
		{\
            auto entity = std::make_shared<T>();\
            FOREACH(JSON_DESERIALIZE_ITEM_PTR, __VA_ARGS__);\
            return entity;\
		}\
		static T FromJson(const Json &json) \
        {\
            T entity;\
            FOREACH(JSON_DESERIALIZE_ITEM, __VA_ARGS__);\
            return entity;\
		}\
	};\
}

namespace serialize
{
typedef picojson::value Json;
template<class T>
class JsonSerializer
{
public:
    static std::string ToString(const std::shared_ptr<T> &entity) 
    {
        return "";
    }
	static std::string ToString(const T &entity) 
    {
        return std::string();
    }
    static Json ToJson(const std::shared_ptr<T> &entity) 
    {
        return Json();
    }
    static Json ToJson(const T &entity) 
    {
        return Json();
    }

    static std::shared_ptr<T> FromStringPtr(const std::string &str)
    {
        return nullptr;
    }

    static T FromString(const std::string &str)
    {
        return T();
    }

    static std::shared_ptr<T> FromJsonPtr(const Json &json) 
    {
        return nullptr;
    }

    static T FromJson(const Json &json) 
    {
        return T();
    }
};

class JsonSerialize
{
public:
    static void Serialize(const std::string &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json(value);
        }
    }

    static void Serialize(bool value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json(value);
        }
    }
    static void Serialize(float value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json(value);
        }
    }

    static void Serialize(double value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json(value);
        }
    }

    static void Serialize(int8_t value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json((double)value);
        }
    }

    static void Serialize(int16_t value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json((double)value);
        }
    }

    static void Serialize(int32_t value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json((double)value);
        }
    }

    static void Serialize(int64_t value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json(value);
        }
    }

    static void Serialize(uint8_t value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json((double)value);
        }
    }

    static void Serialize(uint16_t value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json((double)value);
        }
    }

    static void Serialize(uint32_t value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json((double)value);
        }
    }

    static void Serialize(uint64_t value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            json.get<picojson::object>()[name] = Json((int64_t)value);
        }
    }

    template<typename T>
    static void Serialize(const std::shared_ptr<T> &value, const std::string &name, Json &json)
    {
        if (value != nullptr && !json.is<picojson::null>() && (json.is<picojson::object>() || json.is<std::string>()))
        {
            json.get<picojson::object>()[name] = JsonSerializer<T>::ToJson(value);
        }
    }

    //非枚举类型
    template<typename T>
    typename std::enable_if<!std::is_enum<T>::value, void>::type
    static Serialize(const T &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && (json.is<picojson::object>() || json.is<std::string>()))
        {
            json.get<picojson::object>()[name] = JsonSerializer<T>::ToJson(value);
        }
    }

    //枚举类型
    template<typename T>
    typename std::enable_if<std::is_enum<T>::value, void>::type
    static Serialize(const T &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>())
        {
            json.get<picojson::object>()[name] = Json(static_cast<double>(value));
        }
    }

    static void Serialize(const std::vector<std::string> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<float> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);

            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<double> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<int8_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);

            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<int16_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<int32_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<int64_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<uint8_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<uint16_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<uint32_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::vector<uint64_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((int64_t)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    template<typename T>
    static void Serialize(const std::vector<std::shared_ptr<T>> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value)
            {
                array.emplace_back(JsonSerializer<T>::ToJson(v));
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    template<typename T>
    static void Serialize(const std::vector<T> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value)
            {
                array.emplace_back(JsonSerializer<T>::ToJson(v));
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<std::string> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<float> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<double> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<int8_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<int16_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value)
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<int32_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value)
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<int64_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<uint8_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<uint16_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<uint32_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::list<uint64_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((int64_t)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }


    template<typename T>
    static void Serialize(const std::list<std::shared_ptr<T>> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value)
            {
                array.emplace_back(JsonSerializer<T>::ToJson(v));
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    template<typename T>
    static void Serialize(const std::list<T> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value)
            {
                array.emplace_back(JsonSerializer<T>::ToJson(v));
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<std::string> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<float> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<double> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<int8_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<int16_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<int32_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<int64_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back(v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<uint8_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<uint16_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<uint32_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((double)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void Serialize(const std::set<uint64_t> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value) 
            {
                array.emplace_back((int64_t)v);
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }


    template<typename T>
    static void Serialize(const std::set<std::shared_ptr<T>> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value)
            {
                array.emplace_back(JsonSerializer<T>::ToJson(v));
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    template<typename T>
    static void Serialize(const std::set<T> &value, const std::string &name, Json &json)
    {
        if (!json.is<picojson::null>() && json.is<picojson::object>())
        {
            picojson::array array;
            for (const auto &v : value)
            {
                array.emplace_back(JsonSerializer<T>::ToJson(v));
            }
            json.get<picojson::object>()[name] = Json(array);
        }
    }

    static void DeSerialize(std::string &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<std::string>())
        {
            value = v.get<std::string>();
        }
    }

    static void DeSerialize(bool &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<bool>())
        {
            value = v.get<bool>();
        }
    }

    static void DeSerialize(float &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (float)v.get<double>();
        }
    }

    static void DeSerialize(double &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = v.get<double>();
        }
    }

    static void DeSerialize(int8_t &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (int8_t)v.get<double>();
        }
    }

    static void DeSerialize(int16_t &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (int16_t)v.get<double>();
        }
    }

    static void DeSerialize(int32_t &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (int32_t)v.get<double>();
        }
    }

    static void DeSerialize(int64_t &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (int64_t)v.get<int64_t>();
        }
    }

    static void DeSerialize(uint8_t &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (uint8_t)v.get<double>();
        }
    }

    static void DeSerialize(uint16_t &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (uint16_t)v.get<double>();
        }
    }

    static void DeSerialize(uint32_t &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (uint32_t)v.get<double>();
        }
    }

    static void DeSerialize(uint64_t &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = (uint64_t)v.get<int64_t>();
        }
    }


    template<typename T>
    static void DeSerialize(std::shared_ptr<T> &value, const std::string &name, const Json &json) 
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && (v.is<picojson::object>() || v.is<std::string>()))
        {
            value = JsonSerializer<T>::FromJsonPtr(v);
        }
    }

    template<typename T>
    typename std::enable_if<!std::is_enum<T>::value, void>::type
    static DeSerialize(T &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && (v.is<picojson::object>() || v.is<std::string>()))
        {
            value = JsonSerializer<T>::FromJson(v);
        }
    }

    template<typename T>
    typename std::enable_if<std::is_enum<T>::value, void>::type
    static DeSerialize(T &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<double>())
        {
            value = static_cast<T>(v.get<double>());
        }
    }

    static void DeSerialize(std::vector<std::string> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<std::string>())
                {
                    value.emplace_back(item.get<std::string>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<float> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((float)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<double> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back(item.get<double>());
                }
            }
        }

    }

    static void DeSerialize(std::vector<int8_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((int8_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<int16_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((int16_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<int32_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((int32_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<int64_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back(item.get<int64_t>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<uint8_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((uint8_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<uint16_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((uint16_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<uint32_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((uint32_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::vector<uint64_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((uint64_t)item.get<int64_t>());
                }
            }
        }
    }


    template<typename T>
    static void DeSerialize(std::vector<std::shared_ptr<T>> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                value.emplace_back(JsonSerializer<T>::FromJsonPtr(item));
            }
        }
    }

    template<typename T>
    static void DeSerialize(std::vector<T> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                value.emplace_back(JsonSerializer<T>::FromJson(item));
            }
        }
    }

    static void DeSerialize(std::list<std::string> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<std::string>())
                {
                    value.emplace_back(item.get<std::string>());
                }
            }
        }
    }

    static void DeSerialize(std::list<float> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((float)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::list<double> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back(item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::list<int8_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((int8_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::list<int16_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((int16_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::list<int32_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((int32_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::list<int64_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back(item.get<int64_t>());
                }
            }
        }
    }

    static void DeSerialize(std::list<uint8_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((uint8_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::list<uint16_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((uint16_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::list<uint32_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((uint32_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::list<uint64_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace_back((uint64_t)item.get<int64_t>());
                }
            }
        }
    }


    template<typename T>
    static void DeSerialize(std::list<std::shared_ptr<T>> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                value.emplace(JsonSerializer<T>::FromJsonPtr(item));
            }
        }
    }

    template<typename T>
    static void DeSerialize(std::list<T> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                value.emplace(JsonSerializer<T>::FromJson(item));
            }
        }
    }

    static void DeSerialize(std::set<std::string> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<std::string>())
                {
                    value.emplace(item.get<std::string>());
                }
            }
        }
    }

    static void DeSerialize(std::set<float> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace((float)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::set<double> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace(item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::set<int8_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace((int8_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::set<int16_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace((int16_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::set<int32_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace((int32_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::set<int64_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace(item.get<int64_t>());
                }
            }
        }
    }

    static void DeSerialize(std::set<uint8_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace((uint8_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::set<uint16_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace((uint16_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::set<uint32_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace((uint32_t)item.get<double>());
                }
            }
        }
    }

    static void DeSerialize(std::set<uint64_t> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                if (!item.is<picojson::null>() && item.is<double>())
                {
                    value.emplace((uint64_t)item.get<int64_t>());
                }
            }
        }
    }


    template<typename T>
    static void DeSerialize(std::set<std::shared_ptr<T>> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                value.emplace(JsonSerializer<T>::FromJsonPtr(item));
            }
        }
    }

    template<typename T>
    static void DeSerialize(std::set<T> &value, const std::string &name, const Json &json)
    {
        const Json &v = json.get(name);
        if (!v.is<picojson::null>() && v.is<picojson::array>())
        {
            const auto &array = v.get<picojson::array>();
            for (const auto &item : array)
            {
                value.emplace(JsonSerializer<T>::FromJson(item));
            }
        }
    }
};
}
