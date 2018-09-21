namespace cpp Slice
typedef i64 Pointer
service SliceEntry{
Pointer RequstMDSFile(1:string filePath),
list<i8> GetTileVirtualData(1:i32 Level,2:i32 x,3:i32 y)
i32 add(1:i32 a,2:i32 b)
}
