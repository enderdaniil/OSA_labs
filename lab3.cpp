// variant 9

#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

float Avg(int* arr, int size)  // find avarage
{
    float avg = 0;
    for (int i = 0; i < size; i++)
    {
        avg += arr[i];
    }
    return avg / size;
}

float process(string S1, string S2) // find similarity rate of two strings
{
    int i, x = 0;
    double K, N;
    if (strlen(S1.c_str()) >= strlen(S2.c_str()))
    {
        for (i = 0; i != strlen(S2.c_str()); i++) 
        {
            if (S1[i] == S2[i])
            {
                x++;
            }
        }
    }
    else
        for (i = 0; i != strlen(S1.c_str()); i++)
        {
            if (S1[i] == S2[i])
            {
                x++;
            }
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

struct Node
{
public:
    Student value;
    Node* prev;

    Node()
    {
        prev = NULL;
    }

    Node(Student a)
    {
        value = a;
        prev = NULL;
    }
};

class SimplyLinkedList
{
protected:
    Node* head;
    int size;

public:
    SimplyLinkedList()
    {
        head = NULL;
        size = 0;
    }

    int GetSize() // get size of the list
    {
        return size;
    }

    void AppendToEnd(Student student) // append element to the end
    {
        // Создаем новый узел для значения
        Node* node = new Node(student);
        
        // Новый узел привязывается к старому головному элементу
        node->prev = head;

         // Новый узел сам становится головным элементом
        head = node;
        size++;
    }

    void DeleteEnd() // deleting at the end
    {
        if (size > 1)
        {
            head = head->prev;
            size--;
        }
        else if (size == 1)
        {
            head = NULL;
            size--;

        }
        else
        {
            cout << "List is Empty!!!";
        }
    }

    void DeleteBeginning() // delete element at the beginning
    {
        if (size > 1)
        {
            Node* current = head;

            for (int i = 0; i < size - 1; i++)
            {
                current = current->prev;
            }

            current = NULL;
            size--;
        }
        else if (size == 1)
        {
            head = NULL;
            size--;

        }
        else
        {
            cout << "List is Empty!!!";
        }
    }

    void AppendToBeginning(Student student)  // append element to the beginning
    {
        Node* node = new Node(student);
        Node* current = head;
        
        for (int i = 0; i < size - 1; i++)
        {
            current = current->prev;
        }

        node->prev = current->prev;
        current->prev = node;
        size++;
    }

    void Show() // show the whole list
    {
        Node* current = head;
        for (int i = 0; i < size; i++)
        {
            current->value.Show();
            cout << endl;
            current = current->prev;
        }
    }

    void ShowElement(int index) // show element with this index
    {
        if (index < size || index < 0)
        {
            Node* current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->prev;
            }
            current->value.Show();
        }
        else
        {
            cout << "Index out of range!!!";
        }
    }

    int Search(float avgGrade) // search for the first human being with the most similar average grade to this
    {
        int needed = 0;
        float nearest = head->value.averageGrade;
        Node* current = head;

        for (int i = 0; i < size; i++)
        {
            if (abs(current->value.averageGrade - avgGrade) < abs(nearest - avgGrade))
            {
                nearest = current->value.averageGrade;
                needed = i;
            }
            current = current->prev;
        }

        return needed;
    }

    int Search(string name) // search for the first human being with the most similar name to this
    {
        int needed = 0;
        float maxProximity = -1;
        Node* current = head;

        for (int i = 0; i < size; i++)
        {
            float currentProximity = process(name, current->value.fullName);
            if (currentProximity > maxProximity)
            {
                maxProximity = currentProximity;
                needed = i;
            }

            current = current->prev;
        }

        return needed;
    }

    void InsertAfter(int index, Student student) // Insert element after the element with this index
    {
        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->prev;
        }
        Node* newNode = new Node(student);

        Node* bus = current->prev;
        current->prev = newNode;
        newNode->prev = bus;
        size++;
    }

    void DeleteElement(int index) // delete element with this index
    {
        if (size > 0)
        {
            if (index > 0 && index < size - 1)
            {
                Node* current = head;
                for (int i = 0; i < index - 1; i++)
                {
                    current = current->prev;
                }

                current->prev = current->prev->prev;
                size--;
            }
            else if (index == 0)
            {
                DeleteBeginning();
            }
            else
            {
                DeleteEnd();
            }
        }
        else
        {
            cout << "List is empty!!!";
        }
    }

    void DeleteElementWithName(string name) // delete human being with the most similar name to this
    {
        DeleteElement(Search(name));
    }

    void DeleteElementWithAverageGrade(float avgGrade) // delete human being with the most similar avarage grade to this
    {
        DeleteElement(Search(avgGrade));
    }
};

struct DoublyNode 
{
    Student value;
    DoublyNode* prev;
    DoublyNode* next;

    DoublyNode()
    {
        prev = NULL;
        next = NULL;
    }

    DoublyNode(Student student)
    {
        prev = NULL;
        next = NULL;
        value = student;
    }
};

class DoublyLinkedList {
private:
    DoublyNode* first; //Адрес первого элемента списка
    DoublyNode* last; //Адрес последнего элемента списка
    int size; //Количество элементов в списке

public:
    DoublyLinkedList()
    {
        last = NULL;
        first = NULL;
        size = 0;
    }

    int GetSize() // get size of the list
    {
        return size;
    }

    void AppendToBeginning(Student student) //добавление элемента в начало списка
    {
        DoublyNode* newitem = new DoublyNode(student);
        newitem->prev = NULL;
        if (first == NULL)
        {
            newitem->next = NULL;
            first = newitem;
            last = newitem;
        }
        else
        {
            first->prev = newitem;
            newitem->next = first;
            first = newitem;
        }
        size++;
    }

    void AppendToEnd(Student student) //добавление элемента в конец списка
    {
        DoublyNode* node = new DoublyNode(student);
        if (first == NULL)
        {
            first = node;
        }
        node->next = NULL;
        node->prev = last;
        if (last != NULL)
        {
            last->next = node;
        }
        last = node;
        size++;
    }

    void DeleteBeginning() // delete element at the beginning
    {
        if (size >= 1)
        {
            first = first->next;
            first->prev = NULL;
            size--;
        }
        else
        {
            cout << "List is Empty!!!";
        }
    }

    void DeleteEnd() // delete element at the end
    {
        if (size >= 1)
        {
            last = last->prev;
            last->next = NULL;
            size--;
        }
        else
        {
            cout << "List is Empty!!!";
        }
    }

    void Show() // show the whole list
    {
        DoublyNode* current = first;
        for (int i = 0; i < size; i++)
        {
            current->value.Show();
            cout << endl;
            current = current->next;
        }
    }

    void ShowElement(int index) // show element with this index
    {
        if (index < size || index >= 0)
        {
            DoublyNode* current = first;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            current->value.Show();
        }
        else
        {
            cout << "Index out of range!!!";
        }
    }

    int Search(float avgGrade) // search for the first human being with the most similar average grade to this
    {
        int needed = 0;
        float nearest = last->value.averageGrade;
        DoublyNode* current = first;

        for (int i = 0; i < size; i++)
        {
            if (abs(current->value.averageGrade - avgGrade) < abs(nearest - avgGrade))
            {
                nearest = current->value.averageGrade;
                needed = i;
            }
            current = current->next;
        }

        return needed;
    }

    int Search(string name) // search for the first human being with the most similar name to this
    {
        int needed = 0;
        float maxProximity = -1;
        DoublyNode* current = first;

        for (int i = 0; i < size; i++)
        {
            float currentProximity = process(name, current->value.fullName);
            if (currentProximity > maxProximity)
            {
                maxProximity = currentProximity;
                needed = i;
            }

            current = current->next;
        }

        return needed;
    }

    void InsertAfter(int index, Student student) // insert element after the element with this index
    {
        DoublyNode* current = first;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        DoublyNode* newNode = new DoublyNode(student);

        DoublyNode* afterCurrent = current->next;
        afterCurrent->prev = newNode;
        current->next = newNode;
        newNode->prev = current;
        newNode->next = afterCurrent;
        size++;
    }

    void DeleteElement(int index) // delete element with this index
    {
        if (size > 0)
        {
            if (index > 0 && index < size - 1)
            {
                DoublyNode* current = first;
                for (int i = 0; i < index - 1; i++)
                {
                    current = current->next;
                }

                current->next = current->next->next;
                current->next->prev = current;
                size--;
            }
            else if (index == 0)
            {
                DeleteBeginning();
            }
            else
            {
                DeleteEnd();
            }
        }
        else
        {
            cout << "List is empty!!!";
        }
    }

    void DeleteElementWithName(string name) // delete human being with the most similar name to this
    {
        DeleteElement(Search(name));
    }

    void DeleteElementWithAverageGrade(float avgGrade) // delete human being with the most similar avarage grade to this
    {
        DeleteElement(Search(avgGrade));
    }
};

int main()
{

    int g1[3] = { 2, 3, 4 };
    Student s1 = Student(false, "John", 3, g1);

    int g2[3] = { 5, 2, 3 };
    Student s2 = Student(false, "Annita", 3, g2);

    int g3[4] = { 1, 4, 5, 5 };
    Student s3 = Student(false, "Dorn", 4, g3);

    DoublyLinkedList list;
    list.AppendToEnd(s3);

    list.AppendToBeginning(s2);

    list.AppendToEnd(s1);

    cout << endl;
    cout << endl;
    cout << endl;

    list.Show();

    cout << endl;
    cout << endl;
    cout << endl;

    list.InsertAfter(1, s2);
    list.Show();

    cout << endl;
    cout << endl;
    cout << endl;
    
    list.DeleteElement(0);
    list.Show();

    cout << list.GetSize();
    cout << endl;
    cout << list.Search("Jo");
    cout << endl;
    cout << list.Search(5);

    cout << endl;
    cout << endl;
    cout << endl;

    list.DeleteElementWithAverageGrade(5);
    list.DeleteElementWithName("Jo");
    list.Show();

    SimplyLinkedList list1;
    list1.AppendToEnd(s3);

    list1.AppendToBeginning(s2);

    list1.AppendToEnd(s1);

    cout << endl;
    cout << endl;
    cout << endl;

    list1.Show();

    cout << endl;
    cout << endl;
    cout << endl;

    list1.InsertAfter(1, s2);
    list1.Show();

    cout << endl;
    cout << endl;
    cout << endl;

    list1.DeleteElement(0);
    list1.Show();

    cout << list1.GetSize();
    cout << endl;
    cout << list1.Search("Jo");
    cout << endl;
    cout << list1.Search(5);

    cout << endl;
    cout << endl;
    cout << endl;

    list1.DeleteElementWithAverageGrade(5);
    list1.DeleteElementWithName("Jo");
    list1.Show();
}
