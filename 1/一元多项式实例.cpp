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
class LinkList
{
protected:
	Node<T> *head;
	mutable int curPosition;
	mutable Node<T> *curPtr;
	int count;
	Node<T> *GetElemPtr(int position) const;
public:
	LinkList();
	virtual ~LinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const T&)) const;
	bool GetElem(int position, T&e)const;
	bool SetElem(int position, const T&e);
	bool Delete(int position, T &e);
	bool Insert(int position, const T&e);
	LinkList(const LinkList<T>&copy);
	LinkList<T> &operator=(const LinkList<T>&copy);
};
struct PolyItem
{
	double coef;//系数
	int expn;//指数
	PolyItem();
	PolyItem(double cf, int en);
};
PolyItem::PolyItem()
{
	expn = -1;
}
PolyItem::PolyItem(double cf, int en)
{
	coef = cf;
	expn = en;
}
class Polynomial
{
protected:
	LinkList<PolyItem> polyList;//多项式组成的线性表
public:
	Polynomial() {};
	~Polynomial() {};
	int Length() const;//求多项式的项数
	bool IsZero() const;//判断多项式是否为0
	void SetZero();//将多项式置0
	void Display();
	void InsItem(const Polynomial &p) const;//插入一项
	Polynomial operator+(const Polynomial &p) const;
	Polynomial operator-(const Polynomial &p) const;
	Polynomial operator*(const Polynomial &p) const;
	Polynomial(const Polynomial&copy);
	Polynimial(const <PolyItem> &copyLinkList);//由多项式组成的线性表构造多项式
	Polynomial &operator=(const Polynomial &copy);
	Polynimial &operator=(const LinkList<PolyItem> &copyLinkList);
};
Polynomial Polynimial::operator+(const Polynomial &p) const
{
	LinkList<PolyItem>la = polyList;//当前多项式对应的线性表
	LinkList<PolyItem>lb = p.polyList;//多项式p对应的线性表
	LinkList<PolyItem>lc;//和多项式对应的线性表
	int aPos = 1, bPos = 1;
	PolyItem aItem, bItem;
	while (la.GetElem(aPos, aItem) && lb.GetItem(bPos, bItem))
	{
		if (aItem.expn<bItem.expn)
		{
			lc.Insert(lc.Length() + 1, aItem);
			++aPos;
		}
		else if (aItem.expn>bItem.expn)
		{
			lc.Insert(lc.Length() + 1, bItem);
			++bPos;
		}
		else
		{
			PolyItem sumItem(aItem.coef + bItem.coef, aItem.expn);
			if (sumItem.coef != 0)
				lc.Insert(lc.Length() + 1, sumItem);
			++aPos;
			++bPos;
		}
	}
	while (la.GetElem(aPos++, aItem))
	{
		lc.Insert(lc.Length() + 1, aItem);
	}
	while (lb.GetElem(bPos++, bItem))
	{
		lc.Insert(lc.Length() + 1, bItem);
	}
	Polynomial fs;
	fs.polyList = lc;
	return fs;
}
Polynomial Polynomial::operator*(const Polynomial &p) const
{
	LinkList<PolyItem>la = polyList;//当前多项式对应的线性表
	LinkList<PolyItem>lb = p.polyList;
	LinkList<PolyItem>lc;
	Polynomial fMultiply;
	int aPos = 1, bPos;
	PolyItem aItem, bItem, cItem;
	while (la.GetElem(aPos++, aItem))
	{
		bPos = 1;
		while (lb.GetElem(aPos++, bItem))
		{
			cItem.coef = aItem.coef*bItem.coef;
			cItem.expn = aItem.expn + bItem.expn;
			lc.Clear();
			lc.Insert(lc.Length() + 1, cItem);
			Polynomial fc(lc);
			fMultiply = fMultiply + fc;
		}
	}
	return  fMultiply;
}



