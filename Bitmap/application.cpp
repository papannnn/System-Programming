#include "bitmap.hpp"

int main () {
    Bitmap* bitmap = bitmapCreate(10);
    bitmapSetBit(bitmap, 7);
    bitmapSetBit(bitmap, 0);
    bitmapClear(bitmap);
    bitmapPrint(bitmap);
}