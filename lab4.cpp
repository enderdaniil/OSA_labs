#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class DataBase
{
protected:
    int* arr;
    int length;

public:
    DataBase() // default constructor
    {
        length = 0;
        arr = new int[length];
    }

    DataBase(int len)  // constructor with length parametr
    {
        length = len;
        arr = new int[length];
    }

    void AddElement(int value) // добавление элемнта в базу данных
    {
        int* bus = new int[length];
        for (int i = 0; i < length; i++)
        {
            bus[i] = arr[i];
        }

        length++;

        arr = new int[length];
        for (int i = 0; i < length - 1; i++)
        {
            arr[i] = bus[i];
        }
        arr[length - 1] = value;
    }

    int* GetDBData()
    {
        return arr;
    }

    int GetLength()
    {
        return length;
    }

    // запись в файл массива
    void SaveDB(string filename)
    {
        ofstream outdata;

        outdata.open(filename); // opens the file
        if (!outdata) { // file couldn't be opened
            cerr << "Error: file could not be opened" << endl;
        }

        for (int i = 0; i < length - 1; i++)
        {
            outdata << arr[i] << ", ";
        }
        outdata << arr[length - 1];

        outdata.close();

    }

    // загрузка из файла массива
    void LoadDB(string filename)
    {
        ifstream in(filename);
        string line = "";
        string number = "";
        vector<int> numbers{};

        while (getline(in, line))
        {
            stringstream strStream(line);
            while (getline(strStream, number, ','))
            {
                numbers.push_back(atoi(number.c_str()));
            }

        }

        length = numbers.size();
        arr = new int[length];

        for (int i = 0; i < length; i++)
        {
            arr[i] = numbers[i];
        }
    }
};

struct Node 
{
    Node* left;
    Node* right;
    int value;

    Node()
    {
        left = NULL;
        right = NULL;
        value = 0;
    }

    Node(int value)
    {
        left = NULL;
        right = NULL;
        this->value = value;
    }

    Node(int value, Node* left, Node* right)
    {
        this->left = left;
        this->right = right;
        this->value = value;
    }
};

class BinaryTree
{
protected:
    Node* root;

    int size;
    string way;

    DataBase db;

public:
    BinaryTree()
    {
        root = NULL;
        size = 0;
        way = "";
        db = DataBase(0);
    }

    Node* Search(int value) // поиск в дереве
    {
        Node* bus, * current;
        if (root != NULL)
        {
            current = root;
            bus = current;
            while (current != NULL)
            {
                if (current->value < value)
                {
                    bus = current;
                    current = current->right;
                }
                else if (current->value > value)
                {
                    bus = current;
                    current = current->left;
                }
                else
                {
                    return current;
                }
            }
            return bus;
        }
        else
        {
            return new Node();
        }
    }

    DataBase GetDB() // получение базы данных хранения дерева
    {
        return db;
    }

    void AddNode(int val) // добавление элемента в дерево
    {
        Node* last = Search(val);
        Node* newNode = new Node(val);
        if (root == NULL)
        {
            root = newNode;
        }
        else
        {
            newNode->value = val;
            newNode->left = NULL;
            newNode->right = NULL;
            if (val < last->value)
            {
                last->left = newNode;
            }
            else
            {
                last->right = newNode;
            }
        }
        size++;
        db.AddElement(val);
    }

    BinaryTree(string pathToFile) // загрузка дерева из файла
    {
        db = DataBase();
        db.LoadDB(pathToFile);

        root = NULL;
        size = 0;
        way = "";

        size = db.GetLength();
        int* arr = db.GetDBData();

        int s = db.GetLength();
        for (int i = 0; i < s; i++)
        {
            AddNode(arr[i]);
        }
    }

    Node* GetRoot()
    {
        return root;
    }

    void GetWay(Node* node) // обход дерева по возрастания
    {
        if (node != NULL)
        {
            way += to_string(node->value);
            way += "; ";
            if (node->left != NULL)
            {
                GetWay(node->left);
                way += to_string(node->value);
                way += "; ";
            }
            if (node->right != NULL)
            {
                GetWay(node->right);
                way += to_string(node->value);
                way += "; ";
            }
        }
    }

    int* GetValues(Node* node) // обход дерева с последовательностью вершин: корень, левые, правые
    {
        int* arr = new int(size);
        int i = 0;
        if (node) 
        {
            arr[i++] = node->value;
            GetValues(node->left);
            GetValues(node->right);
        }
    }

    void SaveTreeToFile(string path) // сохранение дерева в файл
    {
        db.SaveDB(path);
    }

    void SaveWayToFile(string path) // сохранения пути, по дереву в файл
    {
        if (way != "")
        {
            ofstream out;
            out.open(path, ios::trunc);

            if (out.is_open())
            {
                out << way << endl;
            }
        }
        else
        {
            cout << "Make GetWay!!!";
        }

    }

    void GetWayFromFile(string path) // получение пути по дереву из файла
    {
        string line;
        ifstream in(path);
        if (in.is_open())
        {
            while (getline(in, line))
            {
                way += line;
            }
        }
        in.close();
    }

    string GetStringWay() // возвращение string с путём
    {
        return way;
    }
};

string path0 = "D:\\qwe.txt";
string path1 = "D:\\ttt.txt";

int main()
{
    BinaryTree binaryTree = BinaryTree();

    int arr[8] = {6, 9, -7, 4, 12, 0, 7, -30};

    for (int i = 0; i < 8; i++)
    {
        binaryTree.AddNode(arr[i]);
    }

    cout << endl;
    cout << endl;
    cout << endl;

    binaryTree.GetWay(binaryTree.GetRoot());
    binaryTree.SaveWayToFile(path0);

    cout << endl;
    cout << endl;
    cout << endl;

    int* array1 =  binaryTree.GetDB().GetDBData();

    for (int i = 0; i < binaryTree.GetDB().GetLength(); i++)
    {
        cout << array1[i] << " ";
    }
    cout << endl << binaryTree.GetDB().GetLength() << endl << endl;
    cout << endl << binaryTree.GetDB().GetLength() << endl << endl;

    binaryTree.SaveTreeToFile(path1);
    BinaryTree newTree = BinaryTree(path1);
    newTree.GetWay(newTree.GetRoot());
    cout << newTree.GetStringWay();

}
