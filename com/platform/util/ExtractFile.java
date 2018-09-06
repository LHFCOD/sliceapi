package com.platform.util;
public class ExtractFile {
	static{
		System.out.println(System.getProperty("java.library.path"));
		System.loadLibrary("libmds");
	}
	ExtractFile(String filePath)
	{
		CreateMDSFile(filePath);
	}
	public native void CreateMDSFile(String filePath);
	public native byte[] GetTileData(int Level,int x,int y);
	public native byte[] GetThumbnail(int height);
	public native void ReleaseMDSFile();
	public long ptrMDS;
	public int maxLevel;
	public int ImageWidth;
	public int ImageHeight;
	public int TileWidth;
	public int TileHeight;

	public static void main(String[] args) {
		ExtractFile newClass=new ExtractFile("data/1.mds");
		System.out.println("maxLevel:"+newClass.maxLevel);
		System.out.println("ImageWidth:"+newClass.ImageWidth);
		System.out.println("ImageHeight:"+newClass.ImageHeight);
		System.out.println("TileWidth:"+newClass.TileWidth);
		System.out.println("TileHeight:"+newClass.TileHeight);
		byte[] data=newClass.GetThumbnail(256);
		for(int i=0;i<20;i++)
		{
			System.out.print((char)data[i]);
		}

		newClass.ReleaseMDSFile();
	}
}
