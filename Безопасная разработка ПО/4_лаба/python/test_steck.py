import unittest
from stack import Stack

class StackTest(unittest.TestCase):

    def test_push_pop(self):
        s = Stack()

        s.push(10)
        s.push(20)

        self.assertEqual(s.peek(), 20)
        self.assertEqual(s.pop(), 20)
        self.assertEqual(s.pop(), 10)

    def test_empty(self):
        s = Stack()
        self.assertTrue(s.empty())

    def test_size(self):
        s = Stack()
        self.assertEqual(s.size(), 0)
        s.push(1)
        self.assertEqual(s.size(), 1)
        s.push(2)
        self.assertEqual(s.size(), 2)
        s.pop()
        self.assertEqual(s.size(), 1)

    def test_peek_empty(self):
        s = Stack()
        with self.assertRaises(IndexError):
            s.peek()

    def test_pop_empty(self):
        s = Stack()
        with self.assertRaises(IndexError):
            s.pop()

if __name__ == "__main__":
    unittest.main()
