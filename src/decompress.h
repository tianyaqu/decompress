#include "tick.h"
int decompress(const char* market,unsigned char *compressed, struct Tick** result, unsigned int* out_len);
void free_mem(void* ptr);