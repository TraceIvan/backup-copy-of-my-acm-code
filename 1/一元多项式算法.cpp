#include<iostream>
using namespace std;
struct Node
{
	double a;
	double b;
	Node *next;
};
class List
{
private:
	Node* head;
	Node* tail;
	int count;
	Node* GetPtr(int pos) const;//找到第pos位置的结点
public:
	List();
	~List();
	void Input_n(int n);//从最后一个开始插入
	void Insert(double a0, double b0, int pos);//在第pos后的一个位置插入
	void Delete(int pos);//删除第pos个结点
	List* Add(List*l1);//多项式相加
					   //List* Mul(List*l1);//多项式相乘
	void Sort();//多项式按幂降序
	void Display();//输出多项式
	void Add_Pos_Node(double a0, double b0, Node*Tmp);//在Tmp指向的结点后面加入
};
List::~List()
{
	if (tail == head)
	{
		delete head;
		head = tail = NULL;
	}
	else
	{
		Node*tmp = head;
		head = head->next;
		for (; head; head = head->next)
		{
			delete tmp;
			tmp = head;
		}
		delete tmp;
		tmp = tail = NULL;
	}
}
Node* List::GetPtr(int pos) const
{
	if (pos<1 || pos>count)
		return NULL;
	else
	{
		Node*tmp = head;
		while (pos--) tmp = tmp->next;
		return tmp;
	}
}
List::List()
{
	head = new Node;
	head->next = NULL;
	tail = head;
	count = 0;
}
void List::Input_n(int n)
{
	while (n--)
	{
		Node*Tmp = new Node;
		double a0, b0;
		cin >> a0 >> b0;
		Add_Pos_Node(a0, b0, tail);
	}
}
void List::Insert(double a0, double b0, int pos)
{
	Node*tmp = GetPtr(pos);
	if (tmp) Add_Pos_Node(a0, b0, tmp);
	else cout << "插入出错" << endl;
}

void List::Delete(int pos)
{
	Node*tmp = GetPtr(pos - 1);
	if (tmp == head&&tail == head->next)
	{
		tmp = tmp->next;
		delete tmp;
		head->next = NULL;
		tail = head;
	}
	else
	{
		Node*tmp0 = tmp->next;
		tmp = tmp0->next;
		delete tmp0;
	}
	count--;
}
List* List::Add(List*l1)
{
	List *c = new List;
	Node*t = c->head;
	Node*t1 = this->head->next;
	Node*t2 = l1->head->next;
	while (t1&&t2)
	{
		if (t1->b>t2->b)
		{
			c->Add_Pos_Node(t1->a, t1->b, t);
			t = t->next;
			t1 = t1->next;
		}
		else if (t1->b<t2->b)
		{
			c->Add_Pos_Node(t2->a, t2->b, t);
			t = t->next;
			t2 = t2->next;
		}
		else
		{
			double sum = t1->a + t2->a;
			if (sum) c->Add_Pos_Node(sum, t1->b, t);
			t = t->next;
			t1 = t1->next;
			t2 = t2->next;
		}
	}
	for (; t1; t1 = t1->next, t = t->next)
	{
		c->Add_Pos_Node(t1->a, t1->b, t);
	}
	for (; t2; t2 = t2->next, t = t->next)
	{
		c->Add_Pos_Node(t2->a, t2->b, t);
	}
	return c;
}
/*List* List::Mul(List*l1)
{

}*/
void List::Sort()
{
	Node* Ptr = head->next;
	for (; Ptr->next->next; Ptr = Ptr->next)
	{
		Node* Ptr0 = Ptr->next;
		Node* Ptr1 = Ptr;
		for (; Ptr0; Ptr0 = Ptr0->next)
		{
			if (Ptr0->b>Ptr1->b) Ptr1 = Ptr0;
		}
		if (Ptr1 != Ptr)
		{
			double a0 = Ptr1->a;
			double b0 = Ptr1->b;
			Ptr1->a = Ptr->a;
			Ptr1->b = Ptr->b;
			Ptr->a = a0;
			Ptr->b = b0;
		}
	}
}
void List::Display()
{
	if (tail == head) cout << "多项式为空" << endl;
	else
	{
		Node*tmp = head->next;
		for (; tmp; tmp = tmp->next)
		{
			if (tmp == head->next)
				cout << "(" << tmp->a << "," << tmp->b << ")";
			else cout << "-->" << "(" << tmp->a << "," << tmp->b << ")";
		}
		cout << endl;
	}
}
void List::Add_Pos_Node(double a0, double b0, Node*Tmp)
{
	Node *Tmp0 = new Node;
	Tmp0->a = a0;
	Tmp0->b = b0;
	Tmp0->next = NULL;
	if (Tmp == tail)
	{
		tail->next = Tmp;
		tail = tail->next;
	}
	else
	{
		Tmp0->next = Tmp->next;
		Tmp->next = Tmp0;
	}
	count++;
}

int main()
{
	List l1, l2;
	int n1, n2;
	cin >> n1;
	l1.Input_n(n1);
	cin >> n2;
	l2.Input_n(n2);
	l1.Sort();
	l2.Sort();
	List *l3 = l1.Add(&l2);
	l3->Display();
	return 0;
}