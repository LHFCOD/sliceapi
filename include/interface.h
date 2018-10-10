#pragma once
#include <pugixml.hpp>
#include <jpeglib.h>
#include <jerror.h>
#define cimg_plugin "plugins/jpeg_buffer.h"
#define cimg_display 0
#include <CImg.h>
using namespace cimg_library;
//#include "MicroComDocIO.h"
//using namespace MicroComDoc;
#include "ComDocIO.h"
using namespace ComDoc;
#include <malloc.h>
#ifdef INTERFACE_EXPORTS
#define INTERFACE _declspec(dllexport)
#else
#define INTERFACE _declspec(dllimport)
#endif
using namespace std;
namespace TileImage
{
class ImageInfo
{
  public:
	int LayerCount = 0;
	int ImageWidth = 0;
	int ImageHeight = 0;
	int TileWidth = 0;
	int TileHeight = 0;
	int maxLevel = 0;
	int minLevel = 0;
};
class LayerProperty
{
  public:
	string folderName;
	float scaleVal;
	int rowCount;
	int colCount;
	int lastImageWidth;
	int lastImageHeight;
	int curImageWidth;
	int curImageHeight;
};
class MDSFile
{
  private:
  int maxImageSize=1000000;
  public:
	ComDocIO *io;
	ImageInfo info;
	std::map<int, LayerProperty> LayerMap;
	CImg<unsigned char> *minLevelImage;
	FileBlock *thumbnailImage = nullptr;

  public:
	MDSFile(string _RootDir);
	void GetImageInfo();
	void GetLayerProperty();
	FileBlock *GetTileData(int Level, int x, int y);
	FileBlock *GetTileVirtualData(int Level, int x, int y);
	FileBlock *GetThumbnail(int height);
	void GetMinLevelImage();
	CImg<unsigned char> *loadImageFromBuffer(FileBlock *block);
	~MDSFile();
};
} // namespace TileImage
