
#include "../include/interface.h"
#include <exception>
#include <QtXml/QtXml>
#include <QtXml/QDomDocument>

#include <cmath>
#include <stdio.h>

#include <QtCore/QtDebug>
#include <ostream>
#include <fstream>
#include <string>
using namespace TileImage;

TileImage::MDSFile::MDSFile(string RootDir) {
    io = new ComDocIO(RootDir);
    GetImageInfo();
    GetLayerProperty();
    GetMinLevelImage();
}


void MDSFile::GetImageInfo() {
    FileBlock *content = io->ReadFromPath(u8"\\DSI0\\MoticDigitalSlideImage");
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(content->p, content->len);
    if (!result) {
        throw std::logic_error("read xml file failed!");
    }
    pugi::xml_node root=doc.first_child().child("ImageMatrix");
    pugi::xml_node LayerCount = root.child("LayerCount");
    pugi::xml_node ImageHeight = root.child("Height");
    pugi::xml_node ImageWidth = root.child("Width");
    pugi::xml_node TileWidth = root.child("CellWidth");
    pugi::xml_node TileHeight = root.child("CellHeight");

    info.LayerCount = LayerCount.attribute("value").as_int() - 1;//»ñÈ¡²ãÊý£¬×îµÍ²ãÅÅ³ý
    info.ImageWidth = ImageWidth.attribute("value").as_int();//»ñÈ¡²ãÊý
    info.ImageHeight = ImageHeight.attribute("value").as_int();//»ñÈ¡²ãÊý
    info.TileWidth = TileWidth.attribute("value").as_int();//»ñÈ¡²ãÊý
    info.TileHeight = TileHeight.attribute("value").as_int();//»ñÈ¡²ãÊý
    //¼ÆËã×î´ólevel
    int widthLevel = std::ceil(std::log(info.ImageWidth) / std::log(2));
    int heightLevel = std::ceil(std::log(info.ImageHeight) / std::log(2));
    if (widthLevel > heightLevel) {
        info.maxLevel = widthLevel;
    } else {
        info.maxLevel = heightLevel;
    }
    //¼ÆËã×îÐ¡level
    info.minLevel = info.maxLevel - info.LayerCount + 1;

    if (content != nullptr) {
        delete content;
        content = nullptr;
    }

}

void MDSFile::GetLayerProperty() {
    FileBlock *content = io->ReadFromPath(u8"\\DSI0\\MoticDigitalSlideImage");

    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_buffer(content->p, content->len);
    if (!result) {
        throw std::logic_error("read xml file failed!");
    }
    pugi::xml_node ImageMatrix=doc.first_child().child("ImageMatrix");
    //ÎÄ¼þ¼ÐºÍ²ãÊýµÄ¶ÔÓ¦¹ØÏµ
    for (int i = info.minLevel; i <= info.maxLevel; i++) {
        LayerProperty prop;
        int layer = info.maxLevel - i;
        string layerStr=string("Layer")+std::to_string(layer);
        pugi::xml_node LayerElement = ImageMatrix.child(layerStr.data());
        pugi::xml_node ScaleElement = LayerElement.child("Scale");
        pugi::xml_node RowsElement = LayerElement.child("Rows");
        pugi::xml_node ColseElement = LayerElement.child("Cols");

        prop.folderName = ScaleElement.attribute("value").as_string();
//		prop.scaleVal = prop.folderName.toFloat();
        prop.rowCount = RowsElement.attribute("value").as_int();
        prop.colCount = ColseElement.attribute("value").as_int();
        //¼ÆËã×îºóÒ»ÐÐ»òÕß×îºóÒ»ÁÐ
        prop.curImageWidth = info.ImageWidth / std::pow(2, info.maxLevel - i);
        prop.curImageHeight = info.ImageHeight / std::pow(2, info.maxLevel - i);
        prop.lastImageWidth = prop.curImageWidth - info.TileWidth * (prop.colCount - 1);
        prop.lastImageHeight = prop.curImageHeight - info.TileHeight * (prop.rowCount - 1);
        LayerMap.insert(pair<int,LayerProperty>(i, prop));
    }
    //ÐéÄâ²ãÊýÌî³ä
    for (int i = 0; i < info.minLevel; i++) {
        int curLevel = info.minLevel - i - 1;
        LayerProperty prop;
        prop.scaleVal = LayerMap[curLevel + 1].scaleVal / 2;
        prop.rowCount = std::ceil(LayerMap[curLevel + 1].rowCount / 2.0);
        prop.colCount = std::ceil(LayerMap[curLevel + 1].colCount / 2.0);
        //¼ÆËã×îºóÒ»ÐÐ»òÕß×îºóÒ»ÁÐ
        prop.curImageWidth = info.ImageWidth / std::pow(2, info.maxLevel - curLevel);
        prop.curImageHeight = info.ImageHeight / std::pow(2, info.maxLevel - curLevel);
        prop.lastImageWidth = prop.curImageWidth - info.TileWidth * (prop.colCount - 1);
        prop.lastImageHeight = prop.curImageHeight - info.TileHeight * (prop.rowCount - 1);

        LayerMap.insert(pair<int,LayerProperty>(curLevel, prop));
    }
    if (content != nullptr) {
        delete content;
        content = nullptr;
    }
}

