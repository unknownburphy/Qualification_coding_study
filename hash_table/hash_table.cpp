#include <iostream>
#include <vector>
#include <string>

class Node {
public:
    std::string value;
    Node* next;

    Node(std::string value = "", Node* next_node = nullptr) : value(value), next(next_node) {}
};

class SLList {
public:
    Node* head;

    SLList() : head(nullptr) {}

    void addFirst(std::string x) {
        Node* new_node = new Node(x);
        new_node->next = head;
        head = new_node;
    }

    // Returns true if x is in the list, false otherwise
    bool contains(std::string x) {
        Node* current = head;
        while (current != nullptr) {
            if (current->value == x) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    bool remove(std::string x) {
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->value == x) {
                if (previous == nullptr) {  // Removing the head
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                return true;  // Indicate that we removed the item
            }
            previous = current;
            current = current->next;
        }
        return false;  // Indicate that the item was not found
    }
};

class di_array {
public:
    int size;
    std::vector<SLList*> array;
    int count;

    di_array() : size(11), array(size, nullptr), count(0) {}

    int hash_value(const std::string& x) {
        int B = 31;
        int ans = 0;
        for (char ch : x) {
            ans = ans * B + ch;
        }
        return ans % size;
    }

    void add(const std::string& x) {
        if (static_cast<float>(count) / size > 1.5) {
            resize();
        }

        int i = hash_value(x);
        if (array[i] == nullptr) {
            array[i] = new SLList();
        }

        if (!array[i]->contains(x)) {  // Avoid duplicates
            array[i]->addFirst(x);
            count++;
        }
    }

    void remove(const std::string& x) {
        int i = hash_value(x);
        if (array[i] != nullptr) {
            if (array[i]->remove(x)) {
                count--;
            }
        }
    }

    void resize() {
        std::vector<SLList*> old_array = array;
        size *= 2;
        array = std::vector<SLList*>(size, nullptr);
        count = 0;

        for (SLList* bucket : old_array) {
            if (bucket != nullptr) {
                Node* current = bucket->head;
                while (current != nullptr) {
                    add(current->value);
                    current = current->next;
                }
                delete bucket;
            }
        }
    }

    bool contains(const std::string& x) {
        int i = hash_value(x);
        if (array[i] != nullptr) {
            return array[i]->contains(x);
        }
        return false;
    }
};

// Testing the updated hash table with remove functionality
int main() {
    di_array A;
    A.add("22222");
    A.add("pace!");
    std::cout << (A.contains("22222") ? "True" : "False") << std::endl;  // True
    std::cout << (A.contains("hello") ? "True" : "False") << std::endl;  // False

    A.remove("22222");
    std::cout << (A.contains("22222") ? "True" : "False") << std::endl;  // False, since it was removed

    A.remove("pace!");
    std::cout << (A.contains("pace!") ? "True" : "False") << std::endl;  // False, since it was removed

    return 0;
}