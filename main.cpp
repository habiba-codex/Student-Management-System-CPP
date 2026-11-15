
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Student
{
    int rollNo;
    string name;
    float marks;
};

// Save student records
void saveStudents(const vector<Student>& students)
{
    ofstream file("students.txt");

    for (const Student &s : students)
    {
        file << s.rollNo << endl;
        file << s.name << endl;
        file << s.marks << endl;
    }

    file.close();
}

// Load student records
void loadStudents(vector<Student>& students)
{
    ifstream file("students.txt");
    Student s;

    while (file >> s.rollNo)
    {
        file.ignore();
        getline(file, s.name);
        file >> s.marks;
        file.ignore();

        students.push_back(s);
    }

    file.close();
}

int main()
{
    vector<Student> students;
    int choice;

    loadStudents(students);

    do
    {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. View Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Delete Student" << endl;
        cout << "6. Exit" << endl;

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            // ADD STUDENT
            case 1:
            {
                Student s;

                cout << "Enter Roll Number: ";
                cin >> s.rollNo;

                bool exists = false;

                for (const Student &st : students)
                {
                    if (st.rollNo == s.rollNo)
                    {
                        exists = true;
                        break;
                    }
                }

                if (exists)
                {
                    cout << "Roll Number Already Exists!" << endl;
                    break;
                }

                cout << "Enter Name: ";
                getline(cin >> ws, s.name);

                cout << "Enter Marks: ";
                cin >> s.marks;

                students.push_back(s);
                saveStudents(students);

                cout << "Student Added Successfully!" << endl;
                break;
            }

            // VIEW STUDENTS
            case 2:
            {
                if (students.empty())
                {
                    cout << "No Students Found!" << endl;
                }
                else
                {
                    for (const Student &s : students)
                    {
                        cout << "\nRoll No: " << s.rollNo;
                        cout << "\nName: " << s.name;
                        cout << "\nMarks: " << s.marks << endl;
                    }
                }

                break;
            }

            // SEARCH STUDENT
            case 3:
            {
                int roll;
                bool found = false;

                cout << "Enter Roll Number: ";
                cin >> roll;

                for (const Student &s : students)
                {
                    if (s.rollNo == roll)
                    {
                        cout << "\nStudent Found!" << endl;
                        cout << "Name: " << s.name << endl;
                        cout << "Marks: " << s.marks << endl;

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Student Not Found!" << endl;

                break;
            }

            // UPDATE STUDENT
            case 4:
            {
                int roll;
                bool found = false;

                cout << "Enter Roll Number: ";
                cin >> roll;

                for (Student &s : students)
                {
                    if (s.rollNo == roll)
                    {
                        cout << "Enter New Name: ";
                        getline(cin >> ws, s.name);

                        cout << "Enter New Marks: ";
                        cin >> s.marks;

                        saveStudents(students);

                        cout << "Record Updated Successfully!" << endl;

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Student Not Found!" << endl;

                break;
            }

            // DELETE STUDENT
            case 5:
            {
                int roll;
                bool found = false;

                cout << "Enter Roll Number: ";
                cin >> roll;

                for (int i = 0; i < students.size(); i++)
                {
                    if (students[i].rollNo == roll)
                    {
                        students.erase(students.begin() + i);

                        saveStudents(students);

                        cout << "Student Deleted Successfully!" << endl;

                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Student Not Found!" << endl;

                break;
            }

            // EXIT
            case 6:
            {
                saveStudents(students);
                cout << "Data Saved. Exiting Program..." << endl;
                break;
            }

            default:
                cout << "Invalid Choice! Try Again." << endl;
        }

    } while (choice != 6);

    return 0;
}
