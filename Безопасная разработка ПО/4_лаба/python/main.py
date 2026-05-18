from stack import Stack

def print_menu():
    print("\n=== Интерактивный стек ===")
    print("1. Добавить элемент (push)")
    print("2. Удалить элемент (pop)")
    print("3. Посмотреть верхний элемент (peek)")
    print("4. Показать размер стека")
    print("5. Вывести содержимое стека")
    print("0. Выход")
    print("Ваш выбор: ", end="")

def main():
    stack = Stack()

    while True:
        print_menu()
        try:
            choice = int(input())
        except ValueError:
            print("Ошибка: введите число от 0 до 6.")
            continue

        if choice == 1:
            try:
                value = int(input("Введите значение для добавления: "))
                stack.push(value)
                print(f"Элемент {value} добавлен в стек.")
            except Exception as e:
                print(f"Ошибка при добавлении: {e}")

        elif choice == 2:
            try:
                popped_value = stack.pop()
                print(f"Удаленный элемент: {popped_value}")
            except IndexError:
                print("Ошибка: невозможно удалить элемент - стек пуст!")

        elif choice == 3:
            try:
                top_value = stack.peek()
                print(f"Верхний элемент стека: {top_value}")
            except IndexError:
                print("Ошибка: стек пуст, нет верхнего элемента!")
        elif choice == 4:
            print(f"Размер стека: {stack.size()}")

        elif choice == 5:
            stack.print_stack()

        elif choice == 0:
            print("Выход из программы.")
            break

        else:
            print("Неверный выбор! Введите число от 0 до 6.")

if __name__ == "__main__":
    main()
