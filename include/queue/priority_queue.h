#pragma once

#include <vector>
#include <algorithm>

template<typename T, typename Container = std::vector<T>, class Compare = std::greater<T>>
class priority_queue {
public:
  // 向上调整
  void shiftUp(int child) {
    int parent = (child - 1) / 2;
    while(child > 0) {
      if (compare_(container_[parent], parent[child])) {
        using std::swap;
        swap(container_[parent], container_[child]);
        child = parent;
        parent = (child - 1) / 2;
      } else {
        break;
      }
    }
  }
  // 向下调整
  void shiftDown(int parent) {
    int child = parent * 2 + 1;
    while(child < container_.size()) {
      if (child + 1 < container_.size() && compare_(container_[child], container_[child + 1])) {
        child++;
      }
      if (compare_(container_[parent], container_[child])) {
        using std::swap;
        swap(container_[parent], container_[child]);
        parent = child;
        child = parent * 2 + 1;
      } else {
        break;
      }
    }
  }

  void push(const T& val) {
    container_.push_back(val);
    shiftUp(container_.size() - 1);
  }

  void pop() {
    using std::swap;
    swap(container_[0], container_[container_.size() - 1]);
    shiftDown(0);
  }

  T& top() {
    return container_.front();
  }

  bool empty() { return container_.empty(); }

  size_t size() { return container_.size(); }
  
private:
  Container container_;
  Compare compare_;
};
