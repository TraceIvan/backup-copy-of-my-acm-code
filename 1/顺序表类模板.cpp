template<class elemType>
class SqList
{
protected://顺序表实现的数据成员
	int count;//元素个数
	int maxSize;//顺序表最大元素个数
	elemType *elems;//存储元素
public://抽象数据类型方法声明及重载编译系统默认方法声明
	SqList(int size = DEFAULT_SIZE);//构造函数模板
	virtual ~SqList