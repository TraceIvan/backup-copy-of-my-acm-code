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
	cout << "请输入结点数并输入各个结点的数值：" << endl;
	int n;
	cin >> n;
	int tmpNum, tmpPos;
	for (int i = 0; i<n; i++)
	{
		cin >> tmpNum;
		L.SetElem(i + 1, tmpNum);
	}
	L.Traverse(display);
	cout << "请输入插入数据的位置（1->n）和插入的数值：" << endl;
	cin >> tmpPos >> tmpNum;
	L.Insert(tmpPos, tmpNum);
	cout << "插入成功！" << endl;
	cout << "请输入删除数据的位置（1->n）：" << endl;
	cin >> tmpPos;
	L.Delete(tmpPos, tmpNum);
	cout << "删除的数据为：" << tmpNum << endl;
	cout << "单链表的全体：" << endl;
	L.Traverse(display);
	L.Clear();
	return 0;
}