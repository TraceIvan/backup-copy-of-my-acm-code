//引用数法广义表
//头结点:用tag=HEAD(0)标识，数据ref存储引用数，子表的引用数表示能访问此子表的广义表或指针个数
//原子结点:用tag=ATOM(1)标识，atom存储原子元素的值
//表结点:用tag=LIST(2)标识，sublink用于存储指向子表头结点的指针
//上述结点还有nextlink,指向后继结点
#ifndef __REF_GEN_LIST_NODE_TYPE__
#define __REF_GEN_LIST_NODE_TYPE__
enum RefGenListNodeType { HEAD, ATOM, LIST };
#endif
#include<iostream>
using namespace std;
template<class T>
struct RefGenListNode
{
	RefGenListNodeType tag;
	//标志，HEAD(0):头结点，ATOM(1):原子结点，LIST(2):表结点
	RefGenListNode<T>*nextLink;
	union
	{
		int ref;
		T atom;
		RefGenListNode<T>*subLink;
	};
	RefGenListNode(RefGenListNodeType tg = HEAD, RefGenListNode<T>*next = NULL);
};

template<class T>
class RefGenList
{
protected:
	RefGenListNode<T> *head;

	char GetChar();//从输入流中跳过制表符，获取一字符
	void ShowHelp(RefGenListNode<T>*hd) const;//显示以hd为人民头结点的引用数法广义表
	int DepthHelp(const RefGenListNode<T>*hd) const;//计算以hd为表头的引用数法广义表的深度
	void ClearHelp(RefGenListNode<T>*hd);//释放以hd为表头的引用数法广义表结构
	void CopyHelp(const RefGenListNode<T>*sourceHead, RefGenListNode<T>*destHead);
	//将以destHead为头结点的引用数法广义表复制成以souceHead为头结点的引用数法广义表
	void CreateHelp(RefGenListNode<T>*&first);//创建以first为首元素结点的引用数法广义表

public:
	RefGenList();
	RefGenList(RefGenListNode<T>*hd);//用头结点指针构造
	~RefGenList();
	RefGenListNode<T>*First() const;//返回引用数法广义表的第一个元素
	RefGenListNode<T>*Next(RefGenListNode<T>*elemPtr) const;//返回elemPtr指向的引用数法广义表元素的后继
	bool Empty() const;//判断引用数法广义表是否为空
	void Push(const T&e);//将原子元素e作为表头加入到引用数法广义表最前面
	void Push(RefGenList<T>&subList);//将子表subList作为表头加入到引用数法广义表最前面
	int Depth() const;//计算引用数法广义表深度
	RefGenList(const RefGenList<T> &copy);//复制构造函数
	RefGenList<T>& operator=(const RefGenList<T>&copy);
	void Input();//输入广义表
	void Show() const;//显示广义表
};
//特点
//①广义表中的所有表，不论是哪一层的子表，都有一个头结点
//②结点层次分明。所有位于同一层的元素，在其存储表示中也在同一层
//③容易计算表的长度。从头结点开始，沿nextLink链能找的节点个数即为表的长度
template<class T>
RefGenList<T>::RefGenList()
{
	head = new RefGenListNode<T>(HEAD);
	head->ref = 1;//引用数
}
template<class T>
RefGenListNode<T>* RefGenList<T>::First() const
{
	return head->nextLink;
}

template<class T>
RefGenListNode<T>* RefGenList<T>::Next(RefGenListNode<T>*elemPtr) const
{
	return elemPtr->nextLink;
}
//广义表的递归编程(对原子结点执行处理，对子表结点进行递归调用)只适合于非递归广义表，对于递归广义表出现无限递归
template<class T>
void RefGenList<T>::CopyHelp(const RefGenListNode<T>*sourceHead, RefGenListNode<T>*destHead)
{
	destHead = new RefGenListNode<T>(HEAD);
	RefGenListNode<T>*destPtr = destHead;
	destHead->ref = 1;
	for (RefGenListNode<T>*tmpPtr = sourceHead->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink)
	{//扫描引用数法广义表sourceHead的顶层
		destPtr = destPtr->nextLink = new RefGenListNode<T>(tmpPtr->tag);
		if (tmpPtr->tag == LIST)
		{//子表
			CopyHelp(tmpPtr->subLink, destPtr->subLink);
		}
		else
		{//原子结点
			destPtr->atom = tmpPtr->atom;
		}
	}
}

template<class T>
RefGenList<T>::RefGenList(const RefGenList<T> &copy)
{
	CopyHelp(copy.head, head);
}
//广义表的深度为广义表中括号的重数
//递归终结:
//Depth(GL)=1  当GL为空时
//Depth(GL)=0 当GL为单元素
//递归计算:
//Depth(GL)=1+Max{Depth(ai)|1≤i≤n} 当n>0
template<class T>
int RefGenList<T>::DepthHelp(const RefGenListNode<T>*hd) const
{
	if (hd->nextLink == NULL) return 1;

	int subMaxDepth = 0;
	for (RefGenListNode<T>*tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink)
	{
		if (tmpPtr->tag == LIST)
		{
			int curSubDepth = DepthHelp(tmpPtr->subLink);
			if (subMaxDepth<curSubDepth) subMaxDepth = curSubDepth;
		}
	}
	return subMaxDepth + 1;
}

