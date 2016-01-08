#include<fstream>
#include<iostream>
#include<stdio.h>
#include<iostream>
#include<string>
#include<memory.h>
#include<limits.h>
#include <sys/time.h>
#include <pthread.h>

using namespace std;


/*
函数名  ：main
函数功能：主函数
*/
int main()
{

	//获取时间
	time_t nowTime;
	time(&nowTime);
	tm *timeOut;
	timeOut=localtime(&nowTime);
	cout<<timeOut->tm_year+1900<<"-"<<timeOut->tm_mon+1<<"-"<<timeOut->tm_mday<<" "<<timeOut->tm_hour<<":"<<timeOut->tm_min<<":"<<timeOut->tm_sec<<endl;
	//存储到文件中
	ofstream outFile("refreshTime.txt", ios::out);
	outFile<<timeOut->tm_year+1900<<"-"<<timeOut->tm_mon+1<<"-"<<timeOut->tm_mday<<" "<<timeOut->tm_hour<<":"<<timeOut->tm_min<<":"<<timeOut->tm_sec<<endl;

	outFile.close();

	return  0;
}

