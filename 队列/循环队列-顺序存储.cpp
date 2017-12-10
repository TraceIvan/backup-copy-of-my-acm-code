//只从front==rear无法判断队空还是队满:
//①另设一个标识符区别队列是空还是满
//设tag=0或1。当插入一个元素设tag=1;删除一个元素时设tag=0.当front==rear时，若tag=1,则满，否则为空
//②用一个数据成员存储元数的个数
//③少用一个元素空间，约定队头在队尾指针的下一位置时作为队满的标志
//②实现(head指向第一个元素，也可实现指向第一个元素的前一个位置)
#include<iostream>
#include<climits>
#include<cfloat>
using namespace std;
#define DEFAULT_SIZE INT_MAX
template<class T>
class SqQueue
{
protected:
	int front, rear;
	int count;
	int maxSize;
	T*elems;
public:
	SqQueue(int size = DEFAULT_SIZE);
	virtual~SqQueue();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const T&))const;
	bool OutQueue(T&e);
	bool GetHead(T&e) const;
	bool InQueue(const T&e);
	SqQueue(const SqQueue<T>&copy);
	SqQueue<T>& operator=(const SqQueue<T>&copy);
};
template<class T>
SqQueue<T>::SqQueue(int size)
{
	maxSize = size;
	elems = new T[maxSize];
	rear = front = 0;
	count = 0;
}
template<class T>
SqQueue<T>::~SqQueue()
{
	delete[]elems;
}
template<class T>
int SqQueue<T>::Length() const
{
	return count;
}
template<class T>
bool SqQueue<T>::Empty() const
{
	return count == 0;
}
template<class T>
void SqQueue<T>::Clear()
{
	rear = front = 0;
	count = 0;
}
template<class T>
void SqQueue<T>::Traverse(void(*visit)(const T&)) const
{
	for (int pos = front; pos != rear; pos = (pos + 1) % maxSize)
	{
		(*visit)(elems[pos]);
	}
}
template<class T>
bool SqQueue<T>::OutQueue(T &e)
{
	if (!Empty())
	{
		e = elems[front];
		front = (front + 1) % maxSize;
		count--;
		return true;
	}
	else
	{
		return false;
	}
}
template<class T>
bool SqQueue<T>::GetHead(T &e) const
{
	if (!Empty())
	{
		e = elems[front];
		return true;
	}
	else
	{
		return false;
	}
}
template<class T>
bool SqQueue<T>::InQueue(const T&e)
{
	if (count == maxSize)
	{
		return false;
	}
	else
	{
		elems[rear] = e;
		rear = (rear + 1) % maxSize;
		count++;
		return true;
	}
}
template<class T>
SqQueue<T>::SqQueue(const SqQueue<T>&copy)
{
	maxSize = copy.maxSize;
	elems = new T[maxSize];
	front = copy.front;
	rear = copy.rear;
	count = copy.count;
	for (int pos = front; pos != rear; pos = (pos + 1) % maxSize)
	{
		elems[pos] = copy.elems[pos];
	}
}
template<class T>
SqQueue<T>& SqQueue<T>::operator=(const SqQueue<T>&copy)
{
	if (&copy != this)
	{
		maxSize = copy.Size;
		delete[]elems;
		elems = new T[maxSize];
		front = copy.front;
		rear = copy.rear;
		count = copy.count;
		for (int pos = front; pos != rear; pos = (pos + 1) % maxSize)
		{
			elems[pos] = copy.elems[pos];
		}
	}
	return *this;
}
int main()
{

	return 0;
}