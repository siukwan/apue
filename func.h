/*
2016-01-02 头文件
*/
#ifndef MY_FUNC_H_
#define MY_FUNC_H_
#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#include<memory.h>
#include<unistd.h>
#include<iostream>
#include<errno.h>
#include<syslog.h>

//2016-01-02 第一章用到的函数
extern void err_doit(int errnoflag, int level ,const char *fmt, va_list ap);
extern void err_sys(const char *fmt,...);
extern void err_quit(const char *fmt,...);


#endif
