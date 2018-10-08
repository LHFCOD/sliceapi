namespace cpp Slice
typedef i64 Pointer
struct SliceInfo{
    1: required i32 LayerCount;
    2: required i32 ImageWidth;
    3: required i32 ImageHeight;
    4: required i32 TileWidth;
    5: required i32 TileHeight;
}
service SliceEntry{
Pointer RequstMDSFile(1:string filePath),
list<i8> GetTileVirtualData(1:Pointer key,2:i32 Level,3:i32 x,4:i32 y),
SliceInfo GetSliceInfo(1:Pointer key),
i32 add(1:i32 a,2:i32 b)
}

