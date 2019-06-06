#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>
#include <cstdlib>

#include <algorithm>
using std::copy;
using std::copy_backward;
using std::fill;

#include <iterator>
using std::iterator;

#include <memory>
using std::allocator;
using std::uninitialized_fill_n;
using std::uninitialized_copy;
// using std::destroy;




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
  
  // typedef  Alloc       data_allocator;
  allocator<T> data_allocator;
  iterator start;               // start of current space
  iterator finish;              // end of space used, points to end, not last element
  iterator end_of_storage;      // end of all space allocated

  void insert_aux(iterator position, const T& x) {
    if (finish != end_of_storage) {
      // still have empty space
      data_allocator.construct(finish, *(finish-1));
      ++finish;
      T x_copy = x;
      // copy elements from [position, finish-2) to [position+1, finish-1)
      copy_backward(position, finish-2, finish-1);
      *position=x_copy;
    } else {
      // no empty space
      const size_type old_size = size();
      // if old_size==0, allocate space of 1, else double of old_space
      const size_type len = (old_size != 0 ? 2 * old_size : 1);
      // std::cout << "new len: " << len << std::endl;
      iterator new_start = data_allocator.allocate(len);
      iterator new_finish = new_start;

      try {
        // copy old elements to new vector
        // copy elements to uninitialized memory
        // returns the end iterator of new space 
        // uninitialized_copy(first, end, new_first);
        new_finish = uninitialized_copy(start, position, new_start);

        // insert new value
        data_allocator.construct(new_finish, x);
        ++new_finish;

        // copy rest elements after insert place
        new_finish = uninitialized_copy(position, finish, new_finish);
      }


      catch(...) {
        // catch(...) can capture many types of exception
        // a supplement to conditions that r not covered 
        // if u define catch(exceptions) yourselves
        
        // commit or rollback semantic
        // destory(new_start, new_finish);
        data_allocator.deallocate(new_start, len);
        throw;
      }

      // deconstruct old vector
      // destroy(begin(), end());
      deallocate();

      // points to new memory space
      start = new_start;
      finish = new_finish;
      end_of_storage = new_start + len;
    }
  }

  // deallocator
  void deallocate() {
    if (start)
      data_allocator.deallocate(start, end_of_storage - start);
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
  iterator begin() { return start; } 

  iterator end() { return finish; }

  size_type size()  { return size_type(end() - begin()); }

  size_type capacity() { return size_type(end_of_storage - begin()); }

  reference operator[] (size_type n) { return *(begin() + n);}
  reference front() { return *begin(); }        // access first element
  reference back() { return *(end() - 1); }     // access last element

  // capacity
  bool empty() const { return begin() == end(); }
  // constructor
  MyVector() : start(0), finish(0), end_of_storage(0) {}; // iterator is init with long int 0
  MyVector(size_type n, const T& value) { fill_initialize(n, value); }
  MyVector(int n, const T& value) { fill_initialize(n, value); }
  MyVector(long n, const T& value) { fill_initialize(n, value); }
    // use default constructor of T, this is to prevent initilization in this format
    // vector<T> test = b; 
  explicit MyVector(size_type n) { fill_initialize(n, T()); }

  // destructor
  ~MyVector() {
    // destroy(start, finish);  // defined in memory std::destroy
    // deallocate();
  }


  void push_back(const T& value) {
    
    if(finish != end_of_storage) { // if acquired space is not full
      data_allocator.construct(finish, value); // defined in memory as std::allocator::construct
      ++finish;
    } else {
      insert_aux(end(), value);
    }
  }

  void pop_back() {
    --finish;
    // destroy(finish);
  }

  iterator erase(iterator position) { // erase one element
    if (position+1 != end())
      copy(position+1, finish, position); // move elements one step forward

    --finish;
    // destroy(finish);
    return position;
  }

  iterator erase(iterator first, iterator last) {
    iterator i = copy(last, finish, first);
    // destroy(i, finish);
    finish = finish - (last - first);
    return first;
}
  
  void resize(size_type new_size, const T& x) {
    if (new_size < size()) 
      erase(begin()+new_size, end());
    else
      insert(end(), new_size-size(), x);
  }

  void resize(size_type new_size) { resize(new_size, T()); }

  void clear() { erase(begin(), end()); }

  void insert(iterator position, size_type n, const T& x) {
    if (n != 0) {
      if (size_type(end_of_storage - finish) >= n) { 
        // has enough capacity to accept new elements
        T x_copy = x;
        // # of elements we had after position
        const size_type elems_after = finish - position;
        iterator old_finish = finish;
        if (elems_after > n) {
          // #elements we had after position greater than #new
          // copy n elements from [finish-n, finish) to [finish, finish+n)
          // [1, 2, 3, 4] insert(1, 1, 0)
          uninitialized_copy(finish-n, finish, finish);
          // output: [1, 2, 3, 4, 4]
          finish += n;
          // input: [1, 2, 3, 4, 4]
          copy_backward(position, old_finish-n, old_finish);
          // output: [1, 2, 2, 3, 4]
          fill(position, position+n, x);
          // output: [1, 0, 2, 3, 4]
        } else {
          // #elements we had after position less than #new
          // input: [1, 2, 3, 4] insert(2, 3, 0) 
          uninitialized_fill_n(finish, n-elems_after, x_copy);
          // output: [1, 2, 3, 4, 0]
          finish +=  n - elems_after;
          uninitialized_copy(position, old_finish, finish);
          // output: [1, 2, 3, 4, 0, 3, 4]
          finish += elems_after;

          fill(position, old_finish, x_copy);
          // output: [1, 2, 0, 0, 0, 3, 4]
        }
      } else {
        // current capacity is not enough
        // decide new length: either 2 * old_size or old_size + n
        const size_type old_size = size();
        const size_type len = old_size + std::max(old_size, n);

        // allocate new vector space
        iterator new_start = data_allocator.allocate(len);
        iterator new_finish = new_start;

        // __STL_TRY {
          // copy [old_start, position) to new space
          new_finish = uninitialized_copy(start, position, new_start);
          // insert new elements
          new_finish = uninitialized_fill_n(new_finish, n, x);
          // copy [position, old_finish) to new space
          new_finish = uninitialized_copy(position, finish, new_finish);
        // }

        // #ifdef __STL_USE_EXCEPTIONS
        // catch(...) {
        //   // if exceptions happen, use commit or roll back semantic
        //   destroy(new_start, new_finish);
        //   data_allocator::deallocate(new_start, len);
        //   throw;
        // }
        // #endif /* __STL_USE_EXCEPTIONS */

        // release space of old vector
        // destroy(start, finish);
        deallocate();

        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;

      }
    }
  }

protected:
  // allocate space and fill with value of x
  iterator allocate_and_fill(size_type n, const T& x) {
    iterator result = data_allocator.allocate(n);
    // uninitialized_fill_n(first, count, value)
    // first: beignning range
    // count: # of elements to construct
    // value: value used to construct
    uninitialized_fill_n(result, n, x);
    return result;
  }



};


#endif