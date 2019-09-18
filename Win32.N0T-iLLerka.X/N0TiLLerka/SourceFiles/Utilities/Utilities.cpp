#include "../../HeaderFiles/N0TiLLerka.h"

BOOL IsUserAdmin() {
	SID_IDENTIFIER_AUTHORITY siaNtA = SECURITY_NT_AUTHORITY;
	PSID psAg;
	BOOL bAais = AllocateAndInitializeSid(&siaNtA, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &psAg);
	if (bAais) {
		if (!CheckTokenMembership(NULL, psAg, &bAais)) {
			bAais = FALSE;
		}
		FreeSid(psAg);
	}

	return bAais;
}