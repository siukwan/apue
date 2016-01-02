/*
 * Copy standard input to standard output
 * using standard I/O
 */
#include"../func.h"


int main(int argc,char *argv[])
{
	int c;
	while((c=getc(stdin))!=EOF)
	{
		if(putc(c,stdout) == EOF)
			err_sys("output error");
	}

	if(ferror(stdin))
		err_sys("input error");

	exit(0);

}
