#include "../hppfolder/FileHandler.hpp"
#include "../hppfolder/DS.hpp"
#include <filesystem>
#include <sstream>

using namespace std;

static string sanitize(const string &s)
{
    string out = s;
    for (char &c : out)
        if (c == '|' || c == '\n' || c == '\r')
            c = ' ';
    return out;
}

void saveMedToFile(const Med &m, int qty)
{
    ofstream file("med_data.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Error opening file for writing.\n";
        return;
    }

    file << sanitize(m.name) << "|"
         << sanitize(m.dosage) << "|"
         << qty << "|"
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
    const string mainFile = "med_data.txt";
    const string tempFile = "temp_med_data.txt";

    ofstream out(tempFile, ios::trunc);
    if (!out.is_open())
    {
        cerr << "[Error] Unable to open temporary file for rewrite.\n";
        return;
    }

    Node *r = L.head;
    while (r)
    {
        const Med &m = r->a;
        int q = 0;
        auto it = L.qty.find({m.name, m.dosage});
        if (it != L.qty.end())
            q = it->second;

        out << sanitize(m.name) << "|"
            << sanitize(m.dosage) << "|"
            << q << "|" // qty from map
            << m.t.h << " " << m.t.m << "|"
            << m.exp.d << " " << m.exp.m << " " << m.exp.y << "|";

        for (size_t i = 0; i < m.dy.size(); i++)
        {
            out << m.dy[i];
            if (i != m.dy.size() - 1)
                out << ",";
        }
        out << "\n";
        r = r->next;
    }

    out.close();

    try
    {
        if (std::filesystem::exists(mainFile))
            std::filesystem::remove(mainFile);
        std::filesystem::rename(tempFile, mainFile);
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        cerr << "[Error] Could not replace old data file: " << e.what() << endl;
        filesystem::remove(tempFile);
    }
}

void loadFromFile(LinkedList &L)
{
    ifstream file("med_data.txt");
    if (!file.is_open())
    {
        cout << "[Info] No medicine file found. Starting fresh.\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        Med m;
        string qtyStr, timeStr, expStr, daysStr;

        getline(ss, m.name, '|');
        getline(ss, m.dosage, '|');
        getline(ss, qtyStr, '|');
        getline(ss, timeStr, '|');
        getline(ss, expStr, '|');
        getline(ss, daysStr, '|');

        int qty = 0;
        stringstream(qtyStr) >> qty;
        stringstream(timeStr) >> m.t.h >> m.t.m;
        stringstream(expStr) >> m.exp.d >> m.exp.m >> m.exp.y;

        m.dy.clear();
        string num;
        stringstream ds(daysStr);
        while (getline(ds, num, ','))
        {
            if (!num.empty())
                m.dy.push_back(stoi(num));
        }

        Node *node = new Node{m, nullptr};

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
        L.qty[{m.name, m.dosage}] = qty; // store qty in map
    }

    file.close();
    cout << "[Info] Medicines loaded successfully.\n";
}
