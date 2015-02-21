// ShellExtConfigEntry.cpp : Implementation of CShellExtConfigEntry

#include "stdafx.h"
#include "ShellExtConfigEntry.h"


// CShellExtConfigEntry

#define HIDA_GetPIDLFolder(pida) (LPCITEMIDLIST)(((LPBYTE)pida)+(pida)->aoffset[0])
#define HIDA_GetPIDLItem(pida, i) (LPCITEMIDLIST)(((LPBYTE)pida)+(pida)->aoffset[i+1])

HRESULT CShellExtConfigEntry::Initialize(LPCITEMIDLIST unusedPidl, LPDATAOBJECT dataObject, HKEY)
{
	FORMATETC etc = {0};
	etc.cfFormat = RegisterClipboardFormat(CFSTR_SHELLIDLIST);
	etc.dwAspect = DVASPECT_CONTENT;
	etc.lindex = -1;
	etc.tymed = TYMED_HGLOBAL;

	STGMEDIUM medium = {0};
	if( SUCCEEDED(dataObject->GetData(&etc,&medium)) )
	{
		LPIDA pida = reinterpret_cast<LPIDA>( GlobalLock(medium.hGlobal) );
		if(pida->cidl != 1)
		{
			GlobalUnlock(medium.hGlobal);
			ReleaseStgMedium(&medium);
			return E_FAIL;
		}

		LPCITEMIDLIST	pidlFolder= HIDA_GetPIDLFolder(pida);
		LPCITEMIDLIST pidl = HIDA_GetPIDLItem(pida,0);
		LPITEMIDLIST pidlFull = ILCombine(pidlFolder,pidl);

		this->pidl.SetFromPIDL(pidlFull);

		GlobalUnlock(medium.hGlobal);
		ReleaseStgMedium(&medium);

		return S_OK;
	}

	return E_FAIL;
}

HRESULT CShellExtConfigEntry::AddPages(LPFNADDPROPSHEETPAGE pfnAddPage, LPARAM lParam)
{
	dlg.obj = this;
	//dlg.m_psp.pcRefParent = (UINT*)&m_dwRef;
	HPROPSHEETPAGE page = dlg.Create();
	pfnAddPage(page, lParam);

	return S_OK;
}

HRESULT CShellExtConfigEntry::ReplacePage(UINT uPageID,  LPFNADDPROPSHEETPAGE pfnReplacePage,  LPARAM lParam)
{
	return E_NOTIMPL;
}