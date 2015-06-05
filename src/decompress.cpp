#include "LzmaLib.h"
#include "decompress.h"
#include "parser.h"

#include <cstdlib>
#include <cstdio>

#define FILE_BUF_SIZE 32*1024*1024

//extern void m_FreeMem(void* ptr);
//extern int parse_string(const char* market, const char* content, struct Tick** result, unsigned* len);


int decompress(const char* market,unsigned char *compressed, struct Tick** buffer, unsigned int* out_len)
{
    unsigned char* content = (unsigned char*)(malloc(FILE_BUF_SIZE));
    if(content == NULL)
    {
        *buffer = 0;
        *out_len = 0;
        return -1;
    }

    const char*ptr = (char*)compressed;

    char props[5] = { 0 };
    memcpy(props, ptr, 5);
    unsigned char*xprops = (unsigned char*)props;

    //  lzma format(one implenmation)
    //  desc 5B len 8B         data
    //  |-----|--------|---xxxxxxxxxxxxx---|
    unsigned long long compress_len = 0;
    memcpy(&compress_len, ptr + 5, 8);
    SizeT xcompress_len = compress_len;
    const unsigned char* compress_ptr = (const unsigned char*)(ptr + 13);

    memset(content, 0, FILE_BUF_SIZE);
    size_t co_len = FILE_BUF_SIZE;

    int ret = LzmaUncompress(content, &co_len, compress_ptr, &xcompress_len, xprops, 5);

    ret = parse_string(market,(const char*)content, (struct Tick**)buffer,out_len);
    
    free(content);

    return ret;
}

void free_mem(void* ptr)
{
    m_FreeMem(ptr);
}


//test method,change the project to an application to use
int test()
{
    //bin.rar is in project dir
    FILE* fp1 = fopen("bin.rar", "rb");

    char* compressed = (char*)malloc(1024 * 1024);
    int len = 1024 * 1024;
    fread(compressed,sizeof(char),len,fp1);
    fclose(fp1);
    char* data = 0;
    unsigned out_len = 0;

    struct Tick* buffer = 0;
    decompress("CFFEX", (unsigned char*)compressed, &buffer,&out_len);
    free(compressed);

    for (int i = 0; i < out_len; i++)
    {
        struct Tick* ptr = buffer+i;
        //printf()
    }

    free_mem(buffer);

}