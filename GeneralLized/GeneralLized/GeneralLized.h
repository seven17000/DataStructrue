#include <iostream>  
#include <Cassert>  
using namespace std;

enum TYPE
{
	HEAD,   //头类型  
	VALUE,  //值类型  
	SUB,    //子表类型  
};

typedef struct GeneralListNode
{
	GeneralListNode(TYPE type, const char str = 0)//创建节点  
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
		char _value;//值节点的值  
		struct GeneralListNode* _sublink;//指向子表的指针  
	};


}Node;

class GeneralLized
{
public:
	GeneralLized(const char* str)//构造函数  
	{
		_head = _CreatList(str);
	}
	GeneralLized(const GeneralLized& g)
		:_head(NULL)
	{
		_head = _Copy(g._head);
	}
	////简洁版的赋值运算符重载1  
	//GeneralLized& operator=(GeneralLized g)  
	//{  
	//  swap(_head,g._head);  
	//  return *this;  
	//}  
	//简洁版的赋值运算符重载2  
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
	void PrintGeneralLized()//打印广义表  
	{
		_Print(_head);
		cout << endl;
	}
	size_t Size()//求值节点个数  
	{
		return _Size(_head);
	}
	size_t Depth()//广义表的深度  
	{
		return _Depth(_head);
	}
protected:
	bool IsValue(const char& s)//判断是否是有效值  
	{
		if ((s >= '0' && s <= '9')
			|| (s >= 'a' && s >= 'z')
			|| (s >= 'A' && s >= 'Z'))
		{
			return true;
		}
		return false;
	}
	Node* _CreatList(const char*& s)//创建广义表  
	{
		assert(*s == '(');//断言第一个字符必须是'('  
		s++;//s向后偏移1，跳过'('  
		Node* head = new Node(HEAD);//创建新节点  
		Node* cur = head;//创建当前节点来插入新数据  

		while (*s)
		{
			if (IsValue(*s))//值节点  
			{
				cur->_next = new Node(VALUE, *s);//创建数据节点  
				cur = cur->_next;
				s++;
			}
			else if (*s == '(')//子表  
			{
				Node* newNode = new Node(SUB);//新建子表节点  
				cur->_next = newNode;//尾插子表节点  
				cur = cur->_next;
				newNode->_sublink = _CreatList(s);//递归创建子表  
			}
			else if (*s == ')')//子表结束  
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
		Node* newHead = new Node(HEAD);//新广义表的头节点  
		Node* newCur = newHead;//新广义表的当前节点  
		cur = cur->_next;//跳过头节点  

		while (cur)
		{
			if (cur->_type == VALUE)//值节点  
			{
				newCur->_next = new Node(VALUE, cur->_value);//创建新的值节点  
				cur = cur->_next;
				newCur = newCur->_next;
			}
			else if (cur->_type == SUB)//子表节点  
			{
				Node* newSub = new Node(SUB);//新建子表节点  
				newCur->_next = newSub;
				newCur = newCur->_next;
				newSub->_sublink = _Copy(cur->_sublink);//递归拷贝子表  
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
			if (cur->_type == SUB)//子表节点  
			{
				del = cur;
				cur = cur->_next;
				_Destroy(del->_sublink);
				delete del;
			}
			else//值节点or头节点  
			{
				del = cur;
				cur = cur->_next;
				delete del;
			}
		}
	}
	Node* _Print(Node* head)//打印广度表  
	{
		Node* cur = head;
		while (cur)
		{
			if (cur->_type == HEAD)//头结点直接打印'('  
			{
				cout << '(';
			}
			else if (cur->_type == VALUE)//值节点  
			{
				cout << cur->_value;
				if (NULL != cur->_next)//子表未结束时，用','分割数据  
				{
					cout << ',';
				}
			}
			else if (cur->_type == SUB)//子表项  
			{
				_Print(cur->_sublink);//递归打印子表  
				if (NULL != cur->_next)//子表结项束时，用','分割  
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
	size_t _Size(Node* head)//数据节点的个数  
	{
		size_t count = 0;
		Node* cur = head;
		while (cur)
		{
			if (cur->_type == VALUE)//若为值节点则count++  
			{
				count++;
			}
			else if (cur->_type == SUB)//若为子表节点，则count+=子表数据节点  
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
	size_t _Depth(Node* head)//求取广义表深度  
	{
		Node* cur = head;
		size_t maxDepth = 1;//头节点不为空，则深度为1  

		while (cur)
		{
			if (cur->_type == SUB)//子表  
			{
				if (maxDepth < _Depth(cur->_sublink) + 1)//当前深度为子表项深度+1  
				{
					maxDepth = _Depth(cur->_sublink) + 1;//更新子表项  
				}
			}
			cur = cur->_next;
		}
		return maxDepth;
	}
protected:
	Node* _head;//广义表的头结点  
};
