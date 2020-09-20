#include <iostream>

using namespace std;

int N = 10;

class Stack {
private:
	int* arr;
	int top;

public:
	Stack()
	{
		arr = new int[N];
		top = -1;
	}

	Stack(int m)
	{
		arr = new int[m];
		top = -1;
	}

	void Push(int n) 
	{
		if (top == N - 1)
		{
			cout << "Stack is full!!!" << endl;
		}
		else
		{
			top++;
			arr[top] = n;
		}
	}

	int Pop()
	{
		if (top < 0)
		{
			cout << "Stack is empty!!!" << endl;
			return 0;
		}
		else
		{
			int element = arr[top];
			top -= 1;
			return element;
		}
	}
};

class Queue {
private:
	int* arr;
	int head;
	int tail;

public:
	Queue()
	{
		arr = new int[N];
		head = 0;
		tail = 0;
	}

	Queue(int n)
	{
		arr = new int[n];
		head = 0;
		tail = 0;
	}

	void Put(int newElement)
	{
		if (head == (tail + 1) % N)
		{
			cout << "Queue is full!!!" << endl;
		}
		else
		{
			arr[tail] = newElement;
			tail = (tail + 1) % N;
		}
	}

	int Get()
	{
		if (head != tail) //проверяем наличие элементов в очереди
		{
			int output = arr[head];
			head = (head + 1) % N;
			return output;
		}
		else
		{
			cout << "Queue is empty!!!";
			return 0;
		}
	}
};

int main() {
	int newElement;
	bool r; 

	cout << "How many elements will be in the stack and queue: ";
	cin >> N;
	Stack stack(N);
	Queue queue(N);

	for (int i = 0; i < N + 5; i++) 
	{
		cout << "For adding input 1, for deleting input 0: ";
		cin >> r;

		if (r)
		{
			cout << "Input value: ";
			cin >> newElement;
			stack.Push(newElement);
		}
		else
		{
			int output = stack.Pop();
			cout << "Value is: " << output;
			cout << endl;
		}

	}

	for (int i = 0; i < N + 5; i++)
	{
		cout << "For adding input 1, for deleting input 0: ";
		cin >> r;

		if (r)
		{
			cout << "Input value: ";
			cin >> newElement;
			queue.Put(newElement);
		}
		else
		{
			int output = queue.Get();
			cout << "Value is: " << output;
			cout << endl;
		}

	}

	return 0;
}
