#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//
//int** ReadFile(string inputFile)
//{
//	//Создаем файловый поток и связываем его с файлом
//	ifstream in(inputFile);
//
//	if (in.is_open())
//	{
//		//Если открытие файла прошло успешно
//
//		//Вначале посчитаем сколько чисел в файле
//		int count = 0;  // число чисел в файле
//		int temp;  //Временная переменная
//
//		while (!in.eof())  // пробегаем пока не встретим конец файла eof
//		{
//			in >> temp;  //в пустоту считываем из файла числа
//			count++;  // увеличиваем счетчик числа чисел
//		}
//
//		//Число чисел посчитано, теперь нам нужно понять сколько
//		//чисел в одной строке
//		//Для этого посчитаем число пробелов до знака перевода на новую строку 
//
//		//Вначале переведем каретку в потоке в начало файла
//		in.seekg(0, ios::beg);
//		in.clear();
//
//		//Число пробелов в первой строчке вначале равно 0
//		int count_space = 0;
//		char symbol;
//		while (!in.eof())  //на всякий случай цикл ограничиваем концом файла
//		{
//			//теперь нам нужно считывать не числа, а посимвольно считывать данные
//			in.get(symbol);  //считали текущий символ
//			if (symbol == ' ') count_space++;  //Если это пробел, то число пробелов увеличиваем
//			if (symbol == '\n') break;  //Если дошли до конца строки, то выходим из цикла
//		}
//		//cout << count_space << endl;
//
//		//Опять переходим в потоке в начало файла
//		in.seekg(0, ios::beg);
//		in.clear();
//
//		//Теперь мы знаем сколько чисел в файле и сколько пробелов в первой строке.
//		//Теперь можем считать матрицу.
//
//		int n = count / (count_space + 1);  //число строк
//		int m = count_space + 1;  //число столбцов на единицу больше числа пробелов
//		
//		int** matrix;
//		matrix = new int* [n];
//		for (int i = 0; i < n; i++)
//		{
//			matrix[i] = new int[m];
//		}
//		//Считаем матрицу из файла
//		for (int i = 0; i < n; i++)
//		{
//			for (int j = 0; j < m; j++)
//			{
//				in >> matrix[i][j];
//			}
//		}
//		//Выведем матрицу
//		for (int i = 0; i < n; i++)
//		{
//			for (int j = 0; j < m; j++)
//				cout << matrix[i][j] << "\t";
//			cout << "\n";
//		}
//		cout << endl << endl << endl;
//
//		in.close();  //в конце закроем файла
//	
//		return matrix;
//	}
//	else
//	{
//		//Если открытие файла прошло не успешно
//		cout << "Файл не найден.";
//		cout << endl << endl << endl;
//		return NULL;
//	}
//}

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
						matrix[i][j] = INT_MAX;
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

	void PrintMatrix()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}

	string GetShortestWay(int start, int end)
	{
		string output = "The shortest way from " + to_string(start) + " to " + to_string(end) + ": ";

		int* minWay = new int[size];
		bool* visited = new bool[size];

		for (int i = 0; i < size; i++)
		{
			minWay[i] = matrix[start][i];
			visited[i] = false;
		}

		minWay[start] = 0;
		int minIndex = 0;
		int k = 0;

		for (int i = 0; i < size; i++)
		{
			int min = INT_MAX;

			for (int j = 0; j < size; j++)
			{
				if (!visited[j] && minWay[j] < min)
				{
					min = minWay[j];
					minIndex = j;
				}
			}

			k = minIndex;
			visited[k] = true;

			for (int j = 0; j < size; j++)
			{
				if (!visited[j] && matrix[k][j] != INT_MAX && minWay[k] != INT_MAX &&(minWay[k] + matrix[k][j] < minWay[j]))
				{
					minWay[j] = minWay[k] + matrix[k][j];
				}
			}
		}

		int* ver = new int[size];
		ver[0] = end;
		int t = 1;
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
						ver[t] = i;
						t++;
					}
				}
			}
		}

		for (int i = t - 1; i >= 0; i--)
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


const string IN_PATH = "D:\\input.txt";
const string OUT_PATH = "D:\\qwe.txt";

int main()
{
	MatrixWithDeikstraAlgorithm* matrix = new MatrixWithDeikstraAlgorithm(IN_PATH);

	matrix->PrintMatrix();
	cout << endl;
	string way = matrix->GetShortestWay(0, 1);
	cout << way;

	matrix->SaveshortestWayToFile(OUT_PATH, 0, 1);

	delete matrix;
}
