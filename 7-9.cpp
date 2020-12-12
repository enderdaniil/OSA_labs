#include <iostream>
#include <fstream>
using namespace std;
const int N = 10;

class Recursion {
private:
	int graph[N][N] = {};
	bool visited[N];
	int VON_PUNKT[N];
	int count;
	int start, end;

public:
	Recursion(int st, int en)
	{
		ifstream in("D:\\input_bfs.txt");
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++) {
				in >> graph[i][j];
			}
		}
		start = st - 1;
		end = en - 1;
		for (int i = 0; i < N; i++)
		{
			visited[i] = 0;
		}
		count = 0;
		visited[start] = 1;
		VON_PUNKT[start] = -1;
	}

	void FindWay(int curr) 
	{
		visited[curr] = 1;
		for (int i = 0; i < N; i++)
		{
			if (visited[i] == 0 && graph[curr][i])
			{
				VON_PUNKT[i] = curr;

				FindWay(i);
			}
		}
	}

	void Print() 
	{
		cout << "\nWay (end-beg): \n";
		cout << end + 1 << " ";
		end = VON_PUNKT[end];
		while (end != start) 
		{
			cout << end + 1 << " ";
			end = VON_PUNKT[end];
		}
		cout << start + 1;
	}
};

struct Item
{
	int data;
	Item* next;
	Item* prev;
};
class Queue 
{
private:
	int graph[N][N] = {};
	bool visited[N];
	int VON_PUNKT[N];
	Item* first;
	Item* last;
	int count;
	int start, end;
	int il = 0;
	int rang[N];
	int line = 0;

public:
	Queue(int st, int en)
	{
		ifstream in("D:\\input_bfs.txt");
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				in >> graph[i][j];
			}
		}
		start = st - 1;
		end = en - 1;
		for (int i = 0; i < N; i++)
		{
			visited[i] = 0;
		}
		last = NULL;
		first = NULL;
		count = 0;
	}

	void FindWay() {
		visited[start] = 1;
		VON_PUNKT[start] = -1;
		rang[start] = line;
		line++;
		Add(start);
		while (!IsEmpty())
		{
			int unit = First();
			DeleteFirst();
			for (int i = 0; i < N; i++)
			{
				if ((visited[i] == 0) && (graph[unit][i] == 1))
				{
					Add(i);
					VON_PUNKT[i] = unit;
					visited[i] = 1;
					rang[i] = line;
				}
			}
			line++;
		}

	}

	void Add(int a)
	{
		Item* newitem = new Item;
		newitem->data = a;
		if (first == NULL)
		{
			first = newitem;
		}
		newitem->next = NULL;
		newitem->prev = last;
		if (last != NULL)
		{
			last->next = newitem;
		}
		last = newitem;
		count++;
	}

	void DeleteFirst()
	{
		Item* place = first;
		if (place != last)
		{
			place->next->prev = NULL;
			first = place->next;
		}
		else
		{
			first = NULL;
			last = NULL;
		}
		count--;
	}

	bool IsEmpty()
	{
		bool empt;
		if (first == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int First()
	{
		return first->data;
	}

	void Print() 
	{
		cout << "\nWay (end-beg): \n";
		cout << end + 1 << " ";
		end = VON_PUNKT[end];
		while (end != start)
		{
			cout << end + 1 << " ";
			end = VON_PUNKT[end];
		}
		cout << start + 1;
	}
};
class Stack {
private:
	int* arr;
	int top;
	int graph[N][N] = {};
	bool visited[N];
	int VON_PUNKT[N];
	int count;
	int start, end;
	int il = 0;
	int teckush = 0;

public:
	Stack(int st, int en)
	{
		ifstream in("D:\\input_bfs.txt");
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++) 
			{
				in >> graph[i][j];
			}
		}
		start = st - 1;
		end = en - 1;
		for (int i = 0; i < N; i++)
		{
			visited[i] = 0;
		}
		top = -1;
		arr = new int[100];
		count = 0;
	}

	void FindWay() 
	{
		visited[start] = 1;
		VON_PUNKT[start] = -1;
		Push(start);
		while (top != -1) 
		{
			Pop();
			visited[teckush] = 1;
			for (int i = N - 1; i >= 0; i--)
			{
				if (graph[teckush][i] == 1 && visited[i] == 0)
				{
					Push(i);
					VON_PUNKT[i] = teckush;
				}
			}
		}
	}

	void Push(int a)
	{
		top++;
		arr[top] = a;
	}

	void Pop()
	{
		teckush = arr[top];
		top--;
	}

	void Print() 
	{
		cout << "\nWay (end-beg): \n";
		cout << end + 1 << " ";
		end = VON_PUNKT[end];
		while (end != start)
		{
			cout << end + 1 << " ";
			end = VON_PUNKT[end];
		}
		cout << start + 1;
	}
};


int main()
{
	Stack stack(1, 5);
	stack.FindWay();
	stack.Print();
	cout << endl;
	cout << endl;
	cout << endl;

	Queue que(3, 6);
	que.FindWay();
    que.Print();
	cout << endl;
	cout << endl;
	cout << endl;

	Recursion recursion(7, 10);
	recursion.FindWay(7 - 1);
	recursion.Print();	
	cout << endl;
	cout << endl;
	cout << endl;

	return 0;
}
