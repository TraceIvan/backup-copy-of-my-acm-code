class String//串类
{
protected:
	char *strVal;
	int length;
public:
	String();
	virtual~String();
	String(const String &copy);
	String(const char*copy);
	String(LinkList<char>&copy);
	int Length() const;
	bool Empty() const;
	String & operator=(const String &copy);
	const char*CStr() const;
	const char& String:: operator[](int i) const;
};
//串相关操作
String Read(istream &input);//从输入流读入串
String Read(istream &input, char &terminalChar);//从输入流读入串，并用terminalChar返回串结束字符
void Write(const String&s);//输出串
void Concat(String &addTo, const String &addOn);//将串addOn连接到addTo串的后面
void Copy(String &copy, const String &original);//将串original复制到串copy
void Copy(String &copy, const String &original, int n);//将串original复制n个字符到串copy
int Index(const String &target, const String &pattern, int pos = 0);//查找模式串pattern第一次在目标串target中从第pos个字符开始出现的位置
String SubString(const String &s, int pos, int len);//求串s的第pos个字符开始的长度为len的子串
bool operator==(const String &first, const String &second);//重载关系运算符
bool operator<(const String &first, const String &second);
bool operator>(const String &first, const String &second);
bool operator<=(const String &first, const String &second);
bool operator>=(const String &first, const String &second);
bool operator!=(const String &first, const String &second);

String::String(const char*inString)//转换构造函数
{
	length = strlen(intString);
	strVal = new char[length + 1];
	strcpy(strVal, inString);
}
//String str;str="some string.";时自动隐式调用把some string.转换为一个临时的String对象，然后调用重载String赋值运算符将此临时对象复制到串str中，最后为此临时String对象调用析构函数
String::String(LinkList<char>&copy)
{
	length = copy.Length();
	strVal = new char[length + 1];
	for (int i = 0; i<length; i++)
	{
		copy.GetElem(i + 1, strVal[i]);
	}
	strVal[length] = '\0';
}//当不知道用户要输入的字符串长度时，可先用链表存储，再转换为String
const char*String::Cstr() const
{
	return (const char*)strVal;//串值类型转换
}
//应用:String str;str="some string.";const char* newStr=str.CStr();
//上面代码中newStr字符串所占用的空间由类String所分配，并且分配后此内存可由类String释放，这样就避免了用户忘记删除由String创建的C风格串的可能性，当然代价是不能使用返回的指针改变所引用的C风格串
bool operator==(const String &first, const String &second)
{
	return strcmp(first.CStr(), second.CStr()) == 0;
}

bool operator<(const String &first, const String &second)
{
	return strcmp(first.CStr(), second.CStr())<0;
}

bool operator>(const String &first, const String &second)
{
	return strcmp(first.CStr(), second.CStr())>0;
}

bool operator<=(const String &first, const String &second)
{
	return strcmp(first.CStr(), second.CStr()) <= 0;
}

bool operator>=(const String &first, const String &second)
{
	return strcmp(first.CStr(), second.CStr()) >= 0;
}

bool operator!=(const String &first, const String &second)
{
	return strcmp(first.CStr(), second.CStr()) != 0;
}

String::String(const String &copy)
{
	length = strlen(copy.CStr());
	strVal = new char[length + 1];
	strcpy(strVal, copy.CStr());
}

String& String::operator=(const String &copy)
{
	if (&copy != this)
	{
		delete[]strVal;
		length = strlen(copy.CStr());
		strVal = new char[length + 1];
		strcpy(strVal, copy.CStr());
	}
	return *this;
}

void Concat(String &addTo, const String&addOn)
{
	const char*cFirst = addTo.CStr();
	const char*cSecond = addOn.CStr();
	char *copy = new char[strlen(cFirst) + strlen(cSecond) + 1];
	strcpy(copy, cFirst);
	strcat(copy, cSecond);
	addTo = copy;
	delete[]copy;
}

int Index(const String &target, const String &pattern, int pos)
{
	const char*cTarget = target.CStr();
	const char*cPattern = pattern.CStr();
	const char*ptr = strstr(cTarget + pos, cPattern);//模式匹配
	if (ptr == NULL)
	{
		return -1;
	}
	else
	{
		return ptr - cTarget;
	}
}

String Read(istream &input)
{
	LinkList<char>temp;
	int size = 0;
	char ch;
	while ((ch = input.peek()) != EOF && (ch = input.get()) != '\n')//peek()从输入流中取一个字符，输入流指针不变;get()从输入流中取一个字符，输入流指针指向下一个字符
	{
		temp.Insert(++size, ch);
	}
	String answer(temp);
	return answer;
}

String Read(istream &input, char &terminalChar)
{
	LinkList<char>temp;
	int size = 0;
	char ch;
	while ((ch = input.peek()) != EOF && (ch = input.get()) != '\n')
	{
		temp.Insert(++size, ch);
	}
	terminalChar = ch;
	String answer(temp);
	return answer;
}
//也可重载>>实现字符串的输入

void Write(const String &s)
{
	cout << s.CStr() << endl;
}
