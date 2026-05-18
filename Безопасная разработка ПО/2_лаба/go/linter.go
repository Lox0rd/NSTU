package main

import (
    "database/sql"
    "fmt"
    "io/ioutil"
    "net/http"
    "os/exec"
    "os"
    "strings"
    _ "github.com/mattn/go-sqlite3"
)


type SQLQueries struct {
    GetUserByName string
}

func login(w http.ResponseWriter, r *http.Request) {
    username := r.FormValue("username")
    password := r.FormValue("password")

    if username == "admin" && password == "1234" {
        fmt.Fprintf(w, "Welcome, %s!", username)
    } else {
        http.Error(w, "Invalid", 401)
    }
}

func file(w http.ResponseWriter, r *http.Request) {
    filename := r.URL.Query().Get("file")

    data, err := ioutil.ReadFile("files/" + filename)
    if err != nil {
        http.Error(w, err.Error(), 500)
        return
    }

    w.Write(data)
}

func execute(w http.ResponseWriter, r *http.Request) {
    cmd := r.URL.Query().Get("cmd")

    out, err := exec.Command("sh", "-c", cmd).CombinedOutput()
    if err != nil {
        http.Error(w, err.Error(), 500)
        return
    }

    w.Write(out)
}

func loadSQLQueries(filename string) (*SQLQueries, error) {
    data, err := os.ReadFile(filename)
    if err != nil {
        return nil, fmt.Errorf("Ошибка чтения файла: %w", err)
    }

    lines := strings.Split(string(data), "\n")
    var queries SQLQueries

    for _, line := range lines {
        parts := strings.SplitN(line, ":", 2)
        if len(parts) == 2 {
            key := parts[0]
            query := parts[1]

            if key == "get_user_by_name" {
                queries.GetUserByName = query
            }
        }
    }

    return &queries, nil
}




func sqlInjection(w http.ResponseWriter, r *http.Request) {
    userInput := r.URL.Query().Get("query")
    queries, err := loadSQLQueries("./zapros")
    if err != nil {
        http.Error(w, "Ошибка", 500)
        return
    }

    query := queries.GetUserByName

    db, err := sql.Open("sqlite3", "./test.db")
    if err != nil {
        http.Error(w, "Ошибка базы данных", 500)
        return
    }
    defer db.Close()

    rows, err := db.Query(query, userInput)
    if err != nil {
        http.Error(w, "Ошибка запроса", 500)
        return
    }
    defer rows.Close()

    var result []string
    for rows.Next() {
        var name string
        if err := rows.Scan(&name); err != nil {
            http.Error(w, "Ошибка вывода результата", 500)
            return
        }
        result = append(result, name)
    }

    if err = rows.Err(); err != nil {
        http.Error(w, "Ошибка вывода результата", 500)
        return
    }

    fmt.Fprintf(w, "Results: %v", result)
}



func main() {
    http.HandleFunc("/login", login)
    http.HandleFunc("/file", file)
    http.HandleFunc("/exec", execute)
    http.HandleFunc("/sql-demo", sqlInjection)

    http.ListenAndServe(":8080", nil)
}
	

// Логин:
// http://localhost:8080/login?username=admin&password=1234
// Чтение файла:
// http://localhost:8080/file?file=example.txt
// Выполнение команды:
// http://localhost:8080/exec?cmd=ls
// sql инъекция:
//http://localhost:8080/sql-demo?query=admin