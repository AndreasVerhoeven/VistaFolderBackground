#pragma once

#include "resource.h"

#include "ColorButton.h"
class CShellExtConfigEntry;

class CPropSheetConfig :
	public CPropertyPageImpl<CPropSheetConfig>
{
public:

	CString imagePath;
	BOOL didReadFromIni;

	CHyperLink link;

	CColorButton colorButton;

	CShellExtConfigEntry* obj;

	enum { IDD = IDD_PROPDLG };

	void OnPageAddRef();
	void OnPageRelease();
	int OnApply();

	BOOL OnEditColor(LPNMHDR notifyData);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
 
	BEGIN_MSG_MAP(CPropSheetConfig)
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_NOTIFY, CPropertyPageImpl<CPropSheetConfig>::OnNotify)
		
		COMMAND_HANDLER(IDC_SETIMAGE, BN_CLICKED, OnBnClickedSetimage)
		COMMAND_HANDLER(IDC_REMOVEIMAGE, BN_CLICKED, OnBnClickedRemoveimage)
		COMMAND_HANDLER(IDC_DOSHADOW, BN_CLICKED, OnBnClickedDoshadow)
		COMMAND_HANDLER(IDC_APPLYTOSUBFOLDERS, BN_CLICKED, OnBnClickedApplytosubfolders)


		REFLECT_NOTIFICATIONS()
		
		CHAIN_MSG_MAP(CPropertyPageImpl<CPropSheetConfig>)
    END_MSG_MAP()

	void ReadSettingsForPidl();
	BOOL ReadSettingsFromIni();
	BOOL ReadSettingsFromReg();
	void WriteSettings();
	void WriteSettingsToIni();
	void WriteSettingsToReg();
	CString GetIniPath();

	void SetImageFromPath(const WCHAR* imgPath);

   
	LRESULT OnBnClickedSetimage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedRemoveimage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedDoshadow(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedApplytosubfolders(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
