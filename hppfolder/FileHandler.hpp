#pragma once
#include <fstream>
#include <string>

struct Med;
class LinkedList;

void saveMedToFile(const Med &m);
void rewriteFile(const LinkedList &L);
void loadFromFile(LinkedList &L);

const std::string FILENAME = "med_data.txt";
