#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100017;

char strm[MAXN];//�����
char strz[MAXN];//�����������ĺ�����
char str[MAXN]; //�����ת����
char s[MAXN];   //���ĺ�����ת����
int Next[MAXN];

void getnext(char T[], int len)
{
    int i = 0, j = -1;
    Next[0] = -1;
    while (i < len)
    {
        if (j == -1 || T[i] == T[j])
        {
            i++, j++;
            Next[i] = j;
        }
        else
            j = Next[j];
    }
}
int KMP(int len1, int len2)
{
    int i, j = 0;
    if (len1 % 2 == 1)
    {
        i = len1 / 2 + 1;
    }
    else
        i = len1 / 2;
    while (i < len1 && j < len2)
    {
        if (j == -1 || strz[i] == s[j])
        {
            i++, j++;
        }
        else
            j = Next[j];
    }
    return j;//jֵ����ľ���ǰ׺�ͺ�׺�����ȳ���
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", strm);
        for (int i = 0; i < 26; i++)
        {
            char ss = strm[i];
            str[ss] = i;
        }
        scanf("%s", strz);
        int lenz = strlen(strz);
        for (int i = 0; i < lenz; i++)//�����ĺ����İ��������ת��
        {
            int tt = str[strz[i]];
            s[i] = 'a' + tt;
        }
        int lens = strlen(s);
        getnext(s, lens);
        int j = KMP(lenz, lens);//�õ����ĵĸ���
        if (j * 2 == lenz)//ǰ׺�ͺ�׺ǡ��ռһ��
        {
            printf("%s\n", strz);
        }
        else
        {
            int tt = lenz - j;
            printf("%s", strz);
            for (int i = j; i < tt; i++)//��Ҫ��ӵ�����
            {
                printf("%c", s[i]);
            }
            printf("\n");
        }
    }
    return 0;
}
