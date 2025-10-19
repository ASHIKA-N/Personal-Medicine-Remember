#pragma once
#include "DS.hpp"
#include <iostream>
#include <ctime>
#include "../hppfolder/Queue.hpp"
using namespace std;

int getTodayDayNumber();                 
Queue buildTodayQueue(const LinkedList &L);  
void reminderCheck(Queue &q);