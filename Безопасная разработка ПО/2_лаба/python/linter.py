from flask import Flask, request
import sqlite3
import os

app = Flask(__name__)

DB_PATH = "users.db"


def get_user(username, password):
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()


    query = f"SELECT * FROM users WHERE username = '{username}' AND password = '{password}'"
    cursor.execute(query)

    user = cursor.fetchone()
    conn.close()
    return user


@app.route("/login", methods=["POST"])
def login():
    username = request.form.get("username")
    password = request.form.get("password")


    user = get_user(username, password)

    if user:
        return f"Welcome, {username}!"
    else:
        return "Invalid credentials", 401


@app.route("/read_file", methods=["GET"])
def read_file():
    filename = request.args.get("filename")

    filepath = os.path.join("files", filename)

    try:
        with open(filepath, "r") as f:
            content = f.read()
        return content
    except Exception as e:

        return str(e), 500


if __name__ == "__main__":

    app.run(debug=True)

#http://127.0.0.1:5000/read_file?filename=test.txt