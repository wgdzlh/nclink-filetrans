#ifndef __JDECODE_H__
#define __JDECODE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void * NJObject;

typedef enum NJType {
	NJT_Null,
	NJT_Boolean,
	NJT_Int,
	NJT_UInt,
	NJT_Float,
	NJT_Binary,
	NJT_String,
	NJT_Array,
	NJT_Object,
	NJT_Discard,
} NJType;

/*
===============================================================================
Decodes an input text octet stream into a JSON object structure
===============================================================================
*/
NJObject NJDecode(const char *input);

void NJFree(NJObject *obj);

/*
===============================================================================
See NJType enum for possible return values
===============================================================================
*/
NJType NJGetType(const NJObject obj);

/*
===============================================================================
Unpacks an Object by matching the key name with the requested format

Each key name needs to be matched by the character in the format string
representing the desired type of the value for that key
B - Boolean
N - Numeric
S - String
A - Array
O - Object
U - Unknown/any

Use lower case to accept JSON Null in place of the expected value.

Arguments:
objObj     - The object to unpack (JSON Object)
keys       - Number of keys to match. Keys can not exceed 64.
format     - Specified the expected types for the key value.
keyNames   - An array of key names
...        - Output value objects (as NJObject *)

Return value:
Returns number of key pairs matched or -1 on error
===============================================================================
*/
int NJObjectUnpack(const NJObject objObj, const char *format, const char *keyNames[], ...);

/*
===============================================================================
Returns the value of a double, long or long long value as a double.
If value is not any of these 0.0 is returned.
===============================================================================
*/
double NJNumericFloat(const NJObject obj);

/*
===============================================================================
Returns the value of a double, long or long long value as an integer.
If value is not any of these types 0 is returned.

Truncation may arrise from word sizes and the presence of decimals when
converting doubles to integers.
===============================================================================
*/
int NJNumericInt(const NJObject obj);
// long long NJNumericLongLong(const NJObject obj);

/*
===============================================================================
Returns the value of a string value as a wide character string pointer. Caller must NOT free returned pointer.
cchOutBuffer contains the character length of the returned string.

If the value is not a string an empty string is returned.
===============================================================================
*/
void NJReadString(char **output, const NJObject obj);


#ifdef __cplusplus
}

#endif

#endif
