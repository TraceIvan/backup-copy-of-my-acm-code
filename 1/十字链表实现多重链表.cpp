//十字链表表示稀疏矩阵
#include<iostream>
using namespace std;
class Node
{
public:
	int row;//行
	int col;//列
	int value;//数值
	Node* next;
	Node *right;
	Node *down;
	Node();
	~Node();
	Node(int a, int b, int va);
};
Node::Node()
{
	row = col = value = 0; right = down = next = NULL;
}
Node::Node(int a, int b, int va)
{
	row = a, col = b, value = va;
}
class List
{
	Node head0;
