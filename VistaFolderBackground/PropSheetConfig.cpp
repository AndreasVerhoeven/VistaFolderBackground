#include "StdAfx.h"
#include "PropSheetConfig.h"

#include "ShellExtConfigEntry.h"

void CPropSheetConfig::OnPageAddRef()
{
	obj->AddRef();
}

void CPropSheetConfig::OnPageRelease()
{
	obj->Release();
}

int CPropSheetConfig::OnApply()
{
	WriteSettings();

	UINT regMsg = RegisterWindowMessage(L"AveAndNadiaForeverMessage");
	::SendMessage(HWND_BROADCAST, regMsg, 0, 0);

	return TRUE;
}

LRESULT CPropSheetConfig::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	didReadFromIni = FALSE;

	link.SubclassWindow(GetDlgItem(IDC_LINK));
	link.SetHyperLink(L"http://www.aveapps.com");

	colorButton.SubclassWindow(GetDlgItem(IDC_TEXTCOLOR));
	colorButton.SetColor(RGB(0,0,0));
	
	ReadSettingsForPidl();

	return TRUE;
}

void CPropSheetConfig::ReadSettingsForPidl()
{
	BOOL didRead = ReadSettingsFromIni();
	didReadFromIni = didRead;

	if(!didRead)
		didRead = ReadSettingsFromReg();
}

BOOL CPropSheetConfig::ReadSettingsFromReg()
{
	return FALSE;
}

void CPropSheetConfig::SetImageFromPath(const WCHAR* imgPath)
{
	imagePath = imgPath;

	Bitmap bmp(imgPath);
	if(bmp.GetLastStatus() == Ok)
	{
		CStatic imgStatic = GetDlgItem(IDC_IMAGE);
		CRect rc;
		imgStatic.GetClientRect(&rc);
		
		Bitmap bmpResize(rc.Width(), rc.Height());
		Graphics g(&bmpResize);
		g.SetSmoothingMode(SmoothingModeAntiAlias);
		g.SetInterpolationMode(InterpolationModeHighQualityBicubic);
		g.DrawImage(&bmp, Rect(0,0, rc.Width(), rc.Height()), 0, 0, bmp.GetWidth(), bmp.GetHeight(), UnitPixel, 0,0,0);

		CBitmap hBmp;
		bmpResize.GetHBITMAP(NULL, &hBmp.m_hBitmap);
		CBitmap tmpBmp = imgStatic.SetBitmap(hBmp);
	}
	else
	{
		CStatic imgStatic = GetDlgItem(IDC_IMAGE);
		CBitmap tmpBmp = imgStatic.SetBitmap(NULL);
	}

}

CString CPropSheetConfig::GetIniPath()
{
	WCHAR folderPath[MAX_PATH] = {0};
	ULONG attr = SFGAO_FILESYSTEM;
	HRESULT hRes = obj->pidl.GetAtrributesOf(&attr);
	if(obj->pidl.IsValid() && SUCCEEDED(hRes) && (attr & SFGAO_FILESYSTEM))
	{						
			wcscpy_s(folderPath, MAX_PATH, obj->pidl.GetFullParseDisplayName().c_str());
	}

	WCHAR iniPath[MAX_PATH] = {0};
	wcscpy_s(iniPath, MAX_PATH, folderPath);
	PathAppendW(iniPath, L"desktop.ini");

	return iniPath;
}

void CPropSheetConfig::WriteSettingsToIni()
{
	CString iniPath = GetIniPath();

	WritePrivateProfileString(L"AveFolder", L"IconArea_Image", imagePath, iniPath);
	WritePrivateProfileString(L"AveFolder", L"ShadowedText", IsDlgButtonChecked(IDC_DOSHADOW) ? L"1" : L"0", iniPath);
	WritePrivateProfileString(L"AveFolder", L"Recursive", IsDlgButtonChecked(IDC_APPLYTOSUBFOLDERS) ? L"1" : L"0", iniPath);

	COLORREF cr = colorButton.GetColor();
	WCHAR val[100] = {0};
	_itow_s(GetRValue(cr), val, 100, 10);
	WritePrivateProfileString(L"AveFolder", L"TextR", val, iniPath);
	_itow_s(GetGValue(cr), val, 100, 10);
	WritePrivateProfileString(L"AveFolder", L"TextG", val, iniPath);
	_itow_s(GetBValue(cr), val, 100, 10);
	WritePrivateProfileString(L"AveFolder", L"TextB", val, iniPath);
}

