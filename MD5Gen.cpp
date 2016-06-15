#include "StdAfx.h"
#include "MD5Gen.h"

#pragma comment(lib, "libeay32.lib")


CMD5Gen::CMD5Gen(void)
{
	memset(m_szMD5, 0, sizeof(m_szMD5[0]) * MD5_DIGEST_LENGTH);
	memset(m_szMD5Trans, 0, sizeof(m_szMD5[0]) * TRANS_LEN);
}


CMD5Gen::~CMD5Gen(void)
{
}

char *CMD5Gen::Trans(unsigned char *)
{
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        sprintf(&(m_szMD5Trans[i * 2]), "%02x", m_szMD5[i]);
    return (m_szMD5Trans);
}

string CMD5Gen::GenMD5(const string &strKey)
{
	EVP_Digest(strKey.c_str(), strKey.length(), m_szMD5, NULL, EVP_md5(), NULL);

	return string(Trans(m_szMD5));
}
