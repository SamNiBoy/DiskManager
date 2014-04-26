// FileNode.cpp: implementation of the CFileNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DiskManager.h"
#include "FileNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long CFileNode::CNT = 0;
SHOW CFileNode::SHOWMOD = SHOWSIZE;

CFileNode::CFileNode()
{
  ID = ++CNT;
}

CFileNode::~CFileNode()
{

}

int CFileNode::GetYear()
{
    return 0;
}

int CFileNode::GetMonth()
{
    return 0;
}

int CFileNode::GetDay()
{
    return 0;
}

int CFileNode::GetHour()
{
    return 0;
}

int CFileNode::GetMinute()
{
    return 0;
}

int CFileNode::GetSecond()
{
    return 0;
}

void CFileNode::SetAttr(CString &path, WIN32_FIND_DATA &fd)
{
	Name = fd.cFileName;
	Path = path;
	IsDir = fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
	Size.LowPart = fd.nFileSizeLow;
    Size.HighPart = fd.nFileSizeHigh;
	LstAccTime = fd.ftLastAccessTime;
	CrtTime = fd.ftCreationTime;
	ModTime = fd.ftLastWriteTime;
}

CString CFileNode::toString()
{
    CString s, sz;

	if (SHOWMOD == SHOWCRTTIME)
	{
		SYSTEMTIME stUTC, stLocal;

        FileTimeToSystemTime(&CrtTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        // Build a string showing the date and time.
        s.Format(" [Creation Time: %02d/%02d/%d  %02d:%02d]",
        stLocal.wMonth, stLocal.wDay, stLocal.wYear,
        stLocal.wHour, stLocal.wMinute);
		s = Name + s;
		return s;
	}

	if (SHOWMOD == SHOWACCTIME)
	{
		SYSTEMTIME stUTC, stLocal;

        FileTimeToSystemTime(&LstAccTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        // Build a string showing the date and time.
        s.Format(" [Access Time: %02d/%02d/%d  %02d:%02d]",
        stLocal.wMonth, stLocal.wDay, stLocal.wYear,
        stLocal.wHour, stLocal.wMinute);
		s = Name + s;
		return s;
	}

	if (SHOWMOD == SHOWMODTIME)
	{
		SYSTEMTIME stUTC, stLocal;

        FileTimeToSystemTime(&ModTime, &stUTC);
        SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

        // Build a string showing the date and time.
        s.Format(" [Modification Time: %02d/%02d/%d  %02d:%02d]",
        stLocal.wMonth, stLocal.wDay, stLocal.wYear,
        stLocal.wHour, stLocal.wMinute);
		s = Name + s;
		return s;
	}

	if (Size.QuadPart > 1024 * 1024 * 1024)
	{
		sz.Format(" [%.2fG]", Size.QuadPart /(1024 * 1024 * 1024.0));
	}
	else if (Size.QuadPart > 1024 * 1024)
	{
		sz.Format(" [%.2fM]", Size.QuadPart /(1024 * 1024.0));
	}
	else if (Size.QuadPart > 1024)
	{
		sz.Format(" [%.2fK]", Size.QuadPart /1024.0);
	}
	else
	{
		sz.Format(" [%.2fB]", Size.QuadPart*1.0);
	}

	s = Name + sz;
	return s;
}

void CFileNode::ResetCNT()
{
    CNT = 0;
}

int CFileNode::SortBySize(const void *f1, const void *f2)
{
	LARGE_INTEGER l1, l2;
	l1 = (*(CFileNode**)f1)->Size;
	l2 = (*(CFileNode**)f2)->Size;
	if (l1.QuadPart > l2.QuadPart)
		return -1;
	else
        return 1;
}

CString CFileNode::GetFullFileName()
{
    return Path+"\\"+Name;
}

int CFileNode::SortByAccTime(const void *f1, const void *f2)
{
	return -::CompareFileTime(&(*(CFileNode**)f1)->LstAccTime, &(*(CFileNode**)f2)->LstAccTime);
}

int CFileNode::SortByCrtTime(const void *f1, const void *f2)
{
	return -::CompareFileTime(&(*(CFileNode**)f1)->CrtTime, &(*(CFileNode**)f2)->CrtTime);
}

int CFileNode::SortByModTime(const void *f1, const void *f2)
{
    return -::CompareFileTime(&(*(CFileNode**)f1)->ModTime, &(*(CFileNode**)f2)->ModTime);
}

void CFileNode::OpenFolder()
{
	CString dirpath =  Path;
    if (IsDir)
	{
		if (Path.Right(1) != "\\")
		    dirpath += "\\" + Name;
		else
			dirpath += Name;
	}

	//AfxMessageBox("Open file:"+dirpath);
	//ShellExecute(NULL, "explorer ", dirpath, NULL, NULL, SW_SHOWMAXIMIZED);
    //ShellExecute(NULL,   "explorer.exe ",   dirpath, NULL,   NULL,   SW_MAXIMIZE);
	dirpath = "explorer " + dirpath;
	system(dirpath);		
}
