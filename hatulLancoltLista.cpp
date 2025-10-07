#include <iostream>

using namespace std;

struct ListNode {
    int data;
    ListNode *next;
    ListNode(int d) : data(d), next(nullptr) {}
};

class List {
    ListNode *head;
    ListNode *tail;

public:
    // konstruktor
    List(){
        head = tail = nullptr;
    }

    // destruktor: felszabad�tjuk a l�ncot
    ~List() {
        while(head) {
            ListNode *tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // m�sol� konstruktor (deep copy)
    List(const List& other){
        head = tail = nullptr;
        ListNode *cur = other.head;
        while(cur) {
            push_back(cur->data); // �j list�ba bem�soljuk az adatot
            cur = cur->next;
        }
    }

    void push_back(int d) {
        ListNode *node = new ListNode(d);
        if(!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    List& operator=(const List& other) {
        if(this != &other) { // �nmag�ra ad�s ellen
            // r�gi tartalom t�rl�se
            this->~List();

            // �jram�sol�s
            head = tail = nullptr;
            ListNode *cur = other.head;
            while(cur) {
                push_back(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    void selection_sort() {
        for (ListNode* i = head; i != nullptr; i = i->next) {
            ListNode* minNode = i;
            for (ListNode* j = i->next; j != nullptr; j = j->next) {
                if (j->data < minNode->data) {
                    minNode = j;
                }
            }
            // ha tal�ltunk kisebbet, csere
            if (minNode != i) {
                swap(i->data, minNode->data);
            }
        }
    }

    void print() const {
        for (ListNode* cur = head; cur; cur = cur->next) {
            cout << cur->data << " ";
        }
        cout << endl;
    }

    ListNode* getHead() const { return head; }
    ListNode* getTail() const { return tail; }

    // Rendezett besz�r�s
    void sorted_insert(int d) {
        ListNode* node = new ListNode(d);

        // �res lista vagy az �j elem kisebb mint head
        if(!head || d <= head->data) {
            node->next = head;
            head = node;
            if (!tail) tail = node;
            return;
        }

        // keres�s: hova sz�rjunk
        ListNode* cur = head;
        while (cur->next && cur->next->data < d) {
            cur = cur->next;
        }

        node->next = cur->next;
        cur->next = node;

        if (!node->next) {
            tail = node; // ha a v�g�re sz�rtunk
        }
    }

    //�sszef�s�l�s
    static List merge(const List& a, const List& b) {
        List result;
        ListNode* p1 = a.getHead();
        ListNode* p2 = b.getHead();

        while (p1 && p2) {
            if (p1->data <= p2->data) {
                result.push_back(p1->data);
                p1 = p1->next;
            } else {
                result.push_back(p2->data);
                p2 = p2->next;
            }
        }

        // marad�k �tm�sol�sa
        while (p1) {
            result.push_back(p1->data);
            p1 = p1->next;
        }
        while (p2) {
            result.push_back(p2->data);
            p2 = p2->next;
        }

        return result;
    }

    // + oper�tor: merge megh�v�sa
    List operator+(const List& other) const {
        return merge(*this, other);
    }

    // << oper�tor: ostream ki�r�s
    friend ostream& operator<<(ostream& os, const List& lst) {
        for (ListNode* cur = lst.head; cur; cur = cur->next) {
            os << cur->data << " ";
        }
        return os;
    }
};

int main() {
    List list1;
    list1.sorted_insert(9);
    list1.sorted_insert(3);
    list1.sorted_insert(5);
    list1.sorted_insert(1);
    list1.sorted_insert(7);

    List list2;
    list2.sorted_insert(8);
    list2.sorted_insert(4);
    list2.sorted_insert(6);
    list2.sorted_insert(2);
    list2.sorted_insert(0);

    cout << "Lista 1: ";
    //list1.print();
    cout << list1 << endl;;
    cout << "Lista 2: ";
    //list2.print();
    cout << list2 << endl;;

    //List merged = List::merge(list1, list2);
    cout << "Osszefesult lista: ";
    //merged.print();
    cout << list1 + list2 << endl;;
    return 0;
}
