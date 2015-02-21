// ShellExtConfigEntry.h : Declaration of the CShellExtConfigEntry

#pragma once
#include "resource.h"       // main symbols

#include "VistaFolderBackground.h"

#include "stdafx.h"

#include "Pidl.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

#include "PropSheetConfig.h"

// CShellExtConfigEntry

class ATL_NO_VTABLE CShellExtConfigEntry :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShellExtConfigEntry, &CLSID_ShellExtConfigEntry>,
	public IShellExtConfigEntry,
	public IShellExtInit,
	public IShellPropSheetExt
{
protected:
	CPropSheetConfig dlg;

public:
	CShellExtConfigEntry()
	{
	}

	CPidl pidl;

DECLARE_REGISTRY_RESOURCEID(IDR_SHELLEXTCONFIGENTRY)


BEGIN_COM_MAP(CShellExtConfigEntry)
	COM_INTERFACE_ENTRY(IShellExtConfigEntry)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IShellPropSheetExt)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHODIMP Initialize(LPCITEMIDLIST, LPDATAOBJECT, HKEY);
	HRESULT CALLBACK AddPages(LPFNADDPROPSHEETPAGE pfnAddPage, LPARAM lParam);
	HRESULT CALLBACK ReplacePage(UINT uPageID,  LPFNADDPROPSHEETPAGE pfnReplacePage,  LPARAM lParam);

};

OBJECT_ENTRY_AUTO(__uuidof(ShellExtConfigEntry), CShellExtConfigEntry)
