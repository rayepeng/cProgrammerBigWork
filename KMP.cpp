#if 1
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
char blackList[10000000][20];
char whiteList[10000000][20];
int next[1000000][100];
int blackListLine = 0;
int blackListRow = 0;
int whiteListLine = 0;
int whiteListRow = 0;
void OpenFile()
{
	printf("Please input the blackList:\n");
	FILE *bfs;//自定义黑名单文件流
	char bfilename[60];
	scanf("%s", bfilename);
	if (fopen_s(&bfs, bfilename, "r"))
	{
		printf("打开文件失败！\n");
		exit(0);
	}
	//黑名单列表读出来之后，应该用什么来存储？
	//应该用二维数组来存储
	//然后将每个ip地址用Trie树来存储
	char bch;
	bch = fgetc(bfs);//第一个bch是什么？
	while (bch != EOF)
	{
		//在没有读到文件结尾的时候
		/*if (blackListLine == 0)
		{
		blackList[blackListRow][blackListLine] = '\n';
		blackListLine++;
		}*/
		blackList[blackListRow][blackListLine] = bch;
		if (bch == '\n')
		{
			blackListRow++;
			blackListLine = 0;
		}
		else
			blackListLine++;
		bch = fgetc(bfs);
	}
	printf("Please input checked file:\n");
	FILE *cs;//自定义待检查的文件流
	char cfilename[60];
	scanf("%s", cfilename);
	if (fopen_s(&cs, cfilename, "r"))
	{
		printf("打开文件失败！\n");
		exit(0);
	}
	char ch;
	ch = fgetc(cs);
	while (ch != EOF)
	{
		//在没有读到文件结尾的时候
		/*if (whiteListLine == 0)
		{
		whiteList[whiteListRow][whiteListLine] = '\n';
		whiteListLine++;
		}*/
		whiteList[whiteListRow][whiteListLine] = ch;
		if (ch == '\n')
		{
			whiteListRow++;
			whiteListLine = 0;
		}
		else
			whiteListLine++;
		ch = fgetc(cs);
	}
}

void buildnext(char *str, int *next, int len)
{
	next[0] = -1;
	int k = -1;
	for (int q = 1; q < len; q++) {
		while (k > -1 && str[k + 1] != str[q])
		{
			k = next[k];
		}
		if (str[k + 1] == str[q])
		{
			k++;
		}
		next[q] = k;
	}
}
int KMP(char *str, int slen, char *ptr, int plen,int i)
{
	// int *next = new int[plen];
	// buildnext(ptr, next, plen);
	int k = -1;
	for (int i = 0; i < slen; i++) {
		while (k > -1 && ptr[k + 1] != str[i])
			k = next[i][k];
		if (ptr[k + 1] == str[i])
			k++;
		if (k == plen - 1)
		{
			return 1;
		}
	}
	return 0;
}
int main()
{
	OpenFile();
	for (int i = 0; i < blackListRow; i++) {
		buildnext(blackList[i], next[i], strlen(blackList[i]));
	}
	for (int i = 0; i < whiteListRow; i++) {
		if (KMP(whiteList[i], strlen(whiteList[i]), blackList[i], strlen(blackList[i]),i))
			printf("%s\n", whiteList[i]);
	}
	system("pause");
	return 0;
}

#endif

#if 0

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
char blackList[10000000][20];
char whiteList[10000000][20];
int blackListLine = 0;
int blackListRow = 0;
int whiteListLine = 0;
int whiteListRow = 0;
void OpenFile()
{
	printf("Please input the blackList:\n");
	FILE *bfs;//自定义黑名单文件流
	char bfilename[60];
	scanf("%s", bfilename);
	if (fopen_s(&bfs, bfilename, "r"))
	{
		printf("打开文件失败！\n");
		exit(0);
	}
	//黑名单列表读出来之后，应该用什么来存储？
	//应该用二维数组来存储
	//然后将每个ip地址用Trie树来存储
	char bch;
	bch = fgetc(bfs);//第一个bch是什么？
	while (bch != EOF)
	{
		//在没有读到文件结尾的时候
		/*if (blackListLine == 0)
		{
		blackList[blackListRow][blackListLine] = '\n';
		blackListLine++;
		}*/
		blackList[blackListRow][blackListLine] = bch;
		if (bch == '\n')
		{
			blackListRow++;
			blackListLine = 0;
		}
		else
			blackListLine++;
		bch = fgetc(bfs);
	}
	printf("Please input checked file:\n");
	FILE *cs;//自定义待检查的文件流
	char cfilename[60];
	scanf("%s", cfilename);
	if (fopen_s(&cs, cfilename, "r"))
	{
		printf("打开文件失败！\n");
		exit(0);
	}
	char ch;
	ch = fgetc(cs);
	while (ch != EOF)
	{
		//在没有读到文件结尾的时候
		/*if (whiteListLine == 0)
		{
		whiteList[whiteListRow][whiteListLine] = '\n';
		whiteListLine++;
		}*/
		whiteList[whiteListRow][whiteListLine] = ch;
		if (ch == '\n')
		{
			whiteListRow++;
			whiteListLine = 0;
		}
		else
			whiteListLine++;
		ch = fgetc(cs);
	}
}

int *buildNext(char *P)
{
	int m = strlen(P);
	int j = 0;
	int *N = new int[m];
	int t = N[0] = -1;
	while(j < m - 1)
	{
		if(0 > t || P[j] == P[t])
		{
			j++;
			t++;
			N[j] = (P[j] != P[t] ? t:N[t]);
		}
		else
		{
			t = N[t];
		}
	}
	return N;
}
//Kmp函数
int match(char *P, char *T)
{
	int *next = buildNext(P);
	int n = (int) strlen(T),i = 0;//文本串指针
	int m = (int) strlen(P),j = 0;//模式串指针
	while(j < m && i < n)
	{
		if(0 > j || T[i] == P[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}

	delete []next;
	return i - j;
}
int main()
{
	OpenFile();
	
	for (int i = 0; i < whiteListRow; i++) 
	{
		for (int i = 0; i < blackListRow; i++) 
		{
			if(!match(blackList[blackListRow], whiteList[whiteListRow]))
				printf("%s\n", whiteList[whiteListRow]);
		}
	}

	
	system("pause");
	return 0;
}

#endif