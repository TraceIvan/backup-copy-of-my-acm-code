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
class LinkStack
{
protected:
	Node<T>*top;//ջ��ָ��
	int count;//Ԫ�ظ���
public:
	LinkStack();
	virtual~LinkStack();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const T&)) const;
	bool Push(const T&e);
	bool Top(T&e) const;
	bool Pop(T &e);
	LinkStack(const LinkStack<T>&copy);
	LinkStack<T> &operator=(const LinkStack<T>&copy);
};
template<class T>
LinkStack<T>::LinkStack()
{
	top = NULL;
	count = 0;
}
template<class T>
LinkStack<T>::~LinkStack()
{
	Clear();
}
template<class T>
int LinkStack<T>::Length() const
{
	return count;
}
template<class T>
bool LinkStack<T>::Empty() const
{
	return top == NULL;
}
template<class T>
void LinkStack<T>::Clear()
{
	T tmpElem;
	while (!Empty())
		Pop(tmpElem);
}
template<class T>
void LinkStack<T>::Traverse(void(*visit)(const T&)) const
{
	Node<T> *tmpPtr;
	LinkStack<T> tmpS;//��ʱջ��Ԫ��˳���뵱ǰջ�෴
	for (tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		tmpS.Push(tmpPtr->data);
	}
	for (tmpPtr = tmpS.top; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		(*visit)(tmpPtr->data);
	}
}
template<class T>
bool LinkStack<T>::Push(const T&e)
{
	Node<T>*newTop = new Node<T>(e, top);
	if (newTop == NULL)
	{
		return false;
	}
	else
	{
		top = newTop;
		count++;
		return true;
	}
}
template<class T>
bool LinkStack<T>::Top(T &e) const
{
	if (Empty())
	{
		return false;
	}
	else
	{
		e = top->data;
		return true;
	}
}
template<class T>
bool LinkStack<T>::Pop(T&e)
{
	if (Empty())
	{
		return false;
	}
	else
	{
		Node<T> *old_top = top;
		e = old_top->data;
		top = old_top->next;
		count--;
		delete old_top;
		return true;
	}
}
template<class T>
LinkStack<T>::LinkStack(const LinkStack<T> &copy)
{
	if (copy.Empty())
	{
		top = NULL;
		count = 0;
	}
	else
	{
		top = new Node<T>(copy.top->data);
		count = copy.count;
		Node<T>*buttomPtr = top;
		for (Node<T>*tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
		{
			buttomPtr->next = new Node<T>(tmpPtr->data);
			buttomPtr = buttomPtr->next;
		}
	}
}
template<class T>
LinkStack<T>&LinkStack<T>::operator=(const LinkStack<T>&copy)
{
	if (&copy != this)
	{
		if (copy.Empty())
		{
			top = NULL;
			count = 0;
		}
		else
		{
			Clear();
			top = new Node<T>(copy.top->data);
			count = copy.count;
			Node<T>*buttomPtr = top;
			for (Node<T>*tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
			{
				buttomPtr->next = new Node<T>(tmpPtr->data);
				buttomPtr = buttomPtr->next;
			}
		}
	}
	return *this;
}
//��:��׺���ʽ��ֵ
char Graph[7][7] = { { '>','>','<','<','<','>','>' },{ '>','>','<','<','<','>','>' },{ '>','>','>','>','<','>','>' },{ '>','>','>','>','<','>','>' },{ '<','<','<','<','<','=','e' },{ '>','>','>','>','e','>','>' },{ '<','<','<','<','<','e','=' } };
char Optr[7] = { '+','-','*','/','(',')','=' };
class Calculator
{
private:
	static char Getchar();//���������������ո񣬻��з����Ʊ��
	static bool IsOperator(char ch);//�ж��ַ�ch�Ƿ�Ϊ������
	static char Precede(char theta1, char theta2);//�ж���̳��ֵĲ�����theta1��theta2�����ȼ�
	static double Operate(double left, char theta, double right);//ִ������ left theta right
	static void Get2Operands(LinkStack<double>&opnd, double &left, double &right);//��ջopnd���˳�����������
public:
	Calculator() {};
	virtual~Calculator() {};
	static void Run();
};
char Calculator::Getchar()
{
	char tmp;
	tmp = cin.get();
	return tmp;
}
bool Calculator::IsOperator(char ch)
{
	if (ch != ' '&&ch != '\n'&&ch != '\t')
		return true;
	else return false;
}
char Calculator::Precede(char theta1, char theta2)
{
	int t1, t2;
	for (int i = 0; i<7; i++)
		if (theta1 == Optr[i])
		{
			t1 = i;
			break;
		}
	for (int i = 0; i<7; i++)
		if (theta2 == Optr[i])
		{
			t2 = i;
			break;
		}
	return Graph[t1][t2];
}
double Calculator::Operate(double left, char theta, double right)
{
	switch (theta)
	{
	case'+':return left + right;
	case'-':return left - right;
	case'*':return left*right;
	case'/':return left / right;
	}
}
void Calculator::Get2Operands(LinkStack<double>&opnd, double &left, double &right)
{
	opnd.Pop(right);
	opnd.Pop(left);
}
void Calculator::Run()
{
	LinkStack<double>opnd;//������ջ
	LinkStack<char>optr;//������ջ
	optr.Push('=');
	char ch;//��ʱ�ַ�
	char optrTop;//optrջ��ջ���ַ�
	double operand;//������
	char theta;//������
	cin >> ch;
	while ((optr.Top(optrTop), optrTop != '=') || ch != '=')
	{
		if (!IsOperator(ch))
		{
			cin.putback(ch);//���ַ�ch�Ż�������
			cin >> operand;
			opnd.Push(operand);
			cin >> ch;
		}
		else
		{
			switch (Precede(optrTop, ch))
			{
			case'<':
				optr.Push(ch);
				cin >> ch;
				break;
			case'=':
				if (ch == ')')
				{
					optr.Pop(optrTop);
					cin >> ch;
				}
				break;
			case'>':
				double left, right;
				Get2Operands(opnd, left, right);
				optr.Pop(theta);
				opnd.Push(Operate(left, theta, right));
				break;
			case'e'://������ƥ���
				cout << "������ƥ���" << endl;
				exit(2);
			}
		}
	}
	opnd.Top(operand);
	cout << "���ʽ��ֵΪ:" << operand << endl;
}

int main()
{
	Calculator C;
	C.Run();
	return 0;
}


