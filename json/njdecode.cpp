
#include <iostream>
#include <string>
#include <map>
#include <cstdarg>
#include "nlohmann/json.hpp"

#include "njdecode.h"

#ifdef _WIN32
#define strdup _strdup
#endif


using json_t = nlohmann::json;
using value_t = json_t::value_t;


static std::map<value_t, NJType> VALUE_TYPE_TRANS = {
    {value_t::array, NJT_Array},
    {value_t::binary, NJT_Binary},
    {value_t::boolean, NJT_Boolean},
    {value_t::number_integer, NJT_Int},
    {value_t::number_unsigned, NJT_UInt},
    {value_t::number_float, NJT_Float},
    {value_t::string, NJT_String},
    {value_t::object, NJT_Object},
    {value_t::null, NJT_Null},
    {value_t::object, NJT_Discard},
};


static std::map<NJType, char> TYPE_TO_CHAR = {
    {NJT_Array, 'A'},
    {NJT_Binary, 'Y'},
    {NJT_Boolean, 'B'},
    {NJT_Int, 'N'},
    {NJT_UInt, 'N'},
    {NJT_Float, 'N'},
    {NJT_String, 'S'},
    {NJT_Object, 'O'},
    {NJT_Null, 'L'},
    {NJT_Discard, 'D'},
};


NJObject NJDecode(const char *input)
{
    const json_t &ret = json_t::parse(input, nullptr, false);
    if (value_t::discarded == ret) {
        return nullptr;
    }
    return new json_t(ret);
}


void NJFree(NJObject *obj)
{
	if (nullptr != *obj) {
		delete (json_t *)*obj;
		*obj = nullptr;
	}
}


NJType NJGetType(const NJObject obj)
{
    const json_t &jo = *(json_t *)obj;
    return VALUE_TYPE_TRANS[jo.type()];
}


static bool checkType(char tc, const NJObject obj)
{
	bool ret = false;

	switch (tc)
	{
	case 'u':
	case 'U':
		ret = true;
		break;
	default:
		NJType type = NJGetType(obj);
		switch (type)
		{
		case NJT_Null:
			ret = (tc >= 'a' && tc <= 'z');
			break;
		default:
			ret = (TYPE_TO_CHAR[type] == tc);
			break;
		}
		break;
	}

	return ret;
}


double NJNumericFloat(const NJObject obj)
{
	if (checkType('N', obj))
	{
		return ((json_t *)obj)->get<double>();
	}
	return .0;
}


int NJNumericInt(const NJObject obj)
{
	if (NJGetType(obj) == NJT_Int)
	{
		return ((json_t *)obj)->get<int>();
	}
	return 0;
}


unsigned int NJNumericUnsignedInt(const NJObject obj)
{
	if (NJGetType(obj) == NJT_UInt)
	{
		return ((json_t *)obj)->get<unsigned int>();
	}
	return 0;
}


void NJReadString(char **output, const NJObject obj)
{
	if (NJGetType(obj) == NJT_String)
	{
		const auto &jo = ((json_t *)obj)->get<std::string>();
		// std::cout << jo << std::endl;
		*output = strdup(jo.c_str());
	} else
	{
		*output = strdup("");
	}
}


int NJObjectUnpack(const NJObject objObj, const char *format, const char *keyNames[], ...)
{
    const json_t &jo = *(json_t *)objObj;
	if (!jo.is_object()) {
		return 0;
	}

	int found = 0;
	int keys = strlen(format);
	if (keys > 64)
	{
		return -1;
	}

	va_list args;
	NJObject *outValue;

	va_start(args, keyNames);
	for (int ki = 0; ki < keys; ki++)
	{
		const char *kn = keyNames[ki];
		outValue = va_arg(args, NJObject *);
		if (nullptr != kn && nullptr != outValue)
		{
			const auto &it = jo.find(kn);
			if (jo.end() != it)
			{
				const NJObject v = (NJObject)&it.value();
				if (checkType(format[ki], v))
				{
					*outValue = v;
					found++;
				}
			}
		}
	}
	va_end(args);

	return found;
}
