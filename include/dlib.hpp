#if defined(_MSC_VER)
	//  Microsoft 
#define APP_EXPORT __declspec(dllexport)
#define APP_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
	//  GCC
#define APP_EXPORT __attribute__((visibility("default")))
#define APP_IMPORT
#else
	//  do nothing and hope for the best?
#define APP_EXPORT
#define APP_IMPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif

APP_EXPORT void bootDlib();