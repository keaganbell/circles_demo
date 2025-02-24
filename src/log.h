#pragma once

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define Assert(val) { if (!(val)) { *(u8 *)0 = 1; } }

// This might actually by pretty nice because I can pass any "print" function to this that takes these
// parameters. i.e., I could use another print function for printing text on the screen
#define LTRACE(msg, ...) PlatformDebugPrint("TRACE (%s:%d): " msg "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#define LDEBUG(msg, ...) PlatformDebugPrint("DEBUG (%s:%d): " msg "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#define  LINFO(msg, ...) PlatformDebugPrint("INFO  (%s:%d): " msg "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#define  LWARN(msg, ...) PlatformDebugPrint("WARN  (%s:%d): " msg "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#define LERROR(msg, ...) PlatformDebugPrint("ERROR (%s:%d): " msg "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
#define LFATAL(msg, ...) PlatformDebugPrint("FATAL (%s:%d): " msg "\n", __FILENAME__, __LINE__, ##__VA_ARGS__)
