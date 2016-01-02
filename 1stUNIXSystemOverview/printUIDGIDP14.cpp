/*
 * Copy standard input to standard output
 * using standard I/O
 */
#include"../func.h"


int main(int argc,char *argv[])
{
	printf("uid = %d, gid = %d\n",getuid(),getgid());
	exit(0);

}
