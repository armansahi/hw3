#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator()): m_(m), cmp_(c), data_() {
    if (m_ < 2) {
      m_ = 2;
    }
  }

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap() { }

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item) {
    data_.push_back(item);
    heapifyUp(data_.size() - 1);
  }

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const {
    if(empty()) {
      throw std::underflow_error("Heap underflow: top() called on an empty heap."); // call top on empty heap
    }
    return data_[0];
  }

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop() {
    if(empty()) {
      throw std::underflow_error("Heap underflow: pop() called on an empty heap.");
    }
    data_[0] = data_.back();
    data_.pop_back();
    if(!empty()) {
      heapifyDown(0);
    }
  }

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const {
    return data_.empty();
  }

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const {
    return data_.size();
  }

private:
  /// Add whatever helper functions and data members you need below
  int m_; // m-ary val must be >= 2

  PComparator cmp_; // comparator functor for priority

  std::vector<T> data_; // container for heap

  void heapifyUp(int i) {
    while(i > 0) {
      int parent = (i - 1) / m_; // find parent in m-ary heap
      if(cmp_(data_[i], data_[parent])) {
        std::swap(data_[i], data_[parent]);
        i = parent; // move up the tree
      }
      else {
        break;
      }
    }
  }

  void heapifyDown(int i) {
    int heapSize = data_.size(); // for reuse
    int bestIndex = i; // tracks index by highest priority 
    int firstChild = m_ * i + 1;

    for (int j = 0; j < m_; j++) { // check all children 
      int child = firstChild + j;
      if (child < heapSize && cmp_(data_[child], data_[bestIndex])) {  // update if certain child has higher priority
        bestIndex = child;
      }
    }
    if(bestIndex != i) {
      std::swap(data_[i], data_[bestIndex]);
      heapifyDown(bestIndex); // recurse down 
    }
  }
};

#endif

