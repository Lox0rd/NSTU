from stack import Stack

def show_help():
    print("Команды:")
    print("s.push <value>   - добавить элемент в стек")
    print("s.pop            - удалить верхний элемент из стека")
    print("s.peek           - посмотреть верхний элемент стека")
    print("s.print          - вывести содержимое стека")
    print("s.size           - показать размер стека")
    print("help             - показать список команд")
    print("exit             - выход из программы")
    print()

def main():
    stack = Stack()
    print("help для списка команд.")

    while True:
        print("> ", end="")
        command = input().strip()

        parts = command.split()
        if not parts:
            continue

        cmd = parts[0]

        if cmd == "exit":
            print("Выход из программы.")
            break

        elif cmd == "help":
            show_help()

        elif cmd == "s.push":
            if len(parts) < 2:
                print("Ошибка: требуется значение")
            else:
                value = int(parts[1])
                stack.push(value)

        elif cmd == "s.pop":
            popped_value = stack.pop()
            print(f"Удаленный элемент: {popped_value}")

        elif cmd == "s.peek":
            try:
                top_value = stack.peek()
                print(f"Верхний элемент стека: {top_value}")
            except IndexError:
                print("Ошибка: стек пуст")

        elif cmd == "s.print":
            stack.print_stack()

        elif cmd == "s.size":
            print(f"Размер стека: {stack.size()}")

        else:
            print(f"Неизвестная команда: '{cmd}'. help для списка команд")

if __name__ == "__main__":
    main()
