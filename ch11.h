#ifndef CH11
#define CH11

#include <iostream>

template<class key_type, class data_type, int m>
class HashTable
{
    class DobuleLinkedList
    {
        struct KeyData {
            key_type key;
            data_type data;
        };
        class DoubleNode {  
        public:
            KeyData _item;
            DoubleNode *_next, *_prev;

            DoubleNode(DoubleNode *next, DoubleNode *prev, KeyData item) {
                _item = item;
                _next = next;
                _prev = prev;
            }
        };

        DoubleNode *head;

    public:
        DobuleLinkedList() {
            head = new DoubleNode(NULL, NULL, KeyData());
        }
        void insert(key_type key, data_type x) {
            KeyData tmp_data;
            tmp_data.key = key;
            tmp_data.data = x;
            DoubleNode *tmp = new DoubleNode(head->_next, head, tmp_data);
            head->_next = tmp;
        }
        DoubleNode* find(key_type key) {
            DoubleNode *result = head;
            while (result && result->_item.key != key)
                result = result->_next;
            return result;
        }
        void del(key_type key) {
            DoubleNode *result = head;
            while (result && result->_item.key != key)
                result = result->_next;

            result->_prev->_next = result->_next;
            if (result->_next)
                result->_next->_prev = result->_prev;

            delete result;
        }
        ~DobuleLinkedList() {
            DoubleNode *current = head;
            while (head->_next)
                this->del(head->_next->_item.key);
            delete head;
        }
    };
    
    DobuleLinkedList table[m];
    int (*h)(key_type);
public:
    HashTable(int (*h_f)(key_type)) {
        this->h = h_f;
    }
    data_type search(key_type k) {
        return table[this->h(k)].find(k)->_item.data;
    }
    void del(key_type k) {
        table[this->h(k)].del(k);
    }
    void insert(key_type key, data_type data) {
        table[this->h(key)].insert(key, data);
    
    }
};


template<class key_type, class data_type, int m>
class OpenHashTable {
// Abstract class
    struct KeyData {
        key_type key;
        data_type data;
    };

    KeyData *table[m];
    bool filled[m];
    virtual int h_iter(key_type k, int i) = 0;
public:
    
    OpenHashTable() {
        for (int i = 0; i < m; i++)
            filled[i] = false;
    }

    void insert(key_type k, data_type x) {
        for (int i = 0; i <= m; i++) {
            int j = this->h_iter(k, i);
            if (!filled[j]) {
                table[j] = new KeyData();
                table[j]->key = k;
                table[j]->data = x;
                filled[j] = true;
                break;
            }
        }
    }

    data_type search(key_type key) {
        for (int i = 0; i <= m; i++) {
            int j = this->h_iter(key, i);
            if (filled[j] && table[j]->key == key) {
                return table[j]->data;
            }
        }
        return data_type();
    }

    void show_table() {        
        for (int i = 0; i < m; i++) {
            if (filled[i])
                std::cout << table[i]->key << " " << table[i]->data << std::endl;
            else
                std::cout << "NIL\n";
        }
    }

    ~OpenHashTable() {
        for (int i = 0; i < m; i++) {
            if (filled[i]) {
                delete table[i];
            }
        }
    }
};


template<class key_type, class data_type, int m>
class LinearOpenHashTable : public OpenHashTable<key_type, data_type, m> {
    int (*h)(key_type);
    int h_iter(key_type k, int i) {
        return (h(k) + i) % m;
    }

public: 

    LinearOpenHashTable(int (*_h)(key_type)) {
        this->h = _h;
    }
};


template<class key_type, class data_type, int m>
class QuadroOpenHashTable : public OpenHashTable<key_type, data_type, m> {
    int (*h)(key_type);
    int _c1, _c2;
    int h_iter(key_type k, int i) {
        return (h(k) + _c1 * i + _c2 * i * i) % m;
    }

public:

    QuadroOpenHashTable(int (*_h)(key_type), int c1, int c2) {
        this->h = _h;
        c1 = _c1;
        c2 = _c2;
    }
};


template<class key_type, class data_type, int m>
class DoubleHashOpenHashTable : public OpenHashTable<key_type, data_type, m> {
    int (*h1)(key_type);
    int (*h2)(key_type);
    int h_iter(key_type k, int i) {
        return (h1(k) + i * h2(k)) % m;
    }
public:

    DoubleHashOpenHashTable(int (*_h1)(key_type), int (*_h2)(key_type)) {
        this->h1 = _h1;
        this->h2 = _h2;
    }
};



#endif