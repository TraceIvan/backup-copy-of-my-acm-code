//①简单字符串模式匹配算法
//用字符串p的字符依次与字符串T中字符进行比较
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
//效率低下，算法的执行过程中有回溯

//②KMP字符串模式匹配算法
//T a b a a b a b
//P a b a b
//根据第一趟比较可知，t0=p0,t1=p1,t2=p2,t3≠p3,然而在P中，由于p0≠p1,所以t1≠p0,所以在第二趟的比较中，将p右移一位，用t1和p0比较一定不等。又由于p0=p2,所以t2=p0,因此在第三趟匹配中，p再右移一位后，t2与p0的比较肯定相等。所以应将p直接右移两位，跳过第二趟，并且跳过t2与p0的比较，直接从t3和p1开始比较。
int KMPIndex(const String&T, const String &P, int pos = 0)//查找模式串P第一次在目标串T中从第pos个字符开始出现的位置
{
	int *next = new int[P.Length()];
	GetNext(P, next);
	int result = KMPIndexHelp(T, P, pos, next);
	delete[]next;
	return result;
}

void GetNext(const String &P, int next[])
//求模式串P的next数组的元素值(在串P0P1…Pj-1中找出最长的相等的两个子串P0P1…Pk-1和Pj-kPj-k+1…Pj-1)
{
	next[0] = -1;
	int j = 0, k = -1;//next[j]=k成立的初始情况
	while (j<P.Length() - 1)
	{
		if (k == -1)
		{//不存在k满足p[k]==p[j]或j==0
			next[j + 1] = 0;
			j++;
			k = 0;
		}
		else if (P[k] == P[j])
		{//此时next[j+1]=next[j]+1
			next[j + 1] = k + 1;
			j++;
			k++;
		}
		else
		{
			//P[k]与P[j]不匹配
			k = next[k];//寻求新的匹配字符
		}
	}
}
int KMPIndexHelp(const String&T, const String &P, int pos, int next[])
{
	int i = pos, j = 0;//i为目标串T中的当前字符位置，j为模式串P的当前字符位置
	while (i<T.Length() && j<P.Length())
	{
		if (j == -1)
		{
			//此时表明P中任何字符都不再与T[i]进行比较，下次P[0]与T[i+1]开始进行比较
			i++;
			j = 0;
		}
		else if (P[j] == T[i])
		{//P[j]和T[i]匹配
			i++;
			j++;
		}
		else
		{//P[j]和T[i]不匹配
			j = next[j];
		}
	}
	if (j<P.Length()) return -1;
	else return i - j;
}.