#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Str {
    long p;
};

void rd(ifstream &f, vector<Str> &v) {
    string s;
    while (1) {
        long pos = f.tellg();
        if (!getline(f, s))
            break;
        Str t;
        t.p = pos;
        v.push_back(t);
    }
}

string gs(ifstream &f, long p) {
    f.clear();
    f.seekg(p);
    string s;
    getline(f, s);
    return s;
}

int main() {
    setlocale(0, "");
    ifstream f1("f1.txt");
    ifstream f2("f2.txt");
    if (!f1 || !f2) {
        cout << "Ошибка открытия файлов\n";
        return 1;
    }
    vector<Str> a, b;
    rd(f1, a);
    rd(f2, b);
    int i = 0, j = 0;
    while (i < a.size() || j < b.size()) {
        string s1 = (i < a.size()) ? gs(f1, a[i].p) : "";
        string s2 = (j < b.size()) ? gs(f2, b[j].p) : "";
        if (i < a.size() && j < b.size() && s1 == s2) {
            i++;
            j++;
        }
        else {
            if (j < b.size()) {
                cout << "\nДобавлено:\n";
                while (j < b.size()) {
                    s2 = gs(f2, b[j].p);
                    bool ok = false;
                    for (int k = i; k < a.size(); k++) {
                        if (s2 == gs(f1, a[k].p)) {
                            ok = true;
                            break;
                        }
                    }
                    if (ok)
                        break;
                    cout << s2 << endl;
                    j++;
                }
            }
            if (i < a.size()) {
                cout << "\nУдалено:\n";
                while (i < a.size()) {
                    s1 = gs(f1, a[i].p);
                    bool ok = false;
                    for (int k = j; k < b.size(); k++) {
                        if (s1 == gs(f2, b[k].p)) {
                            ok = true;
                            break;
                        }
                    }
                    if (ok)
                        break;
                    cout << s1 << endl;
                    i++;
                }
            }
        }
    }
    f1.close();
    f2.close();
    return 0;
}