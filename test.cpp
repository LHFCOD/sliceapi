#include "include/interface.h"
using namespace TileImage;
int main()
{
    MDSFile *file = new MDSFile("data/1.mds");
    FileBlock *block= file->GetTileVirtualData(12,11,4);
    FileBlock *thumbnail=file->GetThumbnail(256);
	return 0;   
}
