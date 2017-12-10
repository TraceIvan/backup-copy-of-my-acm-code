#include<iostream>
using namespace std;
template<class T>
struct Node
{
	T data;
	Node<T> *next;
	Node();
	Node(T item, Node<T> *link = NULL);
};
template<class T>
Node<T>::Node()
{
	next = NULL;
}
template<class T>
Node<T>::Node(T item, Node<T> *link)
{
	data = item;
	next = link;
}
template<class T>
class LinkQueue
{
protected:
	Node<T>*front, *rear;//队头队尾指针
	int count;
public:
	LinkQueue();
	virtual~LinkQueue();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const T&)) const;
	bool OutQueue(T &e);//出队
	bool GetHead(T &e) const;//取队头
	bool InQueue(const T&e);//入队
	LinkQueue(const LinkQueue<T>&copy);
	LinkQueue<T>& operator=(const LinkQueue<T>&copy);
};
template<class T>
LinkQueue<T>::LinkQueue()
{
	rear = front = new Node<T>;
	count = 0;
}
template<class T>
LinkQueue<T>::~LinkQueue()
{
	Clear();
}
template<class T>
int LinkQueue<T>::Length() const
{
	return count;
}
template<class T>
bool LinkQueue<T>::Empty() const
{
	return count == 0;
}
template<class T>
void LinkQueue<T>::Clear()
{
	T tmpElem;
	while (!Empty())
	{
		OutQueue(tmpElem);
	}
}
template<class T>
void LinkQueue<T>::Traverse(void(*visit)(const T&)) const
{
	for (Node<T>*tmpPtr = front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		(*visit)(tmpPtr->data);
	}
}
template<class T>
bool LinkQueue<T>::OutQueue(T &e)
{
	if (!Empty())
	{
		Node<T>*tmpPtr = front->next;
		e = tmpPtr->data;
		front->next = tmpPtr->next;
		if (rear == tmpPtr)
		{
			rear = front;
		}
		delete tmpPtr;
		count--;
		return true;
	}
	else
	{
		return false;
	}
}
template<class T>
bool LinkQueue<T>::GetHead(T &e) const
{
	if (!Empty())
	{
		Node<T>*tmpPtr = front->next;
		e = tmpPtr->data;
		return true;
	}
	else
	{
		return false;
	}
}
template<class T>
bool LinkQueue<T>::InQueue(const T&e)
{
	Node<T>*tmpPtr = new Node<T>(e);
	rear->next = tmpPtr;
	rear = tmpPtr;
	count++;
	return true;
}
template<class T>
LinkQueue<T>::LinkQueue(const LinkQueue<T>&copy)
{
	rear = front = new Node<T>;
	count = 0;
	for (Node<T>*tmpPtr = copy.front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		InQueue(tmpPtr->data);
	}
}
template<class T>
LinkQueue<T>& LinkQueue<T>::operator=(const LinkQueue<T>&copy)
{
	if (&copy != this)
	{
		Clear();
		for (Node<T>*tmpPtr = copy.front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			InQueue(tmpPtr->data);
		}
	}
	return *this;
}
int main()
{
	//利用队列显示二项式(a+b)^i的系数(其展开后系数构成杨辉三角
	int n = 10;
	LinkQueue<int>q;
	int s, t;
	q.InQueue(1);
	q.InQueue(1);
	cout << 1 << "\t" << 1;
	for (int i = 2; i <= 10; i++)
	{
		cout << endl;
		q.InQueue(1);
		cout << 1 << "\t";
		q.OutQueue(s);
		for (int j = 2; j <= i; j++)
		{
			q.OutQueue(t);
			q.InQueue(s + t);
			cout << s + t << "\t";
			s = t;
		}
		q.InQueue(1);
		cout << 1;
	}
	cout << endl;
	return 0;
}
