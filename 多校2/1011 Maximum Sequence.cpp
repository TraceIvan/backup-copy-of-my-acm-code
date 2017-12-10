//Memory Time
//652K  1438MS 

#include<iostream>
#include<memory.h>
using namespace std;

const int prime = 1999;  //����Ϊ2n������������ (����n=1000)

                         //����prime��ȡֵ:
                         // 1n  ����: 997   1704ms
                         // 2n  ����: 1999  1438ms
                         // 8n  ����: 7993  1110ms
                         // 10n ����: 9973  1063ms
                         // 30n ����: 29989 1000ms
                         // 50n ����: 49999 1016ms
                         // 100n����: 99991 1000ms

                         //Ϊ�˾����ﵽkey���ַ��һһӳ�䣬hash[]����Ϊ1n��
                         //��Ϊ1nʱ���ռ���������ߣ�����ַ��ͻҲ��Խ϶࣬���ھ���ҪΪ�����ͻ����Ѱַ��ʹ��Ѱ��keyֵ��ʱO(1)���������
                         //��n̫��ʱ���ռ������ʺܵͣ�������key�ֲ�����ɢ����ַ��ͻҲ��Խ��٣�ʹ��Ѱ�Ҽ�ֵ��ʱ����ΪO(1)�����

typedef class
{
public:
    int x, y;
}Node;

typedef class HashTable
{
public:
    int x, y;   //���keyֵ��Ӧ��x,y
    HashTable* next;  //�����ֵ�ַ��ͻʱ������Ѱַ

    HashTable()  //Initial
    {
        next = 0;
    }
}Hashtable;

Node pos[1001];
Hashtable* Hush[prime];   //hash[]��ָ�����飬��ŵ�ַ

void insert_vist(int k)
{
    int key = ((pos[k].x * pos[k].x) + (pos[k].y * pos[k].y)) % prime + 1;   //+1�Ǳ���==0
                                                                             //ʹkey��[0~1998]���Ƶ�[1~1999]
    if (!Hush[key])
    {
        Hashtable* temp = new Hashtable;
        temp->x = pos[k].x;
        temp->y = pos[k].y;
        Hush[key] = temp;
    }
    else   //hash[key]�Ѵ��ַ����ַ��ͻ
    {
        Hashtable* temp = Hush[key];

        while (temp->next)     //����Ѱַ��ֱ��nextΪ��
            temp = temp->next;

        temp->next = new HashTable;   //�����½�㣬��nextָ�򣬼�¼x��y
        temp->next->x = pos[k].x;
        temp->next->y = pos[k].y;
    }
    return;
}

bool find(int x, int y)
{
    int key = ((x * x) + (y * y)) % prime + 1;

    if (!Hush[key])   //key��Ӧ�ĵ�ַ������
        return false;
    else
    {
        Hashtable* temp = Hush[key];

        while (temp)
        {
            if (temp->x == x && temp->y == y)
                return true;

            temp = temp->next;
        }
    }

    return false;
}

int main(void)
{
    int n;
    while (cin >> n)
    {
        if (!n)
            break;

        memset(Hush, 0, sizeof(Hush));   //0 <-> NULL

        for (int k = 1; k <= n; k++)
        {
            cin >> pos[k].x >> pos[k].y;
            insert_vist(k);   //�����ϣ�����ɢ��
        }

        int num = 0;  //�����εĸ���
        for (int i = 1; i <= n - 1; i++)
            for (int j = i + 1; j <= n; j++)
            {
                int a = pos[j].x - pos[i].x;
                int b = pos[j].y - pos[i].y;

                int x3 = pos[i].x + b;
                int y3 = pos[i].y - a;
                int x4 = pos[j].x + b;
                int y4 = pos[j].y - a;

                if (find(x3, y3) && find(x4, y4))
                    num++;

                x3 = pos[i].x - b;
                y3 = pos[i].y + a;
                x4 = pos[j].x - b;
                y4 = pos[j].y + a;

                if (find(x3, y3) && find(x4, y4))
                    num++;
            }

        cout << num / 4 << endl;  //ͬһ��������ö����4��
    }
    return 0;
}