/*
线性表的形式定义
LinearList=(D,R)
D是一个数据元素的集合，S是定义在D中的数据元素之间的关系的有限集合
D∈{ai|ai∈ElemSet,i=1,2,3,…,n,n≥0},ElemSet为某个数据集合;R={N},N={<ai,a(i-1)>|i=1,2,3,…,n-1}
*/

/*顺序存储结构*/
#inlude<iostream>
using namespace std;
template<class ElemType>
class SqList
{
protected:
	int count;//元素个数
	int maxSize;//数组长度
	ElemType *elems;//数组的数据类型为ElemType
public:
	SqList(int size = DEFAULT_SIZE);
	virtual~sqList();
	int Length() const;
	bool Empty() const;//判断是否为空
	void Clear();//清空
	void Traverse(void(*visit)(const ElemType&)) const;//遍历线性表(依次对线性表的每个元素调用函数(*visit))
	bool GetElem(int position, ElemType &e) const;//求指定位置的元素
	bool SetElem(int position, const ElemType &e);//设置指定位置的元素值
	bool Delete(int position, ElemType &e);//删除第position个元素，用e返回其值
	bool Insert(int position, const ElemType &e);//第position个位置插入元素e
	SqList(const SqList<ElemType>&copy);//复制构造函数模板
	SqList<ElemType>&operator=(const SqList<ElemType> &copy);//重载复制函数
};
template<class ElemType>
SqList<ElemType>::SqList(int size)
{
	maxSize = size;
	elems = new ElemType[maxSize];
	count = 0;
}
template<class ElemType>
SqList<ElemType>::~SqList()
{
	delete[]elems;
}
template<class ElemType>
int SqList<ElemType>::Length() const
{
	return count;
}
template<class ElemType>
bool SqList<ElemType>::Empty() const
{
	return count == 0;
}
template<class ElemType>
void SqList<ElemType>::Clear()
{
	count = 0;
}
template<class ElemType>
void SqList<ElemType>::Traverse(void(*visit)(const ElemType &)) const
{
	for (int pos = 1; pos <= Length(); pos++)
	{
		(*visit)(elems[pos - 1]);
	}
}
template<class ElemType>
bool SqList<ElemType>::GetElem(int position, ElemType &e) const
{
	if (position<1 || position>Length())
	{
		return false;
	}
	else
	{
		e = elems[position - 1];
		return true;
	}
}
template<class ElemType>
bool SqList<ElemType>::SetElem(int position, const ElemType &e)
{
	if (position<1 || position>Length())
	{
		return false;
	}
	else
	{
		elems[position - 1] = e;
		return true;
	}
}
template<class ElemType>
bool SqList<ElemType>::Insert(position, const ElemType &e)
{
	ElemType tmp;
	if (count == maxSize)
	{
		return false;
	}
	else if (position<1 || position>Length() + 1)
	{
		return false;
	}
	else
	{
		count++;
		for (int pos = Length(); pos >= position; pos--)//插入位置之后的元素后移
		{
			GetElem(pos, tmp);
			SetElem(pos + 1, tmp);
		}
		SetElem(position, e);
		return true;
	}
}
/*
平均移动次数:∑(i=1,…,n+1)p(i)(n-i+1)=∑(i=1,…,n+1)(1/(n+1))(n-i+1)=n/2
p(i)为在第i位置插入元素的概率都为1/(n+1)
∴T(n)=O(n)
*/
template<class ElemType>
bool SqList<ElemType>::Delete(int position, ElemType &e)
{
	ElemType tmp;
	if (position<1 || position>Length())
	{
		return false;
	}
	else
	{
		GetElem(position, e);
		for (int pos = position + 1; pos <= Length(); pos++)
		{
			GetElem(pos, tmp);
			SetElem(pos - 1, tmp);
		}
		count--;
		return true;
	}
}
template<class ElemType>
SqList<ElemType>::SqList(const SqList<ElemType> &copy)
{
	maxSize = copy.maxSize;
	elems = new ElemType[maxSize];
	count = copy.count;
	for (int pos = 1; pos <= Length(); pos++)
	{
		elems[pos - 1] = copy.elems[pos - 1];
	}
}
template<class ElemType>
SqList<ElemType>& SqList<ElemType>::operator=(const SqList<ElemType>&copy)
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;
		if (elems != NULL) delete[]elems;
		elems = new ElemType[maxSize];
		count = copy.count;
		for (int pos = 1; pos <= Length(); pos++)
		{
			elems[pos - 1] = copy.elems[pos - 1];
		}
	}
	return *this;
}
void Diffence(const SqList<ElemType>&la, const SqList<ElemType> &lb, SqList<ElemType>&lc)
//用lc返回la和lb表示的集合的差集
{
	ElemType aElem, bElem;
	lc.Clear();
	for (int aPos = 1; aPos <= la.Length(); aPos++)
	{
		la.GetElem(aPos, aElem);
		bool isExist = false;
		for (int bPos = 1; bPos <= lb.Length(); bPos++)
		{
			lb.GetElem(bPos, bElem);
			if (aElem == bElem)
			{
				isExist = true;
				break;
			}
			if (!isExist)
			{
				lc.Insert(lc.Length() + 1, aElem);
			}
		}
	}
}
void Adjust(SqList<ElemType> &la)
//将la调整为左右两部分，左边所有元素为奇数，右边所有元素为偶数，并要求时间复杂度为O(n)
{
	int lPosition = 1, rPosition = la.Length();
	ElemType aElem, bElem;
	while (lPosition<rPosition)
	{
		la.GetElem(lPosition, aElem);
		la.GetElem(rPosition, bElem);
		if (aElem % 2 == 1)
		{
			lPosition++;
		}
		else if (bElem % 2 == 0)
		{
			rPosition++;
		}
		else
		{
			la.SetElem(lPosition++, bElem);
			la.SetElem(rPosition--, aElem);
		}
	}
}
