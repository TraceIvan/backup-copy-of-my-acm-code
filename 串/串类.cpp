class String//����
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
//����ز���
String Read(istream &input);//�����������봮
String Read(istream &input, char &terminalChar);//�����������봮������terminalChar���ش������ַ�
void Write(const String&s);//�����
void Concat(String &addTo, const String &addOn);//����addOn���ӵ�addTo���ĺ���
void Copy(String &copy, const String &original);//����original���Ƶ���copy
void Copy(String &copy, const String &original, int n);//����original����n���ַ�����copy
int Index(const String &target, const String &pattern, int pos = 0);//����ģʽ��pattern��һ����Ŀ�괮target�дӵ�pos���ַ���ʼ���ֵ�λ��
String SubString(const String &s, int pos, int len);//��s�ĵ�pos���ַ���ʼ�ĳ���Ϊlen���Ӵ�
bool operator==(const String &first, const String &second);//���ع�ϵ�����
bool operator<(const String &first, const String &second);
bool operator>(const String &first, const String &second);
bool operator<=(const String &first, const String &second);
bool operator>=(const String &first, const String &second);
bool operator!=(const String &first, const String &second);

String::String(const char*inString)//ת�����캯��
{
	length = strlen(intString);
	strVal = new char[length + 1];
	strcpy(strVal, inString);
}
//String str;str="some string.";ʱ�Զ���ʽ���ð�some string.ת��Ϊһ����ʱ��String����Ȼ���������String��ֵ�����������ʱ�����Ƶ���str�У����Ϊ����ʱString���������������
String::String(LinkList<char>&copy)
{
	length = copy.Length();
	strVal = new char[length + 1];
	for (int i = 0; i<length; i++)
	{
		copy.GetElem(i + 1, strVal[i]);
	}
	strVal[length] = '\0';
}//����֪���û�Ҫ������ַ�������ʱ������������洢����ת��ΪString
const char*String::Cstr() const
{
	return (const char*)strVal;//��ֵ����ת��
}
//Ӧ��:String str;str="some string.";const char* newStr=str.CStr();
//���������newStr�ַ�����ռ�õĿռ�����String�����䣬���ҷ������ڴ������String�ͷţ������ͱ������û�����ɾ����String������C��񴮵Ŀ����ԣ���Ȼ�����ǲ���ʹ�÷��ص�ָ��ı������õ�C���
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
	const char*ptr = strstr(cTarget + pos, cPattern);//ģʽƥ��
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
	while ((ch = input.peek()) != EOF && (ch = input.get()) != '\n')//peek()����������ȡһ���ַ���������ָ�벻��;get()����������ȡһ���ַ���������ָ��ָ����һ���ַ�
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
//Ҳ������>>ʵ���ַ���������

void Write(const String &s)
{
	cout << s.CStr() << endl;
}
