#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <iostream>


using namespace std;

#define HASHSIZE 101
#define max 20
//初始化哈希表
typedef struct _node
{
	char *name;
	char *desc;
	struct _node *next;
}node;
void initia_hash();
int create_hash_table(char *, char *);
void delete_hash();
node * search_hash(char *s);
unsigned int c_hash(char *s);
char* get_desc_pointer(char *c_name);


static node *hashtab[HASHSIZE];

int main(int argc, char const *argv[])
{
	
	char name[5][10] = { "name","address","phone","k101","k102" };
	char desc[5][10] = { "LWJ","NINGBO","588222","value1","value2" };

	//初始化
	initia_hash();

	for(int i = 0; i < 5; i++){
		if(create_hash_table(name[i], desc[i]))
		{
			continue;//如果构建成功
			//就继续
		}
		else
		{
			cout << "fail to create hash table\n";
		}
	}

	cout << "done\n";
	cout << "To see if we are wrong ";
	char a[] = "phone";
	char b[] = "13686888888";
	if(get_desc_pointer(name[4])!=NULL)  
    {  
        printf("k102 is %s\n",get_desc_pointer(name[4]));  
    }  
    else  
    {  
        cout<<"something wrong in function get_desc_pointer\n";  
    }  
	//create_hash_table("phone", "13686888888");
	create_hash_table(a, b);
	//调用这个函数之前，其实phone对应的desc是58822，所以对应的desc会被释放掉

	char c[] = "k101";
	char d[] = "phone";
	printf("if we are right ,we should see %s and %s\n", get_desc_pointer(c), get_desc_pointer(d));

	delete_hash();
	system("pause");
	return 0;
}
void initia_hash()
{
	for (int i = 0; i<HASHSIZE; i++)
	{
		hashtab[i] = NULL;//将哈希表头指针至空  
	}
}	
node *search_hash(char *s)
{
	unsigned int hi = c_hash(s);
	//将传入的字符串hash后去看哈希表中是否已经创建了对应的头节点
	node *p = hashtab[hi];
	return p;
}
unsigned int c_hash(char *s)
{
	unsigned int hi = 0;
	while (1)
	{
		if (*s == '\0')
			return hi % HASHSIZE;
		hi = *s + hi * 31;
		s++;
	}
	//将传入的字符串s做一次hash
	/*for(hi = 0; *s != '\n'; s++){
		hi = *s + hi * 31;
	}*/
	return hi % HASHSIZE;//返回的值就是这个字符串的hash值

}
int create_hash_table(char *name, char *desc)
{
	unsigned int hi = 0;
	node *p;
	//先查找*name在哈希表里面，看返回值
	if((p = search_hash(name)) == NULL)
	{
		hi = c_hash(name);//将传入的name进行一次hash
		p = (node *)malloc(sizeof(node));
		if(p == NULL)
		{
			return 0;
		}//申请失败
		p->next = NULL;
		p->name = (char *)malloc(max * sizeof(char));
		if(p->name == NULL)
		{
			return 0;
		}
		strcpy(p->name, name);
		hashtab[hi] = p;
		//由name的哈希值确定头节点p的位置，p的两个成员分别存有name和desc字符串，一一对应
	}
	else
	{
		//如果search_hash返回值不是空，意思就是有咯
		free(p->desc);
	}
	p->desc = (char *)malloc(max * sizeof(char));
	if(p->desc == NULL)
	{
		return 0;
	}
	strcpy(p->desc, desc);
	return 1;//只要内存申请成功，就可以继续创建
}

char* get_desc_pointer(char *c_name)
{
	node *p = search_hash(c_name);
	//看一看hashtable中是否有对应的头节点

	if(p == NULL)
	{
		return NULL;
	}

	else
	{
		return p->desc;
	}//有的话，就会返回那个desc
}

void delete_hash()
{
	node *p, *t;

	for(int i = 0; i < HASHSIZE; i++){
		if(hashtab[i] != NULL)
		{
			for(p = hashtab[i]; p != NULL; )
			{
				t = p->next;
				free(p->name);
				free(p->desc);

				free(p);
				p = NULL;
				p = t;
			}
		}
	}
}