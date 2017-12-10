#include <iostream>  
#include <stdio.h>  
#include <string.h>
#include<algorithm>
//��ȷ��������Ķ��壺����һ����0-1��ɵľ����Ƿ����ҵ�һ���еļ��ϣ�ʹ�ü�����ÿһ�ж�ǡ�ð���һ��1
const int MN = 1005;//�������
const int MM = 1005;//�������
const int MNN = 1e5 + 5 + MM; //������  

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
        L[R[c]] = L[c];//��ͷ����  //c��ͷָ����ұߵ�Ԫ�ص����ָ��c��ͷָ����ߵ�Ԫ��
        R[L[c]] = R[c];//c��ͷָ�����ߵ�Ԫ�ص��Ҳ�ָ��c��ͷָ���ұߵ�Ԫ��
        for (int i = D[c]; i != c; i = D[i])//�������е�����Ԫ��
            for (int j = R[i]; j != i; j = R[j])
            {//���ڸ��е�ĳ��Ԫ�����ڵ��н��б���
                U[D[j]] = U[j];//�Ѹ�Ԫ�ش����������г�ȥ
                D[U[j]] = D[j];
                --S[Col[j]];//��Ԫ�����ڵ�����Ŀ��һ
            }
    }
    void resume(int c)        //�ָ�c��  
    {
        for (int i = U[c]; i != c; i = U[i])//ö�ٸ���Ԫ��
            for (int j = L[i]; j != i; j = L[j])//ö�ٸ���Ԫ�����ڵ���
                ++S[Col[U[D[j]] = D[U[j]] = j]];//D[U[j]]=j;U[D[j]]=j;S[Col[j]]++;
        L[R[c]] = R[L[c]] = c;//c��ͷָ����������
    }
    bool dance(int d) //ѡȡ��d��  
    {
        if (ansd != -1 && ansd < d)return 0;
        if (R[0] == 0)//ȫ��������
        {
            //ȫ������֮��Ĳ���  
            if(ansd==-1)ansd = d;
            else if (d < ansd) ansd = d;
            return 1;
        }
        int c = R[0];//��ͷ���ָ��ĵ�һ����
        for (int i = R[0]; i != 0; i = R[i])//ö����ͷָ��
            if (S[i]<S[c])//�ҵ�����Ԫ�ظ������ٵ�
                c = i;
        remove(c);//������ɾȥ
        for (int i = D[c]; i != c; i = D[i])
        {//ö�ٸ��е�Ԫ��
            ans[d] = Row[i];//��¼����Ԫ�ص���
            for (int j = R[i]; j != i; j = R[j])
                remove(Col[j]);//�����е�ĳ��Ԫ�ص����ϵ�Ԫ�����ڵ��ж�ɾȥ
            (dance(d + 1));
            for (int j = L[i]; j != i; j = L[j])
                resume(Col[j]);
        }
        resume(c);
        return 0;
    }
}dlx;

int main()
{
    int n, m,p;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d%d", &n, &m, &p);
        dlx.init(p, n*m);//���鵱���У����еĵ�Ԫ�񿴳���
        for (int pp = 1; pp <= p; pp++)
        {
            int x1, x2, y1, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            for (int i = x1 + 1; i <= x2; i++)
            {
                for (int j = y1 + 1; j <= y2; j++)
                {
                    dlx.link(pp, (i - 1)*m + j);
                }
            }
        }
        dlx.ansd = -1;
        dlx.dance(0);
        printf("%d\n", dlx.ansd);
    }
    return 0;
}