#pragma once
#include <fstream>
#include "Struct.hpp"

struct Med;
struct LinkedList;

void saveMedToFile(const Med &m);
void rewriteFile(const LinkedList &L);
void loadFromFile(LinkedList &L);
