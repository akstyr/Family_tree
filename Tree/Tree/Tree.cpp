// Tree.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "fstream"
#include "string"
#include "queue"
#include "iostream"
using namespace std;

class Treee
{
public:
	struct Node //����
	{
		string Data;
		Node *left;
		Node *right;
		int ID;
	};
	Node *parent = nullptr;
	Node *root = nullptr;
	int N = 0;

public:
	Treee() {};
	~Treee()
	{
		queue <Node*> q;
		q.push(root);

		while (!q.empty())
		{
			Node *fq = q.front();
			if (fq != nullptr)
			{
				Node *prost;
				if (fq->left != nullptr)
				{
					prost = fq->left;
					q.push(prost);
				}
				if (fq->right != nullptr)
				{
					prost = fq->right;
					q.push(prost);
				}
				delete fq;
			}
			q.pop();
		}
		parent = nullptr;
		root = nullptr;
		N = 0;
	};
	
	void Push(string D,bool gend)
	{
		N++;
		Node *node = new Node;
		node->Data = D;
		node->ID = N;
		node->left = nullptr;
		node->right = nullptr;
		if (N == 1) // ��� ����� �����
		{
			root = node;
			parent = root;
		}
		else
		{
			if (gend == 0)
			{
				parent->left = node;
				if (N <= 3)
					root->left = node;
			}
			else
			{
				parent->right = node;
				if (N <= 3)
					root->right = node;
			}
		}
	};

	bool Parent(string men)//���� ��������
	{
		queue <Node*> myQueue; //�������, � ��� ����� ��������� ������ ����� ������
		if (root != nullptr)
		{
			Node ro = *root;
			myQueue.push(&ro); //������ ������� ��� ��������� - ������ ������
			while (true)
			{
				if (myQueue.empty() == true) //���� ������� ����� => ������� �� ������
					return 0;
				Node *first = myQueue.front(); //�������� � ������ ���������
				if (first->Data == men)//������� ������
				{
					parent = first;
					return 1;
				}
				else //������ ������� - �� ��� �������, �������� �� ���� => ������� ��� �� �������
					myQueue.pop();
				if (first->left != nullptr) //���� ���� �����, ���� ��������� � �������
					myQueue.push(first->left);
				if (first->right != nullptr) // �� ��, ��� � � �����
					myQueue.push(first->right);
			}
		}
	};
	void Print(Node *q, int level)
	{
		if (q)
		{
			Print(q->left, level + 1);
			for (int i = 0; i < level; i++) cout << "    ";
			cout << q->ID << " " << q->Data << endl;
			Print(q->right, level + 1);
		}
	};
};


int main()
{
	setlocale(0, "");
	Treee tr;
	ifstream file("Family_tree.txt");
	if (!file)
	{
		cout << "������ ������ ������� ������ ������. �������� ��������������� ������ ��� � ������� \n��� � ��� ��������: ������ ���� �������� 2000\n����: ������� ������ �������� 1990\n����: ������ ���� ���������� 1987\n";
		system("Family_tree.txt");
	}
	string men, mama, papa;
	while (!file.eof())
	{
		getline(file, men);
		men = men.substr(20);
		getline(file, mama);
		mama = mama.substr(6);
		getline(file, papa);
		papa = papa.substr(6);
		if (tr.N == 0) //���� �� ���� �������, ������� ������
			tr.Push(men, 1);
		bool b = tr.Parent(men);
		if (b == 1) //���� ��������
		{
			tr.Push(mama, 0); //��������� � ������ ���� � ����
			tr.Push(papa, 1);
		}
		else
			cout << "������� �� ������, �������� �� �� �������� ���\n";
	}
	file.close();
	tr.Print(tr.root, 0);
	tr.~Treee();
	system("Pause");
    return 0;
};