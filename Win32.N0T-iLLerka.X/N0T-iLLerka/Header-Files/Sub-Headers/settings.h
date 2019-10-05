//// settings.h : N0T-iLLerka.X's Settings Header File ////
#pragma once

// Warning Message: //
#define DISABLE_WARNING 0
	// If defined: Shows the user a warning message that he is about to execute Malware.
	//			   ( IT IS NOT RECOMMENDED TO DISABLE THIS FEATURE ! )
	// Default:    FALSE

// Kill MasterBootRecord: //
#define KILL_MBR 0
	// If defined: Kills the MBR (MasterBootRecord) by overwriting it (with Zeros)
	//			   (Optional) ((I might write my own MBR displaying a Message))
	// Default:    FALSE

//// Debug-Mode: ////
#define DEBUG 0
	// If defined: Allows you to disables security features, used by the Malware to prevent the user from tampering with it.
	//			   Also allows you to enable certain debugging features.
	//			   This will also be automatically definded if you set the VSBuild-Configuration to "Debug",
	//			   this is just here so you can still enable Debug-Mode manually in the Release Configuration.
	// Default:    FALSE

//// Debug Suboptions: ////
#if (defined(_DEBUG)) || (DEBUG == TRUE)
	// Debug MessageBoxes: //
	#define DEBUG_MSG 1
		// If defined: Shows the user Error/Warning/Information/(Question) MessageBoxes used for debbuging.
		// Default:    TRUE

	// NT Process Persistency: //
	#define DISABLE_NT_FUNCTIONS 1
		// If defined: Disables and prevents the Malware from utilizing the NT Functions used for Process Persistency.
		// Default:	   TRUE

	// Process Protections: //
	#define DISABLE_PROTECTIONS 1
		// If defined: Disables all "external" Process protections
		//			   (this will control more in the future when features like active process monitoring are getting implemented)
		// Default:    TRUE

	// Mutex/Semaphore utilization: //
	#define DISABLE_SYNCHRONIZATION 0
		// If defined: Disables the usage of a Global Mutex/Semaphore Object
		//			   (It is not recommended to disable this feature, but it might be sometimes necessary for debugging purposes)
		// Default:	   FALSE
#endif