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
                string name = a.NV.name;
                Time t = a.NV.t;
                Node *curr = L.head, *prev = nullptr;
                while (curr && !(curr->a.name == name && curr->a.t == t)) {
                    prev = curr;
                    curr = curr->next;
                }
                if (!curr) break;
                if (!prev) L.head = curr->next;
                else prev->next = curr->next;

                auto &vec = L.hash[name];
                vec.erase(remove(vec.begin(), vec.end(), curr), vec.end());
                if (vec.empty()) L.hash.erase(name);
                delete curr;

                cout << "Undo insert → Deleted: " << name << " at "; t.disp(); cout << endl;
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
                cout << "Undo delete → Inserted back: " << newNode->a.name << " at ";
                newNode->a.t.disp(); cout << endl;
                break;
            }

            case 'a': {
                r.pop();
                a.act='d';
                r.push(a);
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
                cout << "Last deleted node restored.\n";

                if(!u.empty() && u.peek().act!='a') break;

                char o;
                cout << "Group deletion detected. Restore all? (y for all): ";
                cin >> o;
                if (o == 'y' || o == 'Y') {
                    while (!u.empty() && u.peek().act == 'a') {
                        Action x = u.peek();
                        u.pop();
                        r.push(x);

                        Node *newNode = new Node;
                        newNode->a = x.OV;
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
                    }
                    cout << "Multiple deleted nodes restored.\n";
                }
                break;
            }

            case 'u': {
                Node *curr = L.head;
                while (curr) {
                    if (curr->a.name == a.NV.name && curr->a.t == a.NV.t) {
                        curr->a = a.OV;
                        break;
                    }
                    curr = curr->next;
                }
                cout << "Last alteration reverted.\n";

                if(!u.empty() && u.peek().act!='u') break;

                char o;
                cout << "Detected alterations. Undo all? (y for all): ";
                cin >> o;
                if (o == 'y' || o == 'Y') {
                    while (!u.empty() && u.peek().act == 'u') {
                        Action x = u.peek();
                        u.pop();
                        r.push(x);

                        Node *c = L.head;
                        while (c) {
                            if (c->a.name == x.NV.name && c->a.t == x.NV.t) {
                                c->a = x.OV;
                                break;
                            }
                            c = c->next;
                        }
                    }
                    cout << "All alterations reverted.\n";
                }
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
                newNode->a.t.disp(); cout << endl;
                break;
            }

            case 'd': {
                Node *curr = L.head, *prev = nullptr;
                while (curr && !(curr->a.name == a.OV.name && curr->a.t == a.OV.t)) {
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
                curr->a.t.disp(); cout << endl;
                delete curr;
                break;
            }

            case 'u': {
                Node *curr = L.head;
                while (curr) {
                    if (curr->a.name == a.OV.name && curr->a.t == a.OV.t) {
                        curr->a = a.NV;
                        break;
                    }
                    curr = curr->next;
                }

                cout << "Last alteration reapplied.\n";

                if (!r.empty() && r.peek().act != 'u') break;

                char o;
                cout << "Detected consecutive alterations. Redo all? (y for all): ";
                cin >> o;
                if (o == 'y' || o == 'Y') {
                    while (!r.empty() && r.peek().act == 'u') {
                        Action x = r.peek();
                        r.pop();
                        u.push(x);

                        Node *c = L.head;
                        while (c) {
                            if (c->a.name == x.OV.name && c->a.t == x.OV.t) {
                                c->a = x.NV;
                                break;
                            }
                            c = c->next;
                        }
                    }
                    cout << "All alterations reapplied.\n";
                }
                break;
            }
        }

        cout << "Continue redoing? (y/n): ";
        cin >> ch;
        if (ch != 'y' && ch != 'Y') cont = false;
    }
}
