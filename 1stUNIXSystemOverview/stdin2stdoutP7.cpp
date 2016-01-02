/*
 * Copy standard input to standard output
 *
 * terminal input data.txt output
 * ./stdin2stdout >data.txt
 *
 * infile.txt input , outfile.txt output
 * ./stdin2stdout <infile.txt >outfile.txt
 */
#include"../func.h"
#include<string.h>

#define BUFFSIZE 4096

int main(int argc,char *argv[])
{
	//读取的字符串
	char buf[BUFFSIZE];
	int n;
	//循环读入和输出
	while((n = read(STDIN_FILENO,buf ,BUFFSIZE))>0)
	{
		if(write(STDOUT_FILENO,buf,strlen(buf))!=strlen(buf))
			err_sys("write error");
	}

	if(n<0)
		err_sys("read error");

	exit(0);

}
