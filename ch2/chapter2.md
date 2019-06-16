## Chapter 2. Variable and Basic Types

### Concepts

#### Default Initialization:

1. Uninitialized objects of built-in type defined inside a function body have a *undefined* value.
2. Objects of class type that we do not explicitly initialize have a value that is defined by class (i.e. <int, 0>)

```c++
using namespace std;
int global_int; // global, not in local scope, default initialization, 0
std::string global_str; // in namespace std, default initialization, ""

void print() {
  int b; // no value provided, uninitialized
  cout << "b value: " << b << endl; // undefined value
}

struct test {
  int a;   // n value provided, uninitialized
};
int main() {
  int i;
  cout << i << endl; // in main(local), uninitialized
  
  if (true) { // in function body (local)
    int j;  // no value provided, uninitialized
    cout <<"j value: " << j << endl; // undefined value
    print();
  }
  
  test L;
  cout <<"L value: " << L.a << endl; // in struct body (local), undefined value
}
/*
sample output:
i value: 0
j value: 32766
b value: 32733
*/

```



#### Reference:

1. reference a is alias to a object

2. due to 1, reference must be initialized at declaration and 

   can not bind reference to a literal, returned value from a function

#### Pointer

##### nullptr 

```c++
// three ways to initialize a null ptr
int *p1 = nullptr; // best practise
int *p1 = 0;       // equivalent to above
int *p1 = NULL;    // not recomended
```

##### void*

can store addresses of any type

Only used for:

- pointer comparation (==, <, >, etc)
- input/output of function
- assign to another void*



##### ptr&ref

```c++
// read declaration from right to left
int i = 42;
int *p1 = &i;    // ptr points to int
int **p2 = &p1;  // ptr points int ptr
int *&r = p1;		 // a ref to int ptr
```



#### Const

*must be initialized when declared*

```c++
/*
use extern to initialize const once
*/
// defined in file.cc
extern const int bufSize = 512;
// defineed in file.h
extern const int bufSize;
```

```c++
double dval = 3.14;
const int &ri = dval; // legal

// what the complier has done
const int temp = dval;
const int &ri = temp;
// !!! !!! !!! if ri is not const, it is a illegal operation
```

**const reference can ref to a non-const value, but modifying that value
from const ref is not allowed**



***top-level const && low-level const***

Definition:

​	**top-level const**: ptr itself is a const

​	**low-level const**: obj that ptr points to is a const

```c++
// examples from book
int i = 0;
int *const p1 = &i;   		  // top level

const int ci = 42;					// top level
const int *p2 = &ci;   		  // low level
const int *const p3 = &ci;  // top & low level
const int &r = ci;					// low level
```



#### constexpr

*expressions that can get const result during compiling process*

```c++
// examples
const int a = 12;					// yes
const int b = a + 1;			// yes
int c = 10;								// no
const int d = get_size(); // no
```

constexpr can be use on any expressions to allow complier decides its validity



**literal type**: Arithmatic type, ref, ptr(must be 0, nullptr or specific address)

```c++
//constexpr only affects ptr itself
constexpr int *q = nullptr;  // q is const ptr, the value it points to can be changed
```



#### deceltype

deceltype will retain and return the *const* (including top & low level) information

*reference* will also be returned, thought it always used as an alas

```c++
int i=42, *p = &i, &r = i;
decltype(r+0) b;   // int
decltype(*p)  c;	 // wrong, decltype(*p) is a ref

decltype((i)) d;   // wrong, decltype((i)) is ref
decltype(i)   e; 	 // int
```









#### 2.1

C++ guarantees *short* and *int* is at least 16 bits, *long* at least 32 bits, 
*long long* at least 64 bits

*signed* can represents positive, negative and zero, where unsigned can only
represents numbers no less than zero

In most compliers, float is indeed single-precision floating point number
(binary32), and a double is double-precision floating point number(binary64) 

#### 2.2
double (better) or float


