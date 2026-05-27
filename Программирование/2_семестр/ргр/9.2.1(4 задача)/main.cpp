#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;
const int SZ = 1024;

void pk(char* m, int& p) {
    char s[256];
    cout << "Введите строку: ";
    cin.getline(s, 256);
    int i = 0;
    while (s[i]) {
        if (isdigit(s[i])) {
            long x = 0;
            while (isdigit(s[i])) {
                x = x * 10 + (s[i] - '0');
                i++;
            }
            if (p + 1 + sizeof(long) >= SZ) {
                cout << "Переполнение памяти\n";
                return;
            }
            m[p++] = '\1';
            memcpy(m + p, &x, sizeof(long));
            p += sizeof(long);
        }
        else {
            if (p + 1 >= SZ) {
                cout << "Переполнение памяти\n";
                return;
            }
            m[p++] = s[i++];
        }
    }
    m[p++] = '\0';
}

void sh(char* m, int p) {
    cout << "Запаковано: ";
    while (1) {
        if (m[p] == '\0') {
            cout << "\\0";
            p++;
            break;
        }
        if (m[p] == '\1') {
            cout << "\\1 ";
            p++;
            long x;
            memcpy(&x, m + p, sizeof(long));
            cout << x << " ";
            p += sizeof(long);
        }
        else {
            cout << "'" << m[p] << "' ";
            p++;
        }
    }
    cout << endl;
}

void upk(char* m, int& p) {
    while (1) {
        if (m[p] == '\0') {
            p++;
            break;
        }
        if (m[p] == '\1') {
            p++;
            long x;
            memcpy(&x, m + p, sizeof(long));
            cout << x;
            p += sizeof(long);
        }
        else {
            cout << m[p++];
        }
    }
    cout << endl;
}

int main() {
    setlocale(0, "");
    char m[SZ];
    int p = 0;
    int n;
    cout << "Количество строк: ";
    cin >> n;
    cin.ignore();
    int st[100];
    for (int i = 0; i < n; i++) {
        st[i] = p;
        pk(m, p);
        sh(m, st[i]);
    }
    cout << "\nРаспаковка:\n";
    for (int i = 0; i < n; i++) {
        int t = st[i];
        upk(m, t);
    }
    return 0;
}