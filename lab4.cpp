#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <fstream>

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
        length = 10;
        arr = new int[length];
    }

    DataBase(int len)  // constructor with length parametr
    {
        length = len;
        arr = new int[length];
    }

    void AddElement(int value)
    {
        int* bus = new int[length];
        bus = arr;

        length++;

        arr = new int[length];
        for (int i = 0; i < length - 1; i++)
        {
            arr[i] = bus[i];
        }
        arr[length - 1] = value;
    }

    int* GetDB()
    {
        return arr;
    }

    int GetLength()
    {
        return length;
    }

    // запись в файл массива структур
    int SaveDB(string filename)
    {
        FILE* fp, * stream;
        char* c;

        errno_t err;

        // число записываемых байтов
        int size = length * sizeof(int);

        err = fopen_s(&fp, filename.c_str(), "wb");
        // записываем количество структур
        c = (char*)&length;
        for (int i = 0; i < sizeof(int); i++)
        {
            putc(*c++, fp);
        }

        // посимвольно записываем в файл все структуры
        c = (char*)arr;
        for (int i = 0; i < size; i++)
        {
            putc(*c, fp);
            c++;
        }
        fclose(fp);
        return 0;
    }

    int FindDBLength(string filename)
    {
        FILE* fp, * stream;
        char* c;
        int m = sizeof(int);
        int n, i;

        errno_t err;

        // выделяем память для количества данных
        int* pti = (int*)malloc(m);

        err = fopen_s(&fp, filename.c_str(), "r");

        // считываем количество структур
        c = (char*)pti;
        while (m > 0)
        {
            i = getc(fp);
            if (i == EOF) break;
            *c = i;
            c++;
            m--;
        }
        //получаем число элементов
        n = *pti;

        // выделяем память для считанного массива структур
        int* ptr = (int*)malloc(n * sizeof(int));
        c = (char*)ptr;
        // после записи считываем посимвольно из файла
        while ((i = getc(fp)) != EOF)
        {
            *c = i;
            c++;
        }

        free(pti);
        free(ptr);
        fclose(fp);
        return n;
    }

    // загрузка из файла массива структур
    int LoadDB(string filename)
    {
        FILE* fp, * stream;
        char* c;
        int m = sizeof(int);
        int i;

        errno_t err;

        // выделяем память для количества данных
        int* pti = (int*)malloc(m);

        err = fopen_s(&fp, filename.c_str(), "r");

        // считываем количество структур
        c = (char*)pti;
        while (m > 0)
        {
            i = getc(fp);
            if (i == EOF) break;
            *c = i;
            c++;
            m--;
        }
        //получаем число элементов
        length = *pti;

        // выделяем память для считанного массива структур
        int* ptr = (int*)malloc(length * sizeof(int));
        c = (char*)ptr;
        // после записи считываем посимвольно из файла
        while ((i = getc(fp)) != EOF)
        {
            *c = i;
            c++;
        }
        // перебор загруженных элементов и вывод на консоль

        arr = new int[length];

        for (int k = 0; k < length; k++)
        {
            arr[k] = int((ptr + k));
        }

        free(pti);
        free(ptr);
        fclose(fp);
        return 0;
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

    Node* Search(int value)
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
    }

    void AddNode(int val)
    {
        Node* bus = Search(val);
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
            if (val < bus->value)
            {
                bus->left = newNode;
            }
            else
            {
                bus->right = newNode;
            }
        }
        size++;
        db.AddElement(val);
    }

    BinaryTree(string pathToFile)
    {
        db = DataBase();
        db.LoadDB(pathToFile);

        size = db.GetLength();
        int* arr = db.GetDB();

        for (int i = 0; i < size; i++)
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
                cout << node->value << " ";
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

    void SaveTreeToFile(string path)
    {
        db.SaveDB(path);
    }

    void SaveWayToFile(string path)
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

    void GetWayFromFile(string path)
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

    string GetStringWay()
    {
        return way;
    }
};

void PrintFromFile(string path)
{
    string line;
    ifstream in(path);
    if (in.is_open())
    {
        while (getline(in, line))
        {
            cout << line << endl;
        }
    }
    in.close();
}

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

    PrintFromFile(path0);
}
