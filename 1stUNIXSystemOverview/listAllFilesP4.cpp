#include"../func.h"
#include<dirent.h>

int main(int argc,char *argv[])
{
	DIR *dp;
	dirent *dirp;

	if(argc!=2)
	{
		err_quit("usage: ./listAllFiles directory_name\nExample: ./listAllFiles /usr\n");
	}

	if((dp = opendir(argv[1]))==NULL)
		err_sys("can't open %s",argv[1]);

	while((dirp = readdir(dp))!=NULL)
	{
		printf("%s\n",dirp->d_name);
	}

	closedir(dp);
	exit(0);
}
