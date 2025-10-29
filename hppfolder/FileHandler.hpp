#pragma once
#include <fstream>
#include "Struct.hpp"

struct Med;
struct LinkedList;

void loadFromFile(LinkedList &L);
void commitToFile(const LinkedList &L);
