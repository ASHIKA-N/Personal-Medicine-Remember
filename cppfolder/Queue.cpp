#include <iostream>
#include<ctime>
#include "../hppfolder/DS.hpp" 
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

