#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

const string PATH = "D:\\qwe.txt";

float Avg(int* arr, int size)
{

    float avg = 0;
    for (int i = 0; i < size; i++)
    {
        avg += arr[i];
    }
    return avg / size;
}

float process(string S1, string S2)
{
    int i, x = 0;
    double K, N;
    if (strlen(S1.c_str()) >= strlen(S2.c_str()))
    {
        for (i = 0; i != strlen(S2.c_str()); i++) {
            if (S1[i] == S2[i])
                x++;
        }
    }
    else
        for (i = 0; i != strlen(S1.c_str()); i++) {
            if (S1[i] == S2[i])
                x++;
        }
    N = (strlen(S1.c_str()) + strlen(S2.c_str())) / 2;
    return ((x / N) * 100);
}

struct Student 
{
public:
    //////////////////////////////////
    bool isEmpty; // no number
    //////////////////
    string fullName; // no number
    /////////////////////////


    int amountOfGrades; // 0
    int* grades;
    float averageGrade; // 1

    //////////////////////////////////
    Student()
    {
        isEmpty = true;
        fullName = "";
        amountOfGrades = 10;

        grades = new int[10];
        for (int i = 0; i < 10; i++)
        {
            grades[i] = 0;
        }
        averageGrade = 0;
    }
    
    Student(bool empty, string name, int gradesAmount, int* inputGrades)
    {
        isEmpty = false;
        fullName = name;
        amountOfGrades = gradesAmount;

        grades = inputGrades;
        
        averageGrade = Avg(grades, amountOfGrades);
    }

    void Show()
    {
        cout << "Name: " << fullName << endl;
        cout << "AmountOfGrades: " << amountOfGrades << endl;
        cout << "Grades: ";
        for (int i = 0; i < amountOfGrades; i++)
        {
            cout << grades[i];
            cout << " ";
        }
        cout << endl;
        cout << "Average grade: " << averageGrade << endl;
    }
};

class DataBase
{
protected:
    Student* arr;
    int length;

public:
    DataBase() // default constructor
    {
        length = 10;
        arr = new Student[length];
    }

    DataBase(int len)  // constructor with length parametr
    {
        length = len;
        arr = new Student[length];
    }

    void ClearElement(int index) // making element empty
    {
        arr[index].isEmpty = true;
    }

    int FindCleareElement()  // find first cleare element
    {
        for (int i = 0; i < length; i++)
        {
            if (arr[i].isEmpty)
            {
                return i;
            }
        }
        return -1;
    }

    void InputData(int index) // input data for element with index = index
    {
        if ((index < length) && (index >= 0))
        {
            cout << "Input name: ";
            string name;
            cin >> name;
            cout << endl;

            cout << endl << "Input amount of grades: ";
            int amountOfGrades;
            cin >> amountOfGrades;
            cout << endl;

            int* grades = new int[amountOfGrades];
            cout << endl << "Input Grades: ";
            for (int i = 0; i < amountOfGrades; i++)
            {
                cin >> grades[i];
                cout << " ";
            }
            cout << endl;

            arr[index] = Student(false, name, amountOfGrades, grades);
        }
        else
        {
            cout << endl << "ERROR!!!";
        }
    }

    void InputData(int index, Student student) // input data for element with index = index
    {
        arr[index] = student;
    }

    void ShowOneData(int index) // show element with index = index
    {
        if ((index < length) && (index >= 0))
        {
            if (!arr[index].isEmpty)
            {
                cout << "Name: " << arr[index].fullName << endl;
                cout << "AmountOfGrades: " << arr[index].amountOfGrades << endl;
                cout << "Grades: ";
                for (int i = 0; i < length; i++)
                {
                    cout << arr[index].grades[i];
                    cout << " ";
                }
                cout << endl;
                cout << "Average grade: " << arr[index].averageGrade << endl;
            }
        }
        else
        {
            cout << endl << "ERROR!!!";
        }
    }

    void ShowAllData()  // shows all not empty elements
    {
        for (int i = 0; i < length; i++)
        {
            if (!arr[i].isEmpty)
            {
                ShowOneData(i);
                cout << endl;
            }
        }
        
    }

    Student FindStudentWithAverageGrade(float avgGrade)  // finds student with exact or more similar grade
    {
        int index = -1;
        float nearestGrade = -1000;

        for (int i = 0; i < length; i++)
        {
            Student currentStudent = arr[i];
            if (!currentStudent.isEmpty)
            {
                if (avgGrade - nearestGrade > avgGrade - currentStudent.averageGrade)
                {
                    index = i;
                    nearestGrade = currentStudent.averageGrade;
                }
            }
        }

        if (index == -1)
        {
            cout << "DB is empty!!" << endl;
            return Student();
        }
        return arr[index];
    }

    Student FindStudentWithName(string name)  // finds student with exact or more similar name
    {
        float maxProximity = -1;
        int index = -1;

        for (int i = 0; i < length; i++)
        {
            if (!arr[i].isEmpty)
            {
                float currentProximity = process(name, arr[i].fullName);
                if (maxProximity <= process(name, arr[i].fullName))
                {
                    maxProximity = currentProximity;
                    index = i;
                }
            }
        }

        if (index == -1)
        {
            cout << "DB is empty!!" << endl;
            return Student();
        }
        return arr[index];
    }

