#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

char str[10][10];//��¼n���ַ���
int n, ans, deep, Size[10];
char DNA[4] = { 'A','C','G','T' };//һ�����ֿ���

void dfs(int cnt, int *len)
{
    if (cnt > deep)//�������Ƶ���ȣ�������������
        return;
    int maxx = 0;//Ԥ�ƻ�Ҫƥ����ַ�������󳤶�
    for (int i = 0; i<n; i++)
    {
        int t = Size[i] - len[i];
        if (t>maxx)
            maxx = t;
    }
    if (maxx == 0)//����ȫ�����㼴Ϊ���Ž�
    {
        ans = cnt;
        return;
    }
    if (cnt + maxx > deep)//��֦
        return;
    for (int i = 0; i<4; i++)
    {
        int pos[10];//�����ڵ�ǰ�ַ���ѡ��Ϊ������ַ������ַ�ʱ��ʣ�µ��ַ�����ʼ��Ҫƥ���λ��
        int flag = 0;//�ж��Ƿ����ַ����ĵ�ǰҪƥ���λ���Ǹ��ַ�
        for (int j = 0; j<n; j++)
        {//ö��ÿһ���ַ���������posֵ
            if (str[j][len[j]] == DNA[i])
            {
                flag = 1;
                pos[j] = len[j] + 1;
            }
            else
                pos[j] = len[j];
        }
        if (flag)//���ƥ��Ļ�
            dfs(cnt + 1, pos);//��������
        if (ans != -1)//����������Ļ���ֱ�ӷ���
            break;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n;
        int minn = 0;
        for (int i = 0; i<n; i++)
        {
            cin >> str[i];
            Size[i] = strlen(str[i]);//��¼����
            if (Size[i]>minn)
                minn = Size[i];
        }
        ans = -1;
        deep = minn;//����̳��ȿ�ʼ����
        int pos[10] = { 0 };//��¼n���ַ���Ŀǰƥ�䵽��λ��
        while (1)
        {
            dfs(0, pos);
            if (ans != -1)
                break;
            deep++;//�������
        }
        cout << ans << endl;
    }
    return 0;
}