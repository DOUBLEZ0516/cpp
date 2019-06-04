#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>
#include <cstdlib>

#include <algorithm>
using std::copy;
using std::copy_backward;

#include <iterator>
using std::iterator;

#include <memory>
using std::allocator;
using std::uninitialized_fill_n;
using std::uninitialized_copy;




template <class T, class Alloc = allocator<T>>
class MyVector {
public:
  typedef T            value_type;
  typedef value_type*  pointer;
  typedef value_type*  iterator;
  typedef value_type&  reference;
  typedef size_t       size_type; 
  typedef ptrdiff_t    difference_type; // pointer difference type


protected:
  // this is using sgi std::alloc, I am using std::allocator instead
  // typedef simple_alloc<value_type, Alloc> data_allocator;
  
  typedef Alloc        data_allocator;
  iterator start;               // start of current space
  iterator finish;              // end of space used, points to end, not last element
  iterator end_of_storage;      // end of all space allocated

  void insert_aux(iterator position, const T& x); // not sure what's for, used to acquire more space?

  // deallocator
  void deallocate() {
    if (start)
      data_allocator::deallocate(start, end_of_storage - start);
  }

  void fill_initialize(size_type n, const T& value) {
    start = allocate_and_fill(n, value);    
    finish = start + n;
    end_of_storage = finish;
  }

public:
  // element access, const/reverse version is not implemented
  
  // const version is for const vector, which is not supported yet
  // even though non-const vector call begin() can match with
  // begin() const version, this is not a good practise 
  iterator begin(); 

  iterator end() { return finish; }

  size_type size() const { return size_type(end() - begin()); }

  size_type capacity() const { return size_type(end_of_storage - begin()); }

  reference operator[] (size_type n) { return *(begin() + n);}
  reference front() { return *begin(); }        // access first element
  reference back() { return *(end() - 1); }     // access last element

  // capacity
  bool empty() const { return begin() == end(); }
  // constructor
  MyVector() : start(0), finish(0), end_of_storage(0) {}; // iterator is init with long int 0
  MyVector(size_type n, const T& value) { fill_initialize(n, value); }
  MyVector(int n, const T& value) { fill_initialize(n, value); }
  MyVector(long n, const T& value) {fill_initialize(n, value); }
    // use default constructor of T, this is to prevent initilization in this format
    // vector<T> test = b; 
  explicit MyVector(size_type n) { fill_initialize(n, T()); }

  // destructor
  ~MyVector() {
    destroy(start, finish);  // defined in memory std::destroy
    deallocate();
  }


  void push_back(const T& value) {
    
    if(finish != end_of_storage) { // if acquired space is not full
      construct(finish, value); // defined in memory as std::allocator::construct
      ++finish;
    } else {
      insert_aux(end(), value);
    }
  }

  void pop_back() {
    --finish;
    destroy(finish);
  }

  iterator erase(iterator position) { // erase one element
    if (position+1 != end())
      copy(position+1, finish, position); // move elements one step forward

    --finish;
    destroy(finish);
    return position;
  }
  
  void resize(size_type new_size, const T& x); 
  void resize(size_type new_size);

  void clear();


protected:
  // allocate space and fill with value of x
  iterator allocate_and_fill(size_type n, const T& x);



};


#endif