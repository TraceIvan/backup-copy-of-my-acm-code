int main()
{//读输入文件各行到文本缓存中，执行简单的行编辑，并写文本缓存到输出文件
	try
	{
		char infName[256], outfName[256];
		cout << "请输入文件名(默认:file_in.txt):";
		strcpy(infName, Read(cin).CStr());
		if (strlen(infName) == 0)
		{
			strcpy(infName, "file_in.txt");
		}

		cout << "请输出文件名(默认:file_out.txt):";
		strcpy(outfName, Read(cin).CStr());
		if (strlen(outfName) == 0)
		{
			strcpy(outfName, "file_out.txt");
		}

		Editor txt(infName, outfName);
		while (text.GetCommand())
		{//接收并执行用户操作命令
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
	DblLinkList<String> textBuffer;//文本缓存
	int curLineNo;//当前行号
	ifstream inFile;//输入文件
	ofstream outFile;//输出文件
	char userCommand;//用户命令
					 //辅助函数
	char GetChar();//从输入流中跳过空格及制表符获取一字符
	bool NextLine();//转到下一行
	bool PreviousLine();//转到前一行
	bool GotoLine();//转到指定行
	bool InsertLine();//插入一行
	bool ChangeLine();//替换当前行的指定文本串
	void ReadFile();//读入文本文件
	void WriteFile();//写文本文件
	void FindString();//查找串

public:
	Editor(char infName[], char outfName[]);
	bool GetCommand();//读取操作命令符userCommand
	void RunCommand();//运行操作符
};

Editor::Editor(char infName[], char outfName[]) :inFile(infName), outFile(outfName)
{
	if (inFile == NULL) throw"打开输入文件失败!";
	if (outFile == NULL) throw"打开输出文件失败!";
	ReadFile();//读入文本文件
}
bool Editor::GetCommand()
{
	String curLine;
	if (curLineNo != 0)
	{
		textBuffer.GetElem(curLineNo, curLine);//取出当前行
		cout << curLineNo << ":" << curLine.CStr() << endl << "?";
	}
	else
	{
		cout << "文件缓存空" << endl << "?";
	}

	userCommand = GetChar();
	userCommand = tolower(userCommand);//转换为小写字母
	while (cin.get() != '\n');//忽略用户输入的其他字符
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
			cout << "警告:文本缓存空" << endl;
		}
		else
		{
			curLineNo = 1;
		}
		break;

	case 'c'://替换当前行c(hange)
		if (textBuffer.Empty())
		{
			cout << "警告:文本缓存空" << endl;
		}
		else if (!ChangeLine())
		{
			cout << "错误:替换失败" << endl;
		}
		break;

	case 'd'://删除当前行
		if (!textBuffer.Delete(curLineNo, tempString))
		{
			cout << "错误:删除失败" << endl;
		}
		break;

	case 'e'://转到最后一行
		if (textBuffer.Empty())
		{
			cout << "警告:文本缓存空" << endl;
		}
		else
		{
			curLineNo = textBuffer.Length();
		}
		break;

	case 'f'://从当前行开始查找指定文本f
		if (textBuffer.Empty())
		{
			cout << "警告:文本缓存空" << endl;
		}
		else
		{
			FindString();
		}
		break;

	case 'g'://转到指定行
		if (!GotoLine())
		{
			cout << "警告:没有那样的行" << endl;
		}
		break;

	case '?'://获得帮助
	case 'h'://获得帮助
		cout << "有效命令:b(egin)c(hange)d(elete)e(nd)" << endl << "f(ind)g(o)h(elp)i(nsert)n(ext)p(rior)" << endl << "q(uit)r(ead)v(iew)w(rite)" << endl;
		break;

	case 'i'://插入指定行
		if (!InsertLine())
		{
			cout << "错语:插入行出错" << endl;
		}
		break;

	case 'n'://转到下一行
		if (!NextLine())
		{
			cout << "警告:当前行已是最后一行" << endl;
		}
		break;

	case 'p'://转到前一行
		if (!PreviousLine())
		{
			cout << "警告:当前行已是第一行" << endl;
		}
		break;

	case 'r'://读入文本文件
		ReadFile();
		break;

	case 'v'://显示文本
		textBuffer.Traverse(Write);
		break;

	case 'w'://写文本缓存到输出文件中
		if (textBuffer.Empty())
		{
			cout << "警告:文本缓存空" << endl;
		}
		else
		{
			WriteFile();
		}
		break;

	default:
		cout << "输入h或?获得帮助或输入有效命令字符:\n";
	}
}

void Editor::ReadFile()
{
	bool proceed = true;
	if (!textBuffer.Empty())
	{
		cout << "文本缓存非空，读入文件时将覆盖它." << endl;
		cout << "回答yes将执行此操作?" << endl;
		if (proceed = UserSaysYes())
		{
			textBuffer.Clear();
		}
	}

	int lineNumber = 1;
	char terminalChar;
	while (proceed)
	{
		String inString = Read(infile, terminalChar);//读入一行文本
		if (terminalChar == EOF)
		{
			proceed = false;
			if (strlen(inString.CStr())>0)
			{
				textBuffer.Insert(lineNumber, inString);
			}
		}
		else//输入未结束
		{
			textBuffer.Insert(lineNumber++, inString);
		}
	}

	if (textBuffer.Empty())
	{//当前文本缓存为空
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
	cout << "请输入指定行号?";
	cin >> lineNumber;
	while (cin.get() != '\n');//跳过其他字符
	cout << "输入新行文本串:";
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
	cout << "输入被查找的文本串" << endl;
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
		cout << "查找串失败.";
	}
	else
	{
		cout << curLine.CStr() << endl;//显示行
		for (int i = 0; i<index; i++)
		{//在查找串前的位置显行空格
			cout << " ";
		}
		for (int j = 0; j<strlen(searchString.CStr()); j++)
		{//在查找串前的位置显行^，指示目标在行中出现的位置
			cout << "^";
		}
	}
	cout << endl;
}

bool  Editor::ChangeLine()
{
	bool result = true;
	cout << "输入要被替换的指定文本串:";
	String strOld = Read(cin);
	cout << "输入新文本串:";
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
		String newLine;//新串
		Copy(newLine, curLine, index);//复制指定文本前的串
		Concat(newLine, strNew);//连接新文本串
		const char*oldLine = curLine.CStr();//旧行
		Concat(newLine, (String)(oldLine + index + strlen(strOld.CStr())));
		//连接指定文本串后的串，oldLine+index+strlen(strOld.CStr())用于计算一个临时指针，指向紧跟在被替换字符串后的，然后将C风格串转换为String,并被立即连接到newLine的后面
		textBuffer.SetElem(curLineNo, newLine);
	}
	return result;
}