#### 2.3
```c++
unsigned u=10, u2 = 42; // 32 bits in compiler, 8 bits for description
auto ans1 = u2 - u; // ans1 = 32;

// 10: 0000 1010
// 42: 0010 1010
// 10 - 42:
// step1:
// 0000 0000 - 0010 0000
// step2: lhs-1, rhs -1
// 1111 1111 - 0001 1111
// step3:
// result: 1110 0000
auto ans2 = u - u2; // ans2 = 4294967264；

int i = 10, i2 = 42;
int a1 = 32; // i2 - i
int a2 = -32; // i-i2
int a3 = 0; // i-u
int a4 = 0; // u-i
```
#### 2.5
(a) 'a' char; L'a' wchar_t; "a" string; L"a" string wide char;  
(b) 10L long; 10uL unsigned long; 012 oct; 0xC hex;  
(c) 3.14 double; 3.14f float; 3.14L long double;  
(d) 10 int; 10u unsigned int; 10. double; 10e-2 double;  

#### 2.6
first lane: oct number  
second lane: hex number  

#### 2.7

(a) string

(b) long double

(c) float

(d) long double



#### 2.8
```c++
#include<iostream>
using namespace std;
int main() {
    cout << "2M" << '\n';
    cout << '2' << '\t' << 'M' << endl;
}
```


#### 2.9

(a): `error: expected '(' for function-style cast or type construction`.

```c++
int input_value = 0;
std::cin >> input_value;
```

(b): `error: type 'double' cannot be narrowed to 'int' in initializer list.`

```c++
double i = { 3.14 };
```

(c): if declared 'wage' before, it's right. Otherwise, error would be happened: `error: use of undeclared identifier 'wage'`

```c++
double wage;
double salary = wage = 9999.99;
```

(d): Ok: but value will be truncated.

```c++
double i = 3.14;
```



#### 2.10

```c++
int global_int; // global, 0
std::string global_string; //global, ""

int main() {
	int local_int; // local, built in, hence undefined
  std::string local_str; // local, but std::string has a default value, ""
}
```



#### 2.11

- (a) definition

- (b) definition
- (c) declaration



#### 2.12

illegal: `int double = 3.14`,   `int catch-22;`, `int 1_or_2 = 1;`



#### 2.13

j = 100

#### 2.14

Output: `100 45` , 100 is from `int i =100`, 45 is `\sum_{i=0}^{10}`



#### 2.15

Illegal : 

```c++
int &rval1 = 1.01; // wrong, bind to a literal
int &rval3; 			 // wrong, not initialized
```



#### 2.16

```c++
// given
int i = 0, &r1 = i;
double d = 0, &r2 = d;

// judge following
r2 = 3.14159; // correct
r2 = r1; 			// correct, force type cast
i = r2;       // correct, type cast
r1 = d;       // correct, type cast
```

#### 2.17

```c++
int i, &ri = i;
i = 5; ri = 10;
std::cout << i << " " << ri << std::endl;

// output: 10 10
```

#### 2.18

```c++
int a = 0, b = 1;
int *p1 = &a, *p2 = p1;

// change the value of a pointer.
p1 = &b;
// change the value to which the pointer points
*p2 = b;
```



#### 2.19

**definition**:

the pointer is "points to" any other type.

the reference is "another name" of an **object**.

**key difference**:

1. a reference is another name of an **already existing** object. a pointer is an object in its **own right**.
2. Once initialized, a reference remains **bound to** its initial object. There is **no way** to rebind a reference to refer to a different object. a pointer can be **assigned** and **copied**.
3. a reference always get the object to which the reference was initially bound. a single pointer can point to **several different objects** over its lifetime.
4. a reference must be initialized. a pointer need **not be** initialized at the time it is defined.

 

#### 2.20

```c++
int i = 42;
int *p1 = &i; *p1 = *p1 * *p1;
// i = 1764 (42 * 42)
```



#### 2.21

Illegal:

```c++
double* dp = &i; // wrong, double ptr points to int
int *ip = i;     // wrong, no '&' to take address
```



#### 2.22

```c++
if (p) // whether p is nullptr?
if (*p) // whether the value pointed by p is zero?
```



