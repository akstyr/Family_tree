// Tree.cpp: определяет точку входа для консольного приложения.
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
	struct Node //узел
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
		if (N == 1) // все кроме корня
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

	bool Parent(string men)//ищет родителя
	{
		queue <Node*> myQueue; //очередь, в ней будут храниться адреса ячеек дерева
		if (root != nullptr)
		{
			Node ro = *root;
			myQueue.push(&ro); //первый элемент для сравнения - корень дерева
			while (true)
			{
				if (myQueue.empty() == true) //если очередь пуста => человек не найден
					return 0;
				Node *first = myQueue.front(); //работаем с первым элементом
				if (first->Data == men)//человек найден
				{
					parent = first;
					return 1;
				}
				else //первый элемент - не тот человек, которого мы ищем => удаляем его из очереди
					myQueue.pop();
				if (first->left != nullptr) //если есть левый, узел добавляем в очередь
					myQueue.push(first->left);
				if (first->right != nullptr) // то же, что и с левым
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
		cout << "Первая запись являеся корнем дерева. Напишите генеологическое дерево как в примере \nФИО и год рождения: Иванов Иван Иванович 2000\nМама: Иванова Лариса Олеговна 1990\nПапа: Иванов Иван Витальевич 1987\n";
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
		if (tr.N == 0) //если не было записей, создаем корень
			tr.Push(men, 1);
		bool b = tr.Parent(men);
		if (b == 1) //ищем человека
		{
			tr.Push(mama, 0); //записывам в дерево маму и папу
			tr.Push(papa, 1);
		}
		else
			cout << "Человек не найден, возможно вы не написали год\n";
	}
	file.close();
	tr.Print(tr.root, 0);
	tr.~Treee();
	system("Pause");
    return 0;
};