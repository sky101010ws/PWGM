#pragma once
#include <string>
#include "openssl/evp.h"
#include "openssl/md5.h"

using namespace std;
const int TRANS_LEN = 40;

class CMD5Gen
{
private:
	unsigned char m_szMD5[MD5_DIGEST_LENGTH];
	char m_szMD5Trans[TRANS_LEN];

	char *Trans(unsigned char *);

public:
	CMD5Gen(void);
	~CMD5Gen(void);

	string GenMD5(const string &strKey);
};

