#include <iostream>
#include <limits>
#include "../hppfolder/FileHandler.hpp"
#include "../hppfolder/DS.hpp"
#include "../hppfolder/Expiry.hpp"
#include "../hppfolder/Queue.hpp"
#include "../hppfolder/Stack.hpp"

using namespace std;

void menu()
{
    cout << "\n=== Personal Medication Reminder ===\n";
    cout << "Choices\n";
    cout << "1. Insert New Med\n";
    cout << "2. Delete a Med by Name and Time\n";
    cout << "3. Delete all Meds of a Particular Name\n";
    cout << "4. Alter a Med\n";
    cout << "5. View Med Schedule\n";
    cout << "6. Search for a Med\n";
    cout << "7. Undo Last Operation\n";
    cout << "8. Redo Last Undone Operation\n";
    cout << "9. Exit\n";
}

int main()
{
    int ch;
    LinkedList L;
    Queue todayQueue;
    Stack undo, redo;

    while (1)
    {
        menu();
        cout << "Enter choice: ";
        cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (ch)
        {
        case 1:
            L.disp();
            break;

        case 2:
            if (!redo.empty())
                redo.clear();
            L.insert(undo);
            break;

        case 3:
        {
            if (!redo.empty())
                redo.clear();
            if (!L.head)
            {
                cout << "List is empty!\n";
                break;
            }
            string name;
            int h, m;
            cout << "Enter Name: ";
            getline(cin, name);
            if (!L.find(name))
            {
                cout << "No medicine found with that name.\n";
                break;
            }
            cout << "Enter Time (HH MM): ";
            cin >> h >> m;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Time t(h, m);
            L.del(name, t, undo);
            break;
        }

        case 4:
        {
            if (!redo.empty())
                redo.clear();
            if (!L.head)
            {
                cout << "List is empty!\n";
                break;
            }
            string name;
            cout << "Enter Name: ";
            getline(cin, name);
            if (!L.find(name))
            {
                cout << "No medicine found with that name.\n";
                break;
            }
            L.delAll(name, undo);
            break;
        }

        case 5:
            if (!redo.empty())
                redo.clear();
            L.altermed(undo);
            break;

        case 6:
        {
            string name;
            cout << "Enter Name to Search: ";
            getline(cin, name);
            L.search(name);
            break;
        }

        case 7:
            Undo(undo, redo, L);
            break;

        case 8:
            Redo(redo, undo, L);
            break;

        case 9:
        {
            int days;
            cout << "\n--- Expiry Check before Exit ---\n";
            cout << "Enter no. of days to remind before expiry: ";
            cin >> days;
            while (days < 0)
            {
                cout << "Cannot be negative. Enter again: ";
                cin >> days;
            }
            expiry(&L, days);
            Queue todayQ = buildTodayQueue(L);
            reminderCheck(todayQ);
            cout << "Session Complete\nExiting\n";
            return 0;
        }

        default:
            cout << "Invalid Choice, Try Again\n";
        }
    }
}
