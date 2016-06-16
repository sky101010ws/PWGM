/*PasswdFile文件格式定义
**文件头4个字节，16进制表示为FEEFDEED，紧跟后面是2个字节的short表示记录数；后面内容按流形式存储
**每条记录包含信息为：账号、前缀、明钥、秘钥
**存储格式为按顺序存储，每个信息前增加一个字节的长度，具体信息字符串经过加密进行存储
**
**
**
**
**
**
**
**
**
*/

#pragma once
#include <string>
#include <map>

using namespace std;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

const uint FileHeader = 0xFEEFDEED;
const uint ReadLen = 1024 * 1024;

typedef struct _tagLengthInfo
{
	uchar AccountLen;	//账户信息长度
	uchar PrefixLen;	//前缀信息长度
	uchar PublicLen;	//明钥信息长度
	uchar PrivateLen;	//秘钥信息长度
	ushort RemarkLen;	//备注信息长度
}LengthInfo, *LPLengthInfo;

typedef struct _tagItemInfo
{
	string AccountInfo;	//账户信息
	string PrefixInfo;	//前缀信息
	string PublicInfo;	//明钥信息
	string PrivateInfo;	//秘钥信息
	string RemarkInfo;	//备注信息
}ItemInfo, *LPItemInfo;

typedef map<string /*AccountInfo*/, ItemInfo> MapItemInfo;
typedef MapItemInfo::iterator MapItemInfoI;



class CPasswdFile
{
private:
	wstring m_strPasswdFile;
	MapItemInfo m_mapItemInfo;

	
public:
	CPasswdFile(void);
	~CPasswdFile(void);

	bool IsExistAccount(const string &strAccount);

	bool AddItem(const ItemInfo& item);



	void Load();
	bool Save();


};

