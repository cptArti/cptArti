#include "stack.h"

Node::Node(int32_t value, Node* previous) {
    this->value = value;
    this->previous = previous;
}

Stack::Stack() {
    this->head_ = nullptr;
    this->size_ = 0;
}

Stack::~Stack() {
    while (!Empty()) {
        Pop();
    }
}

void Stack::Push(int32_t value) {
    this->head_ = new Node(value, this->head_);
    this->size_++;
}

void Stack::Pop() {
    Node* tmp = this->head_;
    this->head_ = this->head_->previous;
    delete tmp;
    this->size_--;
}

int32_t Stack::Top() const {
    return head_->value;
}

int32_t Stack::Size() const {
    return this->size_;
}

bool Stack::Empty() const {
    return this->size_ == 0;
}

void Stack::Clear() {
    while (!Empty()) {
        Pop();
    }
}
