#include <iostream>
#include <algorithm>
#include "../hppfolder/Stack.hpp"
#include "../hppfolder/DS.hpp"

using namespace std;

void Undo(Stack &u, Stack &r, LinkedList &L)
{
    if (u.empty())
    {
        cout << "Nothing to undo.\n";
        return;
    }

    bool cont = true;
    char ch;

    while (cont)
    {
        Action a = u.peek();
        u.pop();
        r.push(a);

        switch (a.act)
        {

        case 'i':
        {
            string name = a.NV.name;
            Time t = a.NV.t;

            Node *curr = L.head, *prev = nullptr;
            while (curr && !(curr->a.name == name && curr->a.t == t))
            {
                prev = curr;
                curr = curr->next;
            }
            if (!curr)
                break;

            if (!prev)
                L.head = curr->next;
            else
                prev->next = curr->next;

            auto &vec = L.hash[name];
            vec.erase(remove(vec.begin(), vec.end(), curr), vec.end());
            if (vec.empty())
                L.hash.erase(name);

            delete curr;
            cout << "Undo insert -> Deleted: " << name << " at ";
            t.disp();
            cout << endl;
            break;
        }

        case 'd':
        case 'a':
        {
            Node *newNode = new Node;
            newNode->a = a.OV;
            newNode->next = nullptr;

            if (!L.head || newNode->a.t < L.head->a.t)
            {
                newNode->next = L.head;
                L.head = newNode;
            }
            else
            {
                Node *curr = L.head;
                while (curr->next && !(newNode->a.t < curr->next->a.t))
                    curr = curr->next;
                newNode->next = curr->next;
                curr->next = newNode;
            }

            L.hash[newNode->a.name].push_back(newNode);
            cout << "Undo delete -> Restored: " << newNode->a.name << " at ";
            newNode->a.t.disp();
            cout << endl;

            if (!u.empty() && u.peek().act == 'a')
            {
                char o;
                cout << "More deleted items detected. Restore all? (y for all): ";
                cin >> o;
                if (o == 'y' || o == 'Y')
                {
                    while (!u.empty() && u.peek().act == 'a')
                    {
                        Action x = u.peek();
                        u.pop();
                        r.push(x);

                        Node *newNode2 = new Node;
                        newNode2->a = x.OV;
                        newNode2->next = nullptr;

                        if (!L.head || newNode2->a.t < L.head->a.t)
                        {
                            newNode2->next = L.head;
                            L.head = newNode2;
                        }
                        else
                        {
                            Node *curr = L.head;
                            while (curr->next && !(newNode2->a.t < curr->next->a.t))
                                curr = curr->next;
                            newNode2->next = curr->next;
                            curr->next = newNode2;
                        }

                        L.hash[newNode2->a.name].push_back(newNode2);
                    }
                    cout << "All deleted items restored.\n";
                }
            }
            break;
        }

        case 'u':
        {
            Node *curr = L.head;
            while (curr)
            {
                if (curr->a.name == a.NV.name && curr->a.t == a.NV.t)
                {
                    curr->a = a.OV;
                    break;
                }
                curr = curr->next;
            }
            cout << "Undo update -> Reverted last alteration.\n";

            if (!u.empty() && u.peek().act == 'u')
            {
                char o;
                cout << "Detected multiple alterations. Undo all? (y for all): ";
                cin >> o;
                if (o == 'y' || o == 'Y')
                {
                    while (!u.empty() && u.peek().act == 'u')
                    {
                        Action x = u.peek();
                        u.pop();
                        r.push(x);

                        curr = L.head;
                        while (curr)
                        {
                            if (curr->a.name == x.NV.name && curr->a.t == x.NV.t)
                            {
                                curr->a = x.OV;
                                break;
                            }
                            curr = curr->next;
                        }
                    }
                    cout << "All alterations reverted.\n";
                }
            }
            break;
        }
        }
        if (u.empty())
        {
            cout << "Nothing left to Undo\n";
            return;
        }
        cout << "Continue undoing? (y/n): ";
        cin >> ch;
        if (ch != 'y' && ch != 'Y')
            cont = false;
    }
}

