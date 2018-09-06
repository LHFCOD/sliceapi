#include <stdio.h>
#include "../include/export.h"
int main()
{
	printf("Hello World!");
	ReadMDSFile("..//..//data//1.mds");
//	FileBlock* block=GetTileVirtualData(12,1,1);
	FileBlock* block=GetThumbnail(256);
	for (int i=0;i<20;i++)
	{
		printf("%c",*(block->p+i));
	}
	return 0;
}
