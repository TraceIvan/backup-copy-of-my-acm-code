#ifndef BINTREENODE_H_
#define BINTREENODE_H_
//��������:����Ԫ�أ����Һ���ָ��(ȱ���Ǵ�ĳ����������Ҫ�ҵ���˫�׽�㣬��Ҫ�Ӹ���㿪ʼ������Ч�ʵ�)
//��������:����Ԫ�أ����Һ���ָ�룬˫��ָ��
//��ʵ��ʹ���У�������Ҫ�Ӹ���㿪ʼ���ʶ������ĸ�����㣬һ��ʹ�ö�������
template<class T>
struct BinTreeNode
{
    T data;
    BinTreeNode<T>*leftChild;
    BinTreeNode<T>*rightChild;

    BinTreeNode();
    BinTreeNode(const T&val, BinTreeNode<T>*lChild = NULL, BinTreeNode<T>*rChild = NULL);
};
template<class T>
BinTreeNode<T>::BinTreeNode()
{
    leftChild = rightChild = NULL;
}

template<class T>
BinTreeNode<T>::BinTreeNode(const T&val, BinTreeNode<T>*lChild = NULL, BinTreeNode<T>*rChild = NULL)
{
    data = val;
    leftChild = lChild;
    rightChild = rChild;
}

template<class T>
class BinaryTree
{
protected:
    BinTreeNode<T>*root;
    //��������ģ��
    BinTreeNode<T>* CopyTreeHelp(const BinTreeNode<T>*r);//���ƶ�����
    void DestroyHelp(BinTreeNode<T>*&r);//������rΪ���Ķ�����
    void PreOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const;//�������
    void InOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const;//�������
    void PostOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const;//�������
    int HeightHelp(const BinTreeNode<T>*r) const;//���ض������ĸ�
    int NodeCountHelp(const BinTreeNode<T>*r) const;//���ؽ�����
    BinTreeNode<T>* ParentHelp(const BinTreeNode<T>*r, const BinTreeNode<T>*cur) const;//����cur��˫��

public:
    BinaryTree();
    virtual~BinaryTree();
    BinTreeNode<T>*GetRoot() const;//���ض������ĸ�
    bool Empty() const;//�ж϶������Ƿ�Ϊ��
    bool GetElem(const BinTreeNode<T>*cur, T&e) const;//��e���ؽ��Ԫ��ֵ
    bool SetElem(BinTreeNode<T>*cur, const T&e);//�����curֵ��Ϊe
    void InOrder(void(*visit)(const T&)) const;
    //�������
    void PreOrder(void(*visit)(const T&)) const;//�������
    void PostOrder(void(*visit)(const T&))const;//�������
    void LevelOrder(void(*visit)(const T&)) const;//��α���
    int NodeCount()const;//�������
    BinTreeNode<T>* LeftChild(const BinTreeNode<T>*cur) const;//���ؽ��cur������
    BinTreeNode<T>* RightChild(const BinTreeNode<T>*cur) const;//���ؽ��cur���Һ���
    BinTreeNode<T>* Parent(const BinTreeNode<T>*cur) const;//���ؽ��cur��˫��
    void InsertLeftChild(BinTreeNode<T>*cur, const T&e);//��������
    void InsertRightChild(BinTreeNode<T>*cur, const T&e);//�����Һ���
    void DeleteLeftChild(BinTreeNode<T>*cur);//ɾ������
    void DeleteRightChild(BinTreeNode<T>*cur);//ɾ���Һ���
    int Height() const;//���
    BinaryTree(const T&e);//������eΪ���Ķ�����
    BinaryTree(const BinaryTree<T>&copy);
    BinaryTree(BinTreeNode<T>*r);//������rΪ���Ķ�����
    BinaryTree<T>& operator=(const BinaryTree<T>& copy);
};
//��������
//template<class T>
//struct TriLKBinTreeNode
//{
//    T data;
//    TriLKBinTreeNode<T>*leftChild;
//    TriLKBinTreeNode<T>*rightChild;
//    TriLKBinTreeNode<T>*parent;
//
//    TriLKBinTreeNode();
//    TriLKBinTreeNode(const T &val, TriLKBinTreeNode<T>*lChild = NULL, TriLKBinTreeNode<T>*rChild = NULL, TriLKBinTreeNode<T>*pt = NULL);
//};
//template<class T>
//class TriLKBinaryTree
//{
//protected:
//    TriLKBinTreeNode<T>*root;
//    //��������ģ��:�Ͷ���������Ӧ������ȫ��ͬ
//public:
//    //���������Ӧ������ȫ��ͬ
//};
////����Ϊ����������ʵ��
template<class T>
BinaryTree<T>::BinaryTree()
{
    root = NULL;
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
    DestroyHelp(root);
}

