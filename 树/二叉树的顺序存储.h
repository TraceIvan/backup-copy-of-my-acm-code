#ifndef SQBINARYTREE_H_
#define SQBINARYTREE_H_
//������ȫ������������֪���ı�ţ�����ŵĴ���1��n���ν�����ֵ�洢�������1��nλ��
//���ڴ������һ���������Ҫ�������㣬ʹ���Ϊ��ȫ��������Ȼ���Ŵ洢��������һ�ֺܴ���˷�(������Ŀ���ܴܺ�)����ʱ��Ҫ�ñ�־tag���ڱ�ʶ����Ƿ�Ϊ��
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

    int maxSize;//��������
    SqBinTreeNode<T>*elems;
    int root;
    //����ģ�庯��

public:
    SqBinaryTree();
    virtual~SqBinaryTree();
    int GetRoot() const;//���ظ�
    bool NodeEmpty(int cur) const;//�жϽ��cur�Ƿ�Ϊ��
    bool GetEtem(int cur, T &e) const;//���ؽ��cur��Ԫ��ֵ
    bool SetElem(int cur, const T&e);//�����cur��ֵ��Ϊe
    bool Empty() const;//�ж϶������Ƿ�Ϊ��
    void InOrder(void(*visit)(const T&)) const;//�������
    void PreOreder(void(*visit)(const T&)) const;//�������
    void PostOreder(void(*visit)(const T&)) const;//�������
    void LevelOreder(void(*visit)(const T&)) const;//��α���
    int NodeCount() const;//�������
    int LeftChild(const int cur) const;//���ؽ��cur������
    int RightChild(const int cur) const;//���ؽ��cur���Һ���
    int Parent(const int cur) const;//���ؽ��cur��˫��
    void InsertLeftChild(int cur, const T&e);//��������(���Ѵ�����ı�ֵ)
    void InsertRightChild(int cur, const T&e);//�����Һ���(���Ѵ�����ı�ֵ)
    void DeleteLeftChild(int cur);//ɾ��������
    void DeleteRightChild(int cur);//ɾ��������
    int Height() const;//��������ĸ�
    SqBinaryTree(const T&e, int size = DEFAULT_SIZE);//������eΪ���Ķ�����
    SqBinaryTree(const SqBinaryTree<T>&copy);
    SqBinaryTree(SqBinTreeNode<T>es[], int r, int size = DEFAULT_SIZE);//��es[],r��size���������
    SqBinaryTree<T>& operator=(const SqBinaryTree<T>&copy);
};

#endif // !SQBINARYTREE_H_



