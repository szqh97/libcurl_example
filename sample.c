/* 
 * this can get from libcurl's official website
 * */
#include <stdio.h>
#include <curl/curl.h>
//const char *url = "http://ui.ptlogin2.qq.com/cgi-bin/ver";
const char *url = "http://www.baidu.com";
int main ( int argc, char *argv[] )
{
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s \n", curl_easy_strerror(res));

        }

        curl_easy_cleanup(curl);
    }
    return 0;
}			/* ----------  end of function main  ---------- */
