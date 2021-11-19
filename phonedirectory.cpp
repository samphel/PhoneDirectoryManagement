#include <bits/stdc++.h>
using namespace std;

struct TrieNode
{
    unordered_map<char, TrieNode*> child;
    bool isLast;
    TrieNode()
    {
        for (char i = 'a'; i <= 'z'; i++)
            child[i] = NULL;

        isLast = false;
    }
};

TrieNode *root = NULL;

void insert(string s)
{
    int len = s.length();

    TrieNode *itr = root;
    for (int i = 0; i < len; i++)
    {
        TrieNode *nextNode = itr->child[s[i]];
        if (nextNode == NULL)
        {
            nextNode = new TrieNode();

            itr->child[s[i]] = nextNode;
        }

        itr = nextNode;

        if (i == len - 1)
            itr->isLast = true;
    }
}

void deleteWord(string s)
{
    int len = s.length();

    TrieNode *itr = root;
    for (int i = 0; i < len; i++)
    {
        TrieNode *nextNode = itr->child[s[i]];

        itr = nextNode;

        if (i == len - 1)
            itr->isLast = false;
    }
}

long int contactNumberReturn(string nam)
{
    string name;
    long int number;
    fstream file;
    file.open("contactlist.txt", ios::in);
    if (file)
    {
        file >> name >> number;
        while (!file.eof())
        {
            if (nam == name)
            {
                return number;
            }
            file >> name >> number;
        }
        file.close();
    }
    return -1;
}

void displayContactsUtil(TrieNode *curNode, string str)
{
    if (curNode->isLast)
    {
        cout << str << "\t" << contactNumberReturn(str) << endl;
    }

    for (char i = 'a'; i <= 'z'; i++)
    {
        TrieNode *nextNode = curNode->child[i];
        if (nextNode != NULL)
            displayContactsUtil(nextNode, str + (char)i);
    }
}

void displayContacts(string str)
{
    TrieNode *prevNode = root;

    string prefix = "";
    int len = str.length();
    TrieNode *curNode;
    int i;
    for (i = 0; i < len; i++)
    {
        prefix += (char)str[i];

        char lastChar = prefix[i];

        if (prevNode->child[lastChar])
        {
            curNode = prevNode->child[lastChar];

            prevNode = curNode;
        }
        else
        {
            cout << "\nNo Results Found for " << str << "\n";
            return;
        }

    }
    if (curNode != nullptr)
    {
        cout << "\nSuggestions based on " << str << " are \n";
        displayContactsUtil(curNode, str);
    }
    else
        cout << "\nNo Results Found for " << str << "\n";
    for (; i < len; i++)
    {
        prefix += (char)str[i];
        cout << "\nNo Results Found for " << prefix << "\n";

    }
}

void insertIntoTrie(vector<string> c, int n)
{
    root = new TrieNode();

    for (int i = 0; i < n; i++)
        insert(c[i]);
}

void insertIntoTrie(string s)
{
    root = new TrieNode();

    insert(s);
}

class directory
{
    string name;
    long int number;

public:
    directory() {}
    void add();
    void search();
    void delt();
    void showAll();
};

void directory::add()
{
    system("clear");
    fstream file;
    int found = 0;
    long int no;
    string n;
    cout << "\n\n\t\tAdd  a new Contact";
    cout << "\n\nName : ";
    cin >> name;
    cout << "\n\nNumber : ";
    cin >> number;
    file.open("contactlist.txt", ios::in);
    if (!file)
    {
        file.open("contactlist.txt", ios::app | ios::out);
        file << name << " " << number << endl;
        insert(name);
        file.close();
    }
    else
    {
        file >> n >> no;
        while (!file.eof())
        {
            if (n == name)
            {
                found++;
            }
            file >> n >> no;
        }
        file.close();
        if (found == 1)
            directory::add();

        else
        {
            file.open("contactlist.txt", ios::app | ios::out);
            file << name << " " << number << endl;
            insert(name);
            file.close();
        }
    }
    cout << "\n\nContact Added Successfully";
}

void directory::search()
{
    system("clear");
    fstream file;
    string n;
    long int numb;
    cout << "\n\n\t\tSearch for a Contact";
    cout << "\n\nPlease Enter Name : ";
    cin >> n;
    displayContacts(n);
}

void directory::delt()
{
    system("clear");
    fstream file, file1;
    int found = 0;
    string n;
    cout << "\n\n\t\tDelete Contact";
    cout << "\n\nContact Name : ";
    cin >> n;
    file.open("contactlist.txt", ios::in);
    if (!file)
    {
        cout << "No Contacts Available";
    }
    else
    {
        deleteWord(n);
        file1.open("contactlist1.txt", ios::app | ios::out);
        file >> name >> number;
        while (!file.eof())
        {
            if (n == name)
            {
                cout << "Contact Details Deleted Successfully";
                found++;
            }
            else
            {
                file1 << name << " " << number << endl;
            }
            file >> name >> number;
        }
        file.close();
        file1.close();
        remove("contactlist.txt");
        rename("contactlist1.txt", "contactlist.txt");
        if (found == 0)
        {
            cout << "\n\nNo Contact Found";
        }
    }
}

void directory::showAll()
{
    fstream file;
    file.open("contactlist.txt", ios::in);
    cout << "\n\n============================\n";
    cout << "NAME\t\tNUMBER\n";
    cout << "============================\n";
    file >> name >> number;
    while (!file.eof())
    {
        cout << name << "\t\t" << number << "\n";
        file >> name >> number;
    }
    file.close();
}

void contactsAdder(vector<string> &c)
{
    fstream file;
    file.open("contactlist.txt", ios::in);
    string nam;
    long int num;
    if (file)
    {
        file >> nam >> num;
        while (!file.eof())
        {
            c.push_back(nam);
            file >> nam >> num;
        }
        file.close();
    }
}

int main()
{
    vector<string> contacts;
    contactsAdder(contacts);
    int size = contacts.size();
    insertIntoTrie(contacts, size);
    directory d;

    cout << "Hello,User !" << endl;

    int option;

    do
    {
        cout << "\nMain Menu" << endl;
        cout << "1.Search for a Contact.\n";
        cout << "2.Add a Contact.\n";
        cout << "3.Delete a Contact.\n";
        cout << "4.Show all Contacts.\n";
        cout << "5.Close.\n";
        cout << "Please Enter your choice :";
        cin >> option;
        switch (option)
        {
        case 1:
            d.search();
            break;
        case 2:
            d.add();
            break;
        case 3:
            d.delt();
            break;
        case 4:
            d.showAll();
            break;
        case 5:
            exit(0);
            break;
        default:
            cout << "\nInvalid ,Please Enter a valid number! ";
        }

    } while (option != 5);

    return 0;
}