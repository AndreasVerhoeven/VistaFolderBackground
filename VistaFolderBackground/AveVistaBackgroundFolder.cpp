// AveVistaBackgroundFolder.cpp : Implementation of CAveVistaBackgroundFolder

#include "stdafx.h"
#include "AveVistaBackgroundFolder.h"


// CAveVistaBackgroundFolder

#ifndef LVS_EX_TRANSPARENTSHADOWTEXT
#define LVS_EX_TRANSPARENTSHADOWTEXT 0x00800000
#endif

#ifndef LVS_EX_TRANSPARENTBKGND
#define LVS_EX_TRANSPARENTBKGND 0x00400000
#endif

HHOOK CAveVistaBackgroundFolder::hookHandle = NULL;
UINT  CAveVistaBackgroundFolder::regMsg = NULL;

STDMETHODIMP CAveVistaBackgroundFolder::InitMe(void)
{
	if(isInitialized)
		return S_OK;

	isInitialized = TRUE;

	AddRef();
	InternalHookMsgLoop();

	regMsg = RegisterWindowMessage(L"AveAndNadiaForeverMessage");

	return S_OK;
}


HRESULT CAveVistaBackgroundFolder::InternalHookMsgLoop()
{
	hookHandle = SetWindowsHookEx(WH_CALLWNDPROC, GetMsgProc, _AtlBaseModule.GetModuleInstance(), 0); 
	return S_OK;
}

BOOL CAveVistaBackgroundFolder::FindShellBrowser(HWND hwnd, IShellBrowser** browser)
{
	if(NULL == browser)
		return NULL;

	*browser = NULL;

	while(IsWindow(hwnd))
	{
		*browser = (IShellBrowser*)::SendMessage(hwnd, WM_USER + 7, 0, 0);
		if(*browser != NULL)
			break;

		hwnd = GetParent(hwnd);
	}

	return *browser != NULL;
}

BOOL CAveVistaBackgroundFolder::HasParentWithClassName(HWND hwnd, const WCHAR* expectedClassName, HWND* outHwnd)
{
	if(NULL == expectedClassName)
		return FALSE;

	while(IsWindow(hwnd) && !EqualsClassName(hwnd, expectedClassName))
	{
		hwnd = GetParent(hwnd);
	}

	if(!IsWindow(hwnd))
		return FALSE;

	if(outHwnd != NULL)
		*outHwnd = hwnd;

	return TRUE;
}

BOOL CAveVistaBackgroundFolder::EqualsClassName(HWND hwnd, const WCHAR* expectedClassName)
{
	if(!IsWindow(hwnd) || NULL == expectedClassName)
		return FALSE;

	const DWORD MAX_CLASSNAME = 255;
	WCHAR className[MAX_CLASSNAME] = {0};
	GetClassName(hwnd, className, MAX_CLASSNAME);
	return _wcsicmp(className, expectedClassName) == 0;
}

BOOL CAveVistaBackgroundFolder::IsExplorerListView(HWND hwnd, HWND* topParent)
{
	if(!EqualsClassName(hwnd, L"SysListView32"))
		return FALSE;

	HWND defView = ::GetParent(hwnd);
	if(!EqualsClassName(defView, L"SHELLDLL_DefView"))
		return FALSE;

	if(!HasParentWithClassName(defView, L"ShellTabWindowClass", topParent))
		return FALSE;

	return TRUE;
}

LPITEMIDLIST CAveVistaBackgroundFolder::GetPidlFromShellBrowser(IShellBrowser* browser)
{
	if(NULL == browser)
		return NULL;

	CComPtr<IShellView> shellView;
	browser->QueryActiveShellView(&shellView);
	if(NULL == shellView)
		return NULL;

	CComQIPtr<IFolderView> folderView = shellView;
	if(NULL == folderView)
		return NULL;

	CComPtr<IPersistFolder2> persistFolder2;
	folderView->GetFolder(IID_IPersistFolder2, (void**)&persistFolder2);
	if(NULL == persistFolder2)
		return NULL;

	LPITEMIDLIST pidlFolder = NULL;
	persistFolder2->GetCurFolder(&pidlFolder);

	return pidlFolder;
}

