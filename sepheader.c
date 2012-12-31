/*
 * =======================================================================
 *
 *       Filename:  sepheader.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2012年12月31日 22时21分04秒
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
#include <unistd.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    int written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int main ( int argc, char *argv[] )
{
    CURL *curl_handle;
    static const char *http_url = "http://ui.ptlogin2.qq.com/cgi-bin/ver";
    static const char *headerfilename = "head.out";
    FILE *headerfile;
    static const char *bodyfilename = "body.out";
    FILE *bodyfile;
    
    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* set URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, http_url);

    /* send all data to this function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

    /* open the files */
    headerfile = fopen(headerfilename, "w");
    if (headerfile == NULL)
    {
        curl_easy_cleanup(curl_handle);
        return -1;
    }
    bodyfile = fopen(bodyfilename, "w");
    if (bodyfile == NULL)
    {
        curl_easy_cleanup(curl_handle);
        return -1;
    }

    /* we want the headers to this file hand */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEHEADER, headerfile);

    /*
     * Notice here that if you want the actual data sent anywhere else but
     * stdout, you should consider using the CURLOPT_WRITEDATA OPTION
     */

    /* get it! */
    curl_easy_perform(curl_handle);

    /* cleanup curl stuf */
    curl_easy_cleanup(curl_handle);

    return 0;
}			/* ----------  end of function main  ---------- */


