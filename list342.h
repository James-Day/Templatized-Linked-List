#ifndef LIST342_H_
#define LIST342_H_

#include <iostream>
#include <fstream>

using namespace std;
template <class T>
struct Node {
	T* data = nullptr;
	Node* next = nullptr;
};
template <class T>
class List342
{
public:
    
    List342();
    List342(const List342<T>& source);
    ~List342();

    bool BuildList(string file_name);
	bool Insert(T* obj);
	bool Remove(T target, T& result);
	bool Peek(T target, T& result) const;
	bool isEmpty() const;
	void DeleteList();
	bool Merge(List342 &list1);
   
    List342<T> operator+(const List342<T>& rhs) const;
    List342<T>& operator+=(const List342<T>& rhs);
    List342<T>& operator=(const List342<T>& rhs);
    bool operator==(const List342<T>& rhs) const;
    bool operator!=(const List342<T>& rhs) const;
    friend ostream& operator<< <> (ostream& stream, const List342<T>& stack);
private:
	Node<T>* head_ = nullptr;
};

template<class T>
List342<T>::List342(): head_(nullptr) {
}

template<class T>
List342<T>::List342(const List342<T>& source) : head_(nullptr) {
    *this = source;
}
template <class T>
List342<T>::~List342() {
    this->DeleteList();
}

template <class T>
bool List342<T>::BuildList(string file_name) {
    ifstream in_file;

    in_file.open(file_name);
    if (in_file.is_open()) {
        while (!in_file.eof()) {
            T temp;
            in_file >> temp;
            T* insert = new T;
            *(insert) = temp;
            this->Insert(insert);
            delete insert;
        }
        in_file.close();
        return true;
    }
    return false;
}

template <class T>
bool List342<T>::Insert(T* obj){
   
    //empty list
    if (head_ == nullptr) {
        head_ = new Node<T>;
        T* insert_value = new T(*obj);
        head_->data = insert_value;
        return true;
    }
    //insert before first item in the list
    if (*(obj) < *(head_->data)) {
        Node<T>* insert_node = new Node<T>;
        T* insert_value = new T(*obj);
        insert_node->data = insert_value;
        insert_node->next = head_;
        this->head_ = insert_node;
        return true;
    }
    //duplicate of first item in list
    if (*(obj) == *(head_->data)) {
        return false;
    }

    Node<T>* iter = head_;
    while ((iter->next != nullptr) && *(iter->next->data) < *(obj)) {
        iter = iter->next;
    }
    //trying to insert a duplicate in the middle of the list
    if ((iter->next != nullptr) && (*(iter->next->data) == *(obj))) {
        return false;
    }
    Node<T>* insert_node = new Node<T>;
    T* insert_value = new T(*obj);
    insert_node->data = insert_value;
    insert_node->next = iter->next;
    iter->next = insert_node;
    return true;
}

template <class T>
bool List342<T>::Remove(T target, T& result) {
    //if nothing is removed, return garbage for result
    result;
    //delete from empty list
    if (head_ == nullptr) {
        return false;
    }
    //delete is head of the list
    if (target == *(head_->data)) {
        Node<T>* del_ptr = head_;
        head_ = head_->next;
        result = *(del_ptr->data);
        delete del_ptr->data;
        del_ptr->data = nullptr;
        delete del_ptr;
        del_ptr = nullptr;
        return true;
    }

    Node<T>* itr = head_;
    while ((itr->next != nullptr) && (*(itr->next->data) < target)) {
        itr = itr->next;
    }

    //didn't find node, and at end of the list
    if (itr->next == nullptr) {
        return false;
    }
    if (*(itr->next->data) == target) {
        Node<T>* del_ptr = itr->next;
        itr->next = itr->next->next;
        result = *(del_ptr->data);
        delete del_ptr->data;
        del_ptr->data = nullptr;
        delete del_ptr;
        del_ptr = nullptr;
        return true;
    }
    return false;

}

template <class T>
bool List342<T>::Peek(T target, T& result) const{
    //if nothing is found, return garbage for result
    result;
    //empty list
    if (head_ == nullptr) {
        return false;
    }
    //target is head
    if (target == *(head_->data)) {
        result = *(head_->data);
        return true;
    }

    Node<T>* itr = head_;
    while ((itr->next != nullptr) && (*(itr->next->data) < target)) {
        itr = itr->next;
    }

    //didn't find node, and at end of the list
    if (itr->next == nullptr) {
        return false;
    }

    //found middle of list
    if (*(itr->next->data) == target) {
        result = *(itr->next->data);
        return true;
    }
    //didn't find node, middle of list
    return false;

}

