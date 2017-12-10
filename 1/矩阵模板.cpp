template<class T>
class Matrix
{
protected:
	T *elems;
	int rows, cols;//����������
public:
	Matrix(int rs, int cs);
	~Matrix();
	int GetRows() const;
	int GetCols() const;
	T &operator()(int i, int j);
	Matrix(const Matrix<T> &copy);
	Matrix<T> &operator=(const Matrix<T>&copy);
};

template<class T>
Matrix<T>::Matrix(int rs, int cs)
{
	if (rs<1 && cs<1) throw "������������Ч";
	rows = rs;
	cols = cs;
	elems = new T[rows*cols];
}

template<class T>
T &Matrix<T>::operator()(int i, int j)
{
	if (i<1 || i>rows || j<1 || j>cols) throw "�±����";
	return elems[(i - 1)*cols + j - 1];
}

//���ԽǾ���
//��һ��n��n�����ԽǾ����У������Խ���(���Խ���<i=j>,�ͶԽ���<i=j+1>,�߶Խ���<i=j-1>)��֮���Ԫ�ض���0��Ϊһ������
//������ӳ�������ӳ��۶Խ���ӳ���
template<class T>
class TriDiagonalMatrix
{
protected:
	T *elems;
	int n;
public:
	TriDiagonalMatrix(int sz);
	~TriDiagonalMatrix();
	int GetSize() const;//���ؽ���
	T &operator()(int i, int j);
	TriDiagonalMatrix(const TriDiagonalMatrix<T>&copy);
	TriDiagonalMatrix<T>&operator=(const TriDiagonalMatrix<T> &copy);
};

template<class T>
TriDiagonalMatrix<T>::TriDiagonalMatrix(int sz)
{
	if (sz<1) throw "������������Ч!";
	n = sz;
	elems = new T[3 * n - 1];
}

template<class T>
T& TriDiagonalMatrix<T>::operator()(int i, int j)
{
	if (i<1 || i>n || j<1 || j>n) throw "�±����";
	if (i - j == 1) return elems[2 * n + i - 2];
	else if (i - j == 0) return elems[n + i - 1];
	else if (i - j == -1) return elems[i];
	else return elems[0];
}

//���Ǿ���
//�������Ǿ���:����i<jʱa[i,j]=0��c��
//�������Ǿ���:����i>jʱa[i,j]=0��c
//��Ԫ�ظ���:n(n+1)/2+1
//�ٰ���ӳ��̢ڰ���ӳ��
template<class T>
class LowerTriangularMatrix
{
protected:
	T *elems;
	int n;

public:
	LowerTriangularMatrix(int sz);
	~LowerTriangularMatrix();
	int GetSize() const;
	T &operator()(int i, int j);
};

template<class T>
LowerTriangularMatrix<T>::LowerTriangularMatrix(int sz)
{
	if (sz<1) throw "������������Ч!";
	n = sz;
	elems = new T[n*(n - 1) / 2 + 1];
}

template<class T>
T &LowerTriangularMatrix<T>::operator()(int i, int j)
{
	if (i<1 || i>n || j<1 || j>n) throw "�±����";
	if (i >= j) return elems[i*(i - 1) / 2 + j];
	else return elems[0];
}

//�Գƾ���(ֻ�洢�����ǻ��������е�Ԫ��)
//k=i(i-1)/2+j-1 (i��j)
//k=j(j-1)/2+i-1(i<j)
template<class T>
class SymmtryMatrix
{
protected:
	T *elems;
	int n;

public:
	SymmtryMatrix(int sz);
	~SymmtryMatrix();
	int GetSize() const;
	T &operator()(int i, int j);
	SymmtryMatrix(const SymmtryMatrix<T>&copy);
	SymmtryMatrix<T>& operator=(const SymmtryMatrix<T>&copy);
};

template<class T>
T& SymmtryMatrix<T>::operator()(int i, int j)
{
	if (i<1 || i>n || j<1 || j>n) throw "�±����!";
	if (i >= j) return elems[i*(i - 1) / 2 + j - 1];
	else return elems[j*(j - 1) / 2 + i - 1];
}

//ϡ�����(0Ԫ�ؾӶ࣬����m��n�еľ���t������Ԫ�أ��Ʀ�=t/(m��n)Ϊϡ������
//��Ԫ��洢(�кţ��кţ�Ԫ��ֵ)
template<class T>
struct Triple
{
	int row, col;
	T value;

