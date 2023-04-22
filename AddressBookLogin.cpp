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
    file.close();

    file.open("users.txt", ios::in);

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

bool checkUserLogin(vector <User>& users, const string &login)
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

// Contact functions
int loadContactsFromFile(vector <Contact> &contacts, int loggedUserId)
{
    int lastContactId = 0;
    string line, field;
    Contact contact;
    ifstream file("contacts.txt", ios::app);
    file.close();

    file.open("contacts.txt", ios::in);

    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return lastContactId;
    }

    while (getline(file, line)) {
        istringstream iss(line);

        getline(iss, field, '|');
        contact.id = stoi(field);
        lastContactId = contact.id;

        getline(iss, field, '|');
        contact.userId = stoi(field);

        if (contact.userId != loggedUserId)
        {
            continue;
        }

        getline(iss, contact.firstName, '|');
        getline(iss, contact.lastName, '|');
        getline(iss, contact.phone, '|');
        getline(iss, contact.address, '|');
        getline(iss, contact.email, '|');

        contacts.push_back(contact);
    }

    file.close();
    return lastContactId;
}

void addContactToFile(const Contact &contact)
{
    ofstream file("contacts.txt", ios::app);

    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return;
    }

    file << contact.id << '|' << contact.userId << '|' << contact.firstName << '|' << contact.lastName << '|';
    file << contact.phone << '|' << contact.address << '|' << contact.email << '|' << endl;

    file.close();
}

int addContact(vector <Contact>& contacts, int lastContactId, int loggedUserId)
{
    Contact contact;

    contact.id = ++lastContactId;
    contact.userId = loggedUserId;

    titleMessage();

    cout << "Enter first name: ";
    contact.firstName = readLine();

    cout << "Enter last name: ";
    contact.lastName = readLine();

    cout << "Enter phone number: ";
    contact.phone = readLine();

    cout << "Enter e-mail: ";
    contact.email = readLine();

    cout << "Enter address: ";
    contact.address = readLine();

    contacts.push_back(contact);
    addContactToFile(contact);

    cout << "\nNew entry added!\n" << endl;
    system("pause");

    return lastContactId;
}

void readContact(const Contact contact)
{
    cout << "Contact name: " << contact.firstName << " " << contact.lastName << endl;
    cout << "Phone number: " << contact.phone << endl;
    cout << "Address: " << contact.address << endl;
    cout << "E-mail: " << contact.email << endl << endl;
}

void readAllContacts(vector <Contact>& contacts)
{
    for (Contact& contact : contacts)
    {
        readContact(contact);
    }

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
            lastContactId = loadContactsFromFile(contacts, loggedUserId);

            titleMessage();
            mainMenu();
            choice = readSign();

            switch (choice)
            {
            case '1':
                lastContactId = addContact(contacts, lastContactId, loggedUserId);
                break;
            case '2':
                // Search by firstName
                break;
            case '3':
                // Search by lastName
                break;
            case '4':
                readAllContacts(contacts);
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

