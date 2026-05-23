#include "bitmap.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>

static int idxToByteIdx(int idx) {
    return idx / 8;
}

static int idxToBitIdx(int idx) {
    return idx % 8;
}

Bitmap* bitmapCreate(int n_bits) {
    int byteSize = n_bits / 8 + (n_bits % 8 == 0 ? 0 : 1);
    char* mem = reinterpret_cast<char*>(malloc(byteSize));
    memset(mem, 0, byteSize);

    Bitmap *bitmap = reinterpret_cast<Bitmap*>(malloc(sizeof(Bitmap)));
    bitmap->arr_size = n_bits;
    bitmap->bit_arr = mem;
    return bitmap;
}

void bitmapPrint(Bitmap* bitmap) {
    if (bitmap == nullptr) {
        return;
    }

    for (int i = 0 ; i < bitmap->arr_size; i++) {
        int byteIdx = idxToByteIdx(i);
        int bitIdx = idxToBitIdx(i);

        bool isSet = (bitmap->bit_arr[byteIdx] & (1 << bitIdx)) != 0;
        std::cout << isSet;
    }
    std::cout << std::endl;
}

void bitmapSetBit(Bitmap* bitmap, int idx) {
    int byteIdx = idxToByteIdx(idx);
    int bitIdx = idxToBitIdx(idx);
    bitmap->bit_arr[byteIdx] |= (1 << bitIdx);
}

void bitmapUnsetBit(Bitmap* bitmap, int idx) {
    int byteIdx = idxToByteIdx(idx);
    int bitIdx = idxToBitIdx(idx);
    bitmap->bit_arr[byteIdx] &= ~(1 << bitIdx);
}

bool isBitSet(Bitmap* bitmap, int idx) {
    int byteIdx = idxToByteIdx(idx);
    int bitIdx = idxToBitIdx(idx);
    return (bitmap->bit_arr[byteIdx] & (1 << bitIdx)) != 0;
}

void bitmapClear(Bitmap* bitmap) {
    int byteSize = bitmap->arr_size / 8 + (bitmap->arr_size % 8 == 0 ? 0 : 1);
    memset(bitmap->bit_arr, 0, byteSize);
}

void bitmapSetAll(Bitmap* bitmap) {
    int byteSize = bitmap->arr_size / 8 + (bitmap->arr_size % 8 == 0 ? 0 : 1);
    memset(bitmap->bit_arr, 0xFF, byteSize);
}

void bitmapFree(Bitmap* bitmap) {
    free(bitmap->bit_arr);
    free(bitmap);
}