FileBlock *MDSFile::GetTileData(int Level, int x, int y) {
    string folderName = LayerMap[Level].folderName;
    char FileName[100];
    sprintf(FileName, "%04d_%04d", y, x);
    string Path("\\DSI0\\");

    Path = Path + folderName + "\\" + string(FileName);
    FileBlock *imge = io->ReadFromPath(Path);
    return imge;
}

FileBlock *MDSFile::GetTileVirtualData(int Level, int x, int y) {
    if (Level > info.maxLevel || Level < 0) {
        throw std::logic_error("image not exist!");
    }
    if (Level >= info.minLevel) {
        int vWidth = info.TileWidth;
        int vHeight = info.TileHeight;
        if (x < LayerMap[Level].colCount - 1 && y < LayerMap[Level].rowCount - 1) {
            //Õý³£·µ»Ø
            return GetTileData(Level, x, y);
        }
            //×îºóÒ»ÁÐ
        else if (x == LayerMap[Level].colCount - 1 && y != LayerMap[Level].rowCount - 1) {
            vWidth = LayerMap[Level].lastImageWidth;
        }
            //×îºóÒ»ÐÐ
        else if (x != LayerMap[Level].colCount - 1 && y == LayerMap[Level].rowCount - 1) {
            vHeight = LayerMap[Level].lastImageHeight;
        }
            //×îºóÒ»¸ö
        else if (x == LayerMap[Level].colCount - 1 && y == LayerMap[Level].rowCount - 1) {
            vWidth = LayerMap[Level].lastImageWidth;
            vHeight = LayerMap[Level].lastImageHeight;
        }
        //¼ô²Ã´¦Àí
        FileBlock *temp_block = GetTileData(Level, x, y);
        QImage image;
        image.loadFromData(temp_block->p, temp_block->len);
        QImage lastImage = image.copy(0, 0, vWidth, vHeight);

        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        lastImage.save(&buffer, "JPEG"); // writes image into ba in PNG format
        byte_t *p = (byte_t *) malloc(ba.count());
        memcpy(p, ba.data(), ba.count());
        delete temp_block;
        return new FileBlock(p, ba.count());
    } else {
        int vWidth = LayerMap[Level].lastImageWidth;
        int vHeight = LayerMap[Level].lastImageHeight;
        if (x < LayerMap[Level].colCount - 1 && y < LayerMap[Level].rowCount - 1) {
            vWidth = info.TileWidth;
            vHeight = info.TileHeight;
            //²»×ö´¦Àí
        }
            //×îºóÒ»ÁÐ
        else if (x == LayerMap[Level].colCount - 1 && y != LayerMap[Level].rowCount - 1) {
            vHeight = info.TileHeight;
        }
            //×îºóÒ»ÐÐ
        else if (x != LayerMap[Level].colCount - 1 && y == LayerMap[Level].rowCount - 1) {
            vWidth = info.TileWidth;
        }
            //×îºóÒ»¸ö
        else if (x == LayerMap[Level].colCount - 1 && y == LayerMap[Level].rowCount - 1) {
            vWidth = LayerMap[Level].lastImageWidth;
            vHeight = LayerMap[Level].lastImageHeight;
        }
        //¼ô²Ã´¦Àí
        int scaleWidth = LayerMap[info.minLevel].colCount * info.TileWidth / std::pow(2, info.minLevel - Level);
        int scaleHeight = LayerMap[info.minLevel].rowCount * info.TileHeight / std::pow(2, info.minLevel - Level);
        QImage scaleImage = minLevelImage->scaled(scaleWidth, scaleHeight);
        QImage lastImage = scaleImage.copy(x * info.TileWidth, y * info.TileHeight, vWidth, vHeight);
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        lastImage.save(&buffer, "JPEG"); // writes image into ba in PNG format
        byte_t *p = (byte_t *) malloc(ba.count());
        memcpy(p, ba.data(), ba.count());
        return new FileBlock(p, ba.count());
    }
}

void MDSFile::GetMinLevelImage() {
    minLevelImage = new QImage(LayerMap[info.minLevel].colCount * info.TileWidth,
                               LayerMap[info.minLevel].rowCount * info.TileHeight, QImage::Format_RGB32);
    QPainter painter(minLevelImage);
    for (int i = 0; i < LayerMap[info.minLevel].colCount; i++)
        for (int j = 0; j < LayerMap[info.minLevel].rowCount; j++) {
            FileBlock *temp_block = GetTileData(info.minLevel, i, j);
            QImage image;
            image.loadFromData(temp_block->p, temp_block->len);
            painter.drawImage(i * info.TileWidth, j * info.TileHeight, image);
        }

}

FileBlock *MDSFile::GetThumbnail(int height) {
    if (thumbnailImage != nullptr) {
        delete thumbnailImage;
        thumbnailImage = nullptr;
    }
    QImage cutImage = minLevelImage->copy(0, 0, LayerMap[info.minLevel].curImageWidth,
                                          LayerMap[info.minLevel].curImageHeight);
    int width = height * info.ImageWidth / info.ImageHeight;
    QImage scaleImage = cutImage.scaled(width, height);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    scaleImage.save(&buffer, "JPEG"); // writes image into ba in PNG format
    byte_t *p = (byte_t *) malloc(ba.count());
    memcpy(p, ba.data(), ba.count());
    thumbnailImage = new FileBlock(p, ba.count());
    return thumbnailImage;
}

MDSFile::~MDSFile() {
    if (io != nullptr) {
        delete io;
        io = nullptr;
    }

    if (minLevelImage != nullptr) {
        delete minLevelImage;
        minLevelImage = nullptr;
    }
}
