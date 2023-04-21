#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Structs
struct User
{
    int id;
    string login, password;
};

struct Contact
{
    int id, userId;
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

int loginUser()
{
    return 1;
}

void registerUser()
{

}

int main()
{
    bool menuFlag = true;
    char choice;
    int loggedUserId = 0, lastContactId = 0;
    vector <User> users;
    vector <Contact> contacts;

    while(menuFlag)
    {
        titleMessage();
        loginMenu();
        choice = readSign();

        switch (choice)
        {
        case '1':
            loggedUserId = loginUser();
            break;
        case '2':
            registerUser();
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

