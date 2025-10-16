#pragma once
#include "DS.hpp"
#include <iostream>
using namespace std;

void Undo(Stack &u, Stack &r, LinkedList &L);
void Redo(Stack &r, Stack &u, LinkedList &L);