	Trible();
	Trible(int r, int c, T v);
};

//��Ԫ��˳���������ϢԪ��(����������������Ԫ�ظ���)
#define DEFAULT_SIZE 100
template<class T>
class TriSparseMatrix
{
protected:
	Trible<T> *triElems;
	int maxSize;
	int rows, cols, num;

public:
	TriSparseMatrix(int rs = DEFAULT_SIZE, int cs = DEFAULT_SIZE, int size = DEFAULT_SIZE);
	~TriSparseMatrix();
	int GetRows() const;
	int GetCols() const;
	int GetNum() const;
	bool SetElem(int r, int c, const T&v);
	bool GetElem(int r, int c, T&v);
	TriSparseMatrix(const TriSparseMatrix<T>&copy);
	TriSparseMatrix<T>& operator=(const TriSparseMatrix<T> &copy);
	static void SimpleTranspose(const TriSparseMatrix<T>&source, TriSparseMatrix<T>&dest);//��ϡ�����sourceת�ó�ϡ�����dest�ļ��㷨
	static void FastTranspose(const TriSparseMatrix<T>&source, TriSparseMatrix<T>&dest);//��ϡ�����sourceת�ó�ϡ�����dest�Ŀ����㷨
};
template<class T>
bool TriSparseMatrix<T>::SetElem(int r, int c, const T&v)
{
	if (r>rows || c>cols || r<1 || c<1) return false;

	int i, j;
	for (j = num - 1; j >= 0 && (r<triElems[j].row || r == triElems[j].row&&c<triElems[j].col); j--);//����

	if (j >= 0 && triElems[j].row == r&&triElems[j].col == c)
	{//�ҵ���Ԫ��
		if (v == 0)
		{//ɾ����Ԫ��
			for (i = j + 1; i<num; i++)
			{
				triElems[i - 1] = triElems[i];
			}
			num--;
		}
		else
		{//�޸�Ԫ��ֵ
			triElems[j].value = v;
		}
		return true;
	}
	else if (v != 0)
	{
		if (num<maxSize)
		{//������Ԫ��
			for (i = num - 1; i>j; i--)
			{//����Ԫ��
				triElems[i + 1] = triElems[i];
			}
			//j+1Ϊ�ճ���λ��
			triElems[j + 1].row = r;
			triElems[j + 1].col = c;
			triElems[j + 1].value = v;
			num++;
			return true;
		}
		else
		{//���
			return false;
		}
	}
}

template<class T>
void TriSparseMatrix<T>::SimpleTranspose(const TriSparseMatrix<T>&source, TriSparseMatrix<T>&dest)
{
	dest.rows = source.cols;
	dest.cols = source.rows;
	dest.num = source.num;
	dest.maxSize = source.maxSize;
	delete[]dest.triElems;
	dest.triElems = new Triple<T>[dest.maxSize];

	if (dest.num>0)
	{
		int destPos = 0;//dest�ĵ�һ����Ԫ��Ĵ��λ��
		for (int col = 1; col <= source.cols; col++)
		{//ת��ǰ���б�Ϊת�ú����
			for (int sourcePos = 0; sourcePos<source.num; sourcePos++)
			{//���ҵ�col�е���Ԫ��
				if (source.triElems[sourcePos].col == col)
				{//�ҵ���col�е�һ����Ԫ�飬ת�ú����dest
					dest.triElems[destPos].row = source.triElems[sourcePos].col;
					dest.triElems[destPos].col = source.triElems[sourcePos].row;
					dest.triElems[destPos].value = source.triElems[sourcePos].value;
					destPos++;
				}
			}
		}
	}
}
//��ת�ö�ÿһ���кŶ�Ҫ��ͷ��βɨ��һ����Ԫ���

