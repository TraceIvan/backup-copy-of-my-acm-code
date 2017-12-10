#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<map>
#include<queue>
#include<string>
using namespace std;

#define sigma_size 26       
#define maxnode 11000    //�ڵ���� 
#define MAXS 155
map<string, int> ms;
struct Trie//Trieģ��  
{
    int Fail[maxnode];//ÿ���ڵ��ʧ��ָ��ָ������Ե�ǰ�ڵ��ʾ���ַ�Ϊ���һ���ַ������ǰ�ַ����ĺ�׺�ַ��������һ���ڵ㡣
    int last[maxnode]; //last[j]��ʾ���j����ʧ��ָ��������ʱ����������һ�����ʽ����--��׺����
    int cnt[MAXS];//ͳ��ÿ���ַ������ı����ĳ��ִ���
    int ch[maxnode][sigma_size];//maxnode��ʾ�ڵ������ÿ���ڵ���26�����������ch�����ܱ�ʾ�������  
    int val[maxnode];//��ڵ����Ϣ��val[i]>0���ҽ������i�ǵ��ʽ��
    int sz;//�ڵ��ܸ���  
    void clear()
    {//��ʼ�� 
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        memset(cnt, 0, sizeof(cnt));
        ms.clear();
    } 
    int idx(char c)
    {//�ַ�c�ı��
        return c - 'a';
    }

    void insert(char *s, int v)
    {//������Ϊv���ַ����������ֵ���
        int u = 0, n = strlen(s);
        for (int i = 0; i<n; i++)
        {
            int c = idx(s[i]);
            if (!ch[u][c])
            { //�ڵ㲻����  
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;//�м���ĸ�����ϢΪ0
                ch[u][c] = sz++;//�½����
            }
            u = ch[u][c];//������Ϳ��Ա�֤��ÿ���ڵ㣬���ܷ���������һ���ڵ���  
        }
        val[u] = v;//�ַ������һ���ַ��ĸ�����ϢΪv������Ϊģʽ����ţ�
        ms[string(s)] = v;//Ϊ���ַ����������ӳ��
    }

    void getFail()
    {
        queue<int> q;
        Fail[0] = 0;
        for (int c = 0; c<sigma_size; c++)
        {//��Trie���У�root�ڵ�ķ�֧�ڵ㣬������У���ʼ��
            int u = ch[0][c];
            if (u)
            {
                Fail[u] = 0;  q.push(u);  last[u] = 0;
            }
        }
        while (!q.empty())
        {
            int r = q.front(); q.pop();
            for (int c = 0; c<sigma_size; c++)
            {
                int u = ch[r][c];
                if (!u)//if(!u)continue;
                {
                    ch[r][c] = ch[Fail[r]][c]; continue;
                }
                q.push(u);
                int v = Fail[r];
                while (v && !ch[v][c])  v = Fail[v];
                Fail[u] = ch[v][c];
                last[u] = val[Fail[u]] ? Fail[u] : last[Fail[u]];
            }
        }
    }
    //���ı���t����ģ��
    void find(char *t)
    {
        int n = strlen(t);
        int j = 0;//��ǰ����ţ���ʼΪ�����
        for (int i = 0; i<n; i++)//�ı�����ǰָ��
        {
            int c = idx(t[i]);
            //while (j && !ch[j][c]) j = f[j];//˳��ʧ����ߣ�ֱ������ƥ��
            j = ch[j][c];
            if (val[j]) print(j);
            else if (last[j]) print(last[j]);
        }
    }
    //�ݹ��ӡ�Խ��j��β�������ַ���
    void print(int j)
    {
        if (j)
        {
            cnt[val[j]]++;//������+1
            //printf("%d: %d\n", j, val[j]);
            print(last[j]);
        }
    }
};


const int MAXN = 1e6 + 10;
Trie acTree;
char p[MAXS][80];
char text[MAXN];
int main()
{
    int t;
    int i, j, k;
    while (scanf("%d", &t), t)
    {
        acTree.clear();
        for (i = 1; i <= t; i++)
        {
            scanf("%s", p[i]);
            acTree.insert(p[i], i);
        }
        acTree.getFail();
        scanf("%s", text);
        acTree.find(text);
        int best = -1;
        for (i = 1; i <= t; i++)
            if (acTree.cnt[i]>best) best = acTree.cnt[i];
        printf("%d\n", best);
        for (i = 1; i <= t; i++)
            if (acTree.cnt[ms[string(p[i])]] == best)
                printf("%s\n", p[i]);
    }
    return 0;
}