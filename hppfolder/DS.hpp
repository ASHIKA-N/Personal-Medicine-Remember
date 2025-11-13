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
        auto key = make_pair(t->a.name, t->a.dosage);

        if (qty.find(key) == qty.end())
        {
            cout << "Enter Quantity: ";
            cin >> q;
            qty[key] = q;
        }
        else
        {
            q = qty[key];
            cout << "Existing medicine detected. Using previous quantity (" << q << ").\n";
        }
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
        a.NV = t->a;
        u.push(a);
        cout << "Medicine added successfully!\n";
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

        int count = hash[name].size();
        cout << "\n"
             << count << " medicine(s) found for \"" << name << "\":\n";
        cout << "------------------------------------------\n";

        int i = 1;
        for (Node *n : hash[name])
        {
            cout << "[" << i++ << "] ";
            n->a.disp();
            auto key = make_pair(n->a.name, n->a.dosage);
            cout << "Quantity: " << qty[key] << endl;
            cout << "------------------------------------------\n";
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
        if (!r)
        {
            cout << "List is Empty\n";
            return;
        }
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
                auto oldKey = make_pair(c.OV.name, c.OV.dosage);
                auto newKey = make_pair(r->a.name, r->a.dosage);

                if (oldKey != newKey)
                {
                    int oldQty = qty[oldKey];

                    bool stillUsed = false;
                    for (Node *tmp = head; tmp; tmp = tmp->next)
                    {
                        if (tmp != r && tmp->a.name == c.OV.name && tmp->a.dosage == c.OV.dosage)
                        {
                            stillUsed = true;
                            break;
                        }
                    }

                    if (!stillUsed)
                        qty.erase(oldKey);

                    qty[newKey] = oldQty;
                }
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
                auto oldKey = make_pair(r->a.name, c.OV.dosage);
                auto oldIt = qty.find(oldKey);
                int oldQty = (oldIt != qty.end()) ? oldIt->second : 0;

                cout << "Enter new dosage: ";
                getline(cin, r->a.dosage);

                auto newKey = make_pair(r->a.name, r->a.dosage);
                qty[newKey] = oldQty;

                bool stillUsed = false;
                for (Node *tmp = head; tmp; tmp = tmp->next)
                {
                    if (tmp != r && tmp->a.name == oldKey.first && tmp->a.dosage == oldKey.second)
                    {
                        stillUsed = true;
                        break;
                    }
                }

                if (!stillUsed && oldIt != qty.end())
                    qty.erase(oldIt);
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
                c.qb = qty[{r->a.name, r->a.dosage}];
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

    void redqty(const string &name, const string &dosage)
    {
        for (auto &[key, val] : qty)
        {
            if (key.first == name)
            {
                if (val == 0)
                {
                    cout << "Medicine already depleted. Restocking...\n";
                    updqty(name);
                    return;
                }

                val = max(0, val - 1);

                if (val == 0)
                {
                    cout << "Medicine depleted. Auto restocking...\n";
                    updqty(name);
                }
                return;
            }
        }
    }

    void updqty(const string &name)
    {
        for (auto &[key, val] : qty)
        {
            if (key.first == name)
            {
                cout << "Enter new quantity for " << name << " (dosage: " << key.second << "): ";
                cin >> val;
                cout << "Quantity restocked to " << val << endl;
                return;
            }
        }
    }
};
