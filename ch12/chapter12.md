## Chapter 12 Dynamic Memory and Smart Ptr



#### shared_ptr

```c++
// it's explicit to use a ptr to construct a shared_ptr
shared_ptr<int> p1 = new int(1024);		// wrong, it contains a implicit conversion
shared_ptr<int> p1 (new int(1024));		// correct

shared_ptr<int> clone(int p) {
  return new int(p);  	// wrong, implicit conversion
  return shared_ptr<int> (new int(p)); // correction
}
```



#### unique_ptr

```c++
unique_ptr<int> q;
unique_ptr<int> q (new int(12));

// not supporting copy and assignment
unique_ptr<int> p1(p2); // wrong
p3 = p4;								// wrong

// but return a unique_ptr is supported (move is called here)

unique_ptr p2(p1.release());			// p1 is set to nullptr, p2 take over p1's earlier obj
p2.reset(p3.release());						// p3 set to nullptr, p2 relase old obj and take over
																	// obj given up by p3

p2.release();      		// wrong practise, obj is not released and cannot be traced
auto p1 = p2.release(); // correct practise
```



#### weak_ptr

 



#### allocator

```c++

```













#### 12.4

> In our check function we didn’t check whether i was greater than zero. Why is it okay to omit that check?

Because the type of `i` is `std::vector<std::string>::size_type` which is an `unsigned`.When any argument less than 0 is passed in, it will convert to a number greater than 0. In short `std::vector<std::string>::size_type` will ensure it is a positive number or 0.



#### 12.5

###### pros

- The compiler will not use this constructor **in an automatic conversion**.
- We can realize clearly which class we have used.

###### cons 

- We always uses the constructor to construct **a temporary StrBlob object**.
- cannot use the copy form of initialization with an explicit constructor. not easy to use.



#### 12.8

```C++
bool b() {
    int* p = new int;
    // ...
    return p;
}
```

The p will convert to a bool ,which means that the dynamic memory allocated has no chance to be freed. As a result, memory leakage will occur.

#### 12.9

> Explain what happens in the following code:

```c++
int *q = new int(42), *r = new int(100);
r = q;
auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
r2 = q2;
```

- to `q` and `r`:

Memory leakage happens. Because after `r = q` was executed, no pointer points to the int `r` had pointed to. It implies that no chance to free the memory for it.

- to `q2` and `r2`:

Memory that r2 used to point to is freed automatically as it is using smart ptr

#### 12.11

p.get() returns a plain ptr and this ptr is use to construct another shared_ptr p2 that is different from p.

the p2 is deleted after process finished hence p is dangling



#### 12.12

```c++
void process(shared_ptr<int> p) {
  cout << "inside process, use_count: " << p.use_count() << endl; 
}

auto p = new int();        // plain ptr
auto sp = make_shared<int> ();

process(sp);						// legal, a copy of sp is passed
process(new int());			// illegal, implicit conversion is not supported
process(p);							// illegal, same to above
process(shared_ptr<int> (p));	// legal but bad
															// let p2 = shared_ptr<int> (p)
															// *p2 is deleted but p is dangling outside
```



#### 12.13

```c++
auto sp = std::make_shared<int>();
auto p = sp.get();
delete p;

// sp is dangling after p is deleted, which ultimately caused double free
// as program finished
```



#### 12.17

```c++
// given
int ix = 1024;
int *pi = &ix;
int *pi2 = new int(2048);

typedef unique_ptr<int> intp;

intp p0(ix);			// not ptr returned by new
intp p1(pi);				
intp p1(pi2);			// both work, but will cause dangling ptr
intp p3(&ix);			// dangling ptr
intp p4(new int(2048)); // good
intp p5(p2.get());	// dangling ptr

// dangling ptr will cause double free problem.
```



#### 12.18

 Because other shared_ptr that points the same object can still delete this object.Thus, it's meaningless to provide this member more detail can be found a thread on Stack Overflow:

http://stackoverflow.com/questions/1525764/how-to-release-pointer-from-boostshared-ptr



#### 12.21

the origin version is better. cause it's more **readability** and **easier to debug**.



#### 12.23

```c++
#include <iostream>
#include <string>
#include <cstring>	

const char *c1 = "Hello ";
const char *c2 = "World";
unsigned len = strlen(c1) + strlen(c2) + 1; // str has a end at the end
char *r = new char[len]();                  // allocate space
strcat_s(r, len, c1);
strcat_s(r, len, c2);
std::cout << r << std::endl;

std::string s1 = "Hello ";
std::string s2 = "World";
strcpy_s(r, len, (s1 + s2).c_str());
std::cout << r << std::endl;

delete[] r;
```



#### 12.24

```c++
#include <iostream>
// need to tell the size.
std::cout << "How long do you want the string? ";
int size{0};
std::cin >> size;
char* input = new char[size + 1]();
std::cin.ignore();
std::cout << "input the string: ";
std::cin.get(input, size + 1);
std::cout << input;
delete[] input;
// Test: if longer than the array size, we will lost the characters which
// are out of range.
```



#### 12.25

```c++
delete [] pa;
```

#### 12.26

```c++
#include <iostream>
#include <string>
#include <memory>

void input_reverse_output_string(int n)
{
    std::allocator<std::string> alloc;
    auto const p = alloc.allocate(n);
    std::string s;
    auto q = p;
    while (std::cin >> s && q != p + n) 
      alloc.construct(q++, s);

    while (q != p) {
      std::cout << *--q << " ";
      alloc.destroy(q);    // call destory for every element to deallocate
    }
    alloc.deallocate(p, n);
}
```

