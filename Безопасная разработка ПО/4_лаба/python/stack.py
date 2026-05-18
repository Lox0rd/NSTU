class Stack:
    def __init__(self):
        self._items = []

    def push(self, item):
        """Добавить элемент в стек."""
        self._items.append(item)

    def pop(self):
        """Удалить и вернуть верхний элемент стека.
        Вызывает IndexError, если стек пуст."""
        if self.empty():
            raise IndexError("pop from empty stack")
        return self._items.pop()

    def peek(self):
        """Вернуть верхний элемент стека без удаления.
        Вызывает IndexError, если стек пуст."""
        if self.empty():
            raise IndexError("peek from empty stack")
        return self._items[-1]

    def empty(self):
        """Проверить, пуст ли стек."""
        return len(self._items) == 0

    def size(self):
        """Вернуть количество элементов в стеке."""
        return len(self._items)

    def print_stack(self):
        """Вывести содержимое стека (сверху вниз)."""
        if self.empty():
            print("Стек пуст.")
        else:
            print("Содержимое стека (сверху вниз):", " -> ".join(map(str, reversed(self._items))))
