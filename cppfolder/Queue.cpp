#include <iostream>
#include<ctime>
#include "../hppfolder/Queue.hpp" 
using namespace std;
int getTodayDayNumber() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int day = ltm->tm_wday;
    if (day == 0) return 7; 
    return day;
}
Queue buildTodayQueue(const LinkedList &L) {
    Queue todayQ;  
    Node *r = L.head;
    if (!r) {
        cout << "No medicines in schedule.\n";
        return todayQ;
    }
    int today = getTodayDayNumber();
    cout << "\nToday is day number: " << today << " (1=Mon..7=Sun)\n";
    while (r != nullptr) {
        bool takeToday = false;
        for (int d : r->a.dy) {
            if (d == today) {
                takeToday = true;
                break;
            }
        }
        if (takeToday) {
            todayQ.enqueue(r->a);
        }

        r = r->next;
    }
    cout << "\nToday's Medicines Enqueued: " << todayQ.size() << "\n";
    return todayQ;
}
void reminderCheck(Queue &todayQ) {
	cout << "\n--- Reminder Check ---\n";
    while (!todayQ.isEmpty()) {
        Med m = todayQ.peek();
        cout << "\nReminder: Time to take medicine " << m.name << " (" << m.dosage << ") at ";
        m.t.disp();

        char taken;
        cout << "\nMark as taken (y/n)? ";
        cin >> taken;
        if (taken == 'y' || taken == 'Y') {
            todayQ.dequeue();
            cout << "Medicine marked as taken and removed from queue.\n";
        } else {
            cout << "Reminder skipped for now.\n";
            break;
        }
    }

    if (todayQ.isEmpty()) {
        cout << "\nAll today's medicines are taken!\n";
    } else {
        cout << "\nPending medicines remaining: " << todayQ.size() << "\n";
    }
}
