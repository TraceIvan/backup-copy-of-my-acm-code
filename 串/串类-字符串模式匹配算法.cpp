//�ټ��ַ���ģʽƥ���㷨
//���ַ���p���ַ��������ַ���T���ַ����бȽ�
int SimpleIndex(const String &T, const String &p, int pos = 0)
{
	int startPos = pos, i = pos, j = 0;
	while (i<T.Length() && j<P.Length())
	{
		if (T[i] == P[j])
		{
			i++;
			j++;
		}
		else
		{
			i = ++startPos;
			j = 0;
		}
	}
	if (j >= P.Length()) return startPos;
	else return -1;
}
//Ч�ʵ��£��㷨��ִ�й������л���

//��KMP�ַ���ģʽƥ���㷨
//T a b a a b a b
//P a b a b
//���ݵ�һ�˱ȽϿ�֪��t0=p0,t1=p1,t2=p2,t3��p3,Ȼ����P�У�����p0��p1,����t1��p0,�����ڵڶ��˵ıȽ��У���p����һλ����t1��p0�Ƚ�һ�����ȡ�������p0=p2,����t2=p0,����ڵ�����ƥ���У�p������һλ��t2��p0�ıȽϿ϶���ȡ�����Ӧ��pֱ��������λ�������ڶ��ˣ���������t2��p0�ıȽϣ�ֱ�Ӵ�t3��p1��ʼ�Ƚϡ�
int KMPIndex(const String&T, const String &P, int pos = 0)//����ģʽ��P��һ����Ŀ�괮T�дӵ�pos���ַ���ʼ���ֵ�λ��
{
	int *next = new int[P.Length()];
	GetNext(P, next);
	int result = KMPIndexHelp(T, P, pos, next);
	delete[]next;
	return result;
}

void GetNext(const String &P, int next[])
//��ģʽ��P��next�����Ԫ��ֵ(�ڴ�P0P1��Pj-1���ҳ������ȵ������Ӵ�P0P1��Pk-1��Pj-kPj-k+1��Pj-1)
{
	next[0] = -1;
	int j = 0, k = -1;//next[j]=k�����ĳ�ʼ���
	while (j<P.Length() - 1)
	{
		if (k == -1)
		{//������k����p[k]==p[j]��j==0
			next[j + 1] = 0;
			j++;
			k = 0;
		}
		else if (P[k] == P[j])
		{//��ʱnext[j+1]=next[j]+1
			next[j + 1] = k + 1;
			j++;
			k++;
		}
		else
		{
			//P[k]��P[j]��ƥ��
			k = next[k];//Ѱ���µ�ƥ���ַ�
		}
	}
}
int KMPIndexHelp(const String&T, const String &P, int pos, int next[])
{
	int i = pos, j = 0;//iΪĿ�괮T�еĵ�ǰ�ַ�λ�ã�jΪģʽ��P�ĵ�ǰ�ַ�λ��
	while (i<T.Length() && j<P.Length())
	{
		if (j == -1)
		{
			//��ʱ����P���κ��ַ���������T[i]���бȽϣ��´�P[0]��T[i+1]��ʼ���бȽ�
			i++;
			j = 0;
		}
		else if (P[j] == T[i])
		{//P[j]��T[i]ƥ��
			i++;
			j++;
		}
		else
		{//P[j]��T[i]��ƥ��
			j = next[j];
		}
	}
	if (j<P.Length()) return -1;
	else return i - j;
}.