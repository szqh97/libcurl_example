/*
 * =======================================================================
 *
 *       Filename:  getinmemery.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2012年12月30日 22时00分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  szqh97 (), szqh97@163.com
 *   Organization:  
 *
 * ======================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct MemoryStruct{
    char *memory;
    size_t size;
};

static size_t write2MemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct*)userp;
    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL)
    {
        /*  out of memory */
        printf("not enough memory (realloc returned)\n");
        exit(EXIT_FAILURE);
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

int main ( int argc, char *argv[] )
{
    //const char *url = "http://www.baidu.com";
    const char *url = "http://ui.ptlogin2.qq.com/cgi-bin/ver";
    CURL *curl_handle;
    
    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;
    
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, &write2MemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    curl_easy_perform(curl_handle);
    curl_easy_cleanup(curl_handle);

    printf("%lu bytes retrieved\n", (long)chunk.size);
    printf("\n --------\n %s ---------\n", chunk.memory);
    
    if (chunk.memory)
        free(chunk.memory);

    curl_global_cleanup();
    
    return 0;
}			/* ----------  end of function main  ---------- */