template <class T>
bool List342<T>::isEmpty() const{
    if(head_ == nullptr){
        return true;
    }
    else {
        return false;
    }
}

template <class T>
void List342<T>::DeleteList(){
    while (head_ != nullptr) {
        Node<T>* del_ptr = head_;
        head_ = head_->next;
        delete del_ptr->data;
        delete del_ptr;
    }
}

template <class T>
bool List342<T>::Merge(List342& list1){
    Node<T>* this_itr = head_;
    Node<T>* l1_itr = list1.head_;
    //merge being called on itself
    if (this == &list1) {
        return false;
    }
    //nothing to merge
    if (list1.head_ == nullptr) {
        return false;
    }
    //meging into a empty list
    if (this->head_ == nullptr) {
        this->head_ = list1.head_;
        list1.head_ = nullptr;
        return true;
    }

    //while nodes in argument are less than this head
    if ((*(l1_itr->data) < *(this_itr->data))) {
        Node<T>* temp = head_;
        head_ = l1_itr;
        this_itr = head_;
        while((l1_itr->next != nullptr) && (*(l1_itr->next->data) < *(temp->data))) {
            l1_itr = l1_itr->next;
            this_itr = this_itr->next;
        }
        list1.head_ = l1_itr->next;
        l1_itr->next = temp;
    }
   
    l1_itr = list1.head_;

    while (l1_itr != nullptr) {
        if (this_itr->next != nullptr) {
            if ((*(l1_itr->data) > *(this_itr->data)) && *(l1_itr->data) < *(this_itr->next->data)) {
                Node<T>* temp;
                temp = this_itr->next;
                this_itr->next = l1_itr;
                l1_itr = l1_itr->next;
                this_itr->next->next = temp;
                list1.head_ = l1_itr;
            }
            //if there is a duplicate
            else if (*(l1_itr->data) == *(this_itr->data)) {
                Node<T>* temp = l1_itr;
                l1_itr = l1_itr->next;
                //if the duplicate is the head
                if (*(temp->data) == *(list1.head_->data)) {
                   list1.head_ = l1_itr;
                }
                delete temp->data;
                delete temp;
            }
            else {
                this_itr = this_itr->next;
            }
        }
        //all nodes left in l1 are larger than values in this list
        else {
            this_itr->next = l1_itr;
            l1_itr = nullptr;
            list1.head_ = nullptr;
        }
    }
    return true;
}

template <class T>
List342<T> List342<T>::operator+(const List342<T>& rhs) const {
    List342<T> result;
    result = *this;
	result += rhs;
	return result;
}

template <class T>
List342<T>& List342<T>::operator+=(const List342<T>& rhs) { //can't call Insert, should be running through both lists // = then merge is allowed just inefficient
                                                            //on cmd find the exe, using > redirect to output.txt
    Node<T>* this_itr = head_;
    Node<T>* rhs_itr = rhs.head_;
    //+= being called on itself
    if (this == &rhs) {
        return *this;
    }
    //nothing to add
    if (rhs.head_ == nullptr) {
        return *this;
    }
    //I know this is a bit inefficent, if I had a bit more time I could do this with two pointers
    //but, prof said this will get full points for now.
    List342 copy_list = rhs;
    this->Merge(copy_list);
    return *this;
}

template <class T>
List342<T>& List342<T>::operator=(const List342<T>& rhs) {
    
    if (this == &rhs) {
        return *this;
    }

    this->DeleteList();
    Node<T>* this_itr = head_;
    Node<T>* rhs_itr = rhs.head_;
    while (rhs_itr != nullptr) {
        this->Insert(rhs_itr->data);
        rhs_itr = rhs_itr->next;
    }
    return *this;
}

template <class T>
bool List342<T>::operator==(const List342<T>& rhs) const {
    Node<T>* this_itr = head_;
    Node<T>* rhs_itr = rhs.head_;

    if (this_itr == nullptr || rhs_itr == nullptr) {
        if (this_itr == nullptr && rhs_itr == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }
    while ((this_itr != nullptr && rhs_itr != nullptr) && (*(this_itr->data) == *(rhs_itr->data))) {
        this_itr = this_itr->next;
        rhs_itr = rhs_itr->next;
    }
    if (this_itr == nullptr || rhs_itr == nullptr) {
        if (this_itr == nullptr && rhs_itr == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

template <class T>
bool List342<T>::operator!=(const List342<T>& rhs) const {
    return (!(*this == rhs));
}

template <class T>
ostream& operator<<(ostream& stream, const List342<T>& stack) {
    Node<T>* p_node = stack.head_;
    while (p_node != nullptr) {
        stream << *(p_node->data);
        p_node = p_node->next;
    }
    return stream;
}

#endif

