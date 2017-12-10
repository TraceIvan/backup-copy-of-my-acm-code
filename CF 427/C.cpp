#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int>pii;
const int INF = 0x3f3f3f3f;
int bri[110][110][20];
int main()
{
    int n, q, c;
    int x, y, s;
    memset(bri, 0, sizeof(bri));
    scanf("%d%d%d", &n, &q, &c);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d%d%d", &x, &y, &s);
        for (int j = 0; j <= c; j++)
        {
            bri[x][y][j] += (s + j) % (c + 1);
        }
    }
    //    for(int i = 0; i < c; ++ i) {
    //        cout << bri[1][1][i] << ' ';
    //    }
    //    cout << endl;
    //    for(int i = 0; i < c; ++ i) {
    //        cout << bri[3][2][i] << ' ';
    //    }
    //    cout << endl;
    int t, x1, y1, x2, y2;
    while (q--)
    {
        scanf("%d%d%d%d%d", &t, &x1, &y1, &x2, &y2);
        if (c == 0)
        {
            puts("0");
            continue;
        }
        int sum = 0;
        t %= (c + 1);
        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
            {
                sum += bri[i][j][t];
            }
        }
        cout << sum << endl;
    }
    return 0;
}


/*
const int maxn = 1e5 + 5;
const int maxx = 100 + 5;
int n, q, c;
int x[maxn];
int y[maxn];
int s[maxn];
int a[20][maxx][maxx];

int query(int t, int x1, int y1, int x2, int y2)
{
    return a[t][x2][y2] - a[t][x2][y1 - 1] - a[t][x1 - 1][y2] + a[t][x1 - 1][y1 - 1];
}

void solve()
{
    cin >> n >> q >> c;
    FOR(i, 0, n)
    {
        cin >> x[i] >> y[i] >> s[i];
        FOR(k, 0, c + 1)
        {
            a[k][x[i]][y[i]] += (s[i] + k) % (c + 1);
        }
    }
    FOR(k, 0, c + 1)
    {
        FOR(i, 1, maxx) FOR(j, 1, maxx)
        {
            a[k][i][j] += a[k][i - 1][j] + a[k][i][j - 1] - a[k][i - 1][j - 1];
        }
    }
    while (q--)
    {
        int t, x[2], y[2]; cin >> t;
        FOR(i, 0, 2) cin >> x[i] >> y[i];
        t %= c + 1;
        cout << query(t, x[0], y[0], x[1], y[1]) << "\n";
    }
}

int main()
{
    int JUDGE_ONLINE = 1;
    if (fopen("in.txt", "r"))
    {
        JUDGE_ONLINE = 0;
        assert(freopen("in.txt", "r", stdin));
        //assert(freopen("out.txt", "w", stdout));
    }
    else
    {
        ios_base::sync_with_stdio(0), cin.tie(0);
    }
    solve();
    if (!JUDGE_ONLINE)
    {
        //cout << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    }
    return 0;
}
*/