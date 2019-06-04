#include "myvector.h"


template <class T, class Alloc = allocator<T>>
iterator MyVector<T,Alloc>::begin() { return start; }





template <class T, class Alloc = allocator<T>>
void MyVector<T,Alloc>::resize(size_type new_size, const T& x) {
  if (new_size < size()) 
    erase(begin()+new_size, end());
  else
    insert(end(), new_size-size(), x);
}

template <class T, class Alloc = allocator<T>>
void MyVector<T,Alloc>::resize(size_type new_size) {
  resize(new_size, T());
}

template <class T, class Alloc = allocator<T>>
void MyVector<T,Alloc>::clear() {
  erase(begin(), end());
}

template <class T, class Alloc = allocator<T>>
iterator MyVector<T,Alloc>::allocate_and_fill(size_type n, const T& x) {
  iterator result = data_allocator::allocate(n);
  // uninitialized_fill_n(first, count, value)
  // first: beignning range
  // count: # of elements to construct
  // value: value used to construct
  uninitialized_fill_n(result, n, x);
  return result;
}


template <class T, class Alloc = allocator<T>>
void MyVector<T,Alloc>::insert_aux(iterator position, const T& x) {
  if (finish != end_of_storage) {
    // still have empty space
    construct(finish, *(finish-1));
    ++finish;
    T x_copy = x;
    // copy elements from (position to finish-2) to (position+1 to finish-1)
    copy_backward(position, finish-2, finish-1);
    *position=x_copy;
  } else {
    // no empty space
    const size_type old_size = size();
    // if old_size==0, allocate space of 1, else double of old_space
    const size_type len = (old_size != 0 ? 2 * old_size : 1);

    iterator new_start = data_allocator::allocate(len);
    iterator new_finish = new_start;

    try {
      // copy old elements to new vector
      // copy elements to uninitialized memory
      // returns the end iterator of new space 
      // uninitialized_copy(first, end, new_first);
      new_finish = uninitialized_copy(start, position, new_start);

      // insert new value
      construct(new_finish, x);
      ++finish;

      // copy rest elements after insert place
      new_finish = uninitialized_copy(position, finish, new_finish);
    }


    catch(...) {
      // catch(...) can capture many types of exception
      // a supplement to conditions that r not covered 
      // if u define catch(exceptions) yourselves
      
      // commit or rollback semantic
      destory(new_start, new_finish);
      data_allocator::deallocate(new_start, len);
      throw;
    }

    // deconstruct old vector
    destroy(begin(), end());
    deallocate();

    // points to new memory space
    start = new_start;
    finish = new_finish;
    end_of_storage = new_start + len;
  }


}