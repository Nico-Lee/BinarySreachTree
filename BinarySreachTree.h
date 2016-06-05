#pragma once
#include<iostream>
using namespace std;

template<class K,class V>
struct BSNode
{
	BSNode<K, V>* _left;
	BSNode<K, V>* _right;
	K _key;
	V _value;
	BSNode(const K& key, const V& value)
		:_left(NULL)
		, _right(NULL)
		,_key(key)
		, _value(value)
	{}
};

template<class K,class V>
class BSTree
{
public:
	typedef BSNode<K, V> Node;
	BSTree()
		:_root(NULL)
	{}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* parent = NULL;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				return false;
		}
		if (parent->_left == NULL && parent->_key > key)
		{
			parent->_left = new Node(key, value);
		}
		else if (parent->_right == NULL && parent->_key < key)
		{
			parent->_right = new Node(key, value);
		}
		return true;
	}
	bool Insert_R(const K& key, const V& value)
	{
		return _Insert_R(_root, key, value);
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
				return cur;
		}
		return NULL;
	}
	Node* Find_R(const K& key)
	{
		return _Find_R(_root, key);
	}
	bool Remove(const K& key)
	{
		return _Remove(_root, key);
	}
	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}
	void Insort()
	{
		_Insort(_root);
	}
protected:
	bool _Remove_R(Node*& root, const K& key)
	{
		if (root == NULL)
			return false;
		if (root->_key > key)
		{
			_Remove_R(root->_left, key); 
		}
		else if (root->_key < key)
		{
			_Remove_R(root->_right, key);
		}
		else
		{
			Node* del = root;
			if (root->_left == NULL&&root->_right == NULL)
			{
				root = NULL;
			}
			else if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node* parent = NULL;
				Node* firstleft = root->_right;
				while (firstleft->_left)
				{
					parent = firstleft;
					firstleft = firstleft->_left;
				}
				del = firstleft;

				swap(root->_key, firstleft->_key);
				swap(root->_value, firstleft->_value);

				if (parent && parent->_left == firstleft)
				{
					parent->_left = firstleft->_right;
				}
				else if (parent && parent->_right == firstleft)
				{
					parent->_right = firstleft->_right;
				}
				else //parent==NULL。待删除结点的右边只有一个结点，则最左结点就是它
				{
					root->_right = NULL;
				}
			}
			delete del;
			return true;
		}
		return false;
	}
	bool _Remove(Node* root, const K& key)
	{
		if (root == NULL)
			return false;
		Node* parent = NULL;
		Node* cur = root;
		Node* del = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				del = cur;
				//待删除结点左为空
				if (cur->_left == NULL)
				{
					if (parent && parent->_left == cur)
						parent->_left = cur->_right;
					else if (parent && parent->_right == cur)
						parent->_right = cur->_right;
					else
						_root = cur->_right;
				}
				else if (cur->_right == NULL)//待删除结点右为空
				{
					if (parent && parent->_left == cur)
						parent->_left = cur->_left;
					else if (parent &&parent->_right == cur)
						parent->_right = cur->_left;
					else
						_root = cur->_left;
				}
				else if (cur->_left == NULL && cur->_right == NULL)//待删除结点左右都为空
				{
					if (parent && parent->_left == cur)
						parent->_left = NULL;
					else if (parent && parent->_right == cur)
						parent->_right = NULL;
					else
						_root = NULL;
				}
				else if (cur->_left && cur->_right)//待删除结点左右都不为空
				{
					//找出右子树的最左结点
					Node* firstleft = cur->_right;
					parent = cur;
					while (firstleft->_left)
					{
						parent = firstleft;
						firstleft = firstleft->_left;
					}
					del = firstleft;
					swap(cur->_key, firstleft->_key);
					swap(cur->_value, firstleft->_value);
					//判断最左结点是它父节点的左结点还是右结点
					if (parent && parent->_left == firstleft)
					{
						parent->_left = firstleft->_right;
					}
					else if (parent && parent->_right == firstleft)
					{
						parent->_right = firstleft->_right;
					}
					else //parent==NULL。待删除结点的右边只有一个结点，则最左结点就是它
					{
						root->_right = NULL;
					}
				}
				delete del;
				return true;
			}
		}
		return false;
	}
	Node* _Find_R(Node* root,const K& key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key > key)
			_Find_R(root->_left, key);
		else if (root->_key < key)
			_Find_R(root->_right, key);
		else
			return root;
	}
	bool _Insert_R(Node*& root,const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		if (root->_key > key)
			_Insert_R(root->_left, key, value);
		else if (root->_key < key)
			_Insert_R(root->_right, key, value);
		else
			return false;
		return false;
	}
	void _Insort(Node* root)
	{
		if (root == NULL)
			return;
		_Insort(root->_left);
		cout << root->_key<<" ";
		_Insort(root->_right);
	}

protected:
	Node* _root;
};