BOOL CAveVistaBackgroundFolder::SetBackgroundForListViewFromPath(HWND hwnd, const WCHAR* realPath)
{
	if(NULL == realPath || !IsWindow(hwnd))
		return FALSE;

	SetProp(hwnd, L"AveProtect", (HANDLE)1);

	WCHAR path[MAX_PATH] = {0};
	wcscpy_s(path, MAX_PATH, realPath);

	WCHAR iniPath[MAX_PATH] = {0};

	bool found = false;
	bool checkRecursive = false;
	bool isInRoot = false;
	do
	{
		wcscpy_s(iniPath, MAX_PATH, path);
		PathAppendW(iniPath, L"desktop.ini");
		//MessageBox(0, iniPath, 0, 0);
		if(PathFileExists(iniPath))
		{
			if(checkRecursive)
			{
				UINT doRecursive = GetPrivateProfileInt(L"AveFolder", L"Recursive", 0, iniPath);
				found = doRecursive != FALSE;

				if(!found)
				{
					BOOL isRoot = PathIsRoot(path);
					BOOL removedPart = PathRemoveFileSpec(path);
					isInRoot = !removedPart || isRoot;
				}
			}
			else
			{
				found = true;
			}
		}
		else
		{
			found = false;
			checkRecursive = true;
			BOOL isRoot = PathIsRoot(path);
			BOOL removedPart = PathRemoveFileSpec(path);
			isInRoot = !removedPart || isRoot;
		}

	}while(!found && !isInRoot);

	if(found)
	{
		WCHAR imgPath[MAX_PATH] = {0};
		GetPrivateProfileString(L"AveFolder", L"IconArea_Image", L"", imgPath, MAX_PATH, iniPath);
		if(wcslen(imgPath) > 0)
		{
			WCHAR fullImgPath[MAX_PATH]  = {0};
			wcscpy_s(fullImgPath, MAX_PATH, path);
			PathAppendW(fullImgPath, imgPath);
			if(PathFileExists(fullImgPath))
			{
				LVBKIMAGE lvImg = {0};
				lvImg.ulFlags = LVBKIF_SOURCE_URL | LVBKIF_STYLE_TILE;
				lvImg.pszImage = fullImgPath;
				ListView_SetBkImage(hwnd, &lvImg);
			}
		}

		UINT doShadowed = GetPrivateProfileInt(L"AveFolder", L"ShadowedText", 0, iniPath);
		

		UINT textR = GetPrivateProfileInt(L"AveFolder", L"TextR", 0, iniPath);
		UINT textG = GetPrivateProfileInt(L"AveFolder", L"TextG", 0, iniPath);
		UINT textB = GetPrivateProfileInt(L"AveFolder", L"TextB", 0, iniPath);

		SetProp(hwnd, L"_AveShadowText", (HANDLE)doShadowed);
		SetProp(hwnd, L"_AveTextR", (HANDLE)textR);
		SetProp(hwnd, L"_AveTextG", (HANDLE)textG);
		SetProp(hwnd, L"_AveTextB", (HANDLE)textB);

		DWORD color = RGB(textR, textG, textB);
		ListView_SetTextColor(hwnd, color);

		if(doShadowed)
		{
			ListView_SetExtendedListViewStyleEx(hwnd, LVS_EX_TRANSPARENTBKGND |
					LVS_EX_TRANSPARENTSHADOWTEXT, LVS_EX_TRANSPARENTBKGND | LVS_EX_TRANSPARENTSHADOWTEXT);
		}
	}

	SetProp(hwnd, L"AveProtect", (HANDLE)0);

	return TRUE;
}

void CAveVistaBackgroundFolder::OnStyleUpdate(HWND hwnd, CWPSTRUCT* msg)
{
	if(GetProp(hwnd, L"AveProtect") != NULL)
		return;

	SendMessage(msg->hwnd, regMsg, 0, 0);
}

void CAveVistaBackgroundFolder::OnTextColorUpdate(HWND hwnd, CWPSTRUCT* msg)
{
	if((UINT)GetProp(hwnd, L"AveProtect") == 2)
		return;

	PostMessage(msg->hwnd, regMsg, 0, 0);
}

