/*
 * Copy standard input to standard output
 * using standard I/O
 */
#include"../func.h"


int main(int argc,char *argv[])
{
	fprintf(stderr,"EACCES: %s\n",strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}
