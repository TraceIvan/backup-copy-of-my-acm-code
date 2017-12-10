//结点类模板
template<class ElemType>
struct Node
{
	ElemType data;
	Node<ElemType>*next;
	Node();
	Node(ElemType item, Node<ElemType>*link = NULL);//已知数据元素和后继指针建立结构
};
template<class ElemType>
Node<ElemType>::Node()
{
	next = NULL;
}
template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType>*link)
{
	data = item;
	next = link;
}
//简单线性链表模板
template<class ElemType>
class SimpleLinkList
{
protected:
	Node<ElemType>*head;
	Node<ElemType>*GetElemPtr(int position) const;//辅助函数模板，返回指向第position个结点的指针
public:
	SimpleLinkList();
	virtual~SimpleLinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const ElemType &)) const;
	bool GetElem(int position, ElemType &e) const;
	bool SetElem(int position, const ElemType &e);
	bool Delete(int position, ElemType &e);
	bool Insert(int position, const ElemType &e);
	SimpleLinkList(const SimpleLinkList<ElemType>&copy);
	SimpleLinkList<ElemType>& operator=(const SimpleLinkList<ElemType>&copy);
};

