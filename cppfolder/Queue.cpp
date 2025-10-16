#include <iostream>
#include <ctime>
#include "../hppfolder/Queue.hpp"
#include "../hppfolder/DS.hpp"

using namespace std;

int getTodayDayNumber() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int day = ltm->tm_wday;
    return day == 0 ? 7 : day; // Sunday = 7
}

Queue buildTodayQueue(const LinkedList &L) {
    Queue todayQ;
    if (!L.head) {
        cout << "No medicines in schedule.\n";
        return todayQ;
    }

    int today = getTodayDayNumber();
    cout << "\nToday is day number: " << today << " (1=Mon..7=Sun)\n";

    Node* r = L.head;
    while (r) {
        if (find(r->a.dy.begin(), r->a.dy.end(), today) != r->a.dy.end()) {
            todayQ.enqueue(r->a);
        }
        r = r->next;
    }

    cout << "Today's medicines enqueued: " << todayQ.size() << "\n";
    return todayQ;
}

void reminderCheck(Queue &todayQ) {
    cout << "\n--- Reminder Check ---\n";

    while (!todayQ.empty()) {
        Med m = todayQ.peek();
        cout << "\nReminder: Time to take medicine " << m.name << " (" << m.dosage << ") at ";
        m.t.disp();

        char taken;
        cout << "\nMark as taken (y/n)? ";
        cin >> taken;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (taken == 'y' || taken == 'Y') {
            todayQ.dequeue();
            cout << "Medicine marked as taken and removed from queue.\n";
        } else {
            cout << "Reminder skipped for now.\n";
            break;
        }
    }

    if (todayQ.empty())
        cout << "\nAll today's medicines are taken!\n";
    else
        cout << "\nPending medicines remaining: " << todayQ.size() << "\n";
}