template<class T>
BinTreeNode<T>*BinaryTree<T>::GetRoot() const
{
    return root;
}

template<class T>
bool BinaryTree<T>::Empty() const
{
    return root == NULL;
}

template<class T>
void BinaryTree<T>::PreOrder(void(*visit)(T &)) const
{
    PreOrderHelp(root, visit);
}
template<class T>
void BinaryTree<T>::InOrder(void(*visit)(T &)) const
{
    InOrderHelp(root, visit);
}
template<class T>
void BinaryTree<T>::PostOrder(void(*visit)(T &)) const
{
    PostOrderHelp(root, visit);
}

template<class T>
int BinaryTree<T>::NodeCount() const
{
    return NodeCountHelp(root);
}

template<class T>
int BinaryTree<T>::Height() const
{
    return HeightHelp(root);
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
    DestroyHelp(root);
}
/*
A
B      C
D  ��  E  F
��  G
*/
//�������:��(˫��)-������-������(ABDGCEF)
//�������:������-��(˫��)-������(DGBAECF)
//�������:������-������-��(˫��)(GDBEFCA)
//��α���:����Σ����ϵ��£������ҷ��ʸ����(ABCDEFG)
//�����㷨
//�ٵݹ��㷨
template<class T>
void BinaryTree<T>::PreOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const
{
    if (r != NULL)
    {
        (*visit)(r->data);
        PreOrderHelp(r->leftChild, visit);
        PreOrderHelp(r->rightChild, visit);
    }
}
template<class T>
void BinaryTree<T>::InOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const
{
    if (r != NULL)
    {
        InOrderHelp(r->leftChild, visit);
        (*visit)(r->data);
        InOrderHelp(r->rightChild, visit);
    }
}

template<class T>
void BinaryTree<T>::PostOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const
{
    if (r != NULL)
    {
        PostOrderHelp(r->leftChild, visit);
        PostOrderHelp(r->rightChild, visit);
        (*visit)(r->data);
    }
}

//�ڷǵݹ��㷨
template<class T>
void NonRecurPreOrder(const BinaryTree<T>&bt, void(*visit)(const T&))
{
    BinTreeNode<T>*cur = bt.GetRoot();
    LinkStack<BinTreeNode<T>*>s;

    while (cur != NULL)
    {
        (*visit)(cur->data);
        s.Push(cur);
        if (cur->leftChild != NULL)
        {
            cur = cur->leftChild;
        }
        else if (!s.Empty())
        {//cur���������к��Ϊջs��ջ�����ķǿ��Һ���
            while (!s.Empty())
            {
                s.Pop(cur);
                cur = cur->rightChild;
                if (cur != NULL) break;//�Һ��ӷǿռ�Ϊ�������к��
            }
        }
        else
        {//ջsΪ�գ����������к��
            cur = NULL;
        }
    }
}
//�������:���ȷ��������²�Ľ�㣬���Һ��ӷǿգ����������еĺ��Ϊ��������������㣬��֮������Ϊ����ý���������˫�׵�Ϊ���ӽ���˫�׽�㡣
template<class T>
BinTreeNods<T>* GoFarLeft(BunTreeNode<T>*r, LinkStack<BinTreeNode<T>*>&s)
{//������rΪ���Ķ�����������㣬�������������еĽ����뵽ջs��
    if (r == NULL)
    {
        return NULL;
    }
    else
    {
        BinTreeNode<T>*cur = r;//��ǰ���
        while (cur->leftChild != NULL)
        {//cur�������ӣ���cur��������
            s.Push(cur);
            cur = cur->leftChild;
        }
        return cur;//curΪ�������
    }
}
template<class T>
void NonRecurInOrder(const BinaryTree<T>&bt, void(*visit)(const T&))
{
    BinTreeNode<T>*cur;
    LinkStack<BinTreeNode<T>*>s;

    cur = GoFarLeft<T>(bt.GetRoot(), s);//cur���������������
    while (cur != NULL)
    {
        (*visit)(cur->data);

        if (cur->rightChild != NULL)
        {//cur���������к��Ϊ�������������Ľ��
            cur = GoFarLeft(cur->rightChild, s);
        }
        else if (!s.Empty())
        {
            s.Pop(cur);
        }
        else
        {//ջsΪ�գ����������к��
            cur = NULL;
        }
    }
}
//�������:���������ʸ���㣬����һ��㣬Ӧ�����������������������ַ��ջ�У�ֱ��������û��������Ϊֹ�����ý��������������ֱ�ӷ��ʸý�㣬����Ӹý����������𣬰�ͬ�����������������ĸ���㣬�����������������н��󣬲ŷ��ʸý��
template<class T>
struct ModiNode//���ṹ
{
    BinTreeNode<T>*node;//ָ����
    bool rightSubTreeVisited;//�������Ƿ��ѱ�����
};

