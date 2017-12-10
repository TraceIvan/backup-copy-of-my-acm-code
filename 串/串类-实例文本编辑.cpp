int main()
{//�������ļ����е��ı������У�ִ�м򵥵��б༭����д�ı����浽����ļ�
	try
	{
		char infName[256], outfName[256];
		cout << "�������ļ���(Ĭ��:file_in.txt):";
		strcpy(infName, Read(cin).CStr());
		if (strlen(infName) == 0)
		{
			strcpy(infName, "file_in.txt");
		}

		cout << "������ļ���(Ĭ��:file_out.txt):";
		strcpy(outfName, Read(cin).CStr());
		if (strlen(outfName) == 0)
		{
			strcpy(outfName, "file_out.txt");
		}

		Editor txt(infName, outfName);
		while (text.GetCommand())
		{//���ղ�ִ���û���������
			text.RunCommand();
		}
	}
	catch (char *mess)
	{
		cout << mess << endl;
	}

	system("PAUSE");
	return 0;
}

class Editor
{
private:
	DblLinkList<String> textBuffer;//�ı�����
	int curLineNo;//��ǰ�к�
	ifstream inFile;//�����ļ�
	ofstream outFile;//����ļ�
	char userCommand;//�û�����
					 //��������
	char GetChar();//���������������ո��Ʊ����ȡһ�ַ�
	bool NextLine();//ת����һ��
	bool PreviousLine();//ת��ǰһ��
	bool GotoLine();//ת��ָ����
	bool InsertLine();//����һ��
	bool ChangeLine();//�滻��ǰ�е�ָ���ı���
	void ReadFile();//�����ı��ļ�
	void WriteFile();//д�ı��ļ�
	void FindString();//���Ҵ�

public:
	Editor(char infName[], char outfName[]);
	bool GetCommand();//��ȡ���������userCommand
	void RunCommand();//���в�����
};

