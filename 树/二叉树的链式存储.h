#ifndef BINTREENODE_H_
#define BINTREENODE_H_
//二叉链表:数据元素，左右孩子指针(缺点是从某个结点出发，要找到其双亲结点，需要从根结点开始搜索，效率低)
//三叉链表:数据元素，左右孩子指针，双亲指针
//在实际使用中，经常需要从根结点开始访问二叉树的各个结点，一般使用二叉链表
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
    //辅助函数模板
    BinTreeNode<T>* CopyTreeHelp(const BinTreeNode<T>*r);//复制二叉树
    void DestroyHelp(BinTreeNode<T>*&r);//销毁以r为根的二叉树
    void PreOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const;//先序遍历
    void InOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const;//中序遍历
    void PostOrderHelp(const BinTreeNode<T>*r, void(*visit)(const T&)) const;//后序遍历
    int HeightHelp(const BinTreeNode<T>*r) const;//返回二叉树的高
    int NodeCountHelp(const BinTreeNode<T>*r) const;//返回结点个数
    BinTreeNode<T>* ParentHelp(const BinTreeNode<T>*r, const BinTreeNode<T>*cur) const;//返回cur的双亲

public:
    BinaryTree();
    virtual~BinaryTree();
    BinTreeNode<T>*GetRoot() const;//返回二叉树的根
    bool Empty() const;//判断二叉树是否为空
    bool GetElem(const BinTreeNode<T>*cur, T&e) const;//用e返回结点元素值
    bool SetElem(BinTreeNode<T>*cur, const T&e);//将结点cur值置为e
    void InOrder(void(*visit)(const T&)) const;
    //中序遍历
    void PreOrder(void(*visit)(const T&)) const;//先序遍历
    void PostOrder(void(*visit)(const T&))const;//后序遍历
    void LevelOrder(void(*visit)(const T&)) const;//层次遍历
    int NodeCount()const;//求结点个数
    BinTreeNode<T>* LeftChild(const BinTreeNode<T>*cur) const;//返回结点cur的左孩子
    BinTreeNode<T>* RightChild(const BinTreeNode<T>*cur) const;//返回结点cur的右孩子
    BinTreeNode<T>* Parent(const BinTreeNode<T>*cur) const;//返回结点cur的双亲
    void InsertLeftChild(BinTreeNode<T>*cur, const T&e);//插入左孩子
    void InsertRightChild(BinTreeNode<T>*cur, const T&e);//插入右孩子
    void DeleteLeftChild(BinTreeNode<T>*cur);//删除左孩子
    void DeleteRightChild(BinTreeNode<T>*cur);//删除右孩子
    int Height() const;//求高
    BinaryTree(const T&e);//建立以e为根的二叉树
    BinaryTree(const BinaryTree<T>&copy);
    BinaryTree(BinTreeNode<T>*r);//建立以r为根的二叉树
    BinaryTree<T>& operator=(const BinaryTree<T>& copy);
};
//三叉链表
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
//    //辅助函数模板:和二叉链表相应部分完全相同
//public:
//    //与二叉树相应部分完全相同
//};
////下面为二叉链表函数实现
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
D  空  E  F
空  G
*/
//先序遍历:根(双亲)-左子树-右子树(ABDGCEF)
//中序遍历:左子树-根(双亲)-右子树(DGBAECF)
//后序遍历:左子树-右子树-根(双亲)(GDBEFCA)
//层次遍历:按层次，从上到下，从左到右访问各结点(ABCDEFG)
//遍历算法
//①递归算法
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

