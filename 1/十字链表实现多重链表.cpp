//ʮ�������ʾϡ�����
#include<iostream>
using namespace std;
class Node
{
public:
	int row;//��
	int col;//��
	int value;//��ֵ
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
