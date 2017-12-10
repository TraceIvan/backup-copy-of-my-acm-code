// LinkList.cpp: implementation of the LinkList class.
//
//////////////////////////////////////////////////////////////////////
#include<iostream>
using namespace std;
#include "LinkList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
template<class ElemType>
void display(ElemType &e, int pos, int Count)
{
	cout << e;
	if (pos<Count) cout << "-->";
	else cout << endl;
}

int main()
{
	LinkList<int> L;
	cout << "�������������������������ֵ��" << endl;
	int n;
	cin >> n;
	int tmpNum, tmpPos;
	for (int i = 0; i<n; i++)
	{
		cin >> tmpNum;
		L.SetElem(i + 1, tmpNum);
	}
	L.Traverse(display);
	cout << "������������ݵ�λ�ã�1->n���Ͳ������ֵ��" << endl;
	cin >> tmpPos >> tmpNum;
	L.Insert(tmpPos, tmpNum);
	cout << "����ɹ���" << endl;
	cout << "������ɾ�����ݵ�λ�ã�1->n����" << endl;
	cin >> tmpPos;
	L.Delete(tmpPos, tmpNum);
	cout << "ɾ��������Ϊ��" << tmpNum << endl;
	cout << "�������ȫ�壺" << endl;
	L.Traverse(display);
	L.Clear();
	return 0;
}