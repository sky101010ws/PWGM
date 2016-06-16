#include "StdAfx.h"
#include "PasswdFile.h"
#include <fstream>


CPasswdFile::CPasswdFile(void)
{
	Load();
}


CPasswdFile::~CPasswdFile(void)
{
}

void CPasswdFile::Load()
{
	wstring filename = L"D:/deploy/passwd.dat";
	ifstream file(filename);
	if(!file)
	{
		return ;
	}

	do
	{
		uint nFileHeader(0);
		ushort nItemCount(0);

		file.seekg(0, ios_base::end);
		int nFileSize = file.tellg();

		//check file size
		if(nFileSize <= sizeof(nFileHeader) + sizeof(nItemCount))
		{
			break;
		}

		//check file header info and item count
		file.seekg(0, ios::beg);
		file.read((char *)&nFileHeader, sizeof(nFileHeader));
		file.read((char *)&nItemCount, sizeof(nItemCount));
		int nPos = file.tellg();

		if(nFileHeader != FileHeader || 0 == nItemCount)
		{
			break;
		}

		LengthInfo info;
		ItemInfo item;

		char *buf = new char[ReadLen];
		int pos(0);
		do
		{
			file.read(buf + pos, ReadLen - pos);
			nFileSize -= (ReadLen - pos);
			memcpy(&info, buf, sizeof(LengthInfo));
			pos = sizeof(LengthInfo);
			item.AccountInfo.assign(buf + pos, info.AccountLen);
			pos += info.AccountLen;

			item.PrefixInfo.assign(buf + pos, info.PrefixLen);
			pos += info.PrefixLen;

			item.PublicInfo.assign(buf + pos, info.PublicLen);
			pos += info.PublicLen;

			item.PrivateInfo.assign(buf + pos, info.PrivateLen);
			pos += info.PrivateLen;

			item.RemarkInfo.assign(buf + pos, info.RemarkLen);
			pos += info.RemarkLen;



		}while(nFileSize > 0);

	}while(false);

	file.close();

	




}

bool CPasswdFile::Save()
{
	return true;
}

bool CPasswdFile::IsExistAccount(const string &strAccount)
{
	if(m_mapItemInfo.find(strAccount) == m_mapItemInfo.end())
	{
		return false;
	}
	return true;
}

bool CPasswdFile::AddItem(const ItemInfo& item)
{
	m_mapItemInfo[item.AccountInfo] = item;
	wstring filename = L"D:/deploy/passwd.dat";
	ofstream file(filename, ios_base::ate | ios::binary);

	if(!file)
	{
		return false;
	}
	ushort nItemCount = m_mapItemInfo.size();
	file.write((char *)&FileHeader, sizeof(FileHeader));
	file.write((char *)&nItemCount, sizeof(nItemCount));
	
	LengthInfo lenInfo;
	MapItemInfoI it = m_mapItemInfo.begin();
	while(it != m_mapItemInfo.end())
	{
		lenInfo.AccountLen = it->second.AccountInfo.size();
		lenInfo.PrefixLen = it->second.PrefixInfo.size();
		lenInfo.PublicLen = it->second.PublicInfo.size();
		lenInfo.PrivateLen = it->second.PrivateInfo.size();
		lenInfo.RemarkLen = it->second.RemarkInfo.size();

		//write len info
		file.write((char *)&lenInfo.AccountLen,	sizeof(lenInfo.AccountLen));
		file.write((char *)&lenInfo.PrefixLen,	sizeof(lenInfo.PrefixLen));
		file.write((char *)&lenInfo.PublicLen,	sizeof(lenInfo.PublicLen));
		file.write((char *)&lenInfo.PrivateLen,	sizeof(lenInfo.PrivateLen));
		file.write((char *)&lenInfo.RemarkLen,	sizeof(lenInfo.RemarkLen));

		//write content
		ItemInfo &item = it->second;
		file.write(item.AccountInfo.c_str(),	lenInfo.AccountLen);
		file.write(item.PrefixInfo.c_str(),		lenInfo.PrefixLen);
		file.write(item.PublicInfo.c_str(),		lenInfo.PublicLen);
		file.write(item.PrivateInfo.c_str(),	lenInfo.PrivateLen);
		file.write(item.RemarkInfo.c_str(),		lenInfo.RemarkLen);


		//file<<lenInfo.AccountLen<<lenInfo.PrefixLen<<lenInfo.PublicLen<<lenInfo.PrivateLen<<lenInfo.RemarkLen;
		//file<<it->second.AccountInfo<<it->second.PrefixInfo<<it->second.PublicInfo<<it->second.PrivateInfo<<it->second.RemarkInfo;

		++it;
	}

	file.close();
	return true;
}

