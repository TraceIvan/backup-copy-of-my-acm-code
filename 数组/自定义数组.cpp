//�˷�nά�����±��޷���֤�Ϸ��Ե�ȱ��
template<class T>
class Array
{
protected:
	T *base;//����Ԫ�ػ�ַ
	int dim;//����ά��
	int *bounds;//�����ά����
	int *constants;//����ӳ��������
	int Locate(int sub0, va_list &va) const;//��Ԫ����˳��洢�е�λ��
public:
	Array(int d, ��);//��ά��d�����ĸ�ά���ȹ��캯��
	~Array();//��������
	T & operator()(int sub0, ��);//���غ��������
	Array(const Array<T>&copy);
	Array<T>& operator=(const Array<T>&copy);
};//�����õ��˱䳤����
template<class T>
Array<T>::Array(int d, ��)
{
	if (d<1) throw"ά������С��1!";
	dim = d;
	bounds = new int[dim];//���������ά���ȴ洢�ռ�
	va_list va;//�䳤��������
	int elemTotal = 1;//Ԫ������
	int i;//��ʱ����

	va_start(va, d);//��ʼ������va,���ڴ洢�䳤������Ϣ��dΪʡ�Ժ�������ұߵĲ�����ʶ��
	for (i = 0; i<dim; i++)//Ϊ��ά���ȸ�ֵ������������Ԫ�ظ���
	{
		bounds[i] = va_arg(va, int);//ȡ���䳤������Ϊ��ά����
		elemTotal = elemTotal*bounds[i];//ͳ��������Ԫ�ظ���//�о�������
	}
	va_end(va);//�����䳤����������

	base = new T[elemTotal];//��������Ԫ�ؿռ�
	constants = new int[dim];//��������ӳ��������
	constants[dim - 1] = 1;
	for (i = dim - 2; i >= 0; --i)
		constants[i] = bounds[i + 1] * constants[i + 1];//��������ӳ��������
}

template<class T>
int Array<T>::Locate(int sub0, va_list &va) const
{
	if (!(sub >= 0 && sub0<bounds[0])) throw"�±�Խ��";
	int off = constants[0] * sub0;//��ʼ��Ԫ����˳��洢�е�λ��
	for (int i = 1; i<dim; i++)
	{
		int sub = va_arg(va, int);//ȡ������Ԫ���±�
		if (!(sub >= 0 && <bounds[i])) throw"�±�Խ��!";
		off += constants[i] * sub;
	}
	return off;
}

template<class T>
T &Array<T>::operator()(int sub0, ��)
{
	va_list va;
	va_start(va, sub0);//��ʼ������va,���ڴ洢�䳤������Ϣ��sub0Ϊʡ�Ժ�������ұߵĲ�����ʶ��
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
//Ҫ����[]��������ɲ��ֶ���һά���飬��ά���飬������ͨ���Բ