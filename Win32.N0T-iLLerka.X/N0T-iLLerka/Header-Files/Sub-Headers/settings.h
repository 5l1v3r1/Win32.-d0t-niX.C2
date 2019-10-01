//// settings.h : N0T-iLLerka.X's Settings Header File ////
#pragma once

// Warning Message: //
/* #define DISABLE_WARNING */
	// If defined: Shows the user a warning message that he is about to execute Malware.
	//			   ( IT IS NOT RECOMMENDED TO DISABLE THIS FEATURE ! )

// Kill MasterBootRecord: //
/* #define KILL_MBR */
	// If defined: Kills the MBR (MasterBootRecord) by overwriting it (with Zeros)
	//			   (Optional) ((I might write my own MBR displaying a Message))

//// Debug-Mode: ////
/* #define DEBUG */
	// If defined: Allows you to disables security features, used by the Malware to prevent the user from tampering with it.
	//			   Also allows you to enable certain debugging features.
	//			   This will also be automatically definded if you set the VSBuild-Configuration to "Debug",
	//			   this is just here so you can still enable Debug-Mode manually in the Release Configuration.

//// Debug Suboptions: ////
#ifdef DEBUG
	// Debug MessageBoxes: //
#define DEBUG_MSG
	// If defined: Shows the user Error/Warning/Information/(Question) MessageBoxes used for debbuging.

// NT Process Persistency: //
#define DISABLE_NT_FUNCTIONS
	// If defined: Disables and prevents the Malware from utilizing the NT Functions used for Process Persistency.

// Mutex/Semaphore utilization: //
/* #define DISABLE_SYNCHRONIZATION */
	// If defined: Disables the usage of a Global Mutex/Semaphore Object
	//			   (It is not recommended to disable this feature, but it might be sometimes necessary for debugging purposes)
#endif