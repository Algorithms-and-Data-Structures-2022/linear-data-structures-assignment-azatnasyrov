#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* v = new Node(value);
    if(front_ == nullptr){
      front_ = v;
    }else{
      back_ -> next = v;
    }
    back_= v;
    size_ ++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index > size_ || index < 0) {
      return false;
    }
    Node* v = new Node(value);
    if (front_ == nullptr) {
      back_ = v;
      front_ = v;
    } else {
      if (index == 0) {
        v->next = front_;
        front_ = v;
      } else if (index == size_) {
        back_->next = v;
        back_ = v;
      } else {
        Node* prev = FindNode(index - 1);
        Node* next_ = FindNode(index + 1);
        prev->next = v;
        v->next = next_;
      }
    }
  }

  bool LinkedList::Set(int index, int new_value){
    Node* v = FindNode(index);
    if(v == nullptr){
      return false;
    }
    v -> value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if(index < 0 || index >= size_) {
      return std::nullopt;
    }
    if(index == 0){
      Node* removed_n = front_;
      int removed_val = front_ -> value;
      front_ = front_ -> next;
      delete removed_n;
      size_ --;
      return removed_val;
    }else{
      Node* prev_n = FindNode(index - 1);
      Node* next_n = FindNode(index + 1);
      Node* removed_n = prev_n -> next;
      int removed_val = removed_n -> value;
      prev_n -> next = next_n;
      delete removed_n;
      size_--;
      return removed_val;
    }

  }

  void LinkedList::Clear() {
    size_ = 0;
    for(Node* current_n = front_; current_n != nullptr;){
      Node* removed_n = current_n;
      current_n = current_n -> next;
      delete removed_n;
    }
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    Node* get_n = FindNode(index);
    if(get_n == nullptr){
      return std::nullopt;
    }
    int needed_val = get_n -> value;
    return needed_val;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    int current_i = 0;
    for(Node* current_n = front_; current_n != nullptr;){
      int current_v = current_n -> value;
      if(current_v == value){
        return current_i;
      }
      current_n = current_n -> next;
      current_i ++;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    return IndexOf(value)!= std::nullopt;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if(front_ == nullptr) {
      return std::nullopt;
    }
    int val = front_ -> value;
    return val;
  }

  std::optional<int> LinkedList::back() const {
    if(back_ == nullptr) {
      return std::nullopt;
    }
    int val = back_ -> value;
    return val;
  }

  Node* LinkedList::FindNode(int index) const {
    if(index >= size_ || index < 0) {
      return nullptr;
    }
    int i = 0;
    for(Node* v = front_; v != nullptr; v = v -> next) {
      if(i == index){
        return v;
      }
      i += 1;
    }
    if(index == size_ - 1){
      return back_;
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

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

  std::vector<int> LinkedList::toVector() const {

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