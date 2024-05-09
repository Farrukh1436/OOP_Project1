#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<Windows.h>
#include<iomanip>



#include"classes.h"

using namespace std;





// ANSI escape codes for colors
#define COLOR_RESET     "\033[0m"

#define COLOR_BLACK     "\033[0;30m"
#define COLOR_RED       "\033[0;31m"
#define COLOR_GREEN     "\033[0;32m"
#define COLOR_YELLOW    "\033[0;33m"
#define COLOR_BLUE      "\033[0;34m"
#define COLOR_MAGENTA   "\033[0;35m"
#define COLOR_CYAN      "\033[0;36m"
#define COLOR_WHITE     "\033[0;37m"

#define COLOR_BRIGHT_BLACK    "\033[1;30m"
#define COLOR_BRIGHT_RED      "\033[1;31m"
#define COLOR_BRIGHT_GREEN    "\033[1;32m"
#define COLOR_BRIGHT_YELLOW   "\033[1;33m"
#define COLOR_BRIGHT_BLUE     "\033[1;34m"
#define COLOR_BRIGHT_MAGENTA  "\033[1;35m"
#define COLOR_BRIGHT_CYAN     "\033[1;36m"
#define COLOR_BRIGHT_WHITE    "\033[1;37m"


void log();
void s_page(const student  &s);
void p_page(const professor &p);


wstring s2ws(const string& s);
vector<user> readCSV(const string& filename);


void printCSV(const wstring& filename);


vector<student> read_students(const string& filename);
vector<professor> read_professor(const string& filename);
void modifyCSV(int choice, const wstring& filePath, const string& id);
bool deleteRecord(const wstring& filePath, const string& deleteID);
bool addRecordToCSV(const wstring& filePath);

//declarition of all functions
void home();

unsigned int choice;
string input;
void home() 
{
    do 
    {
        printf(COLOR_BRIGHT_BLUE "\n \t \t **Student Management System**"
            COLOR_BRIGHT_CYAN"\n \t \t 1.Login"
            "\n \t \t 2.Quit"
            "\n \t \t Write your choice:" COLOR_RESET);//home page

        string input_1;
        getline(cin, input_1);

        try 
        {
            choice = stoi(input_1);  // Attempt to convert input to an integer
        }
        catch (...) 
        {
            printf(COLOR_RED "Error: Invalid input. Please enter a number.\n" COLOR_RESET);
            continue;
        }

        if (choice < 1 || choice > 2) 
        {
            printf(COLOR_RED "Error: Invalid choice. Please enter a number between 1 and 2.\n" COLOR_RESET);
        }

    } while (choice < 1 || choice > 2);

    switch (choice) 
    {
    case 1:
        system("cls");//clearing screen
        log();
        break;
    case 2:
        exit(0);
        // Quit or exit program
        break;
    default:
        break;
    }
}

void log() 
{
    vector<user> users = readCSV("../Lists/Users/user_list.csv");
    //adding all information from file to users array
    string id_s, password_s;
l:
    printf(COLOR_BRIGHT_CYAN " \t \t If you want to go homepage just write 1");
    printf("\n \t \t Login:" COLOR_RESET);
    getline(cin,id_s);
    if (id_s == "1")
    {
        system("cls");
        home();
    }
    if (id_s[0] == 'u')
        id_s[0] = 'U'; //it  converts u to U letter automatically
    bool found = false;
    for (const auto& u : users) 
    {
        if (u.id == id_s)
        {
            found = true;
            password_s = u.password;
            //checking password from user input with file
            break;
        }
    }

    if (found) 
    {
        string password;
        //cin.ignore(); // Ignore the newline character left by previous input
p:
        printf(COLOR_BRIGHT_CYAN "\t \t Password:" COLOR_RESET);
        getline(cin, password);

        if (password == password_s)
        {
            printf(COLOR_GREEN "Login successful!\n" COLOR_RESET);
            for(int i=0;i<120;++i)
            printf(COLOR_BRIGHT_MAGENTA "*" COLOR_RESET );
            for (const auto &u : users)
            {
                if (id_s == u.id)
                {
                    if (u.user_type == "Student")
                    {
                        vector<student> students = read_students("../Lists/Students/List/students_list.csv");
                        //taking all information from studens.csv file to students array
                        for (const auto& s : students)
                        {
                            if (u.id == s.id)
                                //if user id from user input is found from file
                                //it enters student page automatically
                                s_page(s);
                        }

                    }
                    else if (u.user_type == "Professor")
                    {
                        vector<professor> professors = read_professor("../Lists/Professors/List/Professor_list.csv");
                        //taking all information from studens.csv file to students array
                        for (const auto& p : professors)
                        {
                            if (u.id == p.id)
                                //if user id from user input is found from file
                                //it enters student page automatically
                                p_page(p);
                        }
                    }
                }
                // Proceed with whatever you want to do after successful login
            }
        }
        else 
        {
            printf(COLOR_RED "Incorrect password.\n" COLOR_RESET);
            goto p;
            // Handle incorrect password case
        }
    }
    else 
    {
        printf(COLOR_RED"User not found.Enter valid id again\n" COLOR_RESET);
        goto l;
        // Handle user not found case
    }
}


