//克服n维数组下标无法保证合法性的缺点
template<class T>
class Array
{
protected:
	T *base;//数组元素基址
	int dim;//数组维数
	int *bounds;//数组各维长度
	int *constants;//数组映像函数常量
	int Locate(int sub0, va_list &va) const;//求元素在顺序存储中的位置
public:
	Array(int d, …);//由维数d与随后的各维长度构造函数
	~Array();//析构函数
	T & operator()(int sub0, …);//重载函数运算符
	Array(const Array<T>&copy);
	Array<T>& operator=(const Array<T>&copy);
};//上面用到了变长参数
template<class T>
Array<T>::Array(int d, …)
{
	if (d<1) throw"维数不能小于1!";
	dim = d;
	bounds = new int[dim];//分配数组各维长度存储空间
	va_list va;//变长参数变量
	int elemTotal = 1;//元素总数
	int i;//临时变量

	va_start(va, d);//初始化变量va,用于存储变长参数信息，d为省略号左侧最右边的参数标识符
	for (i = 0; i<dim; i++)//为各维长度赋值并计算数组总元素个数
	{
		bounds[i] = va_arg(va, int);//取出变长参数作为各维长度
		elemTotal = elemTotal*bounds[i];//统计数组总元素个数//感觉有问题
	}
	va_end(va);//结束变长参数的引用

	base = new T[elemTotal];//分配数组元素空间
	constants = new int[dim];//分配数组映像函数常量
	constants[dim - 1] = 1;
	for (i = dim - 2; i >= 0; --i)
		constants[i] = bounds[i + 1] * constants[i + 1];//计算数组映像函数常量
}

template<class T>
int Array<T>::Locate(int sub0, va_list &va) const
{
	if (!(sub >= 0 && sub0<bounds[0])) throw"下标越界";
	int off = constants[0] * sub0;//初始化元素在顺序存储中的位置
	for (int i = 1; i<dim; i++)
	{
		int sub = va_arg(va, int);//取出数组元素下标
		if (!(sub >= 0 && <bounds[i])) throw"下标越界!";
		off += constants[i] * sub;
	}
	return off;
}

template<class T>
T &Array<T>::operator()(int sub0, …)
{
	va_list va;
	va_start(va, sub0);//初始化变量va,用于存储变长参数信息，sub0为省略号左侧最右边的参数标识符
	int off = Locate(sub0, va);
	va_end(va);
	return *(base + off);
}

template<class T>
Array<T>::Array(const Array<T>&copy)
{
	dim = copy.dim;

	int elemTotal = 1;
	int i;
	for (i = 0; i<dim; i++)
	{
		elemTotal = elemTotal*copy.bounds[i];
	}
	base = new T[elemTotal];
	for (i = 0; i<elemTotal; i++)
	{
		base[i] = copy.base[i];
	}

	bounds = new int[dim];
	constants = new int[dim];
	for (i = 0; i<dim; i++)
	{
		bounds[i] = copy.bounds[i];
		constants[i] = copy.constants[i];
	}
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>&copy)
{
	if (&copy != this)
	{
		if (base != NULL) delete[]base;
		if (bounds != NULL) delete[]bounds;
		if (constants != NULL) delete[]constants;

		dim = copy.dim;
		int elemTotal = 1;
		int i;
		for (i = 0; i<dim; i++)
		{
			elemTotal = elemTotal*copy.bounds[i];
		}
		base = new T[elemTotal];
		for (i = 0; i<elemTotal; i++)
		{
			base[i] = copy.base[i];
		}
		bounds = new int[dim];
		constants = new int[dim];
		for (i = 0; i<dim; i++)
		{
			bounds[i] = copy.bounds[i];
			constants[i] = copy.constants[i];
		}
	}
	return *this;
}
//要重载[]运算符，可并分定义一维数组，二维数组，…，但通用性差