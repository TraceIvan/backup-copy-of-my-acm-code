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
	Node<T>*top;//栈顶指针
	int count;//元素个数
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
	LinkStack<T> tmpS;//临时栈，元素顺序与当前栈相反
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
//例:中缀表达式求值
char Graph[7][7] = { { '>','>','<','<','<','>','>' },{ '>','>','<','<','<','>','>' },{ '>','>','>','>','<','>','>' },{ '>','>','>','>','<','>','>' },{ '<','<','<','<','<','=','e' },{ '>','>','>','>','e','>','>' },{ '<','<','<','<','<','e','=' } };
char Optr[7] = { '+','-','*','/','(',')','=' };
class Calculator
{
private:
	static char Getchar();//从输入流中跳过空格，换行符及制表符
	static bool IsOperator(char ch);//判断字符ch是否为操作符
	static char Precede(char theta1, char theta2);//判断相继出现的操作符theta1和theta2的优先级
	static double Operate(double left, char theta, double right);//执行运算 left theta right
	static void Get2Operands(LinkStack<double>&opnd, double &left, double &right);//从栈opnd中退出两个操作数
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
	LinkStack<double>opnd;//操作数栈
	LinkStack<char>optr;//操作符栈
	optr.Push('=');
	char ch;//临时字符
	char optrTop;//optr栈的栈顶字符
	double operand;//操作数
	char theta;//操作符
	cin >> ch;
	while ((optr.Top(optrTop), optrTop != '=') || ch != '=')
	{
		if (!IsOperator(ch))
		{
			cin.putback(ch);//将字符ch放回输入流
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
			case'e'://操作符匹配错
				cout << "操作符匹配错" << endl;
				exit(2);
			}
		}
	}
	opnd.Top(operand);
	cout << "表达式的值为:" << operand << endl;
}

int main()
{
	Calculator C;
	C.Run();
	return 0;
}


