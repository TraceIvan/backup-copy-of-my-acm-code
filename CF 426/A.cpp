#include<iostream>
using namespace std;
char s[] = { '^','>','v','<' };
int main()
{
    char st, ed;
    while (cin >> st >> ed)
    {
        bool cc = false, ccw = false;
        int t;
        cin >> t;
        int st1, ed1;
        for (st1 = 0; st1 < 4; st1++) if (st == s[st1]) break;
        for (ed1 = 0; ed1 < 4; ed1++) if (ed == s[ed1])break;
        if ((st1 + t%4) % 4 == ed1) cc = true;
        if ((st1 - t % 4 + 4) % 4 == ed1) ccw = true;
        if (cc && !ccw)printf("cw\n");
        else if (ccw && !cc) printf("ccw\n");
        else printf("undefined\n");
    }
    return 0;
}