#pragma once
#include <string>
#include "MD5Gen.h"

using namespace std;

class CPasswdGen
{
private:
	CMD5Gen m_md5;
public:
	CPasswdGen(void);
	~CPasswdGen(void);

	string GetPasswd(const string &strKey);
};

