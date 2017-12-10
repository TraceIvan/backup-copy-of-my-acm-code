#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 60//55个格子
#define M 70//60个火柴
#define NN 300//每个格子4根火柴，算上辅助是5
#define inf 0x3f3f3f3f
using namespace std;
/*60火柴，25格*/
int ans;
struct DLX
{
    int U[NN], D[NN], L[NN], R[NN], C[NN];
    int H[M], T[N], cnt;
    inline void init()
    {
        cnt = 0;
        memset(U, 0, sizeof(U));
        memset(D, 0, sizeof(D));
        memset(L, 0, sizeof(L));
        memset(R, 0, sizeof(R));
        memset(C, 0, sizeof(C));
        memset(H, 0, sizeof(H));
        memset(T, 0, sizeof(T));
    }
    inline void newnode(int x, int y)
    {
        C[++cnt] = y; T[y]++;

        if (!H[x])H[x] = L[cnt] = R[cnt] = cnt;
        else L[cnt] = H[x], R[cnt] = R[H[x]];
        R[H[x]] = L[R[H[x]]] = cnt, H[x] = cnt;

        U[cnt] = U[y], D[cnt] = y;
        U[y] = D[U[y]] = cnt;
    }
    int id[N][N][5], eid[2][7][7];
    bool destroy[N], map[N][M];
    inline void build()
    {
        init();
        int i, j, k, n, m;
        int nmrx = 0, npon = 0;
        scanf("%d%d", &n, &m);
        memset(destroy, 0, sizeof(destroy));
        memset(map, 0, sizeof(map));
        for (k = 0; k<n; k++)for (i = 1; i + k <= n; i++)for (j = 1; j + k <= n; j++)id[k][i][j] = ++nmrx;
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)eid[0][i][j] = ++npon;
            for (j = 1; j <= n + 1; j++)eid[1][i][j] = ++npon;
        }
        for (i = 1; i <= n; i++)eid[0][n + 1][i] = ++npon;
        for (k = 0; k<n; k++)
            for (i = 1; i + k <= n; i++)
                for (j = 1; j + k <= n; j++)
                {
                    int A = id[k][i][j], temp;
                    for (temp = j; temp <= j + k; temp++)map[A][eid[0][i][temp]] = map[A][eid[0][i + k + 1][temp]] = 1;
                    for (temp = i; temp <= i + k; temp++)map[A][eid[1][temp][j]] = map[A][eid[1][temp][j + k + 1]] = 1;
                }
        for (i = 1; i <= m; i++)
        {
            scanf("%d", &k);
            for (j = 1; j <= nmrx; j++)if (map[j][k])destroy[j] = 1;
        }
        for (i = 1; i <= nmrx; i++)if (!destroy[i])
        {
            U[i] = D[i] = i;
            L[i] = L[0], R[i] = 0;
            L[0] = R[L[0]] = i;
        }
        cnt = nmrx;
        for (i = 1; i <= nmrx; i++)
            if (!destroy[i])
                for (j = 1; j <= npon; j++)
                    if (map[i][j])
                        newnode(j, i);
    }
    inline void remove(int x)
    {
        int i = x;
        do
        {
            R[L[i]] = R[i];
            L[R[i]] = L[i];
            i = D[i];
        } while (i != x);
    }
    inline void resume(int x)
    {
        int i = x;
        do
        {
            R[L[i]] = i;
            L[R[i]] = i;
            i = U[i];
        } while (i != x);
    }
    inline void dfs(int x)
    {
        if (x >= ans)return;
        if (!R[0])
        {
            ans = x;
            return;
        }
        int S = R[0], W = T[S], i, j;
        int del[N], num;
        for (i = R[S]; i; i = R[i])if (T[i]<W)
        {
            W = T[i];
            S = i;
        }
        remove(S);
        for (i = D[S]; i != S; i = D[i])
        {
            del[num = 1] = R[i];
            for (j = R[R[i]]; j != R[i]; j = R[j])del[++num] = j;
            for (j = 1; j <= num; j++)remove(del[j]);
            dfs(x + 1);
            for (j = num; j; j--)resume(del[j]);
        }
        resume(S);
        return;
    }
}dlx;
int main()
{
    int g;
    scanf("%d", &g);
    while (g--)
    {
        ans = inf;
        dlx.build();
        dlx.dfs(0);
        printf("%d\n", ans);
    }
    return 0;
}
