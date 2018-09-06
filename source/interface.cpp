
#include "../include/interface.h"
#include <exception>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>

#include <cmath>
#include <stdio.h>

#include <QtCore/QtDebug>
using namespace TileImage;

TileImage::MDSFile::MDSFile(QString RootDir)
{
	io = new ComDocIO(RootDir);
	GetImageInfo();
	GetLayerProperty();
	GetMinLevelImage();
}


void MDSFile::GetImageInfo()
{
	FileBlock *content = io->ReadFromPath(u8"\\DSI0\\MoticDigitalSlideImage");
	QByteArray xmlArray = QByteArray::fromRawData((char*)content->p, content->len);
	QDomDocument doc;
	if (!doc.setContent(xmlArray))
	{
		throw std::logic_error("read xml file failed!");
	}
	QDomElement root = doc.documentElement();//¶ÁÈ¡¸ù½Úµã 
	QDomElement ImageMatrix = root.elementsByTagName("ImageMatrix").at(0).toElement();
	QDomElement LayerCount = ImageMatrix.elementsByTagName("LayerCount").at(0).toElement();
	QDomElement ImageWidth = ImageMatrix.elementsByTagName("Width").at(0).toElement();
	QDomElement ImageHeight = ImageMatrix.elementsByTagName("Height").at(0).toElement();
	QDomElement TileWidth = ImageMatrix.elementsByTagName("CellWidth").at(0).toElement();
	QDomElement TileHeight = ImageMatrix.elementsByTagName("CellHeight").at(0).toElement();
	info.LayerCount = LayerCount.attribute("value").toInt() - 1;//»ñÈ¡²ãÊý£¬×îµÍ²ãÅÅ³ý
	info.ImageWidth = ImageWidth.attribute("value").toInt();//»ñÈ¡²ãÊý
	info.ImageHeight = ImageHeight.attribute("value").toInt();//»ñÈ¡²ãÊý
	info.TileWidth = TileWidth.attribute("value").toInt();//»ñÈ¡²ãÊý
	info.TileHeight = TileHeight.attribute("value").toInt();//»ñÈ¡²ãÊý
	//¼ÆËã×î´ólevel
	int widthLevel = std::ceil(std::log(info.ImageWidth) / std::log(2));
	int heightLevel = std::ceil(std::log(info.ImageHeight) / std::log(2));
	if (widthLevel > heightLevel)
	{
		info.maxLevel = widthLevel;
	}
	else
	{
		info.maxLevel = heightLevel;
	}
	//¼ÆËã×îÐ¡level
	info.minLevel = info.maxLevel - info.LayerCount + 1;

	if (content != nullptr)
	{
		delete content;
		content = nullptr;
	}

}
void MDSFile::GetLayerProperty()
{
	FileBlock *content = io->ReadFromPath(u8"\\DSI0\\MoticDigitalSlideImage");
	QByteArray xmlArray = QByteArray::fromRawData((char*)content->p, content->len);
	QString xmlStr(xmlArray);
	std::wstring xmlWStr=xmlStr.toStdWString();	
	for(int i =0;i<xmlWStr.size();i++)
		std::wcout<<xmlWStr.at(i);
	QDomDocument doc;
	if (!doc.setContent(xmlArray))
	{
		throw std::logic_error("read xml file failed!");
	}
	QDomElement root = doc.documentElement();//¶ÁÈ¡¸ù½Úµã 
	QDomElement ImageMatrix = root.elementsByTagName("ImageMatrix").at(0).toElement();
	//ÎÄ¼þ¼ÐºÍ²ãÊýµÄ¶ÔÓ¦¹ØÏµ
	for (int i = info.minLevel; i <= info.maxLevel; i++)
	{
		LayerProperty prop;
		int layer = info.maxLevel - i;
		QDomElement LayerElement = ImageMatrix.elementsByTagName(QString("Layer") + QString::number(layer)).at(0).toElement();
		QDomElement ScaleElement = LayerElement.elementsByTagName("Scale").at(0).toElement();
		QDomElement RowsElement = LayerElement.elementsByTagName("Rows").at(0).toElement();
		QDomElement ColseElement = LayerElement.elementsByTagName("Cols").at(0).toElement();

		prop.folderName = ScaleElement.attribute("value");
		prop.scaleVal = prop.folderName.toFloat();
		prop.rowCount = RowsElement.attribute("value").toInt();
		prop.colCount = ColseElement.attribute("value").toInt();
		//¼ÆËã×îºóÒ»ÐÐ»òÕß×îºóÒ»ÁÐ
		prop.curImageWidth = info.ImageWidth / std::pow(2, info.maxLevel - i);
		prop.curImageHeight = info.ImageHeight / std::pow(2, info.maxLevel - i);
		prop.lastImageWidth = prop.curImageWidth - info.TileWidth*(prop.colCount - 1);
		prop.lastImageHeight = prop.curImageHeight - info.TileHeight*(prop.rowCount - 1);
		LayerMap.insert(i, prop);
	}
	//ÐéÄâ²ãÊýÌî³ä
	for (int i = 0; i < info.minLevel; i++)
	{
		int curLevel = info.minLevel - i - 1;
		LayerProperty prop;
		prop.scaleVal = LayerMap[curLevel + 1].scaleVal / 2;
		prop.rowCount = std::ceil(LayerMap[curLevel + 1].rowCount / 2.0);
		prop.colCount = std::ceil(LayerMap[curLevel + 1].colCount / 2.0);
		//¼ÆËã×îºóÒ»ÐÐ»òÕß×îºóÒ»ÁÐ
		prop.curImageWidth = info.ImageWidth / std::pow(2, info.maxLevel - curLevel);
		prop.curImageHeight = info.ImageHeight / std::pow(2, info.maxLevel - curLevel);
		prop.lastImageWidth = prop.curImageWidth - info.TileWidth*(prop.colCount - 1);
		prop.lastImageHeight = prop.curImageHeight - info.TileHeight*(prop.rowCount - 1);

		LayerMap.insert(curLevel, prop);
	}
	if (content != nullptr)
	{
		delete content;
		content = nullptr;
	}
}
FileBlock* MDSFile::GetTileData(int Level, int x, int y)
{
	QString folderName = LayerMap[Level].folderName;
	char FileName[100];
	sprintf(FileName, "%04d_%04d", y, x);
	QString Path("\\DSI0\\");

	Path = Path + folderName + "\\" + QString(FileName);
	FileBlock *imge = io->ReadFromPath(Path);
	return imge;
}
FileBlock* MDSFile::GetTileVirtualData(int Level, int x, int y)
{
	if (Level > info.maxLevel || Level < 0)
	{
		throw std::logic_error("image not exist!");
	}
	if (Level >= info.minLevel)
	{
		int vWidth = info.TileWidth;
		int vHeight = info.TileHeight;
		if (x < LayerMap[Level].colCount - 1 && y < LayerMap[Level].rowCount - 1)
		{
			//Õý³£·µ»Ø
			return GetTileData(Level, x, y);
		}
		//×îºóÒ»ÁÐ
		else if (x == LayerMap[Level].colCount - 1 && y != LayerMap[Level].rowCount - 1)
		{
			vWidth = LayerMap[Level].lastImageWidth;
		}
		//×îºóÒ»ÐÐ
		else if (x != LayerMap[Level].colCount - 1 && y == LayerMap[Level].rowCount - 1)
		{
			vHeight = LayerMap[Level].lastImageHeight;
		}
		//×îºóÒ»¸ö
		else if (x == LayerMap[Level].colCount - 1 && y == LayerMap[Level].rowCount - 1)
		{
			vWidth = LayerMap[Level].lastImageWidth;
			vHeight = LayerMap[Level].lastImageHeight;
		}
		//¼ô²Ã´¦Àí
		FileBlock *temp_block = GetTileData(Level, x, y);
		QImage image;
		image.loadFromData(temp_block->p, temp_block->len);
		QImage lastImage = image.copy(0, 0,vWidth , vHeight);
		
		QByteArray ba;
		QBuffer buffer(&ba);
		buffer.open(QIODevice::WriteOnly);
		lastImage.save(&buffer, "JPEG"); // writes image into ba in PNG format
		byte_t *p = (byte_t*)malloc(ba.count());
		memcpy(p, ba.data(), ba.count());
		delete temp_block;
		return new FileBlock(p, ba.count());
	}
	else
	{
		int vWidth = LayerMap[Level].lastImageWidth;
		int vHeight = LayerMap[Level].lastImageHeight;
		if (x < LayerMap[Level].colCount - 1 && y < LayerMap[Level].rowCount - 1)
		{
			vWidth = info.TileWidth;
			vHeight = info.TileHeight;
			//²»×ö´¦Àí
		}
		//×îºóÒ»ÁÐ
		else if (x == LayerMap[Level].colCount - 1 && y != LayerMap[Level].rowCount - 1)
		{
			vHeight = info.TileHeight;
		}
		//×îºóÒ»ÐÐ
		else if (x != LayerMap[Level].colCount - 1 && y == LayerMap[Level].rowCount - 1)
		{
			vWidth = info.TileWidth;
		}
		//×îºóÒ»¸ö
		else if (x == LayerMap[Level].colCount - 1 && y == LayerMap[Level].rowCount - 1)
		{
			vWidth = LayerMap[Level].lastImageWidth;
			vHeight = LayerMap[Level].lastImageHeight;
		}
		//¼ô²Ã´¦Àí
		int scaleWidth = LayerMap[info.minLevel].colCount*info.TileWidth / std::pow(2, info.minLevel - Level);
		int scaleHeight = LayerMap[info.minLevel].rowCount*info.TileHeight / std::pow(2, info.minLevel - Level);
		QImage scaleImage = minLevelImage->scaled(scaleWidth, scaleHeight);
		QImage lastImage = scaleImage.copy(x*info.TileWidth,y*info.TileHeight, vWidth, vHeight);
		QByteArray ba;
		QBuffer buffer(&ba);
		buffer.open(QIODevice::WriteOnly);
		lastImage.save(&buffer, "JPEG"); // writes image into ba in PNG format
		byte_t *p = (byte_t*)malloc(ba.count());
		memcpy(p, ba.data(), ba.count());
		return new FileBlock(p, ba.count());
	}
}
void MDSFile::GetMinLevelImage()
{
	minLevelImage = new QImage(LayerMap[info.minLevel].colCount*info.TileWidth, LayerMap[info.minLevel].rowCount*info.TileHeight, QImage::Format_RGB32);
	QPainter painter(minLevelImage);
	for(int i=0;i<LayerMap[info.minLevel].colCount;i++)
		for (int j = 0; j < LayerMap[info.minLevel].rowCount; j++)
		{
			FileBlock *temp_block = GetTileData(info.minLevel, i, j);
			QImage image;
			image.loadFromData(temp_block->p, temp_block->len);
			painter.drawImage(i*info.TileWidth, j*info.TileHeight, image);
		}
	
}
FileBlock* MDSFile::GetThumbnail(int height)
{
	if(thumbnailImage!=nullptr)
	{
		delete thumbnailImage;
		thumbnailImage=nullptr;
	}
	QImage cutImage=minLevelImage->copy(0,0,LayerMap[info.minLevel].curImageWidth,LayerMap[info.minLevel].curImageHeight);
	int width=height*info.ImageWidth/info.ImageHeight;
	QImage scaleImage=cutImage.scaled(width,height);
	QByteArray ba;
	QBuffer buffer(&ba);
	buffer.open(QIODevice::WriteOnly);
	scaleImage.save(&buffer, "JPEG"); // writes image into ba in PNG format
	byte_t *p = (byte_t*)malloc(ba.count());
	memcpy(p, ba.data(), ba.count());
	thumbnailImage=new FileBlock(p, ba.count());
	return thumbnailImage;
}
MDSFile::~MDSFile()
{
	if (io != nullptr)
	{
		delete io;
		io = nullptr;
	}
	
	if (minLevelImage != nullptr)
	{
		delete minLevelImage;
		minLevelImage = nullptr;
	}
}
