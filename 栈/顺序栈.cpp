template<class T>
class SqStack
{
protected:
	int count;
	int maxSize;
	T*elems;
public:
	SqStack(int size = DEAULT_SIZE);
	virtual~SqStack();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const T&)) const;
	bool Push(const T&e);
	bool Top(T &e) const;
	bool Pop(T &e);
	SqStack(const SqStack<T>&copy);
	SqStack<T>&operator=(const SqStack<T> &copy);
};
template<class T>
SqStack<T>::SqStack(int size)
{
	maxSize = size;
	elems = new T[maxSize];
	count = 0;
}
template<class T>
SqStack<T>::~SqStack()
{
	delete[]elems;
}
template<class T>
int SqStack<T>::Length() const
{
	return count;
}
template<class T>
bool SqStack<T>::Empty() const
{
	return count == 0;
}
template<class T>
void SqStack<T>::Clear()
{
	count = 0;
}
template<class T>
void SqStack<T>::Traverse(void(*visit)(const T&)) const
{
	for (int pos = 1; pos <= Length(); pos++)
	{
		(*visit)(elems[pos - 1]);
	}
}
template<class T>
bool SqStack<T>::Push(const T&e)
{
	if (count == maxSize)
	{
		return false;
	}
	else
	{
		elems[count++] = e;
		return true;
	}
}
template<class T>
bool SqStack<T>::Top(T &e) const
{
	if (Empty())
	{
		return false;
	}
	else
	{
		e = elems[count - 1];
		return true;
	}
}
template<class T>
bool SqStack<T>::Pop(T &e)
{
	if (Empty())
	{
		return false;
	}
	else
	{
		e = elems[count - 1];
		count--;
		return true;
	}
}
template<class T>
SqStack<T>::SqStack(const SqStack<T>&copy)
{
	maxSize = copy.maxSize;
	elems = new T[maxSize];
	count = copy.count;
	for (int pos = 1; pos <= Length(); pos++)
	{
		elems[pos - 1] = copy.elems[pos - 1];
	}
}
template<class T>
SqStack<T>&SqStack<T>::operator=(const SqStack<T>&copy)
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;
		delete[]elems;
		elems = new T[maxSize];
		count = copy.count;
		for (int pos = 1; pos <= Length(); pos++)
		{
			elems[pos - 1] = copy.elems[pos - 1];
		}
	}
	return *this;
}
