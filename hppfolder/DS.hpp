#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Struct.hpp"
#include "FileHandler.hpp"

using namespace std;

class Stack
{
    vector<Action> a;

public:
    Stack(int s = 0)
    {
        if (s > 0)
            a.reserve(s);
    }

    void push(const Action &v) { a.push_back(v); }

    Action pop()
    {
        if (empty())
        {
            cout << "Stack Underflow\n";
            return Action();
        }
        Action v = a.back();
        a.pop_back();
        return v;
    }

    Action peek()
    {
        if (empty())
        {
            cout << "Stack Underflow\n";
            return Action();
        }
        return a.back();
    }

    bool empty() const { return a.empty(); }
    int size() const { return a.size(); }
    void clear() { a.clear(); }
};

class Queue
{
    vector<Med> a;

public:
    Queue(int s = 0)
    {
        if (s > 0)
            a.reserve(s);
    }

    void enqueue(const Med &v) { a.push_back(v); }

    Med dequeue()
    {
        if (empty())
        {
            cout << "Queue Underflow\n";
            return Med();
        }
        Med v = a.front();
        a.erase(a.begin());
        return v;
    }

    Med peek()
    {
        if (empty())
        {
            cout << "Queue Underflow\n";
            return Med();
        }
        return a.front();
    }

    bool empty() const { return a.empty(); }
    int size() const { return a.size(); }
};

struct Node
{
    Med a;
    Node *next;
};

struct PairHash
{
    size_t operator()(const pair<string, string> &p) const noexcept
    {
        return hash<string>()(p.first) ^ (hash<string>()(p.second) << 1);
    }
};

struct LinkedList
{
    Node *head;
    unordered_map<string, vector<Node *>> hash;

    unordered_map<pair<string, string>, int, PairHash> qty;

    LinkedList() : head(nullptr) {}