//②非递归算法
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
        {//cur的先序序列后继为栈s的栈顶结点的非空右孩子
            while (!s.Empty())
            {
                s.Pop(cur);
                cur = cur->rightChild;
                if (cur != NULL) break;//右孩子非空即为先序序列后继
            }
        }
        else
        {//栈s为空，无先序序列后继
            cur = NULL;
        }
    }
}
//中序遍历:首先访问最左下侧的结点，若右孩子非空，则中序序列的后继为右子树的最左侧结点，反之，则后继为距离该结点最近且是双亲的为左孩子结点的双亲结点。
template<class T>
BinTreeNods<T>* GoFarLeft(BunTreeNode<T>*r, LinkStack<BinTreeNode<T>*>&s)
{//返回以r为根的二叉树最左侧结点，并将搜索过程中的结点加入到栈s中
    if (r == NULL)
    {
        return NULL;
    }
    else
    {
        BinTreeNode<T>*cur = r;//当前结点
        while (cur->leftChild != NULL)
        {//cur存在左孩子，则cur移向左孩子
            s.Push(cur);
            cur = cur->leftChild;
        }
        return cur;//cur为最左侧结点
    }
}
template<class T>
void NonRecurInOrder(const BinaryTree<T>&bt, void(*visit)(const T&))
{
    BinTreeNode<T>*cur;
    LinkStack<BinTreeNode<T>*>s;

    cur = GoFarLeft<T>(bt.GetRoot(), s);//cur二叉树的最左侧结点
    while (cur != NULL)
    {
        (*visit)(cur->data);

        if (cur->rightChild != NULL)
        {//cur的中序序列后继为右子树的最左侧的结点
            cur = GoFarLeft(cur->rightChild, s);
        }
        else if (!s.Empty())
        {
            s.Pop(cur);
        }
        else
        {//栈s为空，无中序序列后继
            cur = NULL;
        }
    }
}
//后序遍历:由于最后访问根结点，对任一结点，应先沿左子树往下搜索并存地址到栈中，直至搜索到没有左子树为止。若该结点无右子树，则直接访问该结点，否则从该结点的右子树起，按同样方法访问右子树的各结点，访问完右子树的所有结点后，才访问该结点
template<class T>
struct ModiNode//结点结构
{
    BinTreeNode<T>*node;//指向结点
    bool rightSubTreeVisited;//右子树是否已被访问
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
        BinTreeNode<T>*cur = r;//当前结点
        ModiNode<T>*newPtr;//被修改后的结点
        while (cur->leftChild != NULL)
        {
            newPtr = new ModiNode<T>;
            newPtr->node = cur;
            newPtr->rightSubTreeVisited = false;
            s.Push(newPtr);
            cur = cur->leftChild;
        }
        newPtr = new ModiNode<T>;
        newPtr->node = cur;//指向结点
        newPtr->rightSubTreeVisited = false;//表示右子树未被访问
        return newPtr;//最左侧的被修改后的结点
    }
}

template<class T>
void NonRecurPostOrder(const BinaryTree<T>&bt, void(*visit)(const T&))
{
    ModiNode<T>*cur;//当前被搜索结点
    LinkStack<ModiNode<T>*>s;

    cur = GoFarLeft<T>(bt.GetRoot(), s);//cur为二叉树的最左侧的被搜索结点
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

//层次遍历:用队列来存储已访问过的结点的孩子结点
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
//因为每个结点的地址都记录在其双亲结点中，所以销毁的次序应按照后序遍历的次序

template<class T>
BinTreeNode<T>* BinaryTree<T>::CopyTreeHelp(BinTreeNode<T>*r)
{
    if (r == NULL)
    {
        return MULL;
    }
    else
    {
        BinTreeNode<T>*lChild = CopyTreeHelp(r->leftChild);//复制左子树
        BinTreeNode<T>*rChild = CopyTreeHelp(r->rightChild);//复制右子树
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
//二叉树的显示
//树状显示:
/*
1
2    3
空  4  5 空
/3/
//5
1//
//4
/2/
*/
//先右子树，再根结点，后左子树
//显示的列数为层次数
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
//由先序序列与中序序列构造二叉树
//从先序序列中可以确定二叉树的根D,而在中序序列中由D分割成两部分，前一部分为左子树，后一部分是右子树，由此确定的左右子树的结点个数反过来可将先序序列中除根结点外的部分分成左右子树的先序序列。以此类推，便可得到整棵二叉树。

template<class T>
void CreateBinaryTreeHelp(BinTreeNode<T>*&r, T pre[], T in[], int preLeft, int preRight, int inLeft, int inRight)
{//已知先序序列pre[preLeft…preRight]和中序序列[inLeft…inRight]
    if (preLeft>preRight || inLeft>inRight)
    {//二叉树无结点
        r = NULL;
    }
    else
    {//二叉树有结点
        r = new BinTreeNode<T>(pre[preLeft]);//生成根结点
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
    return BinaryTree<T>(r);//返回以r为根的二叉树
}
//由后序序列与中序序列构造类似
//表达式的前缀(波兰式)表示，中缀表示和后缀(逆波兰式)表示
//表达式=(第一操作数--左子树)(运算符--根)(第二操作数--右子树)
//a-b/(c+d)+e*f
//先序:+-a/b+cd*ef ——前缀(波兰式)表示
//中序:a-b/c+d+e*f ——中缀表示
//后序:abcd+/-ef*+ ——后缀(逆波兰式)表示




#endif // !BINTREENODE_H_

