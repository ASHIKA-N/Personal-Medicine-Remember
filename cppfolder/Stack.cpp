#include <iostream>
#include <algorithm>
using namespace std;
#include "../hppfolder/Stack.hpp"
#include "../hppfolder/DS.hpp"

void Undo(Stack &u, Stack &r, LinkedList &L) {
    if (u.empty()) {
        cout << "Nothing to undo.\n";
        return;
    }

    bool cont = true;
    char ch;

    while (!u.empty() && cont) {
        Action a = u.peek();
        u.pop();
        r.push(a);

        switch (a.act) {
            case 'i': { 
                Node *curr = L.head, *prev = nullptr;
                while (curr && !(curr->a == a.NV)) {
                    prev = curr;
                    curr = curr->next;
                }
                if (!curr) break;
                if (!prev) L.head = curr->next;
                else prev->next = curr->next;

                auto &vec = L.hash[curr->a.name];
                vec.erase(remove(vec.begin(), vec.end(), curr), vec.end());
                if (vec.empty()) L.hash.erase(curr->a.name);

                cout << "Undo insert → Deleted: " << curr->a.name << " at ";
                curr->a.t.disp();
                cout << endl;
                delete curr;
                break;
            }

            case 'd': { 
                Node *newNode = new Node;
                newNode->a = a.OV;
                newNode->next = nullptr;

                if (!L.head || newNode->a.t < L.head->a.t) {
                    newNode->next = L.head;
                    L.head = newNode;
                } else {
                    Node *curr = L.head;
                    while (curr->next && !(newNode->a.t < curr->next->a.t))
                        curr = curr->next;
                    newNode->next = curr->next;
                    curr->next = newNode;
                }

                L.hash[newNode->a.name].push_back(newNode);
                cout << "Undo delete → Restored: " << newNode->a.name << " at ";
                newNode->a.t.disp();
                cout << endl;
                break;
            }

            case 'a': { 
                Action temp = a;
                temp.act = 'd';
                Node *newNode = new Node;
                newNode->a = temp.OV;
                newNode->next = nullptr;

                if (!L.head || newNode->a.t < L.head->a.t) {
                    newNode->next = L.head;
                    L.head = newNode;
                } else {
                    Node *curr = L.head;
                    while (curr->next && !(newNode->a.t < curr->next->a.t))
                        curr = curr->next;
                    newNode->next = curr->next;
                    curr->next = newNode;
                }

                L.hash[newNode->a.name].push_back(newNode);
                cout << "Undo group delete → Restored: " << newNode->a.name << " at ";
                newNode->a.t.disp();
                cout << endl;
                break;
            }

            case 'u': { 
                Node *curr = L.head;
                while (curr) {
                    if (curr->a == a.NV) {
                        curr->a = a.OV;
                        break;
                    }
                    curr = curr->next;
                }
                cout << "Last alteration reverted.\n";
                break;
            }
        }

        cout << "Continue undoing? (y/n): ";
        cin >> ch;
        if (ch != 'y' && ch != 'Y') cont = false;
    }
}

void Redo(Stack &r, Stack &u, LinkedList &L) {
    if (r.empty()) {
        cout << "Nothing to redo.\n";
        return;
    }

    bool cont = true;
    char ch;

    while (!r.empty() && cont) {
        Action a = r.peek();
        r.pop();
        u.push(a);

        switch (a.act) {
            case 'i': { 
                Node *newNode = new Node;
                newNode->a = a.NV;
                newNode->next = nullptr;

                if (!L.head || newNode->a.t < L.head->a.t) {
                    newNode->next = L.head;
                    L.head = newNode;
                } else {
                    Node *curr = L.head;
                    while (curr->next && !(newNode->a.t < curr->next->a.t))
                        curr = curr->next;
                    newNode->next = curr->next;
                    curr->next = newNode;
                }

                L.hash[newNode->a.name].push_back(newNode);
                cout << "Redo insert → Inserted: " << newNode->a.name << " at ";
                newNode->a.t.disp();
                cout << endl;
                break;
            }

            case 'd': { 
                Node *curr = L.head, *prev = nullptr;
                while (curr && !(curr->a == a.OV)) {
                    prev = curr;
                    curr = curr->next;
                }
                if (!curr) break;
                if (!prev) L.head = curr->next;
                else prev->next = curr->next;

                auto &vec = L.hash[curr->a.name];
                vec.erase(remove(vec.begin(), vec.end(), curr), vec.end());
                if (vec.empty()) L.hash.erase(curr->a.name);

                cout << "Redo delete → Deleted: " << curr->a.name << " at ";
                curr->a.t.disp();
                cout << endl;
                delete curr;
                break;
            }

            case 'u': { 
                Node *curr = L.head;
                while (curr) {
                    if (curr->a == a.OV) {
                        curr->a = a.NV;
                        break;
                    }
                    curr = curr->next;
                }
                cout << "Last alteration reapplied.\n";
                break;
            }
        }

        cout << "Continue redoing? (y/n): ";
        cin >> ch;
        if (ch != 'y' && ch != 'Y') cont = false;
    }
}

