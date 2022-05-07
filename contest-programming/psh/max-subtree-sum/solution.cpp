#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

#include <queue>
#include <stack>


//Node for a Binary Tree (data, left child, right child)
class TNode
{
public:
	long data;
	TNode* LC;
	TNode* RC;

	TNode()
	{
		data = 0;
		LC = nullptr;
		RC = nullptr;
	}

	TNode(long el, TNode* ptrL = nullptr, TNode* ptrR = nullptr)
	{
		data = el;
		LC = ptrL;
		RC = ptrR;
	}

	~TNode() { }
};


//Return Value for MaxSubtreeSum function
//	sum is the sum of the entire tree
//	max is the max sum of all the subtree
class ReturnValue
{
public:
	long sum;
	long max;

	ReturnValue()
	{
		sum = 0;
		max = 0;
	}

	ReturnValue(long stM, long m)
	{
		sum = stM;
		max = m;
	}

	~ReturnValue() { }

};




//function prototypes
TNode* TreeSerializationTranslator();
//void TreeDepthPreorder(TNode*);
ReturnValue* MaxSubtreeSum(TNode*);

int main()
{
	//std::ios_base::sync_with_stdio(false);

	//uses a series of user inputs to create the tree
	TNode* rootptr = TreeSerializationTranslator();

	long sum = MaxSubtreeSum(rootptr)->max;

	std::cout << sum << endl;

	return 0;
}





//MaxSubtreeSum takes a node to the root of a binary tree
//	it returns a pointer to an object that contains the max sum of the subtrees and sum tree
ReturnValue* MaxSubtreeSum(TNode* T)
{
	if (T == nullptr) return new ReturnValue();
	ReturnValue* sumLC = MaxSubtreeSum(T->LC);
	ReturnValue* sumRC = MaxSubtreeSum(T->RC);
	return new ReturnValue((sumLC->sum + sumRC->sum + T->data), max (max(max (sumLC->sum, sumLC->max), max(sumRC->sum, sumRC->max)), (sumLC->sum + sumRC->sum + T->data)));
}



//TreeSerializationTranslator takes a node to a binary tree
TNode* TreeSerializationTranslator()
{
	string inputS;
	long inputI;

	std::queue<TNode*> q;
	TNode* rootptr;

	std::cin >> inputS;

	//if first input is a dash (null)
	//else first input is an integer to be made into a node
	if (!inputS.compare("-"))
		return nullptr;
	else
	{
		inputI = stoi(inputS);
		//root node for binary tree and push onto q
		rootptr = new TNode{ inputI };
		q.push(rootptr);
	}


	//interates through entire queue
	//the while loop will complete the tree (adding all nodes that should be added
	while (!q.empty())
	{
		//temporary TNode*
		TNode* n = q.front();
		q.pop();

		std::cin >> inputS;

		//if next input is not a - (nullptr)
		if (inputS.compare("-"))
		{
			inputI = stoi(inputS);
			n->LC = new TNode{ inputI };
			q.push(n->LC);
		}

		std::cin >> inputS;

		//if next input is not a - (nullptr)
		if (inputS.compare("-"))
		{
			inputI = stoi(inputS);
			n->RC = new TNode{ inputI };
			q.push(n->RC);
		}
	}

	return rootptr;
}


