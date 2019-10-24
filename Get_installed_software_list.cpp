#include <Windows.h>
#include <winreg.h>
#include <iostream>
#include <atlstr.h>

using namespace std;

void get_software_list()
{
	HKEY hKey = NULL;


	TCHAR subKey_name[MAX_PATH];

	CString net = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");

	RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		net,
		0, KEY_READ, &hKey);

	int cnt=0;
	for (DWORD i = 0;
		RegEnumKey(hKey, i, subKey_name, MAX_PATH)
		!= ERROR_NO_MORE_ITEMS;
		i++)
	{
		HKEY subKey;
		LONG lResult;
		DWORD bufferLen = MAX_PATH;
		TCHAR DisplayName[MAX_PATH];
		TCHAR DisplayVersion[MAX_PATH];

		lResult = RegOpenKeyEx(hKey, subKey_name, 0, KEY_READ, &subKey);
		if (lResult != ERROR_SUCCESS) continue;
		lResult = RegQueryValueEx(subKey, "DisplayName", NULL, NULL,
			(LPBYTE)DisplayName, &bufferLen);
		if (lResult != ERROR_SUCCESS) continue;
		cnt++;

		lResult = RegQueryValueEx(subKey, "DisplayVersion", NULL, NULL, 
			(LPBYTE)DisplayVersion, &bufferLen);
		if (lResult != ERROR_SUCCESS) *DisplayVersion = (TCHAR)"undefined";

		cout <<cnt<<"\t"<< DisplayName << endl;
		cout << "\t" << DisplayVersion << endl;
	}

}