BOOL CAveVistaBackgroundFolder::ClearTaggedEnumChildProc(HWND hwnd, LPARAM lParam)
{
	ClearTagged(hwnd);
	return TRUE;
}

void CAveVistaBackgroundFolder::ClearTagged(HWND hwnd)
{
	if(GetProp(hwnd, L"AveTagged"))
	{
		SetProp(hwnd, L"AveTagged", (HANDLE)0);
		InvalidateRect(hwnd, NULL, TRUE);
	}

	EnumChildWindows(hwnd, ClearTaggedEnumChildProc, 0);
}

UINT lastMsg = 0;

LRESULT CALLBACK CAveVistaBackgroundFolder::GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	//if(HC_ACTION == code)
	{
		CWPSTRUCT* msg = reinterpret_cast<CWPSTRUCT*>(lParam);
		if(msg != NULL)
		{
			if(regMsg == msg->message)
			{
				ClearTagged(msg->hwnd);
			}

			/*
			HWND topParent = NULL;
			if(IsExplorerListView(msg->hwnd, &topParent))
			{
				if(WM_PAINT == msg->message)
					msg->message = msg->message;

				lastMsg = msg->message;
			}

			if(LVM_SETEXTENDEDLISTVIEWSTYLE == msg->message)
			{
				HWND topParent = NULL;
				if(IsExplorerListView(msg->hwnd, &topParent))
				{
					OnStyleUpdate(msg->hwnd, msg);
				}
			}
			else if(LVM_SETTEXTCOLOR  == msg->message)
			{
				HWND topParent = NULL;
				if(IsExplorerListView(msg->hwnd, &topParent))
				{
					OnTextColorUpdate(msg->hwnd, msg);
				}
			}
			else */if((WM_PAINT == msg->message) && GetProp(msg->hwnd, L"AveTagged") == NULL)
			/*|| (
				(WM_WINDOWPOSCHANGING == msg->message && NULL == GetProp(msg->hwnd, L"AveTagged"))))
			{
				WINDOWPOS* wp = reinterpret_cast<WINDOWPOS*>(msg->lParam);
				if((wp != NULL && (wp->flags & SWP_SHOWWINDOW)) || regMsg == msg->message)
				{
					SetProp(msg->hwnd, L"AveTagged", (HANDLE)1);

					if(regMsg != msg->message)
						PostMessage(msg->hwnd, regMsg, 0, 0);
			*/
			{
				{
					SetProp(msg->hwnd, L"AveTagged", (HANDLE)1);

					HWND topParent = NULL;
					if(IsExplorerListView(msg->hwnd, &topParent))
					{
						
						IShellBrowser* browser = NULL;
						//FindShellBrowser(msg->hwnd, &browser);
						browser = (IShellBrowser*)::SendMessage(topParent, WM_USER + 7, 0, 0);
						if(browser != NULL)
						{
							// Explicitely AddRef() / Release()
							browser->AddRef();
							LPITEMIDLIST pidlFolder2 = GetPidlFromShellBrowser(browser);
							//MessageBox(0, pidlFolder.m_Pidl != NULL ? L"pidl" : L"empty", 0, 0);
							CPidl pidlFolder;
							pidlFolder.m_Pidl = pidlFolder2;
							
							if(pidlFolder.IsValid())
							{
								WCHAR folderPath[MAX_PATH] = {0};
								ULONG attr = SFGAO_FILESYSTEM;
								HRESULT hRes = pidlFolder.GetAtrributesOf(&attr);
								if(pidlFolder.IsValid() && SUCCEEDED(hRes) && (attr & SFGAO_FILESYSTEM))
								{
									
									wcscpy_s(folderPath, MAX_PATH, pidlFolder.GetFullParseDisplayName().c_str());
									HWND lv = msg->hwnd;
									SetBackgroundForListViewFromPath(lv, folderPath);
								}
							}
							
							browser->Release();
						}
						
						
					}
					
				}
			}
		}
	}

	return CallNextHookEx(hookHandle, code, wParam, lParam);
}