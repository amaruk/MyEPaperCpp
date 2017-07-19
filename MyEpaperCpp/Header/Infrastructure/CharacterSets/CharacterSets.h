// CharacterSets.h: interface for the CChineseCode class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

class CharacterSets
{
   public:
       static void UTF_8ToUnicode(wchar_t* pOut,char *pText);  // NOT TESTED��UTF-8ת����Unicode
       static void UnicodeToUTF_8(char* pOut,wchar_t* pText);  // Unicode ת����UTF-8
       static void UnicodeToGB2312(char* pOut,wchar_t uData);  // NOT TESTED��Unicode ת���� GB2312 
       static void Gb2312ToUnicode(wchar_t* pOut,char *gbBuffer);// NOT TESTEDGB2312 ת���ɡ�Unicode
       static void GB2312ToUTF_8(std::string& pOut,char *pText, int pLen);// NOT TESTEDGB2312 תΪ UTF-8
       static void UTF_8ToGB2312(std::string &pOut, char *pText, int pLen);// NOT TESTEDUTF-8 תΪ GB2312

       // TODO: This is Windows code page. Shall be abstracted in OSAbstraction layer.
       static const unsigned int CP_GB2312 = 936;
};

