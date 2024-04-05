#include "queue.h"

Node::Node(int32_t value, Node* next) : value(value), next(next) {
}

Queue::Queue() : front_(nullptr), tail_(nullptr), size_(0) {
}

Queue::~Queue() {
    Clear();
}

void Queue::Push(int32_t value) {
    Node* new_node = new Node(value, nullptr);
    if (Empty()) {
        front_ = new_node;
        tail_ = new_node;
    } else {
        tail_->next = new_node;
        tail_ = new_node;
    }
    size_++;
}

void Queue::Pop() {
    if (Empty()) {
        return;
    }
    Node* node_to_remove = front_;
    front_ = front_->next;
    delete node_to_remove;
    if (front_ == nullptr) {
        tail_ = nullptr;
    }
    size_--;
}

int32_t Queue::Front() const {
    if (Empty()) {
        return 0;
    }
    return front_->value;
}

int32_t Queue::Size() const {
    return size_;
}

void Queue::Clear() {
    while (!Empty()) {
        Pop();
    }
}

bool Queue::Empty() const {
    return size_ == 0;
}