void Redo(Stack &r, Stack &u, LinkedList &L)
{
    if (r.empty())
    {
        cout << "Nothing to redo.\n";
        return;
    }

    bool cont = true;
    char ch;

    while (cont)
    {
        Action a = r.peek();
        r.pop();
        u.push(a);

        switch (a.act)
        {

        case 'i':
        {
            Node *newNode = new Node;
            newNode->a = a.NV;
            newNode->next = nullptr;

            if (!L.head || newNode->a.t < L.head->a.t)
            {
                newNode->next = L.head;
                L.head = newNode;
            }
            else
            {
                Node *curr = L.head;
                while (curr->next && !(newNode->a.t < curr->next->a.t))
                    curr = curr->next;
                newNode->next = curr->next;
                curr->next = newNode;
            }

            L.hash[newNode->a.name].push_back(newNode);
            cout << "Redo insert -> Inserted: " << newNode->a.name << " at ";
            newNode->a.t.disp();
            cout << endl;
            break;
        }

        case 'd':
        case 'a':
        {
            Node *curr = L.head, *prev = nullptr;
            while (curr && !(curr->a.name == a.OV.name && curr->a.t == a.OV.t))
            {
                prev = curr;
                curr = curr->next;
            }
            if (!curr)
                break;

            if (!prev)
                L.head = curr->next;
            else
                prev->next = curr->next;

            auto &vec = L.hash[curr->a.name];
            vec.erase(remove(vec.begin(), vec.end(), curr), vec.end());
            if (vec.empty())
                L.hash.erase(curr->a.name);

            cout << "Redo delete -> Deleted: " << curr->a.name << " at ";
            curr->a.t.disp();
            cout << endl;
            delete curr;

            if (!r.empty() && r.peek().act == 'a')
            {
                char o;
                cout << "More deletions detected. Redo all? (y for all): ";
                cin >> o;
                if (o == 'y' || o == 'Y')
                {
                    while (!r.empty() && r.peek().act == 'a')
                    {
                        Action x = r.peek();
                        r.pop();
                        u.push(x);

                        Node *curr2 = L.head, *prev2 = nullptr;
                        while (curr2 && !(curr2->a.name == x.OV.name && curr2->a.t == x.OV.t))
                        {
                            prev2 = curr2;
                            curr2 = curr2->next;
                        }
                        if (!curr2)
                            continue;

                        if (!prev2)
                            L.head = curr2->next;
                        else
                            prev2->next = curr2->next;

                        auto &vec2 = L.hash[curr2->a.name];
                        vec2.erase(remove(vec2.begin(), vec2.end(), curr2), vec2.end());
                        if (vec2.empty())
                            L.hash.erase(curr2->a.name);

                        delete curr2;
                    }
                    cout << "All group deletions redone.\n";
                }
            }
            break;
        }

        case 'u':
        {
            Node *curr = L.head;
            while (curr)
            {
                if (curr->a.name == a.OV.name && curr->a.t == a.OV.t)
                {
                    curr->a = a.NV;
                    break;
                }
                curr = curr->next;
            }
            cout << "Redo update -> Reapplied alteration.\n";

            if (!r.empty() && r.peek().act == 'u')
            {
                char o;
                cout << "Multiple alterations detected. Redo all? (y for all): ";
                cin >> o;
                if (o == 'y' || o == 'Y')
                {
                    while (!r.empty() && r.peek().act == 'u')
                    {
                        Action x = r.peek();
                        r.pop();
                        u.push(x);

                        curr = L.head;
                        while (curr)
                        {
                            if (curr->a.name == x.OV.name && curr->a.t == x.OV.t)
                            {
                                curr->a = x.NV;
                                break;
                            }
                            curr = curr->next;
                        }
                    }
                    cout << "All alterations redone.\n";
                }
            }
            break;
        }
        }
        if (r.empty())
        {
            cout << "Nothing left to Undo\n";
            return;
        }
        cout << "Continue redoing? (y/n): ";
        cin >> ch;
        if (ch != 'y' && ch != 'Y')
            cont = false;
    }
}
