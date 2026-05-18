# //------------------------------------------------------- 1
```cpp
template <class T> class S {
    T *A;
    int n, sp;
public:
    S(int n0) { n = n0; sp = -1; A = new T[n]; }
    S& operator<<(T m) {
        if (sp != n - 1) A[++sp] = m;
        return *this;
    }
    S& operator>>(T &m) {
        if (sp == -1) m = 0; else m = A[sp--];
        return *this;
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует стек с фиксированным размером. Оператор <i>operator<<</i> добавляет элемент в стек (если есть место), <i>operator>></i> извлекает верхний элемент (если стек не пуст, иначе присваивает 0).
</div>

# //------------------------------------------------------- 2
```cpp
template <class T, int n> class S {
    T A[n];
    int sp;
public:
    S() { sp = -1; }
    S& operator<<(T m) {
        if (sp != n - 1) A[++sp] = m;
        return *this;
    }
    S& operator>>(T &m) {
        if (sp == -1) m = 0; else m = A[sp--];
        return *this;
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует стек фиксированного размера (размер задаётся параметром шаблона). Операторы <i>operator<<</i> и <i>operator>></i> добавляют и извлекают элементы аналогично варианту 1.
</div>

# //------------------------------------------------------- 3
```cpp
template <class T> class S {
    T **A;
    int n, sp;
public:
    S(int n0) { n = n0; sp = -1; A = new T*[n]; }
    S& operator<<(T &v) {
        if (sp != n - 1) A[++sp] = &v;
        return *this;
    }
    T* operator()() {
        T *m = NULL;
        if (sp != -1) m = A[sp--];
        return m;
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует стек указателей на элементы типа <i>T</i>. Оператор <i>operator<<</i> сохраняет указатель на переданный элемент, <i>operator()</i> извлекает и возвращает указатель на верхний элемент стека (или NULL, если стек пуст).
</div>

# //------------------------------------------------------- 4
```cpp
template <class T, int n> class S {
    int A[n];
    int k;
public:
    S() { k = 0; }
    S& operator<<(T &m) {
        if (k != n) A[k++] = m;
        return *this;
    }
    S& operator>>(T &m) {
        if (k == 0) return *this;
        m = A[0];
        for (int i = 0; i < k - 1; i++) A[i] = A[i + 1];
        k--;
        return *this;
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует очередь фиксированного размера. Оператор <i>operator<<</i> добавляет элемент в конец, <i>operator>></i> удаляет и возвращает первый элемент (сдвигая остальные влево).
</div>

# //------------------------------------------------------- 5
```cpp
template <class T> class S {
    T *A;
    int n, k;
public:
    S(int n0) { n = n0; k = 0; A = new T[n]; }
    S& operator<<(T m) {
        if (k != n) A[k++] = m;
        return *this;
    }
    T operator[](int i) {
        if (k == 0 || i >= k) return 0;
        return A[i];
    }
    S& operator-(int m) {
        if (k == 0 || m >= k) return *this;
        for (int i = m; i < k - 1; i++) A[i] = A[i + 1];
        k--;
        return *this;
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует динамический массив. Оператор <i>operator<<</i> добавляет элемент, <i>operator[]</i> возвращает элемент по индексу (0, если индекс вне границ), <i>operator-</i> удаляет элемент по индексу со сдвигом оставшихся элементов.
</div>

# //------------------------------------------------------- 6
```cpp
template <class T, int n> class S {
    T A[n];
    int k;
public:
    S() { k = 0; }
    S& operator<<(T m) {
        if (k != n) A[k++] = m;
        return *this;
    }
    T operator[](int i) {
        if (k == 0 || i >= k) return 0;
        return A[i];
    }
    S& operator-(int m) {
        if (k == 0 || m >= k) return *this;
        for (int i = m; i < k - 1; i++) A[i] = A[i + 1];
        k--;
        return *this;
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует массив фиксированного размера. Операторы работают аналогично варианту 5: <i>operator<<</i> добавляет, <i>operator[]</i> читает, <i>operator-</i> удаляет элемент по индексу.
</div>

# //------------------------------------------------------- 7
```cpp
template <class T, int n> class S {
    T *A[n];
    int k;
public:
    S() { k = 0; }
    S& operator<<(T &m) {
        if (k != n) A[k++] = &m;
        return *this;
    }
    T* operator[](int i) {
        if (k == 0 || i >= k) return NULL;
        return A[i];
    }
    S& operator-(int m) {
        if (k == 0 || m >= k) return *this;
        for (int i = m; i < k - 1; i++) A[i] = A[i + 1];
        k--;
        return *this;
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует массив указателей фиксированного размера. <i>operator<<</i> сохраняет указатель, <i>operator[]</i> возвращает указатель по индексу (NULL, если индекс вне границ), <i>operator-</i> удаляет указатель по индексу.
</div>

# //------------------------------------------------------- 8 
```cpp
template <class T> class S {
    T *A;
    int n, k;
public:
    S(int n0) { n = n0; k = 0; A = new T[n]; }
    S& operator<<(T m) {
        int i, j;
        for (i = 0; i < k && m > A[i]; i++);
        for (j = k - 1; j >= i; j--) A[j + 1] = A[j];
        A[i] = m; k++;
        return *this;
    }
    T operator[](int i) {
        if (k == 0 || i >= k) return 0;
        return A[i];
    }
};

```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует отсортированный динамический массив (элементы вставляются по возрастанию). Оператор <i>operator<<</i> находит позицию для нового элемента и вставляет его, сохраняя порядок. Оператор <i>operator[]</i> возвращает элемент по индексу (0, если индекс вне границ).
</div>

# //------------------------------------------------------- 9
```cpp
template <class T, int n> class S {
    T A[n];
    int k;
public:
    S() { k = 0; }
    S& operator<<(T m) {
        int i, j;
        for (i = 0; i < k && m > A[i]; i++);
        for (j = k - 1; j >= i; j--) A[j + 1] = A[j];
        A[i] = m; k++;
        return *this;
    }
    T operator[](int i) {
        if (k == 0 || i >= k) return 0;
        return A[i];
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует отсортированный массив фиксированного размера. Оператор <i>operator<<</i> вставляет элемент в нужную позицию для сохранения порядка по возрастанию. Оператор <i>operator[]</i> возвращает элемент по индексу (0, если индекс вне границ).
</div>

# //------------------------------------------------------- 10
```cpp
template <class T, int n> class S {
    T *A[n];
    int k;
public:
    S() { k = 0; }
    S& operator<<(T &m) {
        int i, j;
        for (i = 0; i < k && m > *A[i]; i++);
        for (j = k - 1; j >= i; j--) A[j + 1] = A[j];
        A[i] = &m; k++;
        return *this;
    }
    T* operator[](int i) {
        if (k == 0 || i >= k) return NULL;
        return A[i];
    }
};
```
<div>
  <b>Что делает код:</b><br>
  Шаблон класса <i>S</i> реализует отсортированный массив указателей фиксированного размера (сортировка по возрастанию значений, на которые указывают указатели). Оператор <i>operator<<</i> сохраняет указатель на элемент в правильной позиции, сохраняя порядок. Оператор <i>operator[]</i> возвращает указатель по индексу (NULL, если индекс вне границ).
</div>

---


