// FileNode.h: interface for the CFileNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILENODE_H__FDBFE102_067A_4EC6_AB4F_F01D8AAFC83A__INCLUDED_)
#define AFX_FILENODE_H__FDBFE102_067A_4EC6_AB4F_F01D8AAFC83A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef enum {
	SHOWSIZE,
	SHOWCRTTIME,
	SHOWMODTIME,
	SHOWACCTIME
}SHOW;

class CFileNode   : public CObject  
{
public:
	void OpenFolder();
	static int SortByModTime(const void*f1, const void *f2);
	static int SortByCrtTime(const void *f1, const void *f2);
	static int SortByAccTime(const void *f1, const void *f2);
	HANDLE fHandle;
	CString GetFullFileName();
	static int SortBySize(const void * f1, const void* f2);
	int Depth;
	static void ResetCNT();
	static long CNT;
	static SHOW SHOWMOD;
	long ID;
	CFileNode * Parent;
	CString toString();
	void SetAttr(CString &path, WIN32_FIND_DATA &fd);
	unsigned long IsDir;
	int GetSecond();
	int GetMinute();
	int GetHour();
	int GetDay();
	int GetMonth();
	int GetYear();
	FILETIME LstAccTime;
	FILETIME CrtTime;
	FILETIME ModTime;
	LARGE_INTEGER Size;
	CString Path;
	CString Name;
	CFileNode();
	virtual ~CFileNode();

};

#endif // !defined(AFX_FILENODE_H__FDBFE102_067A_4EC6_AB4F_F01D8AAFC83A__INCLUDED_)
