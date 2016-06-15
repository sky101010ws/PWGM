#include "StdAfx.h"
#include "PasswdGen.h"



CPasswdGen::CPasswdGen(void)
{
}


CPasswdGen::~CPasswdGen(void)
{
}

string CPasswdGen::GetPasswd(const string &strKey)
{
	return m_md5.GenMD5(strKey);
}
