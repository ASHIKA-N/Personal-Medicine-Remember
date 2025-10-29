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

void commitToFile(const LinkedList &L)
{
    const string mainFile = "med_data.txt";
    const string tempFile = "temp_med_data.txt";

    ofstream out(tempFile, ios::trunc);
    if (!out.is_open())
    {
        cerr << "[Error] Unable to open temporary file for commit.\n";
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
            << q << "|"
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
        cout << "All changes committed successfully.\n";
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        cerr << "[Error] Commit failed, keeping old file: " << e.what() << endl;
        filesystem::remove(tempFile);
    }
}
