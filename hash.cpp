#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <iostream>


using namespace std;

#define HASHSIZE 101
#define max 20
//��ʼ����ϣ��
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

	//��ʼ��
	initia_hash();

	for(int i = 0; i < 5; i++){
		if(create_hash_table(name[i], desc[i]))
		{
			continue;//��������ɹ�
			//�ͼ���
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
	//�����������֮ǰ����ʵphone��Ӧ��desc��58822�����Զ�Ӧ��desc�ᱻ�ͷŵ�

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
		hashtab[i] = NULL;//����ϣ��ͷָ������  
	}
}	
node *search_hash(char *s)
{
	unsigned int hi = c_hash(s);
	//��������ַ���hash��ȥ����ϣ�����Ƿ��Ѿ������˶�Ӧ��ͷ�ڵ�
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
	//��������ַ���s��һ��hash
	/*for(hi = 0; *s != '\n'; s++){
		hi = *s + hi * 31;
	}*/
	return hi % HASHSIZE;//���ص�ֵ��������ַ�����hashֵ

}
int create_hash_table(char *name, char *desc)
{
	unsigned int hi = 0;
	node *p;
	//�Ȳ���*name�ڹ�ϣ�����棬������ֵ
	if((p = search_hash(name)) == NULL)
	{
		hi = c_hash(name);//�������name����һ��hash
		p = (node *)malloc(sizeof(node));
		if(p == NULL)
		{
			return 0;
		}//����ʧ��
		p->next = NULL;
		p->name = (char *)malloc(max * sizeof(char));
		if(p->name == NULL)
		{
			return 0;
		}
		strcpy(p->name, name);
		hashtab[hi] = p;
		//��name�Ĺ�ϣֵȷ��ͷ�ڵ�p��λ�ã�p��������Ա�ֱ����name��desc�ַ�����һһ��Ӧ
	}
	else
	{
		//���search_hash����ֵ���ǿգ���˼�����п�
		free(p->desc);
	}
	p->desc = (char *)malloc(max * sizeof(char));
	if(p->desc == NULL)
	{
		return 0;
	}
	strcpy(p->desc, desc);
	return 1;//ֻҪ�ڴ�����ɹ����Ϳ��Լ�������
}

char* get_desc_pointer(char *c_name)
{
	node *p = search_hash(c_name);
	//��һ��hashtable���Ƿ��ж�Ӧ��ͷ�ڵ�

	if(p == NULL)
	{
		return NULL;
	}

	else
	{
		return p->desc;
	}//�еĻ����ͻ᷵���Ǹ�desc
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