void CPropSheetConfig::WriteSettings()
{
	WriteSettingsToIni();
}

void CPropSheetConfig::WriteSettingsToReg()
{

}

BOOL CPropSheetConfig::ReadSettingsFromIni()
{
	WCHAR folderPath[MAX_PATH] = {0};
	ULONG attr = SFGAO_FILESYSTEM;
	HRESULT hRes = obj->pidl.GetAtrributesOf(&attr);
	if(obj->pidl.IsValid() && SUCCEEDED(hRes) && (attr & SFGAO_FILESYSTEM))
	{						
			wcscpy_s(folderPath, MAX_PATH, obj->pidl.GetFullParseDisplayName().c_str());
	}

	WCHAR iniPath[MAX_PATH] = {0};
	wcscpy_s(iniPath, MAX_PATH, folderPath);
	PathAppendW(iniPath, L"desktop.ini");

	if(!PathFileExists(iniPath))
		return FALSE;
	
	WCHAR imgPath[MAX_PATH] = {0};
	GetPrivateProfileString(L"AveFolder", L"IconArea_Image", L"", imgPath, MAX_PATH, iniPath);
	if(wcslen(imgPath) > 0)
	{
		WCHAR fullImgPath[MAX_PATH]  = {0};
		wcscpy_s(fullImgPath, MAX_PATH, folderPath);
		PathAppendW(fullImgPath, imgPath);
		if(PathFileExists(fullImgPath))
		{
			/*LVBKIMAGE lvImg = {0};
			lvImg.ulFlags = LVBKIF_SOURCE_URL | LVBKIF_STYLE_TILE;
			lvImg.pszImage = fullImgPath;
			ListView_SetBkImage(hwnd, &lvImg);
			*/
			SetImageFromPath(fullImgPath);
		}
	}

	UINT doShadowed = GetPrivateProfileInt(L"AveFolder", L"ShadowedText", 0, iniPath);
	UINT doRecursive = GetPrivateProfileInt(L"AveFolder", L"Recursive", 0, iniPath);

	CheckDlgButton(IDC_DOSHADOW, doShadowed);
	CheckDlgButton(IDC_APPLYTOSUBFOLDERS, doRecursive);
	

	UINT textR = GetPrivateProfileInt(L"AveFolder", L"TextR", 0, iniPath);
	UINT textG = GetPrivateProfileInt(L"AveFolder", L"TextG", 0, iniPath);
	UINT textB = GetPrivateProfileInt(L"AveFolder", L"TextB", 0, iniPath);

	colorButton.SetColor(RGB(textR, textG, textB));



	return TRUE;
}
BOOL CPropSheetConfig::OnEditColor(LPNMHDR notifyData)
{
	SetModified();
	return 0;
}

LRESULT CPropSheetConfig::OnBnClickedSetimage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	COMDLG_FILTERSPEC specs[2] = 
		{
			{L"Image Files", L"*.jpg; *.bmp; *.png"},
			{L"All Files", L"*.*"}
		};
	CShellFileOpenDialog dlg(imagePath, FOS_FORCEFILESYSTEM | FOS_PATHMUSTEXIST | FOS_OVERWRITEPROMPT,
							L"jpg",
							specs, 2);

	if(dlg.DoModal())
	{
		CString path;
		dlg.GetFilePath(path);
		SetImageFromPath(path);
		SetModified();
	}

	return 0;
}

LRESULT CPropSheetConfig::OnBnClickedRemoveimage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SetImageFromPath(L"");
	SetModified();

	return 0;
}
LRESULT CPropSheetConfig::OnBnClickedDoshadow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SetModified();

	return 0;
}

LRESULT CPropSheetConfig::OnBnClickedApplytosubfolders(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	SetModified();

	return 0;
}