#### 2.23

No. Because more information needed to determine whether the pointer is valid or not.



#### 2.24

```c++
int i = 42;
void *p = &i;  // void* can point to any type
long *lp = &i; // type not matching
```

#### 2.25

```c++
int *ip, i, &r=i;   // ip: int ptr;  i: int; r: i's ref
int i, *ip=0;			  // i: int;  ip: nullptr
int *ip, ip2; 			// ip: nullptr; ip2: int
```

#### 2.26

```c++
const int buf; 				// wrong, not initialized
int cnt = 0;   				// correct
const int sz = cnt;	  // correct, sz = 0
++cnt; 								// correct
++sz;  								// wrong, const cannot be changed
```

#### 2.27

```c++
int i = -1, &r = 0;         // illegal, r must refer to an object.
int *const p2 = &i2;        // legal.
const int i = -1, &r = 0;   // legal. r will ref a temp obj
const int *const p3 = &i2;  // legal.
const int *p1 = &i2;        // legal
const int &const r2;        // illegal, r2 is a reference that cannot be const.
const int i2 = i, &r = i;   // legal.
```

#### 2.28

```c++
int i, *const cp;       // illegal, const ptr cp must initialize.
const int ic, &r = ic;  // illegal, const int ic must initialize.
int *p1, *const p2;     // illegal, const ptr p2 must initialize.
const int *const p3;    // illegal, const ptr p3 must initialize.
const int *p;           // legal. a pointer to const int. currently a nullptr
```

#### 2.29

```c++
i = ic;     // legal, assign value to a non-const 
p1 = p3;    // illegal. p3 is a const ptr to const int. p1 is a ptr to int
p1 = &ic;   // illegal. ic is a const int. p1 is a ptr to int
p3 = &ic;   // illegal. p3 is a const pointer. can not change
p2 = p1;    // illegal. p2 is a const pointer. can not change
ic = *p3;   // illegal. ic is a const int. can not change
```



#### 2.30

```c++
const int v2 = 0;  															// low level
int v1 = v2;																		//  
int *p1 = &v1, &r1 = v1;												// 
const int *p2 = &v2, *const p3 = &i, &r2 = v2;  // p2 low; p3 top and low; r2 low
```



#### 2.31

```c++
r1 = v2; // legal, top-level const in v2 is ignored.
p1 = p2; // illegal, p2 has a low-level const but p1 doesn't.
p2 = p1; // legal, we can convert int* to const int*.
p1 = p3; // illegal, p3 has a low-level const but p1 doesn't.
p2 = p3; // legal, p2 has the same low-level const qualification as p3.
```



#### 2.32

```c++
// question
int null = 0, *p = null;		 // illegal

// modification
int null = 0, *p = &null;		 // in this case, *p will output 0

int null = 0, *p = nullptr;  // p points to nullptr, can not deref it

```





#### 2.35

```c++
const int i = 42;								// const int
auto j = i;											// int
const auto &k = i;							// const int&
auto *p = &i;										// const int*
const auto j2 = i, &k2 = i;			// j2: const int
																// k2: const int ref
```



#### 2.36

```c++
int a = 3, b = 4;								// a int, b int
decltype(a) c = a;							// c int
decltype((b)) d = a;						// d int&
++c;                
++d;
// output
// a = 4
// b = 4
// c = 4
// d = 4
```

#### 2.37

```c++
int a = 3, b = 4;					// a int, b int
decltype(a) c = a;				// c int
decltype(a = b) d = a;		// d int&
//output
// a = 3
// b = 4
// c = 3
// d = 3
```

#### 2.38

The way `decltype` handles top-level `const` and references differs **subtly** from the way `auto` does. Another important difference between `decltype` and `auto` is that the deduction done by `decltype` depends on the **form** of its given expression.

```c++
int i = 0, &r = i;
// same
auto a = i;
decltype(i) b = i;
// different
auto c = r;
decltype(r) d = r;
```



#### rest questions of this chapter will be in Sales_data file





