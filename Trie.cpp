#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
typedef struct Trie_node
{
	int count;//统计单词前缀出现的次数
	struct Trie_node* next[26];//指向各个子树的指针
	bool exist;//标记该节点是否构成单词
}TrieNode, *Trie;
Trie root;
char blackList[1000000][20];
char whitelist[1000000][20];
int blackListLine = 0;
int blackListRow = 0;
int whitelistLine = 0;
int whitelistRow = 0;
void OpenFile()
{
	printf("Please input the blackList:\n");
	FILE *bfs;
	scanf("%s", bfilename);
	if (fopen_s(&bfs, bfilename, "r"))
	{
		printf("打开文件失败！\n");
		exit(0);
	}
	
	char bch;
	bch = fgetc(bfs);
	while (bch != EOF)
	{
		
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
		
		whitelist[whitelistRow][whitelistLine] = ch;
		if (ch == '\n')
		{
			whitelistRow++;
			whitelistLine = 0;
		}
		else
			whitelistLine++;
		ch = fgetc(cs);
	}
}
TrieNode *creatTrieNode()
{
	TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
	node->count = 0;
	node->exist = false;
	memset(node->next, 0, sizeof(node->next));//全部初始化为空指针
	return node;
}//这个函数用来创建一个节点


int change(char ch)
{
	if (ch == '.')
		return 10;
	else if (ch == '\n')
		return 11;
	else
		return ch - '0';
}
void  Trie_insert(Trie root, char *word)
{
	Trie node = root;
	char *p = word;
	int id;
	while (*p)
	{
		id = change(*p);
		//先把字符串进行肢解
		if (node->next[id] == NULL)
		{
			//如果相应的节点为空
			node->next[id] = creatTrieNode();
			//就沿着这个节点往后一直创建节点
		}
		node = node->next[id];
		p++;
		node->count++;
	}
	//node->exist = true;
	//完成一个ip地址的插入
	
}
int Trie_search(Trie root, char* word)  
{  
    Trie node = root;  
    char *p = word;  
    int id;  
    while(*p)  
    {  
        id = change(*p);  
        //肢解待查找的字符串
        node = node->next[id];  
        ++p; 
         if(node == NULL)  
            return 0;  
    }  
    return node->exist;  
}//查找函数
int main()
{
	//打开文件
	OpenFile();


	//将黑名单存储到Trie树
	for (int i = 0; i < blackListRow; i++) {
		Trie_insert(root, blackList[blackListRow]);
	}


	//查找所给名单是否在Trie树中
	for(int i = 0; i < whitelistRow; i++){
		if(Trie_search(root,whitelist[whitelistRow]))
			printf("%s\n", whitelist[whitelistRow]);
	}
	system("pause");
	return 0;
}