    Student FindStudentWithMin(int option) // 0 - to find minimum of amount of grades, 1 - to find minimum average grade
    {
        if (option != 1 && option != 0)
        {
            cout << "ERROR" << endl;
            return Student();
        }

        if (option == 0)
        {
            int min = 12345678;
            int index = -1;

            for (int i = 0; i < length; i++)
            {
                if (!arr[i].isEmpty)
                {
                    if (arr[i].amountOfGrades < min)
                    {
                        index = i;
                        min = arr[i].amountOfGrades;
                    }
                }

                if (index == -1)
                {
                    cout << "DB is empty!!" << endl;
                    return Student();
                }
                return arr[index];
            }
        }
        else
        {
            float min = 12345678;
            int index = -1;

            for (int i = 0; i < length; i++)
            {
                if (!arr[i].isEmpty)
                {
                    if (arr[i].averageGrade < min)
                    {
                        index = i;
                        min = arr[i].amountOfGrades;
                    }
                }

                if (index == -1)
                {
                    cout << "DB is empty!!" << endl;
                    return Student();
                }
                return arr[index];
            }
        }
    }

    void SortAscendDB(int option)  // 0 - to sort by amount of grades, 1 - to sort by average grades (ascending)
    {
        if (option == 0)
        {
            for (int i = 0; i < length;)
            {
                if (i == 0 || arr[i].amountOfGrades >= arr[i - 1].amountOfGrades)
                {
                    i++;
                }
                else
                {
                    Student b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                    i--;
                }
            }
        }
        else
        {
            for (int i = 0; i < length;)
            {
                if (i == 0 || arr[i].averageGrade >= arr[i - 1].averageGrade)
                {
                    i++;
                }
                else
                {
                    Student b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                    i--;
                }
            }
        }
    }

    void SortDescendDB(int option)  // 0 - to find sort by amount of grades, 1 - to sort by average grades (descending)
    {
        if (option == 0)
        {
            for (int i = 0; i < length;)
            {
                if (i == 0 || arr[i].amountOfGrades <= arr[i - 1].amountOfGrades)
                {
                    i++;
                }
                else
                {
                    Student b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                    i--;
                }
            }
        }
        else
        {
            for (int i = 0; i < length;)
            {
                if (i == 0 || arr[i].averageGrade <= arr[i - 1].averageGrade)
                {
                    i++;
                }
                else
                {
                    Student b = arr[i];
                    arr[i] = arr[i - 1];
                    arr[i - 1] = b;
                    i--;
                }
            }
        }
    }

    // запись в файл массива структур
    //int SaveDB(string filename, Student* st)
    int SaveDB(string filename)
    {
        FILE* fp, *stream;
        char* c;

        errno_t err;

        // число записываемых байтов
        int size = length * sizeof(Student);

        err = fopen_s(&fp, filename.c_str(), "wb");
        // записываем количество структур
        c = (char*)&length;
        for (int i = 0; i < sizeof(int); i++)
        {
            putc(*c++, fp);
        }

        // посимвольно записываем в файл все структуры
        //c = (char*)st;
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
        Student* ptr = (Student*)malloc(n * sizeof(Student));
        c = (char*)ptr;
        // после записи считываем посимвольно из файла
        while ((i = getc(fp)) != EOF)
        {
            *c = i;
            c++;
        }
        // перебор загруженных элементов и вывод на консоль
        printf("\n%d people in the file stored\n\n", n);


        free(pti);
        free(ptr);
        fclose(fp);
        return n;
    }

    // загрузка из файла массива структур
    int LoadDB(string filename)
    {
        FILE* fp, *stream;
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
        Student* ptr = (Student*) malloc(n * sizeof(Student));
        c = (char*)ptr;
        // после записи считываем посимвольно из файла
        while ((i = getc(fp)) != EOF)
        {
            *c = i;
            c++;
        }
        // перебор загруженных элементов и вывод на консоль

        arr = new Student[n];

        for (int k = 0; k < n; k++)
        {
            arr[k] = Student((ptr + k)->isEmpty, (ptr + k)->fullName, (ptr + k)->amountOfGrades, (ptr + k)->grades);
        }

        free(pti);
        free(ptr);
        fclose(fp);
        return 0;
    }
};

int main()
{
    int length = 3;

    DataBase db = DataBase(3);

    int g1[3] = {2, 3, 4};
    Student s1 = Student(false, "John", 3, g1);

    int g2[3] = { 5, 2, 3 };
    Student s2 = Student(false, "Annita", 3, g2);

    int g3[4] = {1, 4, 5, 5 };
    Student s3 = Student(false, "Dorn", 4, g3);

    db.InputData(0, s1);
    db.InputData(1, s2);
    db.InputData(2, s3);

    db.ShowAllData();
    cout << endl;

    cout << endl;
    //cout << db.FindCleareElement();
    cout << endl;
    db.SortDescendDB(1);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    db.SaveDB(PATH);

    int a = db.FindDBLength(PATH);

    DataBase db1 = DataBase(a);
    db1.LoadDB(PATH);

    db1.ShowAllData();
}