template<class T>
void TriSparseMatrix<T>::FastTranspose(const TriSparseMatrix<T>&source, TriSparseMatrix<T>&dest)//���δ�source�еĵ�1����2��λ��ȡ������Ԫ�飬�������ǵ����кź���õ�dest���ʵ�λ��
																								//��֪��source�е�ÿһ���ϵ�һ������Ԫ����dest��Ӧ���õ�λ�ã�������Ԫ�صĴ��λ�þͿ�ͨ���𲽵�����ʽ���
																								//cPos[col]Ϊsource��col���ϵĵ�һ������Ԫ����dest��Ӧ���õ�λ��
																								//cNum[col]Ϊsource��col���Ϸ���Ԫ�صĸ���
																								//cPos[1]=0;
																								//cPos[col]=cPos[col-1]+cNum[col-1](col��2)
{
	dest.rows = source.cols;
	dest.cols = source.rows;
	dest.num = source.num;
	dest.maxSize = source.maxSize;
	delete[]dest.triElems;
	dest.triElems = new Triple<T>[dest.maxSize];
	int col;
	int sourcePos;
	int* cNum = new int[source.cols + 1];
	int *cPos = new int[source.cols + 1];

	if (dest.num>0)
	{
		for (col = 1; col <= source.cols; col++) cNum[col] = 0;
		for (sourcePos = 0; soucePos<source.num; sourcePos++)
		{
			++cNum[source.triElems[sourcePos].col];
		}
		cPos[1] = 0;
		for (col = 2; col <= source.cols; col++)
		{
			cPos[col] = cPos[col - 1] + cNum[col - 1];
		}

		for (sourcePos = 0; sourcePos<source.num; sourcePos++)
		{
			int destPos = cPos[source.triElems[sourcePos].col];
			dest.triElems[destPos].row = source.triElems[sourcePos].col;
			dest.triElems[destPos].col = source.triElems[sourcePos].row;
			dest.triElems[destPos].value = source.triElems[sourcePos].value;
			++cPos[source.triElems[sourcePos].col];
		}
	}

	delete[]cNum;
	delete[]cPos;
	cNum = cPos = NULL;
}

//ʮ������(�˴������õ�����������һά����洢���������ͷָ��)
template<class T>
struct CLKTriNode
{
	Triple<T> triElem;
	CLKTriNode<T>*right, *down;
	CLKTriNode();
	CLKTriNode(const Triple<T>&e, CLKTriNode<T>*rLink = NULL, CLKTriNode<T>*dLink = NULL);
};

template<class T>
class CLKSparseMatrix
{
protected:
	CLKTriNode<T>**rightHead, **downHead;
	int rows, cols, num;

	void DestroyHelp();//���ϡ�����
	bool InsertHelp(const Triple<T>&e);//����ʮ��������Ԫ����
public:
	CLKSparseMatrix(int rs = DEFAULT_SIZE, int cs = DEFAULT_SIZE);
	~CLKSparseMatrix();
	int GetRows() const;
	int GetCols() const;
	int GetNum() const;
	bool SetElem(int r, int c, const T&v);
	bool GetElem(int r, int c, T&v);
	CLKSparseMatrix(const CLKSparseMatrix<T>&copy);
	CLKSparseMatrix<T>&operator=(const CLKSparseMatrix<T>&copy);
};
template<class T>
bool CLKSparseMatrix<T>::InsertHelp(const Triple<T>&e)
{
	if (e.row>rows || e.col>cols || e.row<1 || e.col<1) return false;
	CLKTriNode<T> *pre, *p;
	int row = e.row, col = e.col;

	CLKTriNode<T> *ePtr = new CLKTriNode<T>(e);

	//��ePtr�����row��������ʵ�λ��
	if (rightHead[row] == NULL || rightHead[row]->triElem.col >= col)
	{//ePtr���ڵ�row������ı�ͷ��
		ePtr->right = rightHead[row];
		rightHead[row] = ePtr;
	}
	else
	{//Ѱ���ڵ�row������Ĳ���λ��
		pre = NULL;
		p = rightHead[row];
		while (p != NULL&&p->triElem.col<col)
		{
			pre = p; p = p->right;
		}
		if (p != NULL&&p->triElem.row == row&&p->triElem.col = col)
		{//�±��ظ�
			return false;
		}
		pre->right = ePtr;
		ePtr->right = p;
	}
	//��ePtr�����ڵ�col��������ʵ�λ��
	if (downHead[col] == NULL || downHead[col]->triElem.row >= row)
	{
		ePtr->down = downHead[col];
		downHead[col] = ePtr;
	}
	else
	{
		pre = NULL; p = downHead[col];
		while (p != NULL&&p->triElem.row<row)
		{
			pre = p, p = p->down;
		}
		if (p != NULL&&p->triElem.row == row&&p->triElem.col == col)
		{
			return false;
		}
		pre->down = ePtr, ePtr->down = p;
	}

	num++;
	return true;
}