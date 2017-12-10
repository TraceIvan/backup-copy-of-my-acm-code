#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<map>
#include<queue>
#include<string>
using namespace std;

#define sigma_size 26       
#define maxnode 11000    //节点个数 
#define MAXS 155
map<string, int> ms;
struct Trie//Trie模板  
{
    int Fail[maxnode];//每个节点的失配指针指向的是以当前节点表示的字符为最后一个字符的最长当前字符串的后缀字符串的最后一个节点。
    int last[maxnode]; //last[j]表示结点j沿着失配指针往回走时，遇到的下一个单词结点编号--后缀链接
    int cnt[MAXS];//统计每个字符串在文本串的出现次数
    int ch[maxnode][sigma_size];//maxnode表示节点个数，每个节点有26种情况，所以ch数组能表示所有情况  
    int val[maxnode];//存节点的信息，val[i]>0当且仅当结点i是单词结点
    int sz;//节点总个数  
    void clear()
    {//初始化 
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        memset(cnt, 0, sizeof(cnt));
        ms.clear();
    } 
    int idx(char c)
    {//字符c的编号
        return c - 'a';
    }

    void insert(char *s, int v)
    {//插入编号为v的字符串，建立字典树
        int u = 0, n = strlen(s);
        for (int i = 0; i<n; i++)
        {
            int c = idx(s[i]);
            if (!ch[u][c])
            { //节点不存在  
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;//中间结点的附加信息为0
                ch[u][c] = sz++;//新建结点
            }
            u = ch[u][c];//这样存就可以保证从每个节点，都能访问他的下一个节点了  
        }
        val[u] = v;//字符串最后一个字符的附加信息为v（这里为模式串编号）
        ms[string(s)] = v;//为该字符串建立编号映射
    }

    void getFail()
    {
        queue<int> q;
        Fail[0] = 0;
        for (int c = 0; c<sigma_size; c++)
        {//将Trie树中，root节点的分支节点，放入队列，初始化
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
    //在文本串t中找模板
    void find(char *t)
    {
        int n = strlen(t);
        int j = 0;//当前结点编号，初始为根结点
        for (int i = 0; i<n; i++)//文本串当前指针
        {
            int c = idx(t[i]);
            //while (j && !ch[j][c]) j = f[j];//顺着失配边走，直到可以匹配
            j = ch[j][c];
            if (val[j]) print(j);
            else if (last[j]) print(last[j]);
        }
    }
    //递归打印以结点j结尾的所有字符串
    void print(int j)
    {
        if (j)
        {
            cnt[val[j]]++;//计数器+1
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