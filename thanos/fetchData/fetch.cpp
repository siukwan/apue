#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <curl/curl.h> 
#include <iostream>
using namespace std;
size_t write_data(void *buffer,size_t size,size_t nmemb,void *userp);
#define FILENAME "curl.log"
int main(int argc, char *argv[])
{
	CURL *curl;
	CURLcode res;
	FILE *fptr;
	struct curl_slist *htp_header = NULL;

	if((fptr = fopen(FILENAME,"w")) == NULL)
	{
		fprintf(stderr, "fopen file error: %s\n",FILENAME);
		exit(1);
	}

	curl = curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,"https://www.baidu.com");
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,fptr);

	res = curl_easy_preform(curl);
	cout<<res<<endl;
	curl_easy_cleanup(curl);
	return 0;
}

size_t write_data(void *buffer,size_t size, size_t nmemb, void *userp)
{
	FILE *fptr = (FILE*) userp;
	fwrite(buffer,size,nmemb,fptr);
}
