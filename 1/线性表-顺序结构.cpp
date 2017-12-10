/*
���Ա����ʽ����
LinearList=(D,R)
D��һ������Ԫ�صļ��ϣ�S�Ƕ�����D�е�����Ԫ��֮��Ĺ�ϵ�����޼���
D��{ai|ai��ElemSet,i=1,2,3,��,n,n��0},ElemSetΪĳ�����ݼ���;R={N},N={<ai,a(i-1)>|i=1,2,3,��,n-1}
*/

/*˳��洢�ṹ*/
#inlude<iostream>
using namespace std;
template<class ElemType>
class SqList
{
protected:
	int count;//Ԫ�ظ���
	int maxSize;//���鳤��
	ElemType *elems;//�������������ΪElemType
public:
	SqList(int size = DEFAULT_SIZE);
	virtual~sqList();
	int Length() const;
	bool Empty() const;//�ж��Ƿ�Ϊ��
	void Clear();//���
	void Traverse(void(*visit)(const ElemType&)) const;//�������Ա�(���ζ����Ա��ÿ��Ԫ�ص��ú���(*visit))
	bool GetElem(int position, ElemType &e) const;//��ָ��λ�õ�Ԫ��
	bool SetElem(int position, const ElemType &e);//����ָ��λ�õ�Ԫ��ֵ
	bool Delete(int position, ElemType &e);//ɾ����position��Ԫ�أ���e������ֵ
	bool Insert(int position, const ElemType &e);//��position��λ�ò���Ԫ��e
	SqList(const SqList<ElemType>&copy);//���ƹ��캯��ģ��
	SqList<ElemType>&operator=(const SqList<ElemType> &copy);//���ظ��ƺ���
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
		for (int pos = Length(); pos >= position; pos--)//����λ��֮���Ԫ�غ���
		{
			GetElem(pos, tmp);
			SetElem(pos + 1, tmp);
		}
		SetElem(position, e);
		return true;
	}
}
/*
ƽ���ƶ�����:��(i=1,��,n+1)p(i)(n-i+1)=��(i=1,��,n+1)(1/(n+1))(n-i+1)=n/2
p(i)Ϊ�ڵ�iλ�ò���Ԫ�صĸ��ʶ�Ϊ1/(n+1)
��T(n)=O(n)
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
//��lc����la��lb��ʾ�ļ��ϵĲ
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
//��la����Ϊ���������֣��������Ԫ��Ϊ�������ұ�����Ԫ��Ϊż������Ҫ��ʱ�临�Ӷ�ΪO(n)
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
