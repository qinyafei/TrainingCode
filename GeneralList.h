#pragma once

template<typename T>
class ListNode
{
public:
	ListNode()
	{
		FirstChild = NextSibling = NULL;
	}
	~ListNode()
	{
		FirstChild = NextSibling = NULL;
	}

	ListNode(T& valuedata)
	{
		Data = valuedata;
		FirstChild = NextSibling = NULL;
	}


public:

	T Data;
	ListNode<T>* FirstChild;
	ListNode<T>* NextSibling;
};

template<typename T>
class GeneralList
{
public:
	GeneralList(void);
	~GeneralList(void);

public:
	//build root
	int BuildRoot(T& data);
	//add insert
	int Insert(ListNode<T>* targ, T& data);
	//remove
	int RemoveSubChild(ListNode<T>* targ, T& data);
	int RemoveNode(ListNode<T>* targ);

	//get listnode
	ListNode<T>* Get(T& data, ListNode<T>* targ);
	ListNode<T>* GetRoot();

public:
	ListNode<T>* Root;
	ListNode<T>* CurNode;


};


template<typename T>
GeneralList<T>::GeneralList(void)
{
	Root = CurNode = NULL;
}


template<typename T>
GeneralList<T>::~GeneralList(void)
{
	
}

template<typename T>
int GeneralList<T>::BuildRoot(T& data)
{
	Root = new ListNode<T>(data);
	CurNode = Root;

	return 0;
}

template<typename T>
int GeneralList<T>::Insert(ListNode<T>* targ, T& data)
{
	if (targ == NULL && Root != NULL)
	{
		return -1;
	}

	//
	ListNode<T>* node = new ListNode<T>(data);
	if (targ->FirstChild == NULL)
	{
		targ->FirstChild = node;
	}
	else
	{
		ListNode<T>* lp = targ->FirstChild;
		while (lp->NextSibling != NULL)
			lp = lp->NextSibling;

		lp->NextSibling = node;			
	}

	return 0;
}

//remove
template<typename T>
int GeneralList<T>::RemoveSubChild(ListNode<T>* targ, T& data)
{
	if (targ == NULL)
	{
		return -1;
	}

	ListNode<T>* PreNode = NULL;
	ListNode<T>* NextNode = NULL;
	PreNode = NextNode = targ->FirstChild;
	int count = 0;
	while (NextNode != NULL)
	{
		if (NextNode->Data == data && count == 0)
		{
			//is first child
			targ->FirstChild = NextNode->NextSibling;
			RemoveNode(NextNode);
			break;
		}
		else if (NextNode->Data == data && count > 0)
		{
			// middle child
			PreNode->NextSibling = NextNode->NextSibling;
			RemoveNode(NextNode);
			break;
		}
    count++;
		PreNode = NextNode;
		NextNode = NextNode->NextSibling;

	}

	return 0;

}


template<typename T>
int GeneralList<T>::RemoveNode(ListNode<T>* targ)
{
	if (targ == NULL)
	{
		return -1;
	}

	if (targ->FirstChild == NULL)
	{
		delete targ;
		targ = NULL;
		return 0;
	}

	ListNode<T>* pNode = targ->FirstChild;
	while (pNode != NULL)
	{
		ListNode<T>* tempNode = pNode;
		pNode = pNode->NextSibling;
		RemoveNode(tempNode);
	}

	delete targ;
	targ = NULL;
	return 0;

}


//get listnode
template<typename T>
ListNode<T>* GeneralList<T>::Get(T &data, ListNode<T>* targ)
{
	if (targ == NULL)
	{
		return NULL;
	}

	if (targ->Data == data)
	{
		return targ;
	}

	if (targ->FirstChild == NULL)
	{
		return NULL;
	}

	ListNode<T>* pNode = targ->FirstChild;
	while (pNode != NULL)
	{
		ListNode<T>* temNode = Get(data, pNode);
		if (temNode != NULL)
		{
			return temNode;
		}
		pNode = pNode->NextSibling;
	}

	return NULL;
}

template<typename T>
ListNode<T>* GeneralList<T>::GetRoot()
{
	return Root;
}


