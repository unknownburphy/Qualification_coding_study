class Node:
    def __init__(self, value=None, next_node=None):
        self.value = value
        self.next = next_node

class SLList:
    def __init__(self):
        self.head = None

    def addFirst(self, x):
        new_node = Node(x)
        new_node.next = self.head
        self.head = new_node

    # Returns True if x is in the list, False otherwise
    def contains(self, x):
        current = self.head
        while current is not None:
            if current.value == x:
                return True
            current = current.next
        return False

    def remove(self, x):
        current = self.head
        previous = None
        while current is not None:
            if current.value == x:
                if previous is None:  # Removing the head
                    self.head = current.next
                else:
                    previous.next = current.next
                return True  # Indicate that we removed the item
            previous = current
            current = current.next
        return False  # Indicate that the item was not found


class di_array:
    def __init__(self):
        self.size = 11
        self.array = [None] * self.size
        self.count = 0

    def hash_value(self, x: str):
        B = 31
        ans = 0
        for ch in x:
            ans = ans * B + ord(ch)
        return ans % self.size

    def add(self, x):
        if self.count / self.size > 1.5:
            self.resize()

        i = self.hash_value(x)
        if self.array[i] is None:
            self.array[i] = SLList()

        if not self.array[i].contains(x):  # Avoid duplicates
            self.array[i].addFirst(x)
            self.count += 1

    def remove(self, x):
        i = self.hash_value(x)
        if self.array[i] is not None:
            if self.array[i].remove(x):
                self.count -= 1

    def resize(self):
        old_array = self.array
        self.size *= 2
        self.array = [None] * self.size
        self.count = 0

        for bucket in old_array:
            if bucket is not None:
                current = bucket.head
                while current is not None:
                    self.add(current.value)
                    current = current.next

    def __contains__(self, x):
        i = self.hash_value(x)
        if self.array[i] is not None:
            return self.array[i].contains(x)
        return False

# Testing the updated hash table with remove functionality
A = di_array()
A.add("")
A.add("pace!")
print("" in A)  # True
print("hello" in A)  # False

A.remove("")
print("" in A)  # False, since it was removed

A.remove("pace!")
print("pace!" in A)  # False, since it was removed