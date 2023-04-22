#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

// Structs
struct User
{
    int id = 0;
    string login, password;
};

struct Contact
{
    int id = 0, userId = 0;
    string firstName, lastName, phone, address, email;
};

// Auxilary functions
string readLine()
{
    string input;
    getline(cin, input);
    return input;
}

char readSign()
{
    char sign;
    string input;
    
    while (true)
    {
        input = readLine();

        if (input.length() == 1)
        {
            sign = input[0];
            break;
        }
        cout << "This is not a single sign. Try again." << endl;
    }
    return sign;
}

int readInt()
{
    int number;
    string input;

    while (true)
    {
        input = readLine();

        stringstream myStream(input);
        if (myStream >> number)
        {
            break;
        }
            
        cout << "This is not a number. Try again." << endl;
    }
    return number;
}

// Menus
void titleMessage()
{
    system("cls");
    cout << "~~~~~~ ADDRESS BOOK ~~~~~~" << endl;
}

void loginMenu()
{
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
}

void mainMenu()
{
    cout << "1. Add contact" << endl;
    cout << "2. Search contact by first name" << endl;
    cout << "3. Search contact by last name" << endl;
    cout << "4. Show all contacts" << endl;
    cout << "5. Edit contact" << endl;
    cout << "6. Remove contact" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "9. Change user's password" << endl;
    cout << "0. Log out" << endl;
}

void goodbyeMessage()
{
    cout << "See you next time User!" << endl;
}

// User functions
void loadUsersFromFile(vector <User>& users)
{
    string line, field;
    User user;
    ifstream file("users.txt", ios::app);

    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return;
    }

    while (getline(file, line)) {
        istringstream iss(line);

        getline(iss, field, '|');
        user.id = stoi(field);

        getline(iss, user.login, '|');
        getline(iss, user.password, '|');

        users.push_back(user);
    }

    file.close();
}

int loginUser(vector <User> &users)
{
    string login, password;

    titleMessage();
    cout << "Enter login: ";
    login = readLine();

    for (User &user : users)
    {
        if (user.login == login)
        {
            for (int i = 0; i < 3; ++i)
            {
                cout << "Enter password: ";
                password = readLine();

                if (user.password == password)
                {
                    cout << "User logged in." << endl;
                    system("pause");
                    return user.id;
                }

                cout << "Password incorrect. You have " << 2 - i << " trials left." << endl;

                if (i == 2)
                {
                    cout << "You tried to login three times. You will be redirected to main menu." << endl;
                    system("pause");
                    return 0;
                }
            }
        }
    }

    cout << "Login incorrect. Try again." << endl;
    system("pause");

    return 0;
}

bool checkUserLogin(vector <User>& users, string login)
{
    for (User& user : users)
    {
        if (user.login == login)
        {
            cout << "\nUsername already exist. Choose another username: " << endl;
            system("pause");
            return true;
        }
    }
    return false;
}

void addUserToFile(User user)
{
    ofstream file("users.txt", ios::app);

    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return;
    }

    file << user.id << '|' << user.login << '|' << user.password << '|' << endl;

    file.close();
}

void registerUser(vector <User>& users)
{
    bool loginExists = true;
    User user;
    user.id = users.empty() ? 1 : users.back().id + 1;

    titleMessage();
    
    while (loginExists)
    {
        cout << "Enter your username: ";
        user.login = readLine();

        loginExists = checkUserLogin(users, user.login);
    }
    
    cout << "Enter your password: ";
    user.password = readLine();

    users.push_back(user);
    addUserToFile(user);

    cout << "\nUser registered!\n" << endl;
    system("pause");
}

int main()
{
    bool menuFlag = true;
    char choice;
    int loggedUserId = 0, lastContactId = 0;
    vector <User> users;
    vector <Contact> contacts;

    loadUsersFromFile(users);

    while(menuFlag)
    {
        titleMessage();
        loginMenu();
        choice = readSign();

        switch (choice)
        {
        case '1':
            loggedUserId = loginUser(users);
            break;
        case '2':
            registerUser(users);
            break;
        case '3':
            goodbyeMessage();
            menuFlag = false;
            break;
        default:
            cout << "There is no such option. Try again." << endl;
            system("pause");
        }

        while (loggedUserId)
        {
            titleMessage();
            mainMenu();
            choice = readSign();

            switch (choice)
            {
            case '1':
                // addContact
                break;
            case '2':
                // Search by firstName
                break;
            case '3':
                // Search by lastName
                break;
            case '0':
                contacts.clear();
                loggedUserId = 0;
                break;
            default:
                cout << "There is no such option. Try again." << endl;
                system("pause");
            }        
        }
    }
    return 0;
}

