#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include "../hppfolder/Queue.hpp"
#include "../hppfolder/DS.hpp"

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

    cout << "Today's medicines enqueued: " << todayQ.size() << "\n";
    return todayQ;
}

void reminderCheck(Queue &todayQ)

{
    while (!todayQ.empty())
    {
        Med m = todayQ.peek();

        auto now = chrono::system_clock::now();
        time_t t_now = chrono::system_clock::to_time_t(now);
        tm *ltm = localtime(&t_now);
        int currHour = ltm->tm_hour;
        int currMin = ltm->tm_min;

        // Check if it’s time for this medicine
        if (currHour > m.t.h || (currHour == m.t.h && currMin >= m.t.m))
        {
            cout << "\nReminder: Time to take medicine " << m.name
                 << " (" << m.dosage << ") at ";
            m.t.disp();

            char taken;
            cout << "\nMark as taken (y/n)? ";
            cin >> taken;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (taken == 'y' || taken == 'Y')
            {
                todayQ.dequeue();
                cout << "Medicine marked as taken.\n";
            }
            else
            {
                cout << "Skipped for now.\n";
            }
        }

        this_thread::sleep_for(chrono::seconds(30));
    }

    cout << "\nAll today's medicines are taken!\n";
}
