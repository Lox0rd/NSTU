## Общая часть класса для всех вариантов (отформатированная)

```cpp
class string {
private:
    char* str;

    void load(char* s) {
        str = strdup(s);
    }

    void add(char* s) {
        str = (char*)realloc(str, strlen(str) + strlen(s) + 1);
        strcat(str, s);
    }

    int find(char* s) {
        char* p = strstr(str, s);
        return p == NULL ? -1 : p - str;
    }

    int cmp(string& t) {
        return strcmp(str, t.str);
    }

public:
    string() {
        load("");
    }

    string(char* s) {
        load(s);
    }

    string(string& t) {
        load(t.str);
    }

    ~string() {
        delete[] str;
    }

    string& operator=(string& r) {
        delete str;
        load(r.str);
        return *this;
    }
};
```

## Ответы на вопросы к лабе3

# //------------------------------------------------------- 1
```cpp
char operator[](int n) {
    return n >= strlen(str) ? '?' : str[n];
}

string& operator()(char c, int n0, int n1) {
    for (int i = n0; i <= n1 && i < strlen(str); i++) {
        str[i] = c;
    }
    return *this;
}
```
<div>
  <b>Что делает код:</b><br>
  Оператор <i>operator[]</i> возвращает символ по индексу <i>n</i>, если индекс выходит за границы строки — возвращает <i>'?'</i>. Оператор <i>operator()</i> заменяет символы в диапазоне от <i>n0</i> до <i>n1</i> на указанный символ <i>c</i>.
</div>

# //------------------------------------------------------- 2
```cpp
string operator+(string& r) {
    string t(str);
    t.add(r.str);
    return t;
}

string operator()(int n0, int n1) {
    if (n1 >= strlen(str)) {
        n1 = strlen(str) - 1;
    }
    char c = str[n1 + 1];
    str[n1 + 1] = '\0';
    string t(str + n0);
    str[n1 + 1] = c;
    return t;
}
```
<div>
  <b>Что делает код:</b><br>
  Оператор <i>operator+</i> создаёт новую строку, объединяя текущую строку с переданной. Оператор <i>operator()</i> извлекает подстроку от <i>n0</i> до <i>n1</i>, сохраняя исходную строку неизменной.
</div>

# //------------------------------------------------------- 3
```cpp
string operator+(string r) {
    r.add(str);
    return r;
}
```
<div>
  <b>Что делает код:</b><br>
  Оператор <i>operator+</i> добавляет текущую строку к переданной строке <i>r</i> и возвращает результат. При этом создаётся копия строки <i>r</i>, к которой добавляется текущая строка.
</div>

# //------------------------------------------------------- 4
```cpp
friend string operator+(string one, string& two) {
    one.add(two.str);
    return one;
}
```
<div>
  <b>Что делает код:</b><br>
  Дружественный оператор <i>operator+</i> объединяет две строки: к копии первой строки <i>one</i> добавляется вторая строка <i>two</i>. Возвращается новая строка — результат конкатенации.
</div>

# //------------------------------------------------------- 5
```cpp
string& operator+(char* s) {
    add(s);
    return *this;
}

string& operator+(string& two) {
    add(two.str);
    return *this;
}
```
<div>
  <b>Что делает код:</b><br>
  Операторы <i>operator+</i> модифицируют текущую строку: первый добавляет строку <i>s</i>, второй — строку <i>two</i>. Оба возвращают ссылку на изменённый объект.
</div>

# //------------------------------------------------------- 6
```cpp
string operator+(char* s) {
    string two(s);
    two.add(str);
    return two;
}

string operator+(string two) {
    two.add(str);
    return two;
}
```
<div>
  <b>Что делает код:</b><br>
  Операторы <i>operator+</i> создают новую строку: первый — из строки <i>s</i> с добавлением текущей строки, второй — из переданной строки <i>two</i> с добавлением текущей. Возвращается новый объект.
</div>

# //------------------------------------------------------- 7
```cpp
string(char c, int n) {
    str = new char[n + 1];
    for (str[n--] = '\0'; n >= 0; n--) {
        str[n] = c;
    }
}

string& operator()(char c, int n0, int n1) {
    for (int i = n0; i <= n1 && i < strlen(str); i++) {
        str[i] = c;
    }
    return *this;
}
```
<div>
  <b>Что делает код:</b><br>
  Конструктор <i>string(char c, int n)</i> создаёт строку из <i>n</i> одинаковых символов <i>c</i>. Оператор <i>operator()</i> заменяет символы в диапазоне <i>n0–n1</i> на символ <i>c</i>.
</div>

# //------------------------------------------------------- 8
```cpp
string& operator+(string& t) {
    for (int i = 0; i < strlen(str) && i < strlen(t.str); i++) {
        str[i] = t.str[i];
    }
    return *this;
}

string& operator+(char* s) {
    string t(s);
    return *this + t;
}
```
<div>
  <b>Что делает код:</b><br>
  Первый оператор <i>operator+</i> копирует символы из строки <i>t</i> в текущую строку до конца одной из строк. Второй оператор преобразует строку <i>s</i> в объект <i>string</i> и вызывает первый оператор.
</div>

# //------------------------------------------------------- 9
```cpp
string& operator()(int n0, int n1) {
    int k = strlen(str);
    n1++;
    while (n1 <= k) {
        str[n0++] = str[n1++];
    }
    return *this;
}

string& operator-(char* s) {
    int k = strlen(s), n0 = find(s);
    if (n0 != -1) {
        (*this)(n0, n0 + k - 1);
    }
    return *this;
}
```
<div>
  <b>Что делает код:</b><br>
  Оператор <i>operator()</i> удаляет подстроку от <i>n0</i> до <i>n1</i>, сдвигая оставшиеся символы влево. Оператор <i>operator-</i> находит и удаляет первое вхождение строки <i>s</i> из текущей строки.
</div>

# //------------------------------------------------------- 10
```cpp
string& operator()(int n0, int l) {
    int k = strlen(str);
    int n1 = n0 + l;
    while (n1 <= k) {
        str[n0++] = str[n1++];
    }
    return *this;
}

int operator[](char* s) {
    return find(s);
}
```
<div>
  <b>Что делает код:</b><br>
    Оператор <i>operator()</i> удаляет из строки <i>l</i> символов, начиная с позиции <i>n0</i>, путём сдвига оставшихся символов влево. Возвращает ссылку на модифицированный объект. Оператор <i>operator[]</i> ищет подстроку <i>s</i> в текущей строке и возвращает индекс её первого вхождения (или -1, если подстрока не найдена).
</div>