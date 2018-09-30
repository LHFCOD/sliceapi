#pragma once
#include "interface.h"
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

extern "C"
{
	DLL_EXPORT void ReadMDSFile(string _RootDir);
	DLL_EXPORT void ReleaseMDSFile();
	DLL_EXPORT FileBlock* GetTileVirtualData(int Level,int x,int y);
	DLL_EXPORT FileBlock* GetThumbnail(int height);
}
