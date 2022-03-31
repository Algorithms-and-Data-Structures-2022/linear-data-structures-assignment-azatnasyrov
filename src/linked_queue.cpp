#include "assignment/linked_queue.hpp"

namespace assignment {

  LinkedQueue::~LinkedQueue() {

    // эквивалентно очистке очереди
    LinkedQueue::Clear();
  }

  void LinkedQueue::Enqueue(int value) {
    Node* added_n = new Node(value);
    if(front_ == nullptr){
      front_ = added_n;
      back_ = added_n;
    }else {
      back_->next = added_n;
      back_ = added_n;
    }
    size_ ++;
  }

  bool LinkedQueue::Dequeue() {
    if(front_ == nullptr) {
      return false;
    }
    Node* removed_n = front_;
    front_ = front_ -> next;
    size_ --;
    delete removed_n;
    if(IsEmpty()) {
      back_ = nullptr;
    }
    return true;
  }

  void LinkedQueue::Clear() {

    size_ = 0;
    for(Node* current_n = front_; current_n != nullptr;){
      Node* removed_n = current_n;
      current_n = current_n -> next;
      delete removed_n;
    }
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedQueue::front() const {
    if(front_ == nullptr) {
      return std::nullopt;
    }
    int val = front_ -> value;
    return val;
  }

  std::optional<int> LinkedQueue::back() const {
    if(back_ == nullptr) {
      return std::nullopt;
    }
    int val = back_ -> value;
    return val;
  }

  bool LinkedQueue::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedQueue::size() const {
    return size_;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedQueue::LinkedQueue(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedQueue::toVector() const {
    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment