#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class Student
{
private:
    int rollNo;
    string name;
    string course;
    float marks;

public:
    // Default constructor
    Student()
    {
        rollNo = 0;
        name = "";
        course = "";
        marks = 0.0;
    }

    // Parameterized constructor
    Student(int r, string n, string c, float m)
    {
        rollNo = r;
        name = n;
        course = c;
        marks = m;
    }

    // Getter function
    int getRollNo() const
    {
        return rollNo;
    }

    // Input student details
    void inputDetails()
    {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Course Name: ";
        getline(cin, course);

        cout << "Enter Marks (0-100): ";
        cin >> marks;

        while (cin.fail() || marks < 0 || marks > 100)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid marks. Enter marks between 0 and 100: ";
            cin >> marks;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Display student details
    void displayDetails() const
    {
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;
        cout << "\nCourse      : " << course;
        cout << "\nMarks       : " << marks << endl;
    }

    // Save student record to a file
    void saveToFile() const
    {
        ofstream file("students.txt", ios::app);

        if (file.is_open())
        {
            file << rollNo << '\n'
                 << name << '\n'
                 << course << '\n'
                 << marks << '\n';

            file.close();
        }
        else
        {
            cout << "Error opening file!\n";
        }
    }

    // Read and display all student records
    static void displayAll()
    {
        ifstream file("students.txt");

        if (!file.is_open())
        {
            cout << "\nNo student records found.\n";
            return;
        }

        int r;
        string n, c;
        float m;
        int count = 0;

        while (file >> r)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!getline(file, n) ||
                !getline(file, c) ||
                !(file >> m))
            {
                cout << "\nInvalid or incomplete record found.\n";
                break;
            }

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            Student s(r, n, c, m);

            cout << "\n----- Student Record -----";
            s.displayDetails();

            count++;
        }

        if (count == 0)
        {
            cout << "\nNo student records found.\n";
        }

        file.close();
    }

    // Search for a student
    static void searchStudent(int searchRoll)
    {
        ifstream file("students.txt");

        if (!file.is_open())
        {
            cout << "\nNo student records found.\n";
            return;
        }

        int r;
        string n, c;
        float m;
        bool found = false;

        while (file >> r)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!getline(file, n) ||
                !getline(file, c) ||
                !(file >> m))
            {
                break;
            }

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (r == searchRoll)
            {
                Student s(r, n, c, m);

                cout << "\nStudent Found!";
                s.displayDetails();

                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "\nStudent not found.\n";
        }

        file.close();
    }

    // Update student details
    static void updateStudent(int searchRoll)
    {
        ifstream file("students.txt");
        ofstream temp("temp.txt");

        if (!file.is_open())
        {
            cout << "\nNo student records found.\n";
            temp.close();
            return;
        }

        if (!temp.is_open())
        {
            cout << "\nUnable to create temporary file.\n";
            file.close();
            return;
        }

        int r;
        string n, c;
        float m;
        bool found = false;

        while (file >> r)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!getline(file, n) ||
                !getline(file, c) ||
                !(file >> m))
            {
                break;
            }

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (r == searchRoll)
            {
                Student s;
                cout << "\nEnter new details:\n";
                s.inputDetails();

                r = s.rollNo;
                n = s.name;
                c = s.course;
                m = s.marks;

                found = true;
            }

            temp << r << '\n'
                 << n << '\n'
                 << c << '\n'
                 << m << '\n';
        }

        file.close();
        temp.close();

        if (found)
        {
            if (remove("students.txt") == 0)
            {
                if (rename("temp.txt", "students.txt") == 0)
                {
                    cout << "\nStudent record updated successfully.\n";
                }
                else
                {
                    cout << "\nCould not rename temporary file.\n";
                }
            }
            else
            {
                cout << "\nCould not replace original file.\n";
            }
        }
        else
        {
            remove("temp.txt");
            cout << "\nStudent not found.\n";
        }
    }

    // Delete student record
    static void deleteStudent(int searchRoll)
    {
        ifstream file("students.txt");
        ofstream temp("temp.txt");

        if (!file.is_open())
        {
            cout << "\nNo student records found.\n";
            temp.close();
            return;
        }

        if (!temp.is_open())
        {
            cout << "\nUnable to create temporary file.\n";
            file.close();
            return;
        }

        int r;
        string n, c;
        float m;
        bool found = false;

        while (file >> r)
        {
            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (!getline(file, n) ||
                !getline(file, c) ||
                !(file >> m))
            {
                break;
            }

            file.ignore(numeric_limits<streamsize>::max(), '\n');

            if (r == searchRoll)
            {
                found = true;
                continue;
            }

            temp << r << '\n'
                 << n << '\n'
                 << c << '\n'
                 << m << '\n';
        }

        file.close();
        temp.close();

        if (found)
        {
            if (remove("students.txt") == 0)
            {
                if (rename("temp.txt", "students.txt") == 0)
                {
                    cout << "\nStudent deleted successfully.\n";
                }
                else
                {
                    cout << "\nCould not rename temporary file.\n";
                }
            }
            else
            {
                cout << "\nCould not replace original file.\n";
            }
        }
        else
        {
            remove("temp.txt");
            cout << "\nStudent not found.\n";
        }
    }
};

int main()
{
    int choice;
    int roll;

    do
    {
        cout << "\n====================================\n";
        cout << "     STUDENT MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPlease enter a valid number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            Student s;
            s.inputDetails();

            s.saveToFile();

            cout << "\nStudent added successfully!\n";
            break;
        }

        case 2:
            Student::displayAll();
            break;

        case 3:
            cout << "Enter Roll Number to Search: ";
            cin >> roll;

            if (!cin.fail())
                Student::searchStudent(roll);
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid roll number.\n";
            }
            break;

        case 4:
            cout << "Enter Roll Number to Update: ";
            cin >> roll;

            if (!cin.fail())
                Student::updateStudent(roll);
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid roll number.\n";
            }
            break;

        case 5:
            cout << "Enter Roll Number to Delete: ";
            cin >> roll;

            if (!cin.fail())
                Student::deleteStudent(roll);
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid roll number.\n";
            }
            break;

        case 6:
            cout << "\nThank you for using the system!\n";
            break;

        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}