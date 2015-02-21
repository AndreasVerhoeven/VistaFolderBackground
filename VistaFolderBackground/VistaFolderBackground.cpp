// VistaFolderBackground.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "VistaFolderBackground.h"
#include "dlldatax.h"

BOOL inline IsRunningInExplorer()
{
	WCHAR path[MAX_PATH] = {0};
	GetModuleFileName(NULL, path, MAX_PATH);
	return wcsstr(path, L"explorer.exe") != NULL || _wcsicmp(path, L"verclsid.exe") != NULL;
	//const WCHAR* fileName = PathFindFileName(path);
	//return _wcsicmp(fileName, L"explorer.exe") == 0 || _wcsicmp(fileName, L"verclsid.exe") == 0;
}

class CVistaFolderBackgroundModule : public CAtlDllModuleT< CVistaFolderBackgroundModule >
{
public :
	DECLARE_LIBID(LIBID_VistaFolderBackgroundLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_VISTAFOLDERBACKGROUND, "{49AE3D99-9D4A-4CD4-AD30-5BC92FA97973}")
};

CVistaFolderBackgroundModule _AtlModule;


#ifdef _MANAGED
#pragma managed(push, off)
#endif

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if(DLL_PROCESS_ATTACH == dwReason)
	{
		if(!IsRunningInExplorer())
			return FALSE;
	}

#ifdef _MERGE_PROXYSTUB
    if (!PrxDllMain(hInstance, dwReason, lpReserved))
        return FALSE;
#endif
	hInstance;
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#ifdef _MANAGED
#pragma managed(pop)
#endif




// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
    HRESULT hr = PrxDllCanUnloadNow();
    if (hr != S_OK)
        return hr;
#endif
    return _AtlModule.DllCanUnloadNow();
}


BOOL hasBeenInitialized = FALSE;

// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	if(!IsRunningInExplorer())
	{
		return E_FAIL;
	}

	if(!hasBeenInitialized)
	{
		hasBeenInitialized = TRUE;
		CComPtr<IAveVistaBackgroundFolder> instance;
		instance.CoCreateInstance(CLSID_AveVistaBackgroundFolder);
		if(instance != NULL)
			instance->InitMe();
	}

#ifdef _MERGE_PROXYSTUB
    if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
        return S_OK;
#endif
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
#ifdef _MERGE_PROXYSTUB
    if (FAILED(hr))
        return hr;
    hr = PrxDllRegisterServer();
#endif
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
#ifdef _MERGE_PROXYSTUB
    if (FAILED(hr))
        return hr;
    hr = PrxDllRegisterServer();
    if (FAILED(hr))
        return hr;
    hr = PrxDllUnregisterServer();
#endif
	return hr;
}

