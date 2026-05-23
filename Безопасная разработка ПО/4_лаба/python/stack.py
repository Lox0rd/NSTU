class Stack:
    def __init__(self):
        self._items = []

    def push(self, item):
        self._items.append(item)

    def pop(self):
        if self.empty():
            raise IndexError("Стек пуст")
        return self._items.pop()

    def peek(self):
        if self.empty():
            raise IndexError("Стек пуст")
        return self._items[-1]

    def empty(self):
        return len(self._items) == 0

    def size(self):
        return len(self._items)

    def print_stack(self):
        if self.empty():
            print("Стек пуст")
        else:
            print("Содержимое стека:", " -> ".join(map(str, reversed(self._items))))