template<class T>
int RefGenList<T>::Depth() const
{
	return DepthHelp(head);
}

template<class T>
void RefGenList<T>::CreateHelp(RefGenListNode<T>*&first)
{
	char ch = GetChar();
	switch (ch)
	{
	case')':
		return;
	case'(':
		first = new RefGenListNode<T>(LIST);//生成表结点

		RefGenListNode<T>*subHead;//子表指针
		subHead = new RefGenListNode<T>(HEAD);//生成子表的头结点
		subHead->ref = 1;//引用数为1
		first->subLink = subHead;//subHead为子表
		CreateHelp(subHead->nextLink);//递归建立子表

		ch = GetChar();//跳过','
		if (ch != ',') cin.putback(ch);
		CreateHelp(first->nextLink);//建立引用数法广义表下一结点
		break;
	default:
		//表头为原子
		cin.putback(ch);
		T amData;//原子结点数据
		cin >> amData;
		first = new RefGenListNode<T>(ATOM);//生成原表结点
		first->atom = amData;

		ch = GetChar();
		if (ch != ',') cin.putback(ch);
		CreateHelp(first->nextLink);
		break;
	}
}

template<class T>
void RefGenList<T>::Input()
{
	head = new RefGenListNode<T>(HEAD);
	head->ref = 1;
	GetChar();//读入第一个'('
	RefGenList<T>::CreateHelp(head->nextLink);
}
//如果一个子表结点subLink指向另一个RefGenList,如何实现?ref的值怎么改变?//可以增加计算原表的结点个数的变量?在第几个结点的位置插入/删除一个原子结点或子表或广义表?递归表的实现?//
template<class T>
void RefGenList<T>::ClearHelp(RefGenListNode<T>*hd)
{
	hd->ref--;
	if (hd->ref == 0)
	{
		RefGenListNode<T>*tmpPre, *tmpPtr;
		for (tmpPre = hd, tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPre = tmpPtr, tmpPtr = tmpPtr->nextLink)
		{
			delete tmpPre;
			if (tmpPtr->tag == LIST)
			{
				ClearHelp(tmpPtr->subLink);
			}
		}
		delete tmpPre;
	}
}

template<class T>
RefGenList<T>::~RefGenList()
{
	ClearHelp(head);
}
//为解决释放递归表的目的，建立一个全局广义表使用空间表对象，专门用于搜集指向广义表中结点的指针，用析构函数再程序结束时统一释放所有广义表结点。此时，不需要引用数，头结点数据部分为空，这样的广义表称为使用空间法广义表
class UseSpaceList
{
protected:
	Node<void*>*head;//使用空间表头指针
public:
	UseSpaceList();//无参构造函数
	~UseSpaceList();//析构函数
	void Push(void *nodePtr);//将指向结点的指针加入到使用空间表中
};
UseSpaceList::~UseSpaceList()
{
	while (head != NULL)
	{
		delete head->data;//head->data存储的是指向结点的指针
		Node<void*>*tmpPtr = head;
		head = head->next;
		delete tmpPtr;
	}
}
//定义全局广义表使用空间表对象
UseSpaceList gUseSpaceList;
//下面实现将指向结点的指针加入到广义表使用空间表
template <class T>
GenListNode<T>::GenListNode(GenListNodeType tg, GenListNode<T>*next)
{//由标识tg和指针next构造广义表结点
	tag = tg;
	nextLink = next;
	gUseSpaceList.Push(this);//将指向当前结点的指针加入到广义表使用空间表
};
//此时对于广义表类，不再需要ClearHelp(),同时析构函数不再释放结点，为空操作，并取消所有关于引用数Ref操作的语句。下面为模板声明
template<class T>
class GenList
{
protected:
	GenListNode<T>*head;

	char GetChar();
	void ShowHelp(GenListNode<T>*hd) const;
	int DepthHelp(const GenListNode<T>*hd) const;
	void CopyHelp(const GenListNode<T>*sourceHead, GenListNode<T>*destHead);
	void CreateHelp(GenListNode<T>*&first);
public:
	GenList();
	GenList(GenListNode<T>*hd);
	~GenList() {}
	GenListNode<T>*First() const;
	GenListNode<T>*Next(GenListNode<T>*elemPtr) const;
	bool Empty() const;
	void Push(const ElemType &e);
	void Push(GenList<T>&subList);

	int Depth() const;
	GenList(const GenList<T>&copy);
	GenList<T> & operator=(const GenList<T>&copy);
	void Input() const;
	void Show() const;
};
//使用空间表法广义表可使编程更加简捷，但是在程序结束时释放结点的，采用动态方式生成结点，采用静态方式释放结点。可将引用数法和使用空间表法结合起来表示



