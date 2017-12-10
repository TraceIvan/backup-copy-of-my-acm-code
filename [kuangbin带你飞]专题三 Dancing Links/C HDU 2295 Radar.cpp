#include <iostream>  
#include <stdio.h>  
#include <string.h>  
//重复覆盖：找到一些行，使得这些行的集合中每列至少有一个1
const int MN = 55;//最大行数
const int MM = 55;//最大列数
const int MNN = MM*MN+MM+MN+10; //最大点数  

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
        //L[R[c]] = L[c];//表头操作  //c列头指针的右边的元素的左侧指向c列头指针左边的元素
        //R[L[c]] = R[c];//c列头指针的左边的元素的右侧指向c列头指针右边的元素
        //for (int i = D[c]; i != c; i = D[i])//遍历该列的所有元素
        //    for (int j = R[i]; j != i; j = R[j])
        //    {//对于该列的某个元素所在的行进行遍历
        //        U[D[j]] = U[j];//把该元素从其所在列中除去
        //        D[U[j]] = D[j];
        //        --S[Col[j]];//该元素所在的列数目减一
        //    }
        /*重复覆盖*//*c为元素编号，而非列号*//*即删除该元素所在的列，包括它自身和列头指针*/
        for (int i = D[c]; i != c; i = D[i])
        {
            L[R[i]] = L[i], R[L[i]] = R[i];
        }
    }
    void resume(int c)//恢复c列  
    {
        //for (int i = U[c]; i != c; i = U[i])//枚举该列元素
        //    for (int j = L[i]; j != i; j = L[j])//枚举该列元素所在的行
        //        ++S[Col[U[D[j]] = D[U[j]] = j]];//D[U[j]]=j;U[D[j]]=j;S[Col[j]]++;
        //L[R[c]] = R[L[c]] = c;//c列头指针左右相连
        /*重复覆盖*/
        for (int i = U[c]; i != c; i = U[i])
        {
            L[R[i]] = R[L[i]] = i;
        }
    }
    int f_check()//精确覆盖区估算剪枝  
    {
        /*
        强剪枝。这个 剪枝利用的思想是A*搜索中的估价函数。即，对于当前的递归深度K下的矩阵，估计其最好情况下（即最少还需要多少步）才能出解。也就是，如果将能够覆盖当 前列的所有行全部选中，去掉这些行能够覆盖到的列，将这个操作作为一层深度。重复此操作直到所有列全部出解的深度是多少。如果当前深度加上这个估价函数返 回值，其和已然不能更优（也就是已经超过当前最优解），则直接返回，不必再搜。
        */
        int vis[MNN];
        memset(vis, 0, sizeof(vis));
        int ret = 0;
        for (int c = R[0]; c != 0; c = R[c]) vis[c] = true;
        for (int c = R[0]; c != 0; c = R[c])
            if (vis[c])
            {
                ret++;
                vis[c] = false;
                for (int i = D[c]; i != c; i = D[i])
                    for (int j = R[i]; j != i; j = R[j])
                        vis[Col[j]] = false;
            }
        return ret;
    }
    bool dance(int d,int limit) //选取了d行,limit为限制选取的最大行数
    {
/*重复覆盖
1、如果矩阵为空，得到结果，返回
2、从矩阵中选择一列，以选取最少元素的列为优化方式
3、删除该列及其覆盖的行
4、对该列的每一行元素：删除一行及其覆盖的列，
5、进行下一层搜索，如果成功则返回
6、恢复现场，跳至4
7、恢复所选择行
*/
        if (d > limit)return false;
        if (d + f_check() > limit)return false;
        if (R[0] == 0)//全部覆盖了  
        {
            //全覆盖了之后的操作  
            ansd = d;
            return true;
        }
        int c = R[0];//表头结点指向的第一个列
        for (int i = R[0]; i != 0; i = R[i])//枚举列头指针
            if (S[i]<S[c])//找到列中元素个数最少的
                c = i;
        //remove(c);//将该列删去(精确覆盖)
        for (int i = D[c]; i != c; i = D[i])
        {//枚举该列的元素
            ans[d] = Row[i];//记录该列元素的行
            remove(i);//新增(重复覆盖)
            for (int j = R[i]; j != i; j = R[j])
                remove(j);//remove(Col[j])(精确覆盖)
            if (dance(d + 1, limit)) return true;
            for (int j = L[i]; j != i; j = L[j])
                resume(j);//resume(Col[j])(精确覆盖)
            resume(i);//新增(重复覆盖)
        }
        //resume(c);(精确覆盖)
        return false;
    }
}dlx;
struct node
{
    int x;
    int y;
}citys[55],radar[55];
double dis[55][55];
int main()
{
    int n, m,k;
    int t;
    scanf("%d", &t);
    
    while (t--)
    {
        double l = 0, r=0,maxx=0,maxy=0;
        scanf("%d%d%d", &n, &m, &k);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d%d", &citys[i].x, &citys[i].y);
            if (citys[i].x + citys[i].y > maxx + maxy)
            {
                maxx = citys[i].x, maxy = citys[i].y;
            }
        }
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &radar[i].x, &radar[i].y);
            if (radar[i].x + radar[i].y > maxx + maxy)
            {
                maxx = radar[i].x, maxy = radar[i].y;
            }
        }
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                dis[i][j] = sqrt((radar[i].x - citys[j].x)*(radar[i].x - citys[j].x) + (radar[i].y - citys[j].y)*(radar[i].y - citys[j].y));
            }
        }
        r = sqrt(maxx*maxx + maxy*maxy);
        while (r - l > 1e-7)
        {
            double mid = (l + r) / 2;
            dlx.init(m, n);
            for (int i = 1; i <= m; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (dis[i][j] <= mid) dlx.link(i, j);
                }
            }
            dlx.ansd = -1;
            if (dlx.dance(0,k)) r = mid;
            else l = mid;
        }
        printf("%.6lf\n", l);
    }
    return 0;
}