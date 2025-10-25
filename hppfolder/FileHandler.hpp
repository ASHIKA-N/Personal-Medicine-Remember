#pragma once
#include <fstream>
#include <string>

const std::string FILENAME = "med_data.txt";

class LinkedList;

void saveMedToFile(const Med &m);
void rewriteFile(const LinkedList &L);
void loadFromFile(LinkedList &L);
