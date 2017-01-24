#pragma once
#include "windows.h"
#include "CommonDefine.h"

void GetItemDef()
{
	char strPathName[MAX_BUFF];
	struct ItemDef TmpItemDef;
	int ret = 0;

	sprintf(strPathName, "%s%s", CONFIG_FILE_PATH, ITEM_H);

	string szLine = "";
	string strGap = " ";

	//����ļ��Ƿ����
	DWORD dwRe = GetFileAttributes(strPathName);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else
	{
		
		return;
	}

	LItemDef.RemoveAll();

	//���ļ�
	CStdioFile StdFile;
	StdFile.Open(strPathName, CFile::modeRead | CFile::shareDenyNone);

	//���ж�ȡ�ַ���
	while (StdFile.ReadString(szLine))
	{
		strResult.RemoveAll();
		szLine.Replace('\t', ' ');
		int nPos = szLine.Find(strGap);
		CString strLeft = _T("");
		while (0 <= nPos)
		{
			strLeft = szLine.Left(nPos);
			if (!strLeft.IsEmpty())
				strResult.Add(strLeft);

			szLine = szLine.Right(szLine.GetLength() - nPos - 1);
			nPos = szLine.Find(strGap);
		}

		if (!szLine.IsEmpty()) {
			strResult.Add(szLine);
		}

		if (!strResult.IsEmpty() && strResult[0].Compare("#define") == 0)
		{
			TmpItemDef.Name = strResult[1];
			TmpItemDef.ID = strResult[2];
			LItemDef.AddTail(TmpItemDef);
		}
	}

	//�ر��ļ�
	StdFile.Close();
}