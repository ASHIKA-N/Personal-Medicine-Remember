#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include <limits>
#include <algorithm>
#include "../hppfolder/Queue.hpp"

using namespace std;

int getTodayDayNumber()
{
    using namespace std::chrono;
    weekday wd{floor<days>(system_clock::now())};
    return wd.c_encoding() == 0 ? 7 : wd.c_encoding();
}

Queue buildTodayQueue(const LinkedList &L)
{
    Queue todayQ;
    if (!L.head)
    {
        cout << "No medicines in schedule.\n";
        return todayQ;
    }

    int today = getTodayDayNumber();
    cout << "\nToday is day number: " << today << " (1=Mon..7=Sun)\n";

    Node *r = L.head;
    while (r)
    {
        if (find(r->a.dy.begin(), r->a.dy.end(), today) != r->a.dy.end())
        {
            todayQ.enqueue(r->a);
        }
        r = r->next;
    }

    cout << "No of medicines to take today: " << todayQ.size() << "\n";
    return todayQ;
}

bool exitRequested()
{
    if (_kbhit())
    {
        char c = _getch();
        if (c == 'e' || c == 'E')
            return true;
    }
    return false;
}

void reminderCheck(Queue &todayQ, LinkedList &L)
{
    bool eFlag = false;

    while (!todayQ.empty() && !eFlag)
    {
        Med m = todayQ.peek();

        auto now = chrono::system_clock::now();
        time_t t_now = chrono::system_clock::to_time_t(now);
        tm *ltm = localtime(&t_now);
        int currHour = ltm->tm_hour;
        int currMin = ltm->tm_min;

        if (currHour > m.t.h || (currHour == m.t.h && currMin >= m.t.m))
        {
            cout << "\nReminder: Time to take medicine " << m.name
                 << " (" << m.dosage << ") at ";
            m.t.disp();

            cout << "\nYou can exit anytime by pressing 'e'.\n";
            char taken;
            while (true)
            {
                cout << "Mark as taken (y/n) or 'e' to exit: ";
                cin >> taken;
                taken = tolower(taken);
                if (taken == 'y' || taken == 'n' || taken == 'e')
                    break;
                cout << "Invalid choice. Please enter y, n, or e.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if (taken == 'y')
            {
                L.redqty(m.name, m.dosage);
                todayQ.dequeue();
                cout << "Medicine marked as taken.\n";
            }
            else if (taken == 'e')
            {
                eFlag = true;
                break;
            }
            else
            {
                cout << "Snoozed! Will remind again after 20 minutes. Press 'e' anytime to exit.\n";
                for (int minute = 0; minute < 20 && !eFlag; ++minute)
                {
                    for (int sec = 0; sec < 60; ++sec)
                    {
                        if (exitRequested())
                        {
                            cout << "\nExiting snooze early.\n";
                            eFlag = true;
                            break;
                        }
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                    if (!eFlag)
                        cout << (20 - minute - 1) << " minutes left...\n";
                }

                if (eFlag)
                    break;

                continue;
            }
        }
        else
        {
            cout << "\nNext medicine (" << m.name << ") at ";
            m.t.disp();
            cout << "\n(Press 'e' anytime to exit.)\n";

            for (int i = 0; i < 30 && !eFlag; ++i)
            {
                if (_kbhit())
                {
                    char c = _getch();
                    if (c == 'e' || c == 'E')
                    {
                        cout << "\nExit requested.\n";
                        eFlag = true;
                        break;
                    }
                }
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }

    if (!eFlag)
        cout << "\nAll today's medicines are taken!\n";
    else
        cout << "\nSession ended. " << todayQ.size()
             << " medicine(s) still remaining today.\n";
}
