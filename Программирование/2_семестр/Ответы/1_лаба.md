## Ответы на вопросы к лабе1
# //------------------------------------------------------- 1
```bash
int F1(double *p[]) {
    int n;
    for (n = 0; p[n] != NULL; n++);
    return n;
}
```
<div>
<h>Ответ на 1 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 2
```bash
void F2(double *p[]) {
    int i, k;
    for (k = 1; p[k] != NULL; k++) {
        for (i = k; i > 0 && *p[i] < *p[i - 1]; i--) {
            double *q = p[i];
            p[i] = p[i - 1];
            p[i - 1] = q;
        }
    }
}
```
<div>
<h>Ответ на 2 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 3
```bash
void F3(double *p[], double *q) {
    int i, n;
    for (i = 0; p[i] != 0; i++) {
        if (*p[i] > *q) break;
    }
    for (n = i; p[n] != NULL; n++);
    for (; n >= i; n--) {
        p[n + 1] = p[n];
    }
    p[i] = q;
}
```
<div>
<h>Ответ на 3 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 4
```bash
int F4(char *p[]) {
    int k, i, j;
    for (k = i = 0; p[i] != NULL; i++) {
        for (j = 0; p[i][j] != 0; j++, k++);
    }
    return k;
}
```
<div>
<h>Ответ на 4 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 5
```bash
char **F5(char a[][80], int n) {
    int i;
    char **p;
    p = new char*[n + 1];
    for (i = 0; i < n; i++) {
        p[i] = a[i];
    }
    p[n] = NULL;
    return p;
}
```
<div>
<h>Ответ на 5 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 6
```bash
char *F6(char *p[]) {
    int i, sz, l, k;
    for (i = sz = k = 0; p[i] != NULL; i++) {
        if ((l = strlen(p[i])) > sz) {
            sz = l;
            k = i;
        }
    }
    return p[k];
}
```
<div>
<h>Ответ на 6 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 7
```bash
char **F7(char c[]) {
    char **p;
    int i, n, cnt;
    p = new char*[20];
    for (i = n = cnt = 0; c[n] != 0; n++) {
        if (c[n] == ' ') {
            c[n] = '\0';
            cnt = 0;
        } else {
            cnt++;
            if (cnt == 1) {
                p[i++] = &c[n];
            }
            if (i == 19) break;
        }
    }
    p[i] = NULL;
    return p;
}
```
<div>
<h>Ответ на 7 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 8
```bash
char *F8(char *p[], int m) {
    int n;
    char *q;
    for (n = 0; p[n] != NULL; n++);
    if (m >= n) return NULL;
    q = p[m];
    for (n = m; p[n] != NULL; n++) {
        p[n] = p[n + 1];
    }
    return q;
}
```
<div>
<h>Ответ на 8 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 9
```bash
int F9(char *p[], char *str) {
    int h, l, m;
    for (h = 0; p[h] != NULL; h++);
    for (h--, l = 0; h >= l;) {
        m = (l + h) / 2;
        int k = strcmp(p[m], str);
        if (k < 0) {
            l = m + 1;
        } else {
            h = m - 1;
        }
    }
    return -1;
}
```
<div>
<h>Ответ на 9 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 10
```bash
char **F10() {
    int n;
    char **p, s[80];
    p = new char*[100];
    for (n = 0; n < 99 && (gets(s), s[0] != '\0'); n++) {
        p[n] = strdup(s);
    }
    p[n] = NULL;
    return p;
}
```
<div>
<h>Ответ на 10 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 11
```bash
void F11(char *p[], int m) {
    int n;
    char *q;
    for (n = 0; p[n] != 0; n++);
    if (m >= n) return;
    for (; n > m; n--) {
        p[n + 1] = p[n];
    }
    p[m + 1] = strdup(p[m]);
}
```
<div>
<h>Ответ на 11 вопрос</h>
<p></p>
</div>

# //------------------------------------------------------- 12
```bash
double F12(double *p[], int n) {
    double s = 0;
    for (int i = 0; p[i] != NULL; i++) {
        for (int j = 0; j < n; j++) {
            s += p[i][j];
        }
    }
    return s;
}
```
<div>
<h>Ответ на 12 вопрос</h>
<p></p>
</div>