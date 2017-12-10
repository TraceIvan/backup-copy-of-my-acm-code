//�������������
//ͷ���:��tag=HEAD(0)��ʶ������ref�洢���������ӱ����������ʾ�ܷ��ʴ��ӱ�Ĺ�����ָ�����
//ԭ�ӽ��:��tag=ATOM(1)��ʶ��atom�洢ԭ��Ԫ�ص�ֵ
//����:��tag=LIST(2)��ʶ��sublink���ڴ洢ָ���ӱ�ͷ����ָ��
//������㻹��nextlink,ָ���̽��
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
	//��־��HEAD(0):ͷ��㣬ATOM(1):ԭ�ӽ�㣬LIST(2):����
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

	char GetChar();//���������������Ʊ������ȡһ�ַ�
	void ShowHelp(RefGenListNode<T>*hd) const;//��ʾ��hdΪ����ͷ�����������������
	int DepthHelp(const RefGenListNode<T>*hd) const;//������hdΪ��ͷ�������������������
	void ClearHelp(RefGenListNode<T>*hd);//�ͷ���hdΪ��ͷ���������������ṹ
	void CopyHelp(const RefGenListNode<T>*sourceHead, RefGenListNode<T>*destHead);
	//����destHeadΪͷ������������������Ƴ���souceHeadΪͷ�����������������
	void CreateHelp(RefGenListNode<T>*&first);//������firstΪ��Ԫ�ؽ����������������

public:
	RefGenList();
	RefGenList(RefGenListNode<T>*hd);//��ͷ���ָ�빹��
	~RefGenList();
	RefGenListNode<T>*First() const;//�����������������ĵ�һ��Ԫ��
	RefGenListNode<T>*Next(RefGenListNode<T>*elemPtr) const;//����elemPtrָ����������������Ԫ�صĺ��
	bool Empty() const;//�ж���������������Ƿ�Ϊ��
	void Push(const T&e);//��ԭ��Ԫ��e��Ϊ��ͷ���뵽���������������ǰ��
	void Push(RefGenList<T>&subList);//���ӱ�subList��Ϊ��ͷ���뵽���������������ǰ��
	int Depth() const;//��������������������
	RefGenList(const RefGenList<T> &copy);//���ƹ��캯��
	RefGenList<T>& operator=(const RefGenList<T>&copy);
	void Input();//��������
	void Show() const;//��ʾ�����
};
//�ص�
//�ٹ�����е����б���������һ����ӱ�����һ��ͷ���
//�ڽ���η���������λ��ͬһ���Ԫ�أ�����洢��ʾ��Ҳ��ͬһ��
//�����׼����ĳ��ȡ���ͷ��㿪ʼ����nextLink�����ҵĽڵ������Ϊ��ĳ���
template<class T>
RefGenList<T>::RefGenList()
{
	head = new RefGenListNode<T>(HEAD);
	head->ref = 1;//������
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
//�����ĵݹ���(��ԭ�ӽ��ִ�д������ӱ�����еݹ����)ֻ�ʺ��ڷǵݹ��������ڵݹ�����������޵ݹ�
template<class T>
void RefGenList<T>::CopyHelp(const RefGenListNode<T>*sourceHead, RefGenListNode<T>*destHead)
{
	destHead = new RefGenListNode<T>(HEAD);
	RefGenListNode<T>*destPtr = destHead;
	destHead->ref = 1;
	for (RefGenListNode<T>*tmpPtr = sourceHead->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink)
	{//ɨ���������������sourceHead�Ķ���
		destPtr = destPtr->nextLink = new RefGenListNode<T>(tmpPtr->tag);
		if (tmpPtr->tag == LIST)
		{//�ӱ�
			CopyHelp(tmpPtr->subLink, destPtr->subLink);
		}
		else
		{//ԭ�ӽ��
			destPtr->atom = tmpPtr->atom;
		}
	}
}

template<class T>
RefGenList<T>::RefGenList(const RefGenList<T> &copy)
{
	CopyHelp(copy.head, head);
}
//���������Ϊ����������ŵ�����
//�ݹ��ս�:
//Depth(GL)=1  ��GLΪ��ʱ
//Depth(GL)=0 ��GLΪ��Ԫ��
//�ݹ����:
//Depth(GL)=1+Max{Depth(ai)|1��i��n} ��n>0
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
		first = new RefGenListNode<T>(LIST);//���ɱ���

		RefGenListNode<T>*subHead;//�ӱ�ָ��
		subHead = new RefGenListNode<T>(HEAD);//�����ӱ��ͷ���
		subHead->ref = 1;//������Ϊ1
		first->subLink = subHead;//subHeadΪ�ӱ�
		CreateHelp(subHead->nextLink);//�ݹ齨���ӱ�

		ch = GetChar();//����','
		if (ch != ',') cin.putback(ch);
		CreateHelp(first->nextLink);//�������������������һ���
		break;
	default:
		//��ͷΪԭ��
		cin.putback(ch);
		T amData;//ԭ�ӽ������
		cin >> amData;
		first = new RefGenListNode<T>(ATOM);//����ԭ����
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
	GetChar();//�����һ��'('
	RefGenList<T>::CreateHelp(head->nextLink);
}
//���һ���ӱ���subLinkָ����һ��RefGenList,���ʵ��?ref��ֵ��ô�ı�?//�������Ӽ���ԭ��Ľ������ı���?�ڵڼ�������λ�ò���/ɾ��һ��ԭ�ӽ����ӱ������?�ݹ���ʵ��?//
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
//Ϊ����ͷŵݹ���Ŀ�ģ�����һ��ȫ�ֹ����ʹ�ÿռ�����ר�������Ѽ�ָ�������н���ָ�룬�����������ٳ������ʱͳһ�ͷ����й�����㡣��ʱ������Ҫ��������ͷ������ݲ���Ϊ�գ������Ĺ�����Ϊʹ�ÿռ䷨�����
class UseSpaceList
{
protected:
	Node<void*>*head;//ʹ�ÿռ��ͷָ��
public:
	UseSpaceList();//�޲ι��캯��
	~UseSpaceList();//��������
	void Push(void *nodePtr);//��ָ�����ָ����뵽ʹ�ÿռ����
};
UseSpaceList::~UseSpaceList()
{
	while (head != NULL)
	{
		delete head->data;//head->data�洢����ָ�����ָ��
		Node<void*>*tmpPtr = head;
		head = head->next;
		delete tmpPtr;
	}
}
//����ȫ�ֹ����ʹ�ÿռ�����
UseSpaceList gUseSpaceList;
//����ʵ�ֽ�ָ�����ָ����뵽�����ʹ�ÿռ��
template <class T>
GenListNode<T>::GenListNode(GenListNodeType tg, GenListNode<T>*next)
{//�ɱ�ʶtg��ָ��next����������
	tag = tg;
	nextLink = next;
	gUseSpaceList.Push(this);//��ָ��ǰ����ָ����뵽�����ʹ�ÿռ��
};
//��ʱ���ڹ�����࣬������ҪClearHelp(),ͬʱ�������������ͷŽ�㣬Ϊ�ղ�������ȡ�����й���������Ref��������䡣����Ϊģ������
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
//ʹ�ÿռ��������ʹ��̸��Ӽ�ݣ������ڳ������ʱ�ͷŽ��ģ����ö�̬��ʽ���ɽ�㣬���þ�̬��ʽ�ͷŽ�㡣�ɽ�����������ʹ�ÿռ�����������ʾ



