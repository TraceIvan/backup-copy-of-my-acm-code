#include <iostream>  
#include <stdio.h>  
#include <string.h>  
//��ȷ��������Ķ��壺����һ����0-1��ɵľ����Ƿ����ҵ�һ���еļ��ϣ�ʹ�ü�����ÿһ�ж�ǡ�ð���һ��1
const int MN = 16*16*16 + 10;//�������,����16*16�����ӣ�ÿ�����ӿ��Է�1~16��A~P��
const int MM = 16*16*4 + 100;//�������
const int MNN = MN*MM;//������  

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
        if (R[0] == 0)//ȫ��������  
        {
            //ȫ������֮��Ĳ���  
            ansd = d;
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
            if (dance(d + 1))
                return 1;
            for (int j = L[i]; j != i; j = L[j])
                resume(Col[j]);
        }
        resume(c);
        return 0;
    }
}dlx;
char s[20];
char path[16 * 16 + 10];
struct node
{
    int r, c, v;
}nds[MN];
void addlink(int r, int c, int v, int& cnt)
{
    dlx.link(cnt, (r - 1) * 16 + c);
    dlx.link(cnt, 16*16 + (r - 1) * 16 + v);
    dlx.link(cnt, 16*16*2 + (c - 1) * 16 + v);
    dlx.link(cnt, 16*16*3 + (((r-1)/4)*4+(c-1)/4) * 16 + v);
    nds[cnt].r = r, nds[cnt].c = c, nds[cnt].v = v;
    cnt++;
}
int main()
{
    while (~scanf("%s", s))
    {
        
        dlx.init(16*16*16, 16 * 16 * 4);
        int r = 1;
        for (int i = 0; i < 16; i++)
        {
            if (s[i] == '-')
            {
                for (int k = 1; k <= 16; k++)
                {
                    addlink(1, i + 1, k,r);
                }
            }
            else
            {
                int v = s[i] - 'A' + 1;
                addlink(1, i + 1, v, r);
            }
        }
        for (int i = 2; i <= 16; i++)
        {
            scanf("%s", s);
            for (int j = 1; j <= 16; j++)
            {
                if (s[j-1] == '-')
                {
                    for (int k = 1; k <= 16; k++)
                    {
                        addlink(i, j, k, r);
                    }
                }
                else
                {
                    int v = s[j-1] - 'A' + 1;
                    addlink(i,j, v, r);
                }
            }
        }
        dlx.ansd = -1;
        dlx.dance(0);
        int deep = dlx.ansd;
        for (int i = 0; i < deep; i++)
        {
            int posr = dlx.ans[i];
            path[(nds[posr].r - 1) * 16 + nds[posr].c - 1] = 'A' + nds[posr].v-1;
        }
        path[deep] = '\0';
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++) printf("%c", path[i * 16 + j]);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
