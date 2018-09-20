#include "../include/export.h"
#include <iostream>
using namespace TileImage;
MDSFile *file;
void ReadMDSFile(QString _RootDir)
{
	file =new MDSFile(_RootDir);
}
void ReleaseMDSFile()
{
	if(file !=nullptr)
	{
		delete file;
		file=nullptr;
	}
}	
FileBlock* GetTileVirtualData(int Level,int x,int y)
{
	if(file!=nullptr)
	{
		return file->GetTileVirtualData(Level,x,y);
	}
	else
		return nullptr;
}
FileBlock* GetThumbnail(int height)
{
if(file!=nullptr)
{
	return file->GetThumbnail(height);
}   
else
	return nullptr;

}