template<class T>
ModiNode<T>* GoFarLeft(BinTreeNode<T>*r, LinkStack<ModiNode<T>*>&s)
{
    if (r == NULL)
    {
        return NULL;
    }
    else
    {
        BinTreeNode<T>*cur = r;//��ǰ���
        ModiNode<T>*newPtr;//���޸ĺ�Ľ��
        while (cur->leftChild != NULL)
        {
            newPtr = new ModiNode<T>;
            newPtr->node = cur;
            newPtr->rightSubTreeVisited = false;
            s.Push(newPtr);
            cur = cur->leftChild;
        }
        newPtr = new ModiNode<T>;
        newPtr->node = cur;//ָ����
        newPtr->rightSubTreeVisited = false;//��ʾ������δ������
        return newPtr;//�����ı��޸ĺ�Ľ��
    }
}

template<class T>
void NonRecurPostOrder(const BinaryTree<T>&bt, void(*visit)(const T&))
{
    ModiNode<T>*cur;//��ǰ���������
    LinkStack<ModiNode<T>*>s;

    cur = GoFarLeft<T>(bt.GetRoot(), s);//curΪ�������������ı��������
    while (cur != NULL)
    {
        if (cur->node->rightChild == NULL || cur->rightSubTreeVisited)
        {
            (*visit)(cur->node->data);
            delete cur;

            if (!s.Empty())
            {
                s.Pop(cur);
            }
            else
            {
                cur = NULL;
            }
        }
        else
        {
            cur->rightSubTreeVisited = true;
            s.Push(cur);
            cur = GoFarLeft<T>(cur->node->rightChild, s);
        }
    }
}

//��α���:�ö������洢�ѷ��ʹ��Ľ��ĺ��ӽ��
template<class T>
void BinaryTree<T>::LevelOrder(void(*visit)(const T&)) const
{
    LinkQueue<BinTreeNode<T>*>q;
    BinTreeNode<T>*t = root;

    if (t != NULL) q.InQueue(t);
    while (!q.Empty())
    {
        q.OutQueue(t);
        (*visit)(t->data);
        if (t->leftChild != NULL)
        {
            q.InQueue(t->leftChild);
        }
        if (t->rightChild != NULL)
        {
            q.InQueue(t->rightChild);
        }
    }
}

template<class T>
int BinaryTree<T>::NodeCountHelp(const BinTreeNode<T>*r)const
{
    if (r == NULL) return 0;
    else return NodeCountHelp(r->leftChild) + NodeCountHelp(r->rightChild) + 1;
}

template<class T>
int BinaryTree<T>::HeightHelp(const BinTreeNode<T>*r) const
{
    if (r == NULL)
    {
        return 0;
    }
    else
    {
        int lHeight, rHeight;
        lHeight = HeightHelp(r->leftChild);
        rHeight = HeightHelp(r->rightChild);
        return (lHeight>rHeight ? lHeight : rHeight) + 1;
    }
}

