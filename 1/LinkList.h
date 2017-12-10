// LinkList.h: interface for the LinkList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKLIST_H__4E9F9092_4971_45B3_B29E_FB78260B04B5__INCLUDED_)
#define AFX_LINKLIST_H__4E9F9092_4971_45B3_B29E_FB78260B04B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
template<class ElemType>
struct Node
{
	ElemType data;
	Node<ElemType> *next;
	Node();
	Node(ElemType item, Node<ElemType> *link = NULL);
};
template<class ElemType>
Node<ElemType>::Node()
{
	next = NULL;
}
template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link)
{
	data = item;
	next = link;
}


template<class ElemType>
class LinkList
{
protected:
	Node<ElemType>*head;
	//以下基于简单线性链表增加
	Node<ElemType>*tail;//指向尾部
	mutable int curPosition;//当前位置的序号
	mutable Node<ElemType> *curPtr;//指向当前位置的指针
	int count;//元素个数
			  //
	Node<ElemType>*  GetElemPtr(int position) const;
public:
	LinkList();
	virtual ~LinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const ElemType &, int pos, int Count)) const;
	bool GetElem(int position, ElemType &e) const;
	bool SetElem(int position, const ElemType &e);
	bool Delete(int position, ElemType &e);
	bool Insert(int position, const ElemType &e);
	LinkList(const LinkList<ElemType>&copy);
	LinkList<ElemType> &operator=(const LinkList<ElemType> &copy);
};
template<class ElemType>
LinkList<ElemType>::LinkList()
{
	head = new Node<ElemType>;
	curPtr = tail = head;
	curPosition = count = 0;
}
template<class ElemType>
LinkList<ElemType>::~LinkList()
{
	Clear();
	delete head;
	delete tail;
	delete curPtr;
}
template<class ElemType>
void LinkList<ElemType>::Clear()
{
	curPtr = tail = head;
	ElemType tmpElem;
	while (!Empty())
	{
		Delete(1, tmpElem);
	}
}
template<class ElemType>
bool LinkList<ElemType>::Empty() const
{
	return head->next == NULL;
}
template<class ElemType>
void LinkList<ElemType>::Traverse(void(*visit)(const ElemType &, int pos, int Count)) const
{
	int position = 1;
	for (Node<ElemType>*tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		(*visit)(tmpPtr->data, position++, count);
	}
}
template<class ElemType>
Node<ElemType>* LinkList<ElemType>::GetElemPtr(int position) const
{
	if (curPosition>position)
	{
		curPosition = 0;
		curPtr = head;
	}
	for (; curPosition<position; curPosition++)
		curPtr = curPtr->next;
	return curPtr;
}
template<class ElemType>
bool LinkList<ElemType>::GetElem(int position, ElemType &e) const
{
	if (position<1 || position>Length())
		return false;
	else
	{
		Node<ElemType> *tmpPtr = GetElemPtr(position);
		e = tmpPtr->data;
		return true;
	}
}
template<class ElemType>
bool LinkList<ElemType>::SetElem(int position, const ElemType &e)
{
	if (position<1 || position>Length())
		return false;
	else
	{
		Node<ElemType> *tmpPtr = GetElemPtr(position);
		tmpPtr->data = e;
		return true;
	}
}
template<class ElemType>
int LinkList<ElemType>::Length() const
{
	return count;
}
template<class ElemType>
bool LinkList<ElemType>::Delete(int position, ElemType &e)
{
	if (position<1 || position>Length())
	{
		return false;
	}
	else
	{
		Node<ElemType>*tmpPtr;
		tmpPtr = GetElemPtr(position - 1);
		Node<ElemType>*nextPtr = tmpPtr->next;
		tmpPtr->next = nextPtr->next;
		e = nextPtr->data;
		if (position == Length())
		{
			tail = tmpPtr;
			curPosition = 0;
			curPtr = head;
		}
		else
		{
			curPosition = position;
			curPtr = tmpPtr->next;
		}
		count--;
		delete nextPtr;
		return true;
	}
}
template<class ElemType>
bool LinkList<ElemType>::Insert(int position, const ElemType &e)
{
	if (position<1 || position>Length() + 1)
	{
		return false;
	}
	else
	{
		Node<ElemType>*tmpPtr;
		tmpPtr = GetElemPtr(position - 1);
		Node<ElemType>*newPtr;
		newPtr = new Node<ElemType>(e, tmpPtr->next);
		tmpPtr->next = newPtr;
		if (position == Length() + 1)
			tail = tail->next;
		curPosition = position;
		curPtr = newPtr;
		count++;
		return true;
	}
}
template<class ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType>&copy)
{
	head = new Node<ElemType>;
	Node<ElemType> *tmpPtr = head->next;
	Node<ElemType> *copyPtr = copy.head->next;
	count = copy.count;
	while (copyPtr != NULL)
	{
		tmpPtr->data = copyPtr->data;
		tmpPtr->next = new Node<ElemType>;
		if (copy.curPtr == copyPtr)
		{
			curPosition = copy.curPosition;
			curPtr = tmpPtr;
		}
		if (copy.tail == copyPtr)
			tail = tmpPtr;
		tmpPtr = tmpPtr->next;
		copyPtr = copyPtr->next;
	}
}
template<class ElemType>
LinkList<ElemType>& LinkList<ElemType>::operator=(const LinkList<ElemType> &copy)
{
	if (&copy != this)
	{
		head = new Node<ElemType>;
		Node<ElemType> *tmpPtr = head->next;
		Node<ElemType> *copyPtr = copy.head->next;
		count = copy.count;
		while (copyPtr != NULL)
		{
			tmpPtr->data = copyPtr->data;
			tmpPtr->next = new Node<ElemType>;
			if (copy.curPtr == copyPtr)
			{
				curPosition = copy.curPosition;
				curPtr = tmpPtr;
			}
			if (copy.tail == copyPtr)
				tail = tmpPtr;
			tmpPtr = tmpPtr->next;
			copyPtr = copyPtr->next;
		}
	}
	return *this;
}
#endif // !defined(AFX_LINKLIST_H__4E9F9092_4971_45B3_B29E_FB78260B04B5__INCLUDED_)