// AveVistaBackgroundFolder.h : Declaration of the CAveVistaBackgroundFolder

#pragma once
#include "resource.h"       // main symbols

#include "VistaFolderBackground.h"

#include "Pidl.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif



// CAveVistaBackgroundFolder

class ATL_NO_VTABLE CAveVistaBackgroundFolder :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAveVistaBackgroundFolder, &CLSID_AveVistaBackgroundFolder>,
	public IAveVistaBackgroundFolder
{
public:

	BOOL isInitialized;

	static UINT regMsg;

	CAveVistaBackgroundFolder()
	{
		isInitialized = FALSE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AVEVISTABACKGROUNDFOLDER)


BEGIN_COM_MAP(CAveVistaBackgroundFolder)
	COM_INTERFACE_ENTRY(IAveVistaBackgroundFolder)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}



	static HHOOK hookHandle;


	static LPITEMIDLIST GetPidlFromShellBrowser(IShellBrowser* browser);

	HRESULT InternalHookMsgLoop();
	static LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam);

	static void OnStyleUpdate(HWND hwnd, CWPSTRUCT* msg);
	static void OnTextColorUpdate(HWND hwnd, CWPSTRUCT* msg);
	static BOOL SetBackgroundForListViewFromPath(HWND hwnd, const WCHAR* path);
	static BOOL FindShellBrowser(HWND hwnd, IShellBrowser** browser);
	static BOOL HasParentWithClassName(HWND hwnd, const WCHAR* expectedClassName, HWND* outHwnd);
	static BOOL EqualsClassName(HWND hwnd, const WCHAR* expectedClassName);
	static BOOL IsExplorerListView(HWND hwnd, HWND* topParent);

	static void ClearTagged(HWND hwnd);
	static BOOL CALLBACK ClearTaggedEnumChildProc(HWND hwnd, LPARAM lParam);

public:
	DECLARE_CLASSFACTORY_SINGLETON(CAveVistaBackgroundFolder);
	STDMETHOD(InitMe)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(AveVistaBackgroundFolder), CAveVistaBackgroundFolder)
DECLARE_CLASSFACTORY_SINGLETON(CAveVistaBackgroundFolder);