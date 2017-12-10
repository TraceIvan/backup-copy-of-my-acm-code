template<class T>
class Matrix
{
protected:
	T *elems;
	int rows, cols;//行数和列数
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
	if (rs<1 && cs<1) throw "行数或列数无效";
	rows = rs;
	cols = cs;
	elems = new T[rows*cols];
}

template<class T>
T &Matrix<T>::operator()(int i, int j)
{
	if (i<1 || i>rows || j<1 || j>cols) throw "下标出界";
	return elems[(i - 1)*cols + j - 1];
}

//三对角矩阵
//在一个n×n的三对角矩阵中，三条对角线(主对角线<i=j>,低对角线<i=j+1>,高对角线<i=j-1>)上之外的元素都是0或为一个常数
//①逐行映射②逐列映射③对角线映射√
template<class T>
class TriDiagonalMatrix
{
protected:
	T *elems;
	int n;
public:
	TriDiagonalMatrix(int sz);
	~TriDiagonalMatrix();
	int GetSize() const;//返回阶数
	T &operator()(int i, int j);
	TriDiagonalMatrix(const TriDiagonalMatrix<T>&copy);
	TriDiagonalMatrix<T>&operator=(const TriDiagonalMatrix<T> &copy);
};

template<class T>
TriDiagonalMatrix<T>::TriDiagonalMatrix(int sz)
{
	if (sz<1) throw "行数或列数无效!";
	n = sz;
	elems = new T[3 * n - 1];
}

template<class T>
T& TriDiagonalMatrix<T>::operator()(int i, int j)
{
	if (i<1 || i>n || j<1 || j>n) throw "下标出界";
	if (i - j == 1) return elems[2 * n + i - 2];
	else if (i - j == 0) return elems[n + i - 1];
	else if (i - j == -1) return elems[i];
	else return elems[0];
}

//三角矩阵
//①下三角矩阵:仅当i<j时a[i,j]=0或c√
//②上三角矩阵:仅当i>j时a[i,j]=0或c
//总元素个数:n(n+1)/2+1
//①按行映射√②按列映射
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
	if (sz<1) throw "行数或列数无效!";
	n = sz;
	elems = new T[n*(n - 1) / 2 + 1];
}

template<class T>
T &LowerTriangularMatrix<T>::operator()(int i, int j)
{
	if (i<1 || i>n || j<1 || j>n) throw "下标出界";
	if (i >= j) return elems[i*(i - 1) / 2 + j];
	else return elems[0];
}

//对称矩阵(只存储上三角或下三角中的元素)
//k=i(i-1)/2+j-1 (i≥j)
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
	if (i<1 || i>n || j<1 || j>n) throw "下标出界!";
	if (i >= j) return elems[i*(i - 1) / 2 + j - 1];
	else return elems[j*(j - 1) / 2 + i - 1];
}

//稀疏矩阵(0元素居多，假设m行n列的矩阵含t个非零元素，称δ=t/(m×n)为稀疏因子
//三元组存储(行号，列号，元素值)
template<class T>
struct Triple
{
	int row, col;
	T value;

	Trible();
	Trible(int r, int c, T v);
};

//三元组顺序表，增设信息元组(行数，列数，非零元素个数)
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
	static void SimpleTranspose(const TriSparseMatrix<T>&source, TriSparseMatrix<T>&dest);//将稀疏矩阵source转置成稀疏矩阵dest的简单算法
	static void FastTranspose(const TriSparseMatrix<T>&source, TriSparseMatrix<T>&dest);//将稀疏矩阵source转置成稀疏矩阵dest的快速算法
};
template<class T>
bool TriSparseMatrix<T>::SetElem(int r, int c, const T&v)
{
	if (r>rows || c>cols || r<1 || c<1) return false;

	int i, j;
	for (j = num - 1; j >= 0 && (r<triElems[j].row || r == triElems[j].row&&c<triElems[j].col); j--);//不懂

	if (j >= 0 && triElems[j].row == r&&triElems[j].col == c)
	{//找到三元组
		if (v == 0)
		{//删除三元组
			for (i = j + 1; i<num; i++)
			{
				triElems[i - 1] = triElems[i];
			}
			num--;
		}
		else
		{//修改元素值
			triElems[j].value = v;
		}
		return true;
	}
	else if (v != 0)
	{
		if (num<maxSize)
		{//插入三元组
			for (i = num - 1; i>j; i--)
			{//后移元素
				triElems[i + 1] = triElems[i];
			}
			//j+1为空出的位置
			triElems[j + 1].row = r;
			triElems[j + 1].col = c;
			triElems[j + 1].value = v;
			num++;
			return true;
		}
		else
		{//溢出
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
		int destPos = 0;//dest的第一个三元组的存放位置
		for (int col = 1; col <= source.cols; col++)
		{//转置前的列变为转置后的行
			for (int sourcePos = 0; sourcePos<source.num; sourcePos++)
			{//查找第col列的三元组
				if (source.triElems[sourcePos].col == col)
				{//找到第col列的一个三元组，转置后存入dest
					dest.triElems[destPos].row = source.triElems[sourcePos].col;
					dest.triElems[destPos].col = source.triElems[sourcePos].row;
					dest.triElems[destPos].value = source.triElems[sourcePos].value;
					destPos++;
				}
			}
		}
	}
}
//简单转置对每一个列号都要从头到尾扫描一遍三元组表

template<class T>
void TriSparseMatrix<T>::FastTranspose(const TriSparseMatrix<T>&source, TriSparseMatrix<T>&dest)//依次从source中的第1，第2…位置取出各三元组，交换它们的行列号后放置到dest中适当位置
																								//若知道source中的每一列上第一个非零元素在dest中应放置的位置，则其他元素的存放位置就可通过逐步递增方式获得
																								//cPos[col]为source第col列上的第一个非零元素在dest中应放置的位置
																								//cNum[col]为source第col列上非零元素的个数
																								//cPos[1]=0;
																								//cPos[col]=cPos[col-1]+cNum[col-1](col≥2)
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

//十字链表(此处行列用单链表，用两个一维数组存储行列链表的头指针)
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

	void DestroyHelp();//清空稀疏矩阵
	bool InsertHelp(const Triple<T>&e);//插入十字链表三元组结点
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

	//将ePtr插入第row行链表的适当位置
	if (rightHead[row] == NULL || rightHead[row]->triElem.col >= col)
	{//ePtr插在第row行链表的表头处
		ePtr->right = rightHead[row];
		rightHead[row] = ePtr;
	}
	else
	{//寻找在第row行链表的插入位置
		pre = NULL;
		p = rightHead[row];
		while (p != NULL&&p->triElem.col<col)
		{
			pre = p; p = p->right;
		}
		if (p != NULL&&p->triElem.row == row&&p->triElem.col = col)
		{//下标重复
			return false;
		}
		pre->right = ePtr;
		ePtr->right = p;
	}
	//将ePtr插入在第col列链表的适当位置
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