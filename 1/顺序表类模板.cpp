template<class elemType>
class SqList
{
protected://˳���ʵ�ֵ����ݳ�Ա
	int count;//Ԫ�ظ���
	int maxSize;//˳������Ԫ�ظ���
	elemType *elems;//�洢Ԫ��
public://�����������ͷ������������ر���ϵͳĬ�Ϸ�������
	SqList(int size = DEFAULT_SIZE);//���캯��ģ��
	virtual ~SqList