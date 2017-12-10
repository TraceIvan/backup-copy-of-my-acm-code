#ifndef SQBINARYTREE_H_
#define SQBINARYTREE_H_
//对于完全二叉树，若已知结点的编号，按编号的次序1～n依次将结点的值存储到数组的1～n位置
//对于大多数的一般二叉树，要补设虚结点，使其成为完全二叉树，然后编号存储。但这是一种很大的浪费(虚结点数目可能很大)。此时需要用标志tag用于标识结点是否为空
enum SqBinTreeNodeTagType
{
    EMPTY_NODE, NON_EMPTY
};
template<class T>
struct SqBinTreeNode
{
    T data;
    SqBinTreeNodeTagType tag;

    SqBinTreeNode();
    SqBinTreeNode(T item, SqBinTreeNodeTagType tg = EMPTY_NODE);
};

template<class T>
class SqBinaryTree
{
protected:

    int maxSize;//最大结点个数
    SqBinTreeNode<T>*elems;
    int root;
    //辅助模板函数

public:
    SqBinaryTree();
    virtual~SqBinaryTree();
    int GetRoot() const;//返回根
    bool NodeEmpty(int cur) const;//判断结点cur是否为空
    bool GetEtem(int cur, T &e) const;//返回结点cur的元素值
    bool SetElem(int cur, const T&e);//将结点cur的值置为e
    bool Empty() const;//判断二叉树是否为空
    void InOrder(void(*visit)(const T&)) const;//中序遍历
    void PreOreder(void(*visit)(const T&)) const;//先序遍历
    void PostOreder(void(*visit)(const T&)) const;//后序遍历
    void LevelOreder(void(*visit)(const T&)) const;//层次遍历
    int NodeCount() const;//求结点个数
    int LeftChild(const int cur) const;//返回结点cur的左孩子
    int RightChild(const int cur) const;//返回结点cur的右孩子
    int Parent(const int cur) const;//返回结点cur的双亲
    void InsertLeftChild(int cur, const T&e);//插入左孩子(若已存在则改变值)
    void InsertRightChild(int cur, const T&e);//插入右孩子(若已存在则改变值)
    void DeleteLeftChild(int cur);//删除左子树
    void DeleteRightChild(int cur);//删除右子树
    int Height() const;//求二叉树的高
    SqBinaryTree(const T&e, int size = DEFAULT_SIZE);//建立以e为根的二叉树
    SqBinaryTree(const SqBinaryTree<T>&copy);
    SqBinaryTree(SqBinTreeNode<T>es[], int r, int size = DEFAULT_SIZE);//由es[],r和size构造二叉树
    SqBinaryTree<T>& operator=(const SqBinaryTree<T>&copy);
};

#endif // !SQBINARYTREE_H_