    ~LinkedList()
    {
        Node *curr = head;
        while (curr)
        {
            Node *tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        hash.clear();
        qty.clear();
        head = nullptr;
    }

    void insert(Stack &u)
    {
        Action a;
        a.act = 'i';
        Node *t = new Node;

        cout << "Enter Name: ";
        getline(cin, t->a.name);
        cout << "Enter Dosage: ";
        getline(cin, t->a.dosage);
        int q;
        cout << "Enter Quantity: ";
        cin >> q;
        a.qb = q;
        cout << "Time (HH MM): ";
        cin >> t->a.t.h >> t->a.t.m;

        cout << "Expiry Date (DD MM YYYY): ";
        cin >> t->a.exp.d >> t->a.exp.m >> t->a.exp.y;

        int c;
        cout << "Which days to take?\n1.certain days\n2.daily\n";
        cin >> c;

        t->a.dy.clear();
        if (c == 1)
        {
            char o;
            cout << "It goes as 1-Monday ... 7-Sunday\n";
            for (int i = 1; i <= 7; i++)
            {
                cout << "Day " << i << "? (y/n): ";
                cin >> o;
                if (o == 'y' || o == 'Y')
                    t->a.dy.push_back(i);
            }
        }
        else
        {
            for (int i = 1; i <= 7; i++)
                t->a.dy.push_back(i);
        }

        t->next = nullptr;
        if (!head || t->a.t < head->a.t)
        {
            t->next = head;
            head = t;
        }
        else
        {
            Node *r = head;
            while (r->next && !(t->a.t < r->next->a.t))
                r = r->next;
            t->next = r->next;
            r->next = t;
        }

        hash[t->a.name].push_back(t);
        qty[{t->a.name, t->a.dosage}] = q;
        a.NV = t->a;
        u.push(a);
        cout << "Medicine added successfully!\n";
        saveMedToFile(t->a, q);
    }

    void disp()
    {
        if (!head)
        {
            cout << "No medicines in the list.\n";
            return;
        }
        Node *r = head;
        while (r)
        {
            r->a.disp();
            auto key = make_pair(r->a.name, r->a.dosage);
            if (qty.find(key) != qty.end())
                cout << "Quantity: " << qty[key] << endl;
            r = r->next;
        }
    }

    void del(const string &medName, const Time &t, Stack &u)
    {
        Action a;
        a.act = 'd';

        if (head->a.name == medName && t == head->a.t)
        {
            Node *temp = head;
            head = head->next;
            a.OV = temp->a;
            a.qb = qty[{temp->a.name, temp->a.dosage}];
            auto &vec = hash[temp->a.name];
            vec.erase(remove(vec.begin(), vec.end(), temp), vec.end());
            if (vec.empty())
                hash.erase(temp->a.name);
            bool stillExists = false;
            for (Node *n : hash[temp->a.name])
            {
                if (n->a.dosage == temp->a.dosage)
                {
                    stillExists = true;
                    break;
                }
            }
            if (!stillExists)
                qty.erase({temp->a.name, temp->a.dosage});
            delete temp;
            cout << medName << " at ";
            t.disp();
            cout << " deleted.\n";
            u.push(a);
            return;
        }

        Node *r = head;
        while (r->next && !(r->next->a.name == medName && t == r->next->a.t))
            r = r->next;

        if (r->next)
        {
            Node *temp = r->next;
            r->next = temp->next;
            a.OV = temp->a;
            a.qb = qty[{temp->a.name, temp->a.dosage}];
            auto &vec = hash[temp->a.name];
            vec.erase(remove(vec.begin(), vec.end(), temp), vec.end());
            if (vec.empty())
                hash.erase(temp->a.name);
            bool stillExists = false;
            for (Node *n : hash[temp->a.name])
            {
                if (n->a.dosage == temp->a.dosage)
                {
                    stillExists = true;
                    break;
                }
            }
            if (!stillExists)
                qty.erase({temp->a.name, temp->a.dosage});
            delete temp;
            cout << medName << " at ";
            t.disp();
            cout << " deleted.\n";
            u.push(a);
            rewriteFile(*this);
            return;
        }
        else
        {
            cout << medName << " at ";
            t.disp();
            cout << " not found.\n";
        }
    }

    void delAll(const string &medName, Stack &u)
    {
        Action c;
        c.act = 'a';
        bool found = false;

        while (head && head->a.name == medName)
        {
            found = true;
            Node *temp = head;
            head = head->next;
            c.OV = temp->a;
            c.qb = qty[{temp->a.name, temp->a.dosage}];
            u.push(c);
            delete temp;
        }

        Node *r = head;
        while (r && r->next)
        {
            if (r->next->a.name == medName)
            {
                found = true;
                Node *temp = r->next;
                r->next = temp->next;
                c.OV = temp->a;
                c.qb = qty[{temp->a.name, temp->a.dosage}];
                u.push(c);
                delete temp;
            }
            else
            {
                r = r->next;
            }
        }

        hash.erase(medName);
        for (auto it = qty.begin(); it != qty.end();)
        {
            if (it->first.first == medName)
                it = qty.erase(it);
            else
                ++it;
        }

        if (found)
        {
            cout << "All medicines named \"" << medName << "\" deleted successfully.\n";
            rewriteFile(*this);
        }
        else
            cout << "No medicine named \"" << medName << "\" found.\n";
    }

    void search(const string &name)
    {
        if (hash.find(name) == hash.end())
        {
            cout << "No medicine named \"" << name << "\" found.\n";
            return;
        }
        for (Node *n : hash[name])
        {
            cout << "\nFound\n";
            n->a.disp();
        }
    }

    bool find(const string &name)
    {
        return hash.find(name) != hash.end();
    }

    void altermed(Stack &u)
    {
        Action c;
        c.act = 'u';
        Node *r = head;
        while (r)
        {
            r->a.disp();
            auto key = make_pair(r->a.name, r->a.dosage);
            if (qty.find(key) != qty.end())
                cout << "Quantity: " << qty[key] << endl;
            else
                cout << "Quantity: (not set)\n";
            char op;
            cout << "Do you want to change any details? (y/n): ";
            cin >> op;
            cin.ignore();

            if (op != 'y' && op != 'Y')
            {
                r = r->next;
                continue;
            }

            c.OV = r->a;

            cout << "Change medicine name? (y/n): ";
            cin >> op;
            cin.ignore();
            if (op == 'y' || op == 'Y')
            {
                auto &oldVec = hash[c.OV.name];
                oldVec.erase(remove(oldVec.begin(), oldVec.end(), r), oldVec.end());
                if (oldVec.empty())
                    hash.erase(c.OV.name);
                cout << "Enter new name: ";
                getline(cin, r->a.name);
                hash[r->a.name].push_back(r);
            }

            cout << "Change time? (y/n): ";
            cin >> op;
            if (op == 'y' || op == 'Y')
            {
                cout << "Enter hour and min: ";
                cin >> r->a.t.h >> r->a.t.m;
            }

            cout << "Change dosage? (y/n): ";
            cin >> op;
            cin.ignore();
            if (op == 'y' || op == 'Y')
            {
                cout << "Enter dosage: ";
                getline(cin, r->a.dosage);
            }

            cout << "Change days? (y/n): ";
            cin >> op;
            if (op == 'y' || op == 'Y')
            {
                r->a.dy.clear();
                int c;
                cout << "1.Certain days 2.Daily: ";
                cin >> c;
                if (c == 1)
                {
                    char o;
                    for (int i = 1; i <= 7; i++)
                    {
                        cout << "Day " << i << "? (y/n): ";
                        cin >> o;
                        if (o == 'y' || o == 'Y')
                            r->a.dy.push_back(i);
                    }
                }
                else
                {
                    for (int i = 1; i <= 7; i++)
                        r->a.dy.push_back(i);
                }
            }

            cout << "Change quantity? (y/n): ";
            cin >> op;
            if (op == 'y' || op == 'Y')
            {
                int newQty;
                cout << "Enter new quantity: ";
                cin >> newQty;
                qty[{r->a.name, r->a.dosage}] = newQty;
            }

            cout << "Change expiry date? (y/n): ";
            cin >> op;
            if (op == 'y' || op == 'Y')
            {
                int d, m, y;
                cout << "Day Month Year: ";
                cin >> d >> m >> y;
                r->a.exp = Date(Date::isValid(d, m, y) ? d : 1, Date::isValid(d, m, y) ? m : 1, Date::isValid(d, m, y) ? y : 2000);
            }

            c.NV = r->a;
            u.push(c);
            r = r->next;
        }
        rewriteFile(*this);
    }

    void viewqty()
    {
        if (qty.empty())
        {
            cout << "No quantities recorded.\n";
            return;
        }

        cout << "\n--- Medicine Quantities ---\n";
        for (auto &[key, val] : qty)
        {
            cout << "Name: " << key.first
                 << " | Dosage: " << key.second
                 << " | Quantity: " << val << endl;
        }
        cout << "----------------------------\n";
    }

    void redqty(const string &name, int q)
    {
        for (auto &[key, val] : qty)
        {
            if (key.first == name)
            {
                val = max(0, val - q);
                if (!val)
                    cout << "Medicine Depleted\n";
                return;
            }
        }
    }

    void updatequt(const string &name)
    {
        for (auto &[key, val] : qty)
        {
            if (key.first == name)
            {
                val += 10;
                cout << "Quantity restocked to " << val << endl;
                return;
            }
        }
    }
};
