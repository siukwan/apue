/*
 * Copy standard input to execute shell
 */
#include"../func.h"
//需要使用waitpid
#include<sys/wait.h>

//信号处理函数
static void sig_int(int);

int main(void)
{
	char  buf[MAXLINE];//MAXLINE在func.h中定义
	pid_t pid;
	int   status;

	if(signal(SIGINT,sig_int) == SIG_ERR)
		err_sys("signal error");

	printf("%% ");

	while(fgets(buf,MAXLINE,stdin)!=NULL)
	{
		//如果最后一个字符是换行符，则改为空字符NULL
		if(buf[strlen(buf) - 1]=='\n')
			buf[strlen(buf) - 1]=0;

		//返回小于0，开启进程失败
		if((pid=fork())<0)
			err_sys("fork error");
		//子进程
		else if(pid == 0)
		{
			execlp(buf,buf,(char*)0);
			err_ret("couldn't execute:%s",buf);
			exit(127);//why 127？
		}

		//父进程等待子进程结束，避免僵死进程
		if( (pid = waitpid(pid,&status,0))<0)
			err_sys("waitpid error");
		printf("%% ");
	}

	exit(0);
}

void sig_int(int signo)
{
	printf("interrupt\n%% ");
}
