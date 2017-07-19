// CharacterSets.h: interface for the CChineseCode class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

class CharacterSets
{
   public:
       static void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // NOT TESTED把UTF-8转换成Unicode
       static void UnicodeToUTF_8(char* pOut,wchar_t* pText);  // Unicode 转换成UTF-8
       static void UnicodeToGB2312(char* pOut,wchar_t uData);  // NOT TESTED把Unicode 转换成 GB2312 
       static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// NOT TESTEDGB2312 转换成　Unicode
       static void GB2312ToUTF_8(std::string& pOut,char *pText, int pLen);// NOT TESTEDGB2312 转为 UTF-8
       static void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);// NOT TESTEDUTF-8 转为 GB2312

       // TODO: This is Windows code page. Shall be abstracted in OSAbstraction layer.
       static const unsigned int CP_GB2312 = 936;
};

