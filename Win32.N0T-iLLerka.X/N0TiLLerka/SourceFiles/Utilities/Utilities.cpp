#include "../../HeaderFiles/N0TiLLerka.h"

BOOL fnIsUserAdmin(VOID) {
	SID_IDENTIFIER_AUTHORITY siaSNtA = SECURITY_NT_AUTHORITY;
	PSID psAg;
	BOOL bAais = AllocateAndInitializeSid(&siaSNtA, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &psAg);
	if (bAais) {
		if (!CheckTokenMembership(NULL, psAg, &bAais)) {
			bAais = FALSE;
		}
		FreeSid(psAg);
	}

	return bAais;
}

#ifdef DEBUG_MSG
// Will be replaced with a better error handler now that I know how a va_list works
VOID fnFormatMessageW(LPCWSTR lpCaption, LPCWSTR lpText, UINT uType, BOOL bDisMfn, BOOL bDisLec) {
	std::wstring szTextTMP_;
	if (lpText) {
		szTextTMP_ = std::wstring(lpText);
	} else {
		szTextTMP_ = L"An Error occurred";
		bDisMfn = TRUE;
		bDisLec = TRUE;
	}

	if (bDisMfn) {
		WCHAR szMfn[MAX_PATH];
		GetModuleFileName(NULL, szMfn, MAX_PATH);
		szTextTMP_ += L"\nModule: " + std::wstring(szMfn);
	}
	if (bDisLec) {
		szTextTMP_ += L"\nErrorcode: %d";
		StringCchPrintf(pszDest, cnDest, szTextTMP_.c_str(), GetLastError());
	} else {
		StringCchPrintf(pszDest, cnDest, szTextTMP_.c_str(), GetLastError());
	}

	MessageBox(NULL, pszDest, lpCaption, uType | MB_SYSTEMMODAL);
}
#endif // DEBUG_MSG