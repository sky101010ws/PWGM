/*PasswdFile�ļ���ʽ����
**�ļ�ͷ4���ֽڣ�16���Ʊ�ʾΪFEEFDEED������������2���ֽڵ�short��ʾ��¼�����������ݰ�����ʽ�洢
**ÿ����¼������ϢΪ���˺š�ǰ׺����Կ����Կ
**�洢��ʽΪ��˳��洢��ÿ����Ϣǰ����һ���ֽڵĳ��ȣ�������Ϣ�ַ����������ܽ��д洢
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
	uchar AccountLen;	//�˻���Ϣ����
	uchar PrefixLen;	//ǰ׺��Ϣ����
	uchar PublicLen;	//��Կ��Ϣ����
	uchar PrivateLen;	//��Կ��Ϣ����
	ushort RemarkLen;	//��ע��Ϣ����
}LengthInfo, *LPLengthInfo;

typedef struct _tagItemInfo
{
	string AccountInfo;	//�˻���Ϣ
	string PrefixInfo;	//ǰ׺��Ϣ
	string PublicInfo;	//��Կ��Ϣ
	string PrivateInfo;	//��Կ��Ϣ
	string RemarkInfo;	//��ע��Ϣ
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

