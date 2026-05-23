
struct Bitmap {
    char *bit_arr;
    int arr_size;
};

Bitmap* bitmapCreate(int n_bits);
void bitmapPrint(Bitmap* bitmap);
void bitmapSetBit(Bitmap* bitmap, int idx);
void bitmapUnsetBit(Bitmap* bitmap, int idx);
bool isBitSet(Bitmap* bitmap, int idx);
void bitmapClear(Bitmap* bitmap);
void bitmapSetAll(Bitmap* bitmap);
void bitmapFree(Bitmap* bitmap);