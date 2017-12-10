#include<iostream>
#include<algorithm>
using namespace std;
int L, N, M;
int st, ed;
const int maxn = 50005;
int Rocks[maxn];
bool Judge(int dis)
{
    int rmvrocks = 0;
    int tdis = 0;
    int refpos = 0;
    int tnumrocks = 0;
    for (int i = 0; i < N;)
    {
        tnumrocks = 0;
        while (i<N&&Rocks[i] - refpos < dis) tnumrocks++,i++;
        rmvrocks += tnumrocks;
        refpos = Rocks[i];
        i++;
    }
    if (tnumrocks == 0 && L - Rocks[N - 1] < dis) rmvrocks++;
    if (rmvrocks > M) return false;
    else return true;
}
int main()
{
    while (cin >> L)
    {
        cin >> N >> M;
        for (int i = 0; i < N; i++) cin >> Rocks[i];
        sort(Rocks, Rocks + N);
        int mindis = Rocks[0];
        for (int i = 1; i < N; i++)
            if (Rocks[i] - Rocks[i - 1] < mindis) mindis = Rocks[i] - Rocks[i - 1];
        if (L - Rocks[N - 1] < mindis) mindis = L - Rocks[N - 1];
        int l = mindis, r = L;
        while (l <= r)
        {
            int mid = (l + r) / 2;
            if (Judge(mid)) l = mid + 1;
            else r = mid - 1;
        }
        cout << r << endl;
    }
    return 0;
}