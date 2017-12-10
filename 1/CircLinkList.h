#ifndef _CIRCLINKLIST_H_
#define _CIRCLINKLIST_H_
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
class CircLinkList//头结点指向第一个结点
{
protected:
	Node<T> *head;
	mutable int curPosition;
	mutable Node<T> *curPtr;
	int count;
	Node<T>* GetElemPtr(int position) const;
public:
	CircLinkList();
	virtual~CircLinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const T &)) const;
	bool GetElem(int position, T &e) const;
	bool SetElem(int position, const T&e);
	bool Delete(int position, T &e);
	bool Insert(int position, const T&e);
	CircLinkList(const CircLinkList<T>&copy);
	CircLinkList<T>& operator=(const CircLinkList<T>&copy);
};

template<class T>
Node<T>* CircLinkList<T>::GetElemPtr(int position) const
{
	while (curPosition != position)
	{
		curPosition = (curPosition + 1) % (Length() + 1);
		curPtr = curPtr->next;
	}
	return curPtr;
}

template<class T>
int CircLinkList<T>::Length() const
{
	return count;
}

template<class T>
bool CircLinkList<T>::Delete(int position, T &e)//删除第position个位置的元素
{
	if (position<1 || position>Length())
	{
		return false;
	}
	else
	{
		Node<T> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);
		Node<T> *nextPtr = tmpPtr->next;
		tmpPtr->next = nextPtr->next;
		e = nextPtr->data;
		if (position == Length())
		{//删除尾结点，当前结点变为头结点
			curPosition = 0;
			curPtr = head;
		}
		else
		{
			curPositon = position;
			curPtr = tmpPtr->next;
		}
		count--;
		delete nextPtr;
		return true;
	}
}

template<class T>
bool CircLinkList<T>::Insert(int position, const T&e)
{
	if (position<1 || position>Length() + 1)
	{
		return false;
	}
	else
	{
		Node<T> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);
		Node<T> *newPtr;
		newPtr = new Node<T>(e, tmpPtr->next);
		tmpPtr->next = position;
		curPtr = newPtr;
		curPosition = position;
		count++;
		return true;
	}
}

template<class T>
CircLinkList<T>::CircLinkList()
{
	head = new Node<T>;
	head->next = head;
}

template<class T>
CircLinkList<T>::~CircLinkList()
{
	Clear();
	delete head;
}

template<class T>
bool CircLinkList<T>::Empty() const
{
	return head->next == head;
}

template<class T>
void CircLinkList<T>::Clear()
{
	T tmpElem;
	while (!Empty())
	{
		Delete(1, tmpElem);
	}
}

template<class T>
void CircLinkList<T>::Traverse(void(*visit)(const T &)) const
{
	for (Node<T>*tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next)
	{
		(*visit)(tmpPtr->data);
	}
}

template<class T>
bool CircLinkList::GetElem(int position, T &e) const
{
	if (position<1 || position>Length())
	{
		return false;
	}
	else
	{
		Node<T> *tmpPtr;
		tmpPtr = GetElemPtr(position);
		e = tmpPtr->data;
		return true;
	}
}

template<class T>
bool CircLinkList<T>::SetElem(int position, const T&e)
{
	if (position<1 || position>Length())
	{
		return false;
	}
	else
	{
		Node<T> *tmpPtr;
		tmpPtr = GetElemPtt(position);
		tmpPtr->data = e;
		returm true;
	}
}

template<class T>
LinkList<T>::LinkList(const LinkList<T>&copy)
{
	head = new Node<T>;
	Node<T> *tmpPtr = head;
	Node<T> *copyPtr = copy.head->next;
	count = copy.count;
	while (copyPtr != head)
	{
		tmpPtr->next = new Node<T>(copyPtr->data, head);
		if (copy.curPtr == copyPtr)
		{
			curPosition = copy.curPosition;
			curPtr = tmpPtr;
		}
		tmpPtr = tmpPtr->next;
		copyPtr = copyPtr->next;
	}
}

template<class T>
LinkList<T>& LinkList<T>::operator=(const LinkList<T> &copy)
{
	if (&copy != this)
	{
		head = new Node<T>;
		Node<T> *tmpPtr = head;
		Node<T> *copyPtr = copy.head->next;
		count = copy.count;
		while (copyPtr != head)
		{
			tmpPtr->next = new Node<T>(copyPtr->data, head);
			if (copy.curPtr == copyPtr)
			{
				curPosition = copy.curPosition;
				curPtr = tmpPtr;
			}
			tmpPtr = tmpPtr->next;
			copyPtr = copyPtr->next;
		}
	}
	return *this;
}
#endif