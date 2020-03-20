#include <iostream>
using namespace std;

template<typename T>
class SinglyList {
    private:
        // node defination
        struct Node {
            T data;
            Node* next;
        };

        // internal head node
        Node* head;
        // internal tail node (this is used to optimize the insertion operation)
        Node* tail;
        // this keeps track of number of nodes in the list
        int _size;

        Node* createNewNode() {
            Node* node = new Node;
            node->next = NULL;
            return node;
        }

    public:
        SinglyList() {
            head = NULL;
            tail = head;
            _size = 0;
        }

        class Iterator {
            private:
                Node* it;
            public:
                Iterator(Node* it) {
                    this->it = it;
                }

                Node* &operator*() {
                    return it;
                }

                Iterator &operator++() {
                    it = it->next;
                    return *this;
                }

                Iterator &operator++(int k) {
                    it = it->next;
                    return *this;
                }

                Iterator &operator+(int k) {
                    for(int i = 0; i < k; i++) {
                        it = it->next;
                    }
                    return *this;
                }

                bool operator!=(const Iterator &other) const{
                    return it != other.it;
                }

                bool operator==(const Iterator &other) const{
                    return it == other.it;
                }
        };

        Iterator begin() {
            return Iterator(head);
        }

        Iterator end() {
            return Iterator(NULL);
        }

        void emplaceBack(const T &data) {
            Node* newNode = createNewNode();
            newNode->data = data;
            if(_size == 0) {
                head = newNode;
                tail = head;
            }
            tail->next = newNode;
            tail = newNode;
            _size++;
        }

        void emplaceFront(const T &data) {
            Node* newNode = createNewNode();
            newNode->data = data;
            newNode->next = head;
            head = newNode;
            _size++;
        }

        void popBack() {
            Node* it = head;
            while (it->next != tail) {
                it = it->next;
            }

            it->next = NULL;
            delete tail;
            tail = it;
            _size--;
        }

        void popFront() {
            Node* temp = head;
            head = head->next;
            delete temp;
            _size--;
        }

        void insert(Iterator at,const T &data) {
            
            if (begin() == at) {
                emplaceFront(data);
                return;
            } else if(end() == at) {
                emplaceBack(data);
                return;
            }

            Node* newNode = createNewNode();
            newNode->data = data;
            auto it = begin();
            while((*it)->next != (*at)) {
                it++;
            }
            newNode->next = (*at);
            (*it)->next = newNode;
            _size++;
        }

        int size() const {
            return _size;
        }
 };

int main() {

    SinglyList<int> a;

    cout << "Size : " << a.size() << endl;

    a.emplaceBack(1);
    a.emplaceBack(2);
    a.emplaceBack(3);
    
    // 0 indexed
    a.insert(a.begin() + 1, 22);

    // Method 1: iterating Linked List
    auto it = a.begin();
    for(int i = 0; i < a.size(); i++) {
        cout << (*it)->data << " -> ";
        (*it) = (*it)->next;
    }
    cout << "NULL\n";
    
    cout << "Size : " << a.size() << endl;

    a.emplaceBack(4);
    a.emplaceBack(5);

    // Method 2: Iterating Linked List
    for(auto i = a.begin(); i != a.end(); i++) {
        cout << (*i)->data << " -> ";
    }
    cout << "NULL\n";

    a.emplaceFront(6);
    
    for(auto i = a.begin(); i != a.end(); i++) {
        cout << (*i)->data << " -> ";
    }
    cout << "NULL\n";

    cout << "Size : " << a.size() << endl;

    a.popBack();
    a.popBack();

    cout << "Size : " << a.size() << endl;
    
    // Method 3: Iterating Linked List
    for(auto i : a) {
        cout << i->data << " -> ";
    }
    cout << "NULL\n";

    a.popFront();
    a.popFront();
    
    cout << "Size : " << a.size() << endl;

    for(auto i : a) {
        cout << i->data << " -> ";
    }
    cout << "NULL\n";

    return 0;
}