 ////�ٿ�KMP�㷨
 //#include <iostream>
 //#include <cstdio>
 //int next[100];
 //void GetNext(char *p, int next[])
 //{
 //	int pLen = strlen(p);
 //	next[0] = -1;
 //	int k = -1;
 //	int j = 0;
 //	while(j < pLen - 1)
 //	{
 //		//p[k]��ʾǰ׺,p[j]��ʾ��׺
 //		if(k == -1 || p[j] == p[k])
 //		{
 //			k++;
 //			j++;
 //			next[j] = k;
 //		}
 //		else
 //		{
 //			k = next[k];//���û�У�����Сһ�����ͬǰ׺
 //		}
 //	}
 //}


 //int KmpSearch(char * s, char *p)
 //{
 //	int i = 0;
 //	int j = 0;
 //	int sLen = strlen(s);
 //	int pLen = strlen(p);

 //	while(i < sLen && j < sLen)
 //	{
 //		///���j = -1���ߵ�ǰ�ַ���ƥ��ɹ�������i++����j++
 //		if(j == -1 || s[i] == p[j])
 //		{
 //			i++;
 //			j++;
 //		}
 //		else
 //		{
 //			j = next[j];
 //		}
 //	}
 //	if(j == pLen - 1)
 //		return i - j;
 //	else
 //		return -1;
 //}

 //int main(int argc, char const *argv[])
 //{

 //	char p[] = "abcdef";
 //	char s[] = "a";
 //	GetNext(p,next);
 //	int i = KmpSearch(s,p);
 //	printf("i = %d\n", i);
 //	system("pause");

 //	return 0;
 //}

#if 1
#include <iostream>
#include <cstdio>
#include <cstring>

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
//Kmp����
int match(char *P, char *T)
{
	int *next = buildNext(P);
	int n = (int) strlen(T),i = 0;//�ı���ָ��
	int m = (int) strlen(P),j = 0;//ģʽ��ָ��
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
	
	
	system("pause");
	return 0;
}

#endif