#include "FileHandler.hpp"
#include "DS.hpp"

void saveMedToFile(const Med &m)
{
    ofstream file(FILENAME, ios::app);
    if (!file)
    {
        cout << "Error opening file for writing.\n";
        return;
    }

    file << m.name << "|"
         << m.dosage << "|"
         << m.qty << "|"
         << m.t.h << " " << m.t.m << "|"
         << m.exp.d << " " << m.exp.m << " " << m.exp.y << "|";

    for (size_t i = 0; i < m.dy.size(); i++)
    {
        file << m.dy[i];
        if (i != m.dy.size() - 1)
            file << ",";
    }
    file << "\n";
    file.close();
}

void rewriteFile(const LinkedList &L)
{
    ofstream file(FILENAME, ios::trunc);
    if (!file)
    {
        cout << "Error opening file for rewrite.\n";
        return;
    }

    Node *r = L.head;
    while (r)
    {
        const Med &m = r->a;
        file << m.name << "|"
             << m.dosage << "|"
             << m.qty << "|"
             << m.t.h << " " << m.t.m << "|"
             << m.exp.d << " " << m.exp.m << " " << m.exp.y << "|";
        for (size_t i = 0; i < m.dy.size(); i++)
        {
            file << m.dy[i];
            if (i != m.dy.size() - 1)
                file << ",";
        }
        file << "\n";
        r = r->next;
    }
    file.close();
}

void loadFromFile(LinkedList &L)
{
    ifstream file(FILENAME);
    if (!file)
    {
        cout << "No existing medicine file found.\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Med m;
        string daysPart;
        replace(line.begin(), line.end(), '|', ' ');
        stringstream ss(line);

        ss >> ws;
        getline(ss, m.name, ' ');
        getline(ss, m.dosage, ' ');
        ss >> m.qty;
        ss >> m.t.h >> m.t.m;
        ss >> m.exp.d >> m.exp.m >> m.exp.y;

        m.dy.clear();
        string rest;
        getline(ss, rest);
        stringstream ds(rest);
        string num;
        while (getline(ds, num, ','))
        {
            if (!num.empty())
                m.dy.push_back(stoi(num));
        }

        Node *node = new Node;
        node->a = m;
        node->next = nullptr;

        if (!L.head || m.t < L.head->a.t)
        {
            node->next = L.head;
            L.head = node;
        }
        else
        {
            Node *r = L.head;
            while (r->next && !(m.t < r->next->a.t))
                r = r->next;
            node->next = r->next;
            r->next = node;
        }

        L.hash[m.name].push_back(node);
    }

    file.close();
    cout << "Loaded medicines from file successfully.\n";
}
