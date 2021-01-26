#ifndef __CNC_WIN_H__
#define __CNC_WIN_H__
#if _WIN32
#include "windows/windows.h"
#ifdef NCLINKLIB
#define NCLINKAPI __declspec(dllexport)
#else 
#define NCLINKAPI __declspec(dllimport)
#endif
#pragma warning( disable : 4996)
#elif __linux__
#include "linux/linux.h"
#define NCLINKAPI
#endif
#endif