Editor::Editor(char infName[], char outfName[]) :inFile(infName), outFile(outfName)
{
	if (inFile == NULL) throw"�������ļ�ʧ��!";
	if (outFile == NULL) throw"������ļ�ʧ��!";
	ReadFile();//�����ı��ļ�
}
bool Editor::GetCommand()
{
	String curLine;
	if (curLineNo != 0)
	{
		textBuffer.GetElem(curLineNo, curLine);//ȡ����ǰ��
		cout << curLineNo << ":" << curLine.CStr() << endl << "?";
	}
	else
	{
		cout << "�ļ������" << endl << "?";
	}

	userCommand = GetChar();
	userCommand = tolower(userCommand);//ת��ΪСд��ĸ
	while (cin.get() != '\n');//�����û�����������ַ�
	if (userCommand == 'q')
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Editor::RunCommand()
{
	String tempString;
	switch (userCommand)
	{
	case 'b':
		if (textBuffer.Empty())
		{
			cout << "����:�ı������" << endl;
		}
		else
		{
			curLineNo = 1;
		}
		break;

	case 'c'://�滻��ǰ��c(hange)
		if (textBuffer.Empty())
		{
			cout << "����:�ı������" << endl;
		}
		else if (!ChangeLine())
		{
			cout << "����:�滻ʧ��" << endl;
		}
		break;

	case 'd'://ɾ����ǰ��
		if (!textBuffer.Delete(curLineNo, tempString))
		{
			cout << "����:ɾ��ʧ��" << endl;
		}
		break;

	case 'e'://ת�����һ��
		if (textBuffer.Empty())
		{
			cout << "����:�ı������" << endl;
		}
		else
		{
			curLineNo = textBuffer.Length();
		}
		break;

	case 'f'://�ӵ�ǰ�п�ʼ����ָ���ı�f
		if (textBuffer.Empty())
		{
			cout << "����:�ı������" << endl;
		}
		else
		{
			FindString();
		}
		break;

	case 'g'://ת��ָ����
		if (!GotoLine())
		{
			cout << "����:û����������" << endl;
		}
		break;

	case '?'://��ð���
	case 'h'://��ð���
		cout << "��Ч����:b(egin)c(hange)d(elete)e(nd)" << endl << "f(ind)g(o)h(elp)i(nsert)n(ext)p(rior)" << endl << "q(uit)r(ead)v(iew)w(rite)" << endl;
		break;

	case 'i'://����ָ����
		if (!InsertLine())
		{
			cout << "����:�����г���" << endl;
		}
		break;

	case 'n'://ת����һ��
		if (!NextLine())
		{
			cout << "����:��ǰ���������һ��" << endl;
		}
		break;

	case 'p'://ת��ǰһ��
		if (!PreviousLine())
		{
			cout << "����:��ǰ�����ǵ�һ��" << endl;
		}
		break;

	case 'r'://�����ı��ļ�
		ReadFile();
		break;

	case 'v'://��ʾ�ı�
		textBuffer.Traverse(Write);
		break;

	case 'w'://д�ı����浽����ļ���
		if (textBuffer.Empty())
		{
			cout << "����:�ı������" << endl;
		}
		else
		{
			WriteFile();
		}
		break;

	default:
		cout << "����h��?��ð�����������Ч�����ַ�:\n";
	}
}

void Editor::ReadFile()
{
	bool proceed = true;
	if (!textBuffer.Empty())
	{
		cout << "�ı�����ǿգ������ļ�ʱ��������." << endl;
		cout << "�ش�yes��ִ�д˲���?" << endl;
		if (proceed = UserSaysYes())
		{
			textBuffer.Clear();
		}
	}

	int lineNumber = 1;
	char terminalChar;
	while (proceed)
	{
		String inString = Read(infile, terminalChar);//����һ���ı�
		if (terminalChar == EOF)
		{
			proceed = false;
			if (strlen(inString.CStr())>0)
			{
				textBuffer.Insert(lineNumber, inString);
			}
		}
		else//����δ����
		{
			textBuffer.Insert(lineNumber++, inString);
		}
	}

	if (textBuffer.Empty())
	{//��ǰ�ı�����Ϊ��
		curLineNo = 0;
	}
	else
	{
		curLineNo = 1;
	}
}

bool Editor::InsertLine()
{
	int lineNumber;
	cout << "������ָ���к�?";
	cin >> lineNumber;
	while (cin.get() != '\n');//���������ַ�
	cout << "���������ı���:";
	String toInsert = Read(cin);
	if (textBuffer.Insert(lineNumber, toInsert))
	{
		curLineNo = lineNumber;
		return true;
	}
	else
	{
		return false;
	}
}

void Editor::FindString()
{
	int index;
	cout << "���뱻���ҵ��ı���" << endl;
	String searchString = Read(cin);
	String curLine;
	textBuffer.GetElem(curLineNo, curLine);
	while ((index = Index(curLine, searchString)) == -1)
	{
		if (curLineNo<textBuffer.Length())
		{
			curLineNo++;
			textBuffer.GetElem(curLineNo, curLine);
		}
		else
		{
			break;
		}
	}

	if (index == -1)
	{
		cout << "���Ҵ�ʧ��.";
	}
	else
	{
		cout << curLine.CStr() << endl;//��ʾ��
		for (int i = 0; i<index; i++)
		{//�ڲ��Ҵ�ǰ��λ�����пո�
			cout << " ";
		}
		for (int j = 0; j<strlen(searchString.CStr()); j++)
		{//�ڲ��Ҵ�ǰ��λ������^��ָʾĿ�������г��ֵ�λ��
			cout << "^";
		}
	}
	cout << endl;
}

bool  Editor::ChangeLine()
{
	bool result = true;
	cout << "����Ҫ���滻��ָ���ı���:";
	String strOld = Read(cin);
	cout << "�������ı���:";
	String strNew = Read(cin);

	String curLine;
	textBuffer.GetElem(curLineNo, curLine);
	int index = Index(curLine, strOld);
	if (index == -1)
	{
		result = false;
	}
	else
	{
		String newLine;//�´�
		Copy(newLine, curLine, index);//����ָ���ı�ǰ�Ĵ�
		Concat(newLine, strNew);//�������ı���
		const char*oldLine = curLine.CStr();//����
		Concat(newLine, (String)(oldLine + index + strlen(strOld.CStr())));
		//����ָ���ı�����Ĵ���oldLine+index+strlen(strOld.CStr())���ڼ���һ����ʱָ�룬ָ������ڱ��滻�ַ�����ģ�Ȼ��C���ת��ΪString,�����������ӵ�newLine�ĺ���
		textBuffer.SetElem(curLineNo, newLine);
	}
	return result;
}


