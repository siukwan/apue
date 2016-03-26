/*
题目描述

请编写程序交换一个数的二进制的奇数位和偶数位。（使用越少的指令越好）
给定一个int x，请返回交换后的数int。
测试样例：
10
返回：5

*/

class Exchange {
public:
	int exchangeOddEven(int x) {
		// write code here
		return (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	}
};