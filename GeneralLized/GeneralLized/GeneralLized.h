#include <iostream>  
#include <Cassert>  
using namespace std;

enum TYPE
{
	HEAD,   //ͷ����  
	VALUE,  //ֵ����  
	SUB,    //�ӱ�����  
};

typedef struct GeneralListNode
{
	GeneralListNode(TYPE type, const char str = 0)//�����ڵ�  
		:_type(type)
		, _next(NULL)
	{
		if (type == HEAD || type == VALUE)
		{
			_value = str;
		}
		else if (type == SUB)
		{
			_sublink = NULL;
		}
		else
		{
			assert(false);
		}
	}

	TYPE  _type;  
	GeneralListNode* _next;

	union
	{
		char _value;//ֵ�ڵ��ֵ  
		struct GeneralListNode* _sublink;//ָ���ӱ��ָ��  
	};


}Node;

class GeneralLized
{
public:
	GeneralLized(const char* str)//���캯��  
	{
		_head = _CreatList(str);
	}
	GeneralLized(const GeneralLized& g)
		:_head(NULL)
	{
		_head = _Copy(g._head);
	}
	////����ĸ�ֵ���������1  
	//GeneralLized& operator=(GeneralLized g)  
	//{  
	//  swap(_head,g._head);  
	//  return *this;  
	//}  
	//����ĸ�ֵ���������2  
	GeneralLized& operator=(const GeneralLized& g)
	{
		Node* tmp = _Copy(g._head);
		_Destroy(_head);
		swap(_head, tmp);

		return *this;
	}
	~GeneralLized()
	{
		if (NULL != _head)
		{
			_Destroy(_head);
			_head = NULL;
		}
	}
	void PrintGeneralLized()//��ӡ�����  
	{
		_Print(_head);
		cout << endl;
	}
	size_t Size()//��ֵ�ڵ����  
	{
		return _Size(_head);
	}
	size_t Depth()//���������  
	{
		return _Depth(_head);
	}
protected:
	bool IsValue(const char& s)//�ж��Ƿ�����Чֵ  
	{
		if ((s >= '0' && s <= '9')
			|| (s >= 'a' && s >= 'z')
			|| (s >= 'A' && s >= 'Z'))
		{
			return true;
		}
		return false;
	}
	Node* _CreatList(const char*& s)//���������  
	{
		assert(*s == '(');//���Ե�һ���ַ�������'('  
		s++;//s���ƫ��1������'('  
		Node* head = new Node(HEAD);//�����½ڵ�  
		Node* cur = head;//������ǰ�ڵ�������������  

		while (*s)
		{
			if (IsValue(*s))//ֵ�ڵ�  
			{
				cur->_next = new Node(VALUE, *s);//�������ݽڵ�  
				cur = cur->_next;
				s++;
			}
			else if (*s == '(')//�ӱ�  
			{
				Node* newNode = new Node(SUB);//�½��ӱ�ڵ�  
				cur->_next = newNode;//β���ӱ�ڵ�  
				cur = cur->_next;
				newNode->_sublink = _CreatList(s);//�ݹ鴴���ӱ�  
			}
			else if (*s == ')')//�ӱ����  
			{
				s++;
				return head;
			}
			else
			{
				s++;
			}
		}
		return head;
	}
	Node* _Copy(Node* head)
	{
		Node* cur = head;
		Node* newHead = new Node(HEAD);//�¹�����ͷ�ڵ�  
		Node* newCur = newHead;//�¹����ĵ�ǰ�ڵ�  
		cur = cur->_next;//����ͷ�ڵ�  

		while (cur)
		{
			if (cur->_type == VALUE)//ֵ�ڵ�  
			{
				newCur->_next = new Node(VALUE, cur->_value);//�����µ�ֵ�ڵ�  
				cur = cur->_next;
				newCur = newCur->_next;
			}
			else if (cur->_type == SUB)//�ӱ�ڵ�  
			{
				Node* newSub = new Node(SUB);//�½��ӱ�ڵ�  
				newCur->_next = newSub;
				newCur = newCur->_next;
				newSub->_sublink = _Copy(cur->_sublink);//�ݹ鿽���ӱ�  
				cur = cur->_next;
			}
			else
			{
				assert(false);
			}
		}
		return newHead;
	}
	void _Destroy(Node* head)
	{
		Node* cur = head;
		Node* del = cur;

		while (cur)
		{
			if (cur->_type == SUB)//�ӱ�ڵ�  
			{
				del = cur;
				cur = cur->_next;
				_Destroy(del->_sublink);
				delete del;
			}
			else//ֵ�ڵ�orͷ�ڵ�  
			{
				del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}
	Node* _Print(Node* head)//��ӡ��ȱ�  
	{
		Node* cur = head;
		while (cur)
		{
			if (cur->_type == HEAD)//ͷ���ֱ�Ӵ�ӡ'('  
			{
				cout << '(';
			}
			else if (cur->_type == VALUE)//ֵ�ڵ�  
			{
				cout << cur->_value;
				if (NULL != cur->_next)//�ӱ�δ����ʱ����','�ָ�����  
				{
					cout << ',';
				}
			}
			else if (cur->_type == SUB)//�ӱ���  
			{
				_Print(cur->_sublink);//�ݹ��ӡ�ӱ�  
				if (NULL != cur->_next)//�ӱ������ʱ����','�ָ�  
				{
					cout << ',';
				}
			}
			else
			{
				assert(false);
			}
			cur = cur->_next;
		}
		cout << ')';
		return head;
	}
	size_t _Size(Node* head)//���ݽڵ�ĸ���  
	{
		size_t count = 0;
		Node* cur = head;
		while (cur)
		{
			if (cur->_type == VALUE)//��Ϊֵ�ڵ���count++  
			{
				count++;
			}
			else if (cur->_type == SUB)//��Ϊ�ӱ�ڵ㣬��count+=�ӱ����ݽڵ�  
			{
				count += _Size(cur->_sublink);
			}
			else
			{
				;
			}

			cur = cur->_next;
		}
		return count;
	}
	size_t _Depth(Node* head)//��ȡ��������  
	{
		Node* cur = head;
		size_t maxDepth = 1;//ͷ�ڵ㲻Ϊ�գ������Ϊ1  

		while (cur)
		{
			if (cur->_type == SUB)//�ӱ�  
			{
				if (maxDepth < _Depth(cur->_sublink) + 1)//��ǰ���Ϊ�ӱ������+1  
				{
					maxDepth = _Depth(cur->_sublink) + 1;//�����ӱ���  
				}
			}
			cur = cur->_next;
		}
		return maxDepth;
	}
protected:
	Node* _head;//������ͷ���  
};
