/*
 * usage: ./listAllFiles directory_name
 * Example: ./listAllFiles /usr
 */
#include"../func.h"
#include<dirent.h>

int main(int argc,char *argv[])
{
	DIR *dp;
	dirent *dirp;

	//如果没有输入目录参数，则提示用法，并退出
	if(argc!=2)
	{
		err_quit("usage: ./listAllFiles directory_name\nExample: ./listAllFiles /usr\n");
	}

	//如果目录打开失败，则报错
	if((dp = opendir(argv[1]))==NULL)
		err_sys("can't open %s",argv[1]);

	//读取目录，为什么能够遍历整个目录？This function reads the next entry from the directory
	while((dirp = readdir(dp))!=NULL)
	{
		printf("%s\n",dirp->d_name);
		printf("索引节点号%10d 在目录文件中的偏移%6d 文件名长%6d 文件类型:%s\n\n",dirp->d_ino,dirp->d_off,dirp->d_reclen,dirp->d_type);
	}

	closedir(dp);
	exit(0);
}
