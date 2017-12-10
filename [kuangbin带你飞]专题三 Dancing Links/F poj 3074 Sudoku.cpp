#include <iostream>  
#include <stdio.h>  
#include <string.h>  
//精确覆盖问题的定义：给定一个由0-1组成的矩阵，是否能找到一个行的集合，使得集合中每一列都恰好包含一个1
const int MN = 9*9*9+10;//最大行数,共有9*9个格子，每个格子可以放1~9
const int MM = 9*9+9*9+9*9+9*9+100;//最大列数
//用第(i - 1) * 9 + j列为1表示i行j列的已经填数。一共占用81列。
//用81 + (i - 1) * 9 + v列表示第i行已经有v这个值。一共占用81列。
//用162 + (j - 1) * 9 + v列表示第j列已经有v这个值。一共占用81列。
//用243 + (3 * ((i - 1) / 3) + (j + 2) / 3 - 1) + v列表示第3*((i - 1) / 3) + (j + 2) / 3宫格已经有v这个值。一共占用81列。
const int MNN = MN*MM; //最大点数  

struct DLX
{
    int n, m, si;//n行数m列数si目前有的节点数  
                 //十字链表组成部分  
    int U[MNN], D[MNN], L[MNN], R[MNN], Row[MNN], Col[MNN];
    //第i个结点的U向上指针D下L左R右，所在位置Row行Col列  
    int H[MN], S[MM]; //记录行的选择情况和列的覆盖情况  
    int ansd, ans[MN];
    void init(int _n, int _m)  //初始化空表  
    {
        n = _n;
        m = _m;
        for (int i = 0; i <= m; i++) //初始化第一横行（表头）  
        {
            S[i] = 0;
            U[i] = D[i] = i;      //目前纵向的链是空的  
            L[i] = i - 1;
            R[i] = i + 1;         //横向的连起来  
        }
        R[m] = 0; L[0] = m;
        si = m;                 //目前用了前0~m个结点  
        for (int i = 1; i <= n; i++)
            H[i] = -1;
    }
    void link(int r, int c)    //插入点(r,c)  
    {
        ++S[Col[++si] = c];     //si++;Col[si]=c;S[c]++;  
        Row[si] = r;//si该结点的行数为r
        D[si] = D[c];//向下指向c的下面的第一个结点
        U[D[c]] = si;//c的下面的第一个结点的上面为si
        U[si] = c;//si的上面为列指针
        D[c] = si;//列指针指向的第一个该列中的元素设为si
        if (H[r]<0)//如果第r行没有元素
            H[r] = L[si] = R[si] = si;
        else
        {
            R[si] = R[H[r]];//si的右边为行指针所指的右边第一个元素
            L[R[H[r]]] = si;//行指针所指的右边第一个元素的左侧为si
            L[si] = H[r];//si的左侧为行指针
            R[H[r]] = si;//行指针的右侧为si
        }
    }
    void remove(int c)        //列表中删掉c列  
    {
        L[R[c]] = L[c];//表头操作  //c列头指针的右边的元素的左侧指向c列头指针左边的元素
        R[L[c]] = R[c];//c列头指针的左边的元素的右侧指向c列头指针右边的元素
        for (int i = D[c]; i != c; i = D[i])//遍历该列的所有元素
            for (int j = R[i]; j != i; j = R[j])
            {//对于该列的某个元素所在的行进行遍历
                U[D[j]] = U[j];//把该元素从其所在列中除去
                D[U[j]] = D[j];
                --S[Col[j]];//该元素所在的列数目减一
            }
    }
    void resume(int c)        //恢复c列  
    {
        for (int i = U[c]; i != c; i = U[i])//枚举该列元素
            for (int j = L[i]; j != i; j = L[j])//枚举该列元素所在的行
                ++S[Col[U[D[j]] = D[U[j]] = j]];//D[U[j]]=j;U[D[j]]=j;S[Col[j]]++;
        L[R[c]] = R[L[c]] = c;//c列头指针左右相连
    }
    bool dance(int d) //选取了d行  
    {
        if (R[0] == 0)//全部覆盖了  
        {
            //全覆盖了之后的操作  
            ansd = d;
            return 1;
        }
        int c = R[0];//表头结点指向的第一个列
        for (int i = R[0]; i != 0; i = R[i])//枚举列头指针
            if (S[i]<S[c])//找到列中元素个数最少的
                c = i;
        remove(c);//将该列删去
        for (int i = D[c]; i != c; i = D[i])
        {//枚举该列的元素
            ans[d] = Row[i];//记录该列元素的行
            for (int j = R[i]; j != i; j = R[j])
                remove(Col[j]);//将该列的某个元素的行上的元素所在的列都删去
            if (dance(d + 1))
                return 1;
            for (int j = L[i]; j != i; j = L[j])
                resume(Col[j]);
        }
        resume(c);
        return 0;
    }
}dlx;
char s[90],path[90];
struct node
{
    int r, c, v;
}nds[MN];
int main()
{
    while (~scanf("%s",s))
    {
        if (s[0] == 'e')break;
        dlx.init(9*9*9,9*9*4);
        int r=1;
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                if (s[(i - 1) * 9 + j - 1] == '.')
                {
                    for (int z = 1; z <= 9; z++)
                    {
                        dlx.link(r, (i - 1) * 9 + j);
                        dlx.link(r, 81 + (i - 1) * 9 + z);
                        dlx.link(r, 162 + (j - 1) * 9 + z);
                        dlx.link(r, 243 + (((i - 1) / 3) * 3 + (j + 2) / 3 - 1) * 9 + z);
                        nds[r].r = i, nds[r].c = j, nds[r].v = z;
                        r++;
                    }
                }
                else
                {
                    int z = s[(i - 1) * 9 + j - 1] - '0';
                    dlx.link(r, (i - 1) * 9 + j);
                    dlx.link(r, 81 + (i - 1) * 9 + z);
                    dlx.link(r, 162 + (j - 1) * 9 + z);
                    dlx.link(r, 243 + (((i - 1) / 3) * 3 + (j + 2) / 3 - 1) * 9 + z);
                    nds[r].r = i, nds[r].c = j, nds[r].v = z;
                    r++;
                }
            }
        }
        dlx.ansd = -1;
        dlx.dance(0);
        int deep = dlx.ansd;
        for (int i = 0; i < deep; i++)
        {
            int posr = dlx.ans[i];
            path[(nds[posr].r - 1) * 9 + nds[posr].c - 1] = '0' + nds[posr].v;
        }
        path[deep] = '\0';
        printf("%s\n", path);
    }
    return 0;
}
/*
.2738..1..1...6735.......293.5692.8...........6.1745.364.......9518...7..8..6534.
......52..8.4......3...9...5.1...6..2..7........3.....6...1..........7.4.......3.
end
*/