template<class T>
void BinaryTree<T>::DestroyHelp(BinTreeNode<T>*&r)
{
    if (r != NULL)
    {
        DestroyHelp(r->leftChild);
        DestroyHelp(r->rightChild);
        delete r;
        r = NULL;
    }
}
//��Ϊÿ�����ĵ�ַ����¼����˫�׽���У��������ٵĴ���Ӧ���պ�������Ĵ���

template<class T>
BinTreeNode<T>* BinaryTree<T>::CopyTreeHelp(BinTreeNode<T>*r)
{
    if (r == NULL)
    {
        return MULL;
    }
    else
    {
        BinTreeNode<T>*lChild = CopyTreeHelp(r->leftChild);//����������
        BinTreeNode<T>*rChild = CopyTreeHelp(r->rightChild);//����������
        BinTreeNode<T>*r = new BinTreeNode<T>(r->data, lChild, rChild);

        return r;
    }
}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>&copy)
{
    root = CopyTreeHelp(copy.root);
}

template<class T>
BinaryTree<T>&BinaryTree<T>::operator=(const BinaryTree<T>&copy)
{
    if (&copy != this)
    {
        DestroyHelp(root);
        root = CopyTreeHelp(copy.root);
    }
    return *this;
}
//����������ʾ
//��״��ʾ:
/*
1
2    3
��  4  5 ��
/3/
//5
1//
//4
/2/
*/
//�����������ٸ���㣬��������
//��ʾ������Ϊ�����
template<class T>
void DisplayBTWithTreeShapeHelp(BinTreeNode<T>*r, int level)
{
    if (r != NULL)
    {
        DisplayBTWithTreeShapeHelp<T>(r->rightChild, level + 1);
        cout << endl;
        for (int i = 0; i<level - 1; i++)
        {
            cout << " ";
        }
        cout << r->data;
        DisplayBTWithTreeShapeHelp<T>(r->leftChild, level + 1);
    }
}

template<class T>
void DisplayBTWithTreeShape(const BinaryTree<T>&bt)
{
    DisplayBTWithTreeShapeHelp<T>(bt.GetRoot(), 1);
    cout << endl;
}
//�������������������й��������
//�����������п���ȷ���������ĸ�D,����������������D�ָ�������֣�ǰһ����Ϊ����������һ���������������ɴ�ȷ�������������Ľ������������ɽ����������г��������Ĳ��ֳַ������������������С��Դ����ƣ���ɵõ����ö�������

template<class T>
void CreateBinaryTreeHelp(BinTreeNode<T>*&r, T pre[], T in[], int preLeft, int preRight, int inLeft, int inRight)
{//��֪��������pre[preLeft��preRight]����������[inLeft��inRight]
    if (preLeft>preRight || inLeft>inRight)
    {//�������޽��
        r = NULL;
    }
    else
    {//�������н��
        r = new BinTreeNode<T>(pre[preLeft]);//���ɸ����
        int mid = inLeft;
        while (in[mid] != pre[preLeft])
        {
            mid++;
        }
        CreateBinaryTreeHelp(r->leftChild, pre, in, preLeft + 1, preLeft + mid - inLeft, inLeft, mid - 1);
        CreateBinaryTreeHelp(r->rightChild, pre, in, preLeft + mid - inLeft + 1, preRight, mid + 1, inRight);
    }
}
template<class T>
BinaryTree<T>CreateBinaryTree(T pre[], T in[], int n)
{
    BinTreeNode<T>*r;
    CreateBinaryTreeHelp<T>(r, pre, in, 0, n - 1, 0, n - 1);
    return BinaryTree<T>(r);//������rΪ���Ķ�����
}
//�ɺ����������������й�������
//���ʽ��ǰ׺(����ʽ)��ʾ����׺��ʾ�ͺ�׺(�沨��ʽ)��ʾ
//���ʽ=(��һ������--������)(�����--��)(�ڶ�������--������)
//a-b/(c+d)+e*f
//����:+-a/b+cd*ef ����ǰ׺(����ʽ)��ʾ
//����:a-b/c+d+e*f ������׺��ʾ
//����:abcd+/-ef*+ ������׺(�沨��ʽ)��ʾ




#endif // !BINTREENODE_H_

