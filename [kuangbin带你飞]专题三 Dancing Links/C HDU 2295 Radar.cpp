#include <iostream>  
#include <stdio.h>  
#include <string.h>  
//�ظ����ǣ��ҵ�һЩ�У�ʹ����Щ�еļ�����ÿ��������һ��1
const int MN = 55;//�������
const int MM = 55;//�������
const int MNN = MM*MN+MM+MN+10; //������  

struct DLX
{
    int n, m, si;//n����m����siĿǰ�еĽڵ���  
                 //ʮ��������ɲ���  
    int U[MNN], D[MNN], L[MNN], R[MNN], Row[MNN], Col[MNN];
    //��i������U����ָ��D��L��R�ң�����λ��Row��Col��  
    int H[MN], S[MM]; //��¼�е�ѡ��������еĸ������  
    int ansd, ans[MN];
    void init(int _n, int _m)  //��ʼ���ձ�  
    {
        n = _n;
        m = _m;
        for (int i = 0; i <= m; i++) //��ʼ����һ���У���ͷ��  
        {
            S[i] = 0;
            U[i] = D[i] = i;      //Ŀǰ��������ǿյ�  
            L[i] = i - 1;
            R[i] = i + 1;         //�����������  
        }
        R[m] = 0; L[0] = m;
        si = m;                 //Ŀǰ����ǰ0~m�����  
        for (int i = 1; i <= n; i++)
            H[i] = -1;
    }
    void link(int r, int c)    //�����(r,c)  
    {
        ++S[Col[++si] = c];     //si++;Col[si]=c;S[c]++;  
        Row[si] = r;//si�ý�������Ϊr
        D[si] = D[c];//����ָ��c������ĵ�һ�����
        U[D[c]] = si;//c������ĵ�һ����������Ϊsi
        U[si] = c;//si������Ϊ��ָ��
        D[c] = si;//��ָ��ָ��ĵ�һ�������е�Ԫ����Ϊsi
        if (H[r]<0)//�����r��û��Ԫ��
            H[r] = L[si] = R[si] = si;
        else
        {
            R[si] = R[H[r]];//si���ұ�Ϊ��ָ����ָ���ұߵ�һ��Ԫ��
            L[R[H[r]]] = si;//��ָ����ָ���ұߵ�һ��Ԫ�ص����Ϊsi
            L[si] = H[r];//si�����Ϊ��ָ��
            R[H[r]] = si;//��ָ����Ҳ�Ϊsi
        }
    }
    void remove(int c)        //�б���ɾ��c��  
    {
        //L[R[c]] = L[c];//��ͷ����  //c��ͷָ����ұߵ�Ԫ�ص����ָ��c��ͷָ����ߵ�Ԫ��
        //R[L[c]] = R[c];//c��ͷָ�����ߵ�Ԫ�ص��Ҳ�ָ��c��ͷָ���ұߵ�Ԫ��
        //for (int i = D[c]; i != c; i = D[i])//�������е�����Ԫ��
        //    for (int j = R[i]; j != i; j = R[j])
        //    {//���ڸ��е�ĳ��Ԫ�����ڵ��н��б���
        //        U[D[j]] = U[j];//�Ѹ�Ԫ�ش����������г�ȥ
        //        D[U[j]] = D[j];
        //        --S[Col[j]];//��Ԫ�����ڵ�����Ŀ��һ
        //    }
        /*�ظ�����*//*cΪԪ�ر�ţ������к�*//*��ɾ����Ԫ�����ڵ��У��������������ͷָ��*/
        for (int i = D[c]; i != c; i = D[i])
        {
            L[R[i]] = L[i], R[L[i]] = R[i];
        }
    }
    void resume(int c)//�ָ�c��  
    {
        //for (int i = U[c]; i != c; i = U[i])//ö�ٸ���Ԫ��
        //    for (int j = L[i]; j != i; j = L[j])//ö�ٸ���Ԫ�����ڵ���
        //        ++S[Col[U[D[j]] = D[U[j]] = j]];//D[U[j]]=j;U[D[j]]=j;S[Col[j]]++;
        //L[R[c]] = R[L[c]] = c;//c��ͷָ����������
        /*�ظ�����*/
        for (int i = U[c]; i != c; i = U[i])
        {
            L[R[i]] = R[L[i]] = i;
        }
    }
    int f_check()//��ȷ�����������֦  
    {
        /*
        ǿ��֦����� ��֦���õ�˼����A*�����еĹ��ۺ������������ڵ�ǰ�ĵݹ����K�µľ��󣬹������������£������ٻ���Ҫ���ٲ������ܳ��⡣Ҳ���ǣ�������ܹ����ǵ� ǰ�е�������ȫ��ѡ�У�ȥ����Щ���ܹ����ǵ����У������������Ϊһ����ȡ��ظ��˲���ֱ��������ȫ�����������Ƕ��١������ǰ��ȼ���������ۺ����� ��ֵ�������Ȼ���ܸ��ţ�Ҳ�����Ѿ�������ǰ���Ž⣩����ֱ�ӷ��أ��������ѡ�
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
    bool dance(int d,int limit) //ѡȡ��d��,limitΪ����ѡȡ���������
    {
/*�ظ�����
1���������Ϊ�գ��õ����������
2���Ӿ�����ѡ��һ�У���ѡȡ����Ԫ�ص���Ϊ�Ż���ʽ
3��ɾ�����м��串�ǵ���
4���Ը��е�ÿһ��Ԫ�أ�ɾ��һ�м��串�ǵ��У�
5��������һ������������ɹ��򷵻�
6���ָ��ֳ�������4
7���ָ���ѡ����
*/
        if (d > limit)return false;
        if (d + f_check() > limit)return false;
        if (R[0] == 0)//ȫ��������  
        {
            //ȫ������֮��Ĳ���  
            ansd = d;
            return true;
        }
        int c = R[0];//��ͷ���ָ��ĵ�һ����
        for (int i = R[0]; i != 0; i = R[i])//ö����ͷָ��
            if (S[i]<S[c])//�ҵ�����Ԫ�ظ������ٵ�
                c = i;
        //remove(c);//������ɾȥ(��ȷ����)
        for (int i = D[c]; i != c; i = D[i])
        {//ö�ٸ��е�Ԫ��
            ans[d] = Row[i];//��¼����Ԫ�ص���
            remove(i);//����(�ظ�����)
            for (int j = R[i]; j != i; j = R[j])
                remove(j);//remove(Col[j])(��ȷ����)
            if (dance(d + 1, limit)) return true;
            for (int j = L[i]; j != i; j = L[j])
                resume(j);//resume(Col[j])(��ȷ����)
            resume(i);//����(�ظ�����)
        }
        //resume(c);(��ȷ����)
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