void s_page(const student &s)
{
    do
    {
S:
        printf(COLOR_BRIGHT_CYAN
            "\n \t \t 1.Information about student"
            "\n \t \t 2.Data from last semester"
            "\n \t \t 3.Home-page"
            "\n \t \t 4.Quit"
            "\n \t \t Write your choice:" COLOR_RESET);
        string input;
        getline(cin, input);
        system("cls");
        try
        {
            choice = stoi(input);  // Attempt to convert input to an integer
        }
        catch (...)
        {
            printf(COLOR_RED "Error: Invalid input. Please enter a number.\n" COLOR_RESET);
            goto S;
        }

        if (choice < 1 || choice > 4)
        {
            printf(COLOR_RED "Error: Invalid choice. Please enter a number between 1 and 4.\n" COLOR_RESET);
            goto S;
        }
    } while (choice < 1 || choice > 4);

    string searchPath = "..\\Lists\\Students";//it is path to find specific user data
    wstring fullPath = s2ws(searchPath) +
        L"\\"+s2ws(s.id) + L"\\" + s2ws(s.id) + L".csv";

    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW(fullPath.c_str(), &findData);
   
    switch (choice)
    {
    case 1:
        printf(COLOR_BRIGHT_RED"\t \t Name:%s"
            "\n \t \t ID:%s"
            "\n \t \t Gender:%s"
            "\n \t \t Age:%d"
            "\n \t \t GPA:%.2f"
            "\n \t \t Group:%s"
            "\n \t \t Course level:%s", 
            s.name.c_str(),s.id.c_str(),s.gender.c_str(),
            s.age,s.gpa,s.group.c_str(),s.course_lvl.c_str());
        printf("\n");
        for (int i = 0; i < 120; ++i)
            printf(COLOR_BRIGHT_MAGENTA "*" COLOR_RESET);
        break;
    case 2:
       

        if (hFind != INVALID_HANDLE_VALUE)
        {
            
            FindClose(hFind);
            printCSV(fullPath);//printing all datas about user's 1semeter
        }
        else
        {
            printf(COLOR_RED);
            wcout << "File not found: " << fullPath;
            printf("\n" COLOR_RESET);
        }
        break;
    case 3:
        system("cls");
        home();
    case 4:
        exit(0);
    default:
        printf(COLOR_RED "Invalid input" COLOR_RESET);
        break;
    }
    s_page(s);
}


void p_page(const professor &p)
{
    do
    {
p:
        printf(COLOR_BRIGHT_CYAN "\n \t \t1.Information about Professor"
            "\n \t \t2.Information about students of course"
            "\n \t \t3.Editing student's data to course"
            "\n \t \t4.Deleting student's record from course"
            "\n \t \t5.Adding record to course"
            "\n \t \t6.Home Page"
            "\n \t \t7.Quit"
            "\n \t \tWrite your choice:" COLOR_RESET);
       
        getline(cin, input);
        cin.clear(); // Clear any error flags
        cin.sync();  // Clear the input buffer

        system("cls");
        try
        {
            choice = stoi(input);  // Attempt to convert input to an integer
        }
        catch (...)
        {
            printf(COLOR_RED "Error: Invalid input. Please enter a number.\n" COLOR_RESET);
            goto p;
        }

        if (choice < 1 || choice > 7)
        {
            printf(COLOR_RED "Error: Invalid choice. Please enter a number between 1 and 7.\n" COLOR_RESET);
            goto p;
        }
    } while (choice < 1 || choice > 7);
    string searchPath = "..\\Lists\\Professors"; // Path to find specific user data
    string sub;
        // Construct the full path for the CSV file based on the subject
        wstring fullPath;
        // Perform file search for the current subject
        WIN32_FIND_DATAW findData;
        HANDLE hFind;
        // Clear the console screen


        // Switch based on user choice
        bool check = true;
        bool deleted;
        bool success;
        string deleteID;
        string uid;
        string in;

        switch (choice)
        {
        case 1:
            printf(COLOR_BRIGHT_RED "\t \t Name:%s"
                "\n \t \t ID:%s"
                "\n \t \t Gender:%s"
                "\n \t \t Age:%d"
                "\n \t \t Subject:" ,
                p.name.c_str(), p.id.c_str(), p.gender.c_str(),
                p.age);
            for (const auto& subject : p.show_subjects())
            {
                cout<< subject<<(check == true ? "," : " ");
                check = false;
            }
            check = true;
            printf("\n");
            for (int i = 0; i < 120; ++i)
                printf(COLOR_BRIGHT_MAGENTA "*" COLOR_RESET);
            break;
        case 2:
            printf(COLOR_BRIGHT_CYAN "\n \t \tWhich subject do you want to see?"
            "\n \t \t");
            for (const auto& subject : p.show_subjects())
            {
                cout << subject << (check == true ? " or " : " ");
                check = false;
            }
            while(check != true)
            {
                printf(COLOR_BRIGHT_CYAN "\n \t \tWrite your subject name to see:" COLOR_RESET);
                getline(cin, sub);
                for (const auto& subject : p.show_subjects())
                {
                    if (sub == subject)
                        check = true;
                }
                if (check == false)
                    printf(COLOR_RED"\n \t \tInvalid INPUT Enter correct input!!" COLOR_RESET);
            }

            system("cls");
            do
            {
            lb:
                printf(COLOR_BRIGHT_CYAN "\n \t \tWhich section do you want to see?");

                printf("\n \t \t3.SECTION-3"
                    "\n \t \t4.SECTION-4"
                    "\n \t \t5.SECTION-5"
                    "\n \t \t6.SECTION-6"
                    "\n \t \tWrite your choice:" COLOR_RESET);

                getline(cin, in);
                system("cls");
                try
                {
                    choice = stoi(in);  // Attempt to convert input to an integer
                }
                catch (...)
                {
                    printf(COLOR_RED "Error: Invalid input. Please enter a number.\n" COLOR_RESET);
                    goto lb;
                }

                if (choice < 3 || choice > 6)
                {
                    printf(COLOR_RED "Error: Invalid choice. Please enter a number between 3 and 6.\n" COLOR_RESET);
                    goto lb;
                }
            } while (choice < 3|| choice > 6);

            fullPath = s2ws(searchPath) +
                L"\\" + s2ws(p.id) + L"\\" + s2ws(sub) + L"\\" + L"SECTION-" + s2ws(in) + L".csv";
            hFind = FindFirstFileW(fullPath.c_str(), &findData);


            if (hFind != INVALID_HANDLE_VALUE)
            {

                FindClose(hFind);
                printCSV(fullPath);//printing all datas about user's 1semeter
            }
            else
            {
                printf(COLOR_RED);
                wcout << "File not found: " << fullPath;
                printf("\n" COLOR_RESET);
            }
            for (int i = 0; i < 120; ++i)
                printf(COLOR_BRIGHT_MAGENTA "*" COLOR_RESET);
            break;
        case 3:
            printf(COLOR_BRIGHT_CYAN "\n \t \tWhich subject do you want to see?"
                "\n \t \t");
            for (const auto& subject : p.show_subjects())
            {
                cout << subject << (check == true ? " or " : " ");
                check = false;
            }
            while (check != true)
            {
                printf(COLOR_BRIGHT_CYAN "\n \t \tWrite your subject name to see:" COLOR_RESET);
                getline(cin, sub);
                for (const auto& subject : p.show_subjects())
                {
                    if (sub == subject)
                        check = true;
                }
                if (check == false)
                    printf(COLOR_RED"\n \t \tInvalid INPUT Enter correct input!!" COLOR_RESET);
            }
            system("cls");
            do
            {
            cb:
            printf(COLOR_BRIGHT_CYAN "\n \t \tWhich section do you want to see?");
            
             printf("\n \t \t3.SECTION-3"
                "\n \t \t4.SECTION-4"
                "\n \t \t5.SECTION-5"
                "\n \t \t6.SECTION-6"
                "\n \t \tWrite your choice:" COLOR_RESET);

            getline(cin, in);
            system("cls");
            try
            {
                choice = stoi(in);  // Attempt to convert input to an integer
            }
            catch (...)
            {
                printf(COLOR_RED "Error: Invalid input. Please enter a number.\n" COLOR_RESET);
                goto cb;
            }

            if (choice < 3 || choice > 6)
            {
                printf(COLOR_RED "Error: Invalid choice. Please enter a number between 3 and 6.\n" COLOR_RESET);
                goto cb;
            }
            } while (choice < 3 || choice > 6);

            fullPath = s2ws(searchPath) +
                L"\\" + s2ws(p.id) + L"\\" + s2ws(sub) + L"\\"+L"SECTION-"+s2ws(in) + L".csv";
            hFind = FindFirstFileW(fullPath.c_str(), &findData);

            do
        {
        d:
            printf(COLOR_BRIGHT_CYAN "\n \t \tEnter which id do you want to modify:" COLOR_RESET);
            getline(cin,uid);
            system("cls");
            if (uid[0] == 'u')
                uid[0] = 'U';
            printf(COLOR_BRIGHT_CYAN"\n \t \tWhich Parameters you want to change from %s", uid.c_str());
            printf("\n \t \t1.Mid-score"
                   "\n \t \t2.Finale-score"
                   "\n \t \t3.Grade"
                   "\n \t \t4.Absences"
                   "\n \t \tWrite your choice:" COLOR_RESET);
           
            getline(cin, in);
            system("cls");
            try
            {
                choice = stoi(in);  // Attempt to convert input to an integer
            }
            catch (...)
            {
                printf(COLOR_RED "Error: Invalid input. Please enter a number.\n" COLOR_RESET);
                goto d;
            }

            if (choice < 1 || choice > 4)
        {
                printf(COLOR_RED "Error: Invalid choice. Please enter a number between 1 and 4.\n" COLOR_RESET);
                goto d;
            }
        } while (choice < 1 || choice > 4);

        modifyCSV(choice, fullPath, uid);
            break;
        case 4:
            printf(COLOR_BRIGHT_CYAN "\n \t \tWhich subject do you want to delete in?"
                "\n \t \t");
            for (const auto& subject : p.show_subjects())
            {
                cout << subject << (check == true ? " or " : " ");
                check = false;
            }
            while (check != true)
            {
                printf(COLOR_BRIGHT_CYAN "\n \t \tWrite your subject name to delete:" COLOR_RESET);
                getline(cin, sub);
                for (const auto& subject : p.show_subjects())
                {
                    if (sub == subject)
                        check = true;
                }
                if (check == false)
                    printf(COLOR_RED"\n \t \tInvalid INPUT Enter correct input!!" COLOR_RESET);
            }  do
            {
            kb:
                system("cls");
                printf(COLOR_BRIGHT_CYAN "\n \t \tWhich section do you want to delete user from?");

                printf("\n \t \t3.SECTION-3"
                    "\n \t \t4.SECTION-4"
                    "\n \t \t5.SECTION-5"
                    "\n \t \t6.SECTION-6"
                    "\n \t \tWrite your choice:" COLOR_RESET);

                getline(cin, in);
                system("cls");
                try
                {
                    choice = stoi(in);  // Attempt to convert input to an integer
                }
                catch (...)
                {
                    printf(COLOR_RED "Error: Invalid input. Please enter a number.\n" COLOR_RESET);
                    goto kb;
                }

                if (choice < 3 || choice > 6)
                {
                    printf(COLOR_RED "Error: Invalid choice. Please enter a number between 3 and 6.\n" COLOR_RESET);
                    goto kb;
            }
            } while (choice < 3 || choice > 6);

            fullPath = s2ws(searchPath) +
                L"\\" + s2ws(p.id) + L"\\" + s2ws(sub) + L"\\" + L"SECTION-" + s2ws(in) + L".csv";
            hFind = FindFirstFileW(fullPath.c_str(), &findData);

            printf(COLOR_BRIGHT_CYAN "\n \t \tEnter the ID of the record you want to delete:" COLOR_RESET);
            getline(cin, deleteID);

            // Construct the full path for the CSV file based on the professor's ID and subject
            
            // Perform the deletion
            deleted = deleteRecord(fullPath, deleteID); // Assuming you have a function deleteRecord defined

            if (deleted)
            {
                printf(COLOR_GREEN "\n \t \tRecord deleted successfully.\n" COLOR_RESET);
            }
            else
            {
                printf(COLOR_RED "\n \t \tFailed to delete record.\n" COLOR_RESET);
            }
            break;
        case 5:
            printf(COLOR_BRIGHT_CYAN "\n \t \tWhich subject do you want to add  in?"
                "\n \t \t");
            for (const auto& subject : p.show_subjects())
            {
                cout << subject << (check == true ? " or " : " ");
                check = false;
            }
            while (check != true)
            {
                printf(COLOR_BRIGHT_CYAN "\n \t \tWrite your subject name to add record:" COLOR_RESET);
                getline(cin, sub);
                for (const auto& subject : p.show_subjects())
                {
                    if (sub == subject)
                        check = true;
                }
                if (check == false)
                    printf(COLOR_RED"\n \t \tInvalid INPUT Enter correct input!!" COLOR_RESET);
            } 
            do
            {
            fb:
                system("cls");
                printf(COLOR_BRIGHT_CYAN "\n \t \tWhich section do you want to add user for?");

                printf("\n \t \t3.SECTION-3"
                    "\n \t \t4.SECTION-4"
                    "\n \t \t5.SECTION-5"
                    "\n \t \t6.SECTION-6"
                    "\n \t \tWrite your choice:" COLOR_RESET);

                getline(cin, in);
                system("cls");
                try
                {
                    choice = stoi(in);  // Attempt to convert input to an integer
                }
                catch (...)
                {
                    printf(COLOR_RED "Error: Invalid input. Please enter a number.\n" COLOR_RESET);
                    goto fb;
                }

                if (choice < 3 || choice > 6)
                {
                    printf(COLOR_RED "Error: Invalid choice. Please enter a number between 3 and 6.\n" COLOR_RESET);
                    goto fb;
                }
            } while (choice < 3 || choice > 6);

            fullPath = s2ws(searchPath) +
                L"\\" + s2ws(p.id) + L"\\" + s2ws(sub) + L"\\" + L"SECTION-" + s2ws(in) + L".csv";
            hFind = FindFirstFileW(fullPath.c_str(), &findData);

            
            success = addRecordToCSV(fullPath);

            
            if(!success)
            {
                printf(COLOR_RED "\n \t \tFailed to add record.\n" COLOR_RESET);
            }
            break;
        case 6:
            home();
        case 7:
            exit(0);

        }
        // Clear the input buffer
        printf(COLOR_BRIGHT_BLUE"\n \t \tPress enter to continue:");
        cin.ignore(1337, '\n');

        cin.clear(); // Clear any error flags
        cin.sync();  // Clear the input buffer
        system("cls");
        p_page(p);
}

vector<user> readCSV(const string& filename)
{
    vector<user> users;
    ifstream file(filename);
    string line;

    // Skip header line if present
    getline(file, line);

    while (getline(file, line))
    {
        istringstream iss(line);
        string name, id, password, gender, user_type;
        unsigned short int age;

        if (getline(iss, name, ',') &&
            getline(iss, id, ',') &&
            getline(iss, password, ',') &&
            (iss >> age) &&
            (iss.ignore(1, ',')) &&
            getline(iss, gender, ',') &&
            getline(iss, user_type)) 
        {
            users.emplace_back(name, id, password, age, gender, user_type);
        }
    }
    file.close();
    return users;
}
vector<student> read_students(const string& filename)
{
    vector<student> students;
    ifstream file(filename);
    string line;

    if (!file.is_open()) 
    {
        printf(COLOR_RED);
        cerr << "Error opening file: " << filename << endl;
        
        return students; // Return empty vector on error
    }

    // Skip header line if present
    getline(file, line);

    while (getline(file, line))
    {
        istringstream iss(line);
        string name, id, gender, group, course_lvl;
        unsigned short int age;
        float gpa;

        if (getline(iss, name, ',') &&
            getline(iss, id, ',') &&
            (iss >> age) &&
            (iss.ignore(1, ',')) &&
            getline(iss, gender, ',') &&
            (iss >> gpa) &&
            (iss.ignore(1, ',')) &&
            getline(iss, group, ',') &&
            getline(iss, course_lvl)) 
        {
            students.emplace_back(name, id, age, gender, gpa, group, course_lvl);
        }
        else
        {
            printf(COLOR_RED);
            cerr << "Error parsing line: " << line;
            printf("\n" COLOR_RESET);
        }
    }
    file.close();
    return students;
}
wstring s2ws(const string& s) 
{
    int len;
    int slength = static_cast<int>(s.length()) + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, nullptr, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    wstring result(buf);
    delete[] buf;
    return result;
}
void printCSV(const wstring &filename)
{
    ifstream file(filename); // Open the CSV file
    string line;

    // Iterate over each line in the CSV file
    while (getline(file, line))
    {
        vector<string> row;
        stringstream ss(line);
        string cell;

        // Split each line into cells based on comma delimiter
        while (getline(ss, cell, ',')) 
        {
            row.push_back(cell);
        }

        // Print each cell in the row
        for (const auto& cell : row)
        {
            printf(COLOR_BRIGHT_YELLOW);
            cout << cell;
            for (int i = 0; i < 20 - cell.length(); ++i)
                printf(" ");//printing space in order to make a table
        }
        printf("\n" COLOR_RESET);
    }

    file.close(); // Close the file
}
vector<professor> read_professor(const string& filename)
{
    vector<professor> professors;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        printf(COLOR_RED);
        cerr << "Error opening file: " << filename;
        printf(COLOR_RESET);
        return professors; // Return empty vector on error
    }

    // Skip header line if present
    getline(file, line);

    while (getline(file, line))
    {
        istringstream iss(line);
        string name, id, gender, subjects;
        unsigned short int age;
        int number_subject;

        if (getline(iss, name, ',') &&
            getline(iss, id, ',') &&
            (iss >> age) &&
            (iss.ignore(1,','))&&
            (getline(iss,gender,',')) &&
            (iss >> number_subject))
        {
            // Create a professor object
            // Create a professor object
getline(iss, subjects, ',');
            professor p(name, id,"Null", age, gender, "Professor", number_subject);
            for (int i = 0; i < number_subject; ++i)
            {
                string subject;
                if (getline(iss, subject, ','))
                {
                    // Pass subject directly to the professor's get_subject function
                    p.get_subject(subject, i);
                }
            }
            // Add the professor object to the vector
            professors.push_back(p);
        }
        else
        {
            printf(COLOR_RED);
            cerr << "Error parsing line: " << line;
            printf("\n" COLOR_RESET);
        }
    }
    file.close();
    return professors;
}
bool deleteRecord(const wstring& filePath, const string& deleteID) 
{
    // Open the CSV file for reading
    wifstream file(filePath);
    if (!file.is_open())
    {
        printf(COLOR_RED"Error opening file: "),wcerr << filePath;
        printf("\n" COLOR_RESET);
        return false;
    }

    wstring line;
    vector<wstring> lines;
    bool idFound = false;  // Flag to indicate if the ID was found

    // Read each line of the file
    while (getline(file, line))
    {
        // Check if the line contains the deleteID
        if (line.find(s2ws(deleteID)) == wstring::npos) 
        {
            // If the line does not contain the deleteID, keep it
            lines.push_back(line);
        }
        else {
            idFound = true;  // Set the flag to true if the ID is found
        }
    }

    // Close the file
    file.close();

    if (!idFound) 
    {
       printf(COLOR_RED "Error: ID not found in the file.\n" COLOR_RESET);
        return false;  // Exit early if ID not found
    }

    // Reopen the file in write mode to overwrite it with updated content
    wofstream outFile(filePath);
    if (!outFile.is_open()) 
    {
        printf(COLOR_RED "Error opening file for writing") ,wcerr<< filePath;
        printf("\n", COLOR_RESET);
        return false;
    }

    // Rewrite the file without the deleted record
    for (const auto& l : lines)
    {
        outFile << l << endl;
    }

    // Close the file
    outFile.close();

    return true;
}
void modifyCSV(int choice, const wstring& filePath, const string& id)
{
    // Convert id to uppercase if it starts with lowercase 'u'
    string modifiedId = id;
    if (!id.empty() && id[0] == 'u')
    {
        modifiedId[0] = 'U';
    }

    // Open the CSV file for reading and writing
    wifstream file(filePath);
    if (!file.is_open())
    {
        printf(COLOR_RED "Error opening file: "), wcerr << filePath;
        printf("\n" COLOR_RESET);
        return;
    }

    wstring line;
    vector<wstring> lines;
    bool idFound = false;

    // Read each line of the file
    while (getline(file, line))
    {
        if (line.find(s2ws(modifiedId)) != wstring::npos)
        {
            idFound = true;
            vector<wstring> cells;
            wstringstream wss(line);
            wstring cell;

            while (getline(wss, cell, L','))
            {
                cells.push_back(cell);
            }

            if (choice == 1 && cells.size() >= 2)
            {
                printf(COLOR_BRIGHT_CYAN);
                wcout << L"Enter new Mid-score for ID " << s2ws(modifiedId) << L": ";
                printf(COLOR_RESET);
                wstring newMidScore;
                getline(wcin, newMidScore);

                try
                {
                    int midScore = stoi(newMidScore);
                    if (midScore > 30)
                    {
                        printf(COLOR_RED "Error: Mid-score should not exceed 30.\n" COLOR_RESET);
                        return;
            }
                    cells[1] = to_wstring(midScore);
                }
                catch (const std::invalid_argument&)
            {
                    printf(COLOR_RED "Error: Mid-score should be an integer.\n" COLOR_RESET);
                    return;
                }
            }
            else if (choice == 2 && cells.size() >= 3)
            {
                printf(COLOR_BRIGHT_CYAN);
                wcout << L"Enter new Final-score for ID " << s2ws(modifiedId) << L": ";
                wstring newFinalScore;
                printf(COLOR_RESET);
                getline(wcin, newFinalScore);

                try
                {
                    int finalScore = stoi(newFinalScore);
                    if (finalScore > 30)
                    {
                        printf(COLOR_RED "Error: Final-score should not exceed 30.\n" COLOR_RESET);
                        return;
            }
                    cells[2] = to_wstring(finalScore);
                }
                catch (const std::invalid_argument&)
            {
                    printf(COLOR_RED "Error: Final-score should be an integer.\n" COLOR_RESET);
                    return;
                }
            }
            else if (choice == 3 && cells.size() >= 4)
            {
                printf(COLOR_BRIGHT_CYAN);
                wcout << L"Enter new Grade for ID " << s2ws(modifiedId) << L": ";
                printf(COLOR_RESET);
                wstring newGrade;
                getline(wcin, newGrade);

                if (newGrade != L"B" && newGrade != L"B+" && newGrade != L"A" && newGrade != L"A+" && newGrade != L"A-")
                {
                    printf(COLOR_RED "Error: Invalid Grade entered.\n" COLOR_RESET);
                    return;
                }
                cells[3] = newGrade;
            }
            else if (choice == 4 && cells.size() >= 5)
            {
                printf(COLOR_BRIGHT_CYAN);
                wcout << L"Enter new Absences for ID " << s2ws(modifiedId) << L": ";
                printf(COLOR_RESET);
                wstring newAbsences;
                getline(wcin, newAbsences);

                try
                {
                    int absences = stoi(newAbsences);
                    cells[4] = to_wstring(absences);
                }
                catch (const std::invalid_argument&)
                {
                    printf(COLOR_RED "Error: Absences should be a number.\n" COLOR_RESET);
                    return;
                }
            }
            else
            {
                printf(COLOR_RED "Error: Not enough fields in the CSV line.\n" COLOR_RESET);
                return;
            }

            wstring modifiedLine;
            for (const auto& cell : cells)
            {
                modifiedLine += cell + L",";
            }
            modifiedLine.pop_back();
            lines.push_back(modifiedLine);
        }
        else
        {
            lines.push_back(line);
        }
    }

    file.close();

    if (!idFound)
    {
        printf(COLOR_RED "Error: ID not found in the file.\n" COLOR_RESET);
        return;
    }

    wofstream outFile(filePath);
    if (!outFile.is_open())
    {
        printf(COLOR_RED "Error opening file for writing"), wcerr << filePath;
        printf("\n", COLOR_RESET);
        return;
    }

    for (const auto& l : lines)
    {
        outFile << l << endl;
    }

    outFile.close();
}
bool addRecordToCSV(const wstring& filePath)
{
    // Open the CSV file for appending
    wofstream file(filePath, ios::app);
    if (!file.is_open())
    {
        printf(COLOR_RED "Error opening file for appending: "), wcerr << filePath;
        printf("\n" COLOR_RESET);
        return false;
    }

    // Ask the user for ID, Mid-score, Final-score, Grade, and Absence
    wstring id, midScore, finalScore, grade, absence;
    printf(COLOR_BRIGHT_CYAN);
    wcout << L"Enter ID: ";
    printf(COLOR_RESET);
    wcin >> id;

    // Convert id to uppercase if it starts with lowercase 'u'
    if (!id.empty() && id[0] == 'u')
    {
        id[0] = 'U';
    }

    printf(COLOR_BRIGHT_CYAN);
    wcout << L"Enter Mid-score: ";
    printf(COLOR_RESET);
    wcin >> midScore;

    // Validate Mid-score
    try
    {
        int mid = stoi(midScore);
        if (mid < 0 || mid > 30)
        {
            printf(COLOR_RED "Error: Mid-score should be between 0 and 30.\n" COLOR_RESET);
            file.close();
            return false;
        }
    }
    catch (const std::invalid_argument&)
    {
        printf(COLOR_RED "Error: Mid-score should be an integer.\n" COLOR_RESET);
        file.close();
        return false;
    }

    printf(COLOR_BRIGHT_CYAN);
    wcout << L"Enter Final-score: ";
    printf(COLOR_RESET);
    wcin >> finalScore;

    // Validate Final-score
    try
    {
        int final = stoi(finalScore);
        if (final < 0 || final > 30)
        {
            printf(COLOR_RED "Error: Final-score should be between 0 and 30.\n" COLOR_RESET);
            file.close();
            return false;
        }
    }
    catch (const std::invalid_argument&)
    {
        printf(COLOR_RED "Error: Final-score should be an integer.\n" COLOR_RESET);
        file.close();
        return false;
    }

    printf(COLOR_BRIGHT_CYAN);
    wcout << L"Enter Grade (e.g., B, B+, A, A+, A-): ";
    printf(COLOR_RESET);
    wcin >> grade;

    // Validate Grade
    if (grade != L"B" && grade != L"B+" && grade != L"A" && grade != L"A+" && grade != L"A-")
    {
        printf(COLOR_RED "Error: Invalid Grade entered.\n" COLOR_RESET);
        file.close();
        return false;
    }

    printf(COLOR_BRIGHT_CYAN);
    wcout << L"Enter Absences: ";
    printf(COLOR_RESET);
    wcin >> absence;

    // Validate Absences
    try
    {
        int abs = stoi(absence);
        if (abs < 0)
        {
            printf(COLOR_RED "Error: Absences should be a non-negative integer.\n" COLOR_RESET);
            file.close();
            return false;
        }
    }
    catch (const std::invalid_argument&)
    {
        printf(COLOR_RED "Error: Absences should be an integer.\n" COLOR_RESET);
        file.close();
        return false;
    }

    // Construct the CSV line from user input
    wstring csvLine = id + L"," + midScore + L"," + finalScore + L"," + grade + L"," + absence;

    // Append the CSV line to the file
    file << csvLine << endl;

    // Close the file
    file.close();

    printf(COLOR_GREEN "Record added successfully to the CSV file.\n" COLOR_RESET);
    return true;
}
