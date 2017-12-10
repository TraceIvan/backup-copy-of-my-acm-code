#include <iostream>  
#include <stdio.h>  
#include <string.h>  
//��ȷ��������Ķ��壺����һ����0-1��ɵľ����Ƿ����ҵ�һ���еļ��ϣ�ʹ�ü�����ÿһ�ж�ǡ�ð���һ��1
const int MN = 9 * 9 * 9 + 10;//�������,����9*9�����ӣ�ÿ�����ӿ��Է�1~9
const int MM = 9 * 9 + 9 * 9 + 9 * 9 + 9 * 9 + 100;//�������
                                                   //�õ�(i - 1) * 9 + j��Ϊ1��ʾi��j�е��Ѿ�������һ��ռ��81�С�
                                                   //��81 + (i - 1) * 9 + v�б�ʾ��i���Ѿ���v���ֵ��һ��ռ��81�С�
                                                   //��162 + (j - 1) * 9 + v�б�ʾ��j���Ѿ���v���ֵ��һ��ռ��81�С�
                                                   //��243 + (3 * ((i - 1) / 3) + (j + 2) / 3 - 1) + v�б�ʾ��3*((i - 1) / 3) + (j + 2) / 3�����Ѿ���v���ֵ��һ��ռ��81�С�
const int MNN = MN*MM; //������  
int Count;//���ֽ������
bool iscontinue;//���ҵ����ּ����Ͻ������ʱ�˳�
struct DLX
{
    int n, m, si;//n����m����siĿǰ�еĽڵ���  
                 //ʮ��������ɲ���  
    int U[MNN], D[MNN], L[MNN], R[MNN], Row[MNN], Col[MNN];
    //��i������U����ָ��D��L��R�ң�����λ��Row��Col��  
    int H[MN], S[MM]; //��¼�е�ѡ��������еĸ������  
    int ansd, ans[MN];
    int tans[MN];//�����һ���������
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
    void dance(int d) //ѡȡ��d��  
    {
        if (!iscontinue) return;
        if (R[0] == 0)//ȫ��������  
        {
            //ȫ������֮��Ĳ���  
            ansd = d;
            if (Count == 0)
            {
                memcpy(tans, ans, sizeof(ans));
                Count++;
            }
            else if (Count == 1) iscontinue = false;
            return;
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
            dance(d + 1);
            for (int j = L[i]; j != i; j = L[j])
                resume(Col[j]);
        }
        resume(c);
        return ;
    }
}dlx;
struct node
{
    int r, c, v;
}nds[MN];
int dr[] = { 0,0,1,-1 };
int dc[] = { 1,-1,0,0 };
int mp[10][10];//��¼ֵ
bool wall[10][10][2][2];//��¼ĳ�������������Ƿ���ǽ
//[0][0]��[0][1]�ң�[1][0]�ϣ�[1][1]��
int block[10][10];//��Ƿֿ�
int solution[10][10];
void DFS(int r, int c, int flag)
{
    block[r][c] = flag;
    if (!wall[r][c][0][0]&&!block[r][c-1]) DFS(r, c - 1, flag);
    if (!wall[r][c][0][1]&&!block[r][c+1]) DFS(r, c + 1, flag);
    if (!wall[r][c][1][0]&&!block[r-1][c]) DFS(r - 1, c, flag);
    if (!wall[r][c][1][1]&&!block[r+1][c]) DFS(r + 1, c, flag);
}
int main()
{
    int t,Case=1;
    scanf("%d", &t);
    while (t--)
    {
        int num;
        memset(mp, 0, sizeof(mp));
        memset(wall, 0, sizeof(wall));
        memset(block, 0, sizeof(block));
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                scanf("%d", &num);
                if (num - 128 >= 0) num -= 128, wall[i][j][0][0] = true;
                if (num - 64 >= 0) num -= 64, wall[i][j][1][1] = true;
                if (num - 32 >= 0) num -= 32, wall[i][j][0][1] = true;
                if (num - 16 >= 0) num -= 16, wall[i][j][1][0] = true;
                mp[i][j] = num;
            }
        }
        int id = 0;
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                if (!block[i][j])
                {
                    DFS(i, j, ++id);
                }
            }
        }
        dlx.init(9 * 9 * 9, 9 * 9 * 4);
        int Cnt = 1;
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                if (mp[i][j]==0)
                {
                    for (int z = 1; z <= 9; z++)
                    {
                        dlx.link(Cnt, (i - 1) * 9 + j);
                        dlx.link(Cnt, 81 + (i - 1) * 9 + z);
                        dlx.link(Cnt, 162 + (j - 1) * 9 + z);
                        dlx.link(Cnt, 243 + (block[i][j]-1) * 9 + z);
                        nds[Cnt].r = i, nds[Cnt].c = j, nds[Cnt].v = z;
                        Cnt++;
                    }
                }
                else
                {
                    int z =mp[i][j];
                    dlx.link(Cnt, (i - 1) * 9 + j);
                    dlx.link(Cnt, 81 + (i - 1) * 9 + z);
                    dlx.link(Cnt, 162 + (j - 1) * 9 + z);
                    dlx.link(Cnt, 243 + (block[i][j]-1) * 9 + z);
                    nds[Cnt].r = i, nds[Cnt].c = j, nds[Cnt].v = z;
                    Cnt++;
                }
            }
        }
        dlx.ansd = -1;
        iscontinue = true;
        Count = 0;
        dlx.dance(0);
        printf("Case %d:\n", Case++);
        if (Count == 0)
        {
            printf("No solution\n");
            continue;
        }
        else if (!iscontinue)
        {
            printf("Multiple Solutions\n");
            continue;
        }
        int deep = dlx.ansd;
        for (int i = 0; i < deep; i++)
        {
            int posr = dlx.tans[i];
            solution[nds[posr].r][nds[posr].c] = nds[posr].v;
        }
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                printf("%d", solution[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
