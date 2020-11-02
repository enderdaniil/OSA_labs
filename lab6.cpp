#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MatrixWithDeikstraAlgorithm
{
private:
	int size;
	int** matrix;

public:
	MatrixWithDeikstraAlgorithm()
	{
		size = 0;
		matrix = NULL;
	}

	void SetSize(string path)
	{
		ifstream in(path);

		if (in.is_open())
		{
			//Если открытие файла прошло успешно

			//Число пробелов в строчке вначале равно 0
			int count_space = 0;
			char symbol;
			while (!in.eof())  //на всякий случай цикл ограничиваем концом файла
			{
				//теперь нам нужно считывать не числа, а посимвольно считывать данные
				in.get(symbol);  //считали текущий символ
				if (symbol == ' ')
				{
					count_space++;  //Если это пробел, то число пробелов увеличиваем
				}
				if (symbol == '\n')
				{
					break;  //Если дошли до конца строки, то выходим из цикла
				}
			}

			size = count_space + 1;  //число столбцов на единицу больше числа пробелов

			matrix = new int*[size];
			for (int i = 0; i < size; i++)
			{
				matrix[i] = new int[size];
			}

			in.close();
		}
		else
		{
			cout << "This file doesn't exist!!!";
		}
	}

	MatrixWithDeikstraAlgorithm(string path)
	{
		SetSize(path);
		ifstream in(path);

		if (in.is_open())
		{
			in.seekg(0, ios::beg);
			in.clear();

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					in >> matrix[i][j];
					if (matrix[i][j] == -1)
					{
						matrix[i][j] = INT_MAX - 3000;
					}
				}
			}

			in.close();
		}
		else
		{
			cout << "This file doesn't exist!!!";
		}
	}

	void SetSize(int size)
	{
		this->size = size;
		matrix = new int* [size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
		}
	}

	int GetSize()
	{
		return size;
	}

	int** GetMatrix()
	{
		return matrix;
	}

	string GetShortestWay(int start, int end)
	{
		string output = "The shortest way from " + to_string(start) + " to " + to_string(end) + ": ";

		int* minWay = new int[size];
		bool* visited = new bool[size];

		for (int i = 0; i < size; i++)
		{
			minWay[i] = INT_MAX - 20;
			visited[i] = false;
		}

		minWay[start] = 0;
		int minIndex = -1;
		do {
			int temp = 0;
			int min = INT_MAX;

			for (int i = 0; i < size; i++)
			{
				if (!visited[i] && minWay[i] < min)
				{
					min = minWay[i];
					minIndex = i;
				}
			}

			if (minIndex != -1)
			{
				for (int i = 0; i < size; i++)
				{
					if (matrix[minIndex][i] > 0)
					{
						temp = min + matrix[minIndex][i];
						if (temp < minWay[i])
						{
							minWay[i] = temp;
						}
					}
				}
				visited[minIndex] = true;
			}
		} while (minIndex != -1);

		int* ver = new int[size];
		ver[0] = end + 1;
		int k = 1;
		int weight = minWay[end];

		while (end != start)
		{
			for (int i = 0; i < size; i++)
			{
				if (matrix[i][end] != 0)
				{
					int temp = weight - matrix[i][end];

					if (temp == minWay[i])
					{
						weight = temp;
						end = i;
						ver[k] = i + 1;
						k++;
					}
				}
			}
		}

		for (int i = k - 1; i >= 0; i--)
		{
			output = output + to_string(ver[i]) + " ";
		}

		return output;
	}

	void SaveshortestWayToFile(string path, int start, int end)
	{
		ofstream out;
		out.open(path);

		if (out.is_open())
		{
			out << GetShortestWay(start, end);
		}
		else
		{
			cout << "This file doesn't exist!!!";
		}
	}
};


const string IN_PATH = "D:\\ttt.txt";
const string OUT_PATH = "D:\\qwe.txt";

int main()
{
	
}
