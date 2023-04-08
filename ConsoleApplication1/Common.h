#ifndef Downloader_Common_h
#define Downloader_Common_h

#pragma mark - Common Header
#define CURL_STATICLIB
#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <mutex>
#include <vector>
#include "curl/pthread.h"

#ifdef _DEBUG
#pragma comment(lib,"curl/libcurl_a_debug.lib")
#pragma comment(lib,"curl/pthread.lib")
#else
#pragma comment(lib,"curl/libcurl_a.lib")
#endif
#pragma comment(lib,"Normaliz.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Wldap32.lib")
#pragma comment(lib,"Crypt32.lib")
#pragma comment(lib,"Advapi32.lib")
using namespace std;
#pragma mark - Useful Macros

#define kPathSeparator      '/'
#define kMaxDownloadThreads 5

#pragma mark - Macro Swiches

#define DEBUG_MODE

#endif

