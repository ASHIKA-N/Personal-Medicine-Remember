#pragma once
#include "DS.hpp"
#include <iostream>
#include <ctime>
using namespace std;

int getTodayDayNumber();                 
Queue buildTodayQueue(const LinkedList &L);  
void reminderCheck(Queue &todayQ);           
