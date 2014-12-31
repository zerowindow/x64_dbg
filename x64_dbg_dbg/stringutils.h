#ifndef _STRINGUTILS_H
#define _STRINGUTILS_H

#include <string>
#include <vector>

typedef std::string String;
typedef std::wstring WString;
typedef std::vector<String> StringList;
typedef std::vector<WString> WStringList;

class StringUtils
{
public:
    static StringList Split(const String & s, char delim, std::vector<String> & elems);
    static StringList Split(const String & s, char delim);
    static String Escape(const String & s);
    static String Trim(const String & s);
    static String TrimLeft(const String & s);
    static String TrimRight(const String & s);
    static String Utf16ToUtf8(const WString & wstr);
    static String Utf16ToUtf8(const wchar_t* wstr);
    static WString Utf8ToUtf16(const String & str);
    static WString Utf8ToUtf16(const char* str);

private:
    static const String WHITESPACE;
};

#endif //_STRINGUTILS_H