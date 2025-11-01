#include <iostream>
#include <chrono>
#include "../hppfolder/DS.hpp"
#include "../hppfolder/Expiry.hpp"

using namespace std;
using namespace std::chrono;

void expiry(LinkedList *L, int e)
{
    if (!L || !L->head)
    {
        cout << "No medicines in list.\n";
        return;
    }

    Node *n = L->head;
    auto today = floor<days>(system_clock::now());
    year_month_day ymd{today};
    Date currentDate;
    currentDate.d = static_cast<unsigned>(ymd.day());
    currentDate.m = static_cast<unsigned>(ymd.month());
    currentDate.y = static_cast<int>(ymd.year());

    Stack dummy;
    bool none = true;
    while (n)
    {
        char opt;
        Node *next = n->next;
        int diff = n->a.exp - currentDate;

        if (diff <= 0)
        {
            none = false;
            cout << "\nMedicine expired\n";
            cout << "Name: " << n->a.name << " at ";
            n->a.t.disp();
            cout << endl;
            cout << "Do you need to refill (y/n): ";
            cin >> opt;
            if (opt == 'y' || opt == 'Y')
            {
                L->updqty(n->a.name);
            }
            else
            {
                cout << "No refill needed.\n";
                L->del(n->a.name, n->a.t, dummy);
            }
        }
        else if (diff <= e)
        {
            none = false;
            cout << "\nMedicine will expire in " << diff << " day(s):\n";
            cout << "Name: " << n->a.name << " at ";

            n->a.t.disp();
            cout << endl;
            cout << "Do you need to refill (y/n): ";
            cin >> opt;
            if (opt == 'y' || opt == 'Y')
            {
                L->updqty(n->a.name);
            }
        }

        n = next;
    }
    if (none)
        cout << "No medicines expiring within " << e << " days.\n";
    cout << "\nExpiry check complete.\n";
}