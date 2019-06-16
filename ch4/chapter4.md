## Chapter 4 Expression

### Concepts

#### L-value & R-value



#### size_of operator

right associative

```c++
sizeof (type);
sizeof expr;
```



#### comma operator

evaluate from left ot right, the final value of comma operator is that behind the comma, see 4.33 as explanation.



#### conversion

##### intergral promotion



##### unsigned int conversion

- unsigned int not less than signed int (unsigned type has more bits)

  int will be convet to unsigned

+ Signed int greater than unsigned int

  if all values of unsigned int can be stored in signed 

  ​	convert unsigned to signed

  else 

  ​	convert signed to unsigned

```c++
// example from book
bool 	flag;		char 					 cval;
short sval; 	unsigned short usval;
int 	ival;		unsigned int	 uival;
long  lval;   unsigned long  ulval;
float fval;   double         dval;

3.14159L + 'a';  // 'a' promoted to int, int converted to long double
dval + ival;     //  ival converted to double
dval + fval;     // fval converted to double
ival = dval;     // dval converted to int
flag = dval;     // dval == 0 ? flag = false : flag = true
cval + fval;     // cval converted to int, then to float
sval + cval;     // cval to int, sval to int
cval + lval;     // cval to int, then to long int
ival + ulval;    // ival to unsigned long
usval + ival;    // promote according to the bytes of unsigned short and int
uival + lval;    // convert according to the bytes of unsigned int and long

```

##### implicit conversion

```c++
// array to pointer
int ia[10];
int *ip = ia;   // ia converts to ptr that points to its begin

// 0, nullptr can converts to any types of ptr
// any ptr can be converted to void *

// arithmatic to bool

// non-const to const
// the reverse is not promised
int i;
const int &j = i;
const int *p = &i;

// class conversion
```



##### explicit conversion (cast)

```c++
cast-name<type> (expression);


// static cast


// const cast
	// can only change low-level const
const char *pc;
char *p const_cast<char*> (pc); // correct, but modify value thru p is an undifined hehavior

const char *cp;

char *q = static_cast<char*>(cp); // wrong, static cast can not remove const
static_cast<string> (cp);					// correct, change char to string
const_cast<string> (cp);					// wrong, const cast only affect const property

// dynamic cast

// reinterpret cast
```







#### 4.1

105

#### 4.2

```C++
*vec.begin() //=> *(vec.begin())
*vec.begin() + 1 //=> (*(vec.begin())) + 1
```

#### 4.3

Yes, I think it necessary to hold the trade-off. Because the speed is always the biggest advantage of C++. Sometimes, we need the compiler's features for efficient work. But if you are not a expert. I have to advice you do not touch the undefined behaviors.

For an instance, `cout << i << ++i <<endl` should never appear in your code.

#### 4.4

```C++
12 / 3 * 4 + 5 * 15 + 24 % 4 / 2
  
(12 / 3 * 4) + (5 * 15) + (24 % 4 / 2)
// 91
```

#### 4.5

```c++
-30 * 3 + 21 / 5  // -90+4 = -86
-30 + 3 * 21 / 5  // -30+63/5 = -30+12 = -18
30 / 3 * 21 % 5   // 10*21%5 = 210%5 = 0
-30 / 3 * 21 % 4  // -10*21%4 = -210%4 = -2
```

#### 4.6

```c++
int n; // any number

std::string decision = i % 2 == 0 ? "even" : "odd";

if (n % 2)
  cout << "odd num" << endl;
else
	cout << "even num" << endl;
```



#### 4.7

```C++
short svalue = 32767; ++svalue; // -32768
unsigned uivalue = 0; --uivalue;  // 4294967295
unsigned short usvalue = 65535; ++usvalue;  // 0
```



#### 4.8

from the book:

> The logical `AND` and `OR` operators always evaluate their left operand before the right. Moreover, the right operand is evaluated if and only if the left operand does not determine the result. This strategy is known as **short-circuit evaluation**.

- logical `AND` : the second operand is evaluated if and only if the left side is `true`.
- logical `OR` : the second operand is evaluated if and only if the left side is `false`
- equality operators : `true` only if both operands have the same value, otherwise, it returns `false`.





#### 4.9

> Explain the behavior of the condition in the following `if`:
>
> ```c++
> const char *cp = "Hello World";
> if (cp && *cp)
> ```

cp is a pointer to `const char *`, and it's not a `nullptr`. true.

`*cp` is a `const char`: `'H'`, and it is explicit a nonzero value. true.

`true && true => true`



#### 4.10

```c++
int input;
while (std::cin>>input && input != 42)
```



#### 4.11

> Write an expression that tests four values, a, b, c, and d, and ensures that a is greater than b, which is greater than c, which is greater than d.

```c++
a > b && b > c && c > d
```



#### 4.12

> Assuming `i`, `j`, and `k` are all ints, explain what `i != j < k` means.

According to Operator precedence, `i != j < k` is same as `i != (j < k)`.

The condition group `j` and `k` to the `<` operator. The `bool` result of that expression is the right hand operand of the `!=` operator. That is `i`(int) is compared to the `true/false` result of the first comparison! To accomplish the test we intended, we can rewrite the expression as follows:

```c++
i != j && j < k
```







#### 4.13

What are the values of i and d after each assignment?

```c++
int i;   double d;
d = i = 3.5; // i = 3, d = 3.0
i = d = 3.5; // d = 3.5, i = 3
```



#### 4.14

Explain what happens in each of the if tests:

```c++
if (42 = i)   // compile error: expression is not assignable
if (i = 42)   // true.
```

#### 4.15

The following assignment is illegal. Why? How would you correct it?

```c++
double dval; int ival; int *pi;
dval = ival = pi = 0;
// pi is a pointer to int.
// can not assign to 'int' from type 'int *'
// correct it:
dval = ival = 0;
pi = 0;
```



#### 4.16

Although the following are legal, they probably do not behave as the programmer expects. Why? Rewrite the expressions as you think they should be.

```c++
if (p = getPtr() != 0)
if (i = 1024) // always true. use an assigment as a condition.

// correction
if ((p = getPtr()) != 0)
if (i == 1024)
```

#### 4.17

> Explain the difference between prefix and postfix increment.

The postfix operators increment(or decrement) the operand but yield a copy of the original, unchanged value as its result.

The prefix operators return the object itself as an **lvalue**.

The postfix operators return a copy of the object's original value as an **rvalue**.

#### 4.18



#### 4.19

Given that `ptr` points to an `int`, that `vec` is a `vector<int>`, and that `ival` is an `int`, explain the behavior of each of these expressions. Which, if any, are likely to be incorrect? Why? How might each be corrected?

```c++
ptr != 0 && *ptr++  				// check ptr is not a nullptr. and check the pointer value and
  													// move next
  
ival++ && ival 							// check ival and ival+1 whether equal zero.
vec[ival++] <= vec[ival] 		// incorrect. not sure which side of <= evaluate first

// correction
vec[ival] <= vec[ival+1]
```

#### 4.20

Assuming that iter is a `vector<string>::iterator`, indicate which, if any, of the following expressions are legal. Explain the behavior of the legal expressions and why those that aren’t legal are in error.

```c++
*iter++;  				// return *iter, then ++iter.
(*iter)++;  			// illegal, *iter is a string, cannot increment value.
*iter.empty() 		// illegal, iter should use '->' to indicate whether empty.
iter->empty();  	// indicate the iter' value whether empty.
++*iter;        	// illegal, string have not increment.
iter++->empty();  // return iter->empty(), then ++iter.
```

#### 4.21

```c++
#include <iostream>
#include <vector>

int main() {
	std::vector<int> a{1,2,3,4,5};
  for (auto &num : a) 
    if (num % 2)
  		num *= 2;
}
```



#### 4.22

```c++
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main(){
    unsigned grade;
    while (cin >> grade) {
        cout << 
          	((grade > 90) ? "high pass" : (grade < 60) ? "fail" : (grade < 75) ? "low pass"
                                                                 : "pass");
        cout << endl;
    }
    return 0;
}
```



#### 4.23

> The following expression fails to compile due to operator precedence. Using Table 4.12 (p. 166), explain why it fails. How would you fix it?
>
> ```c++
> string s = "word";
> string pl = s + s[s.size() - 1] == 's' ? "" : "s" ;
> 
> // correction
> string pl = s + (s[s.size() - 1] == 's' ? "" : "s") ;
> ```



#### 4.24

> Our program that distinguished between high pass, pass, and fail depended on the fact that the conditional operator is right associative. Describe how that operator would be evaluated if the operator were left associative.

if the operator were left associative.

```c++
finalgrade = (grade > 90) ? "high pass" : (grade < 60) ? "fail" : "pass";
```

would same as :

```c++
finalgrade = ((grade > 90) ? "high pass" : (grade < 60)) ? "fail" : "pass";
```



#### 4.25 - 4.27 omited



#### 4.28

```c++
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    cout << "bool is " << sizeof(bool) << "bytes." << endl;
  	// char group
    cout << "char is " << sizeof(char) << "bytes." << endl;
    cout << "wchar_t is " << sizeof(wchar_t) << "bytes." << endl;
    cout << "char16_t is " << sizeof(char16_t) << "bytes." << endl;
    cout << "char32_t is " << sizeof(char32_t) << "bytes." << endl;
    // int group
  	cout << "short is " << sizeof(short) << "bytes." << endl;
  	cout << "int is " << sizeof(int) << "bytes." << endl;
    cout << "long  is " << sizeof(long) << "bytes." << endl;
    cout << "long long is " << sizeof(long long) << "bytes." << endl;
  	
  	// float group
    cout << "float is " << sizeof(float) << "bytes." << endl;
    cout << "double is " << sizeof(double) << "bytes." << endl;
    cout << "long double is " << sizeof(long double) << "bytes." << endl;

    return 0;
}

```



#### 4.29

Predict the output of the following code and explain your reasoning. Now run the program. Is the output what you expected? If not, figure out why.

```c++
int x[10];   int *p = x;
cout << sizeof(x)/sizeof(*x) << endl;  // 10 sizeof(array) / sizeof(int)
cout << sizeof(p)/sizeof(*p) << endl;  // 2  sizeof(ptr) / sizeof(int)
```



#### 4.30

Using Table 4.12 (p. 166), parenthesize the following expressions to match the default evaluation:

```c++
sizeof x + y      // (sizeof x)+y . "sizeof" has higher precedence than binary`\+`.
sizeof p->mem[i]  // sizeof(p->mem[i])
sizeof a < b      // sizeof(a) < b
sizeof f()        // if`f()`returns`void`, this statement is undefined, otherwise it returns 
  								// the size of return type.
```



#### 4.31

just for a good habbits

```c++
// modification
for(vector<int>::size_type ix = 0; ix != ivec.size(); ix++, cnt--)
    ivec[ix] = cnt;
```

#### 4.32

just loop on the array  by iterator and index at the same time

```c++
constexpr int size = 5;
int ia[size] = {1,2,3,4,5};
for (int *ptr = ia, ix = 0; 
     ix != size && ptr != ia+size;
     ++ix, ++ptr) { /* ... */ }
```

#### 4.33

```c++
SomeValue ? ++x, ++y : --x, --y;
/*
the precedence from high to low is 
++, -- 
?: 
,
*/
//due to the most lowest precedence of the comma, it will first split the expression
(someValue ? ++x, ++y : --x), --y
//If someValue is true, then ++x, ++y, then comma, then --y
//if someValue is false, then --x, then comma, then --y

someValue ? (++x, y) : (--x, --y);
// Even though the result has nothing to do with x, the evaluation of someValue does effect
// the operation on x.

// example:
int x = 5, y = 10;
int a = ( 1 ? ++x, ++y : --x, --y); // a = 10

x = 5, y = 10;											// reset x, y
int b = ( 0 ? ++x, ++y : --x, --y); // b = 9

```



#### 4.34

```c++
if (fval);  				// fval to bool
dval = fval + ival; // ival to float, then float to double
dval + ival * cval; // cval to int, then their result to double
```

#### 4.35

```c++
// given
char cval;
int ival;
unsigned int ui;
float fval;
double dval;

cval = 'a' + 3;					    //'a' to int, 'a'+3 to char

fval = ui - ival * 1.0;     // ival to double, ui to double, result of 
														// right (double) to float (by truncation)

dval = ui * fval;           // ival to float, then result of (ui * fval) to double

cval = ival + fval + dval;  // ival to float, (ival + fval) to double,
														// result of right (double) to char (by truncation)
```



#### 4.36

```c++
i *= static_cast<int> (d);
```



#### 4.37

```c++
int i; double d; const string *ps; char *pc; void *pv;
pv = (void*)ps; 
i = int(*pc);   
pv = &d;        
pc = (char*)pv; 

// new style
pv = static_cast<void*> (const_cast<string*>(ps));
i = static_cast<int> (*pc);
pv = static_cast<void*> (&d);
pc = static_cast<char*> (pv);

```



#### 4.38

> Explain the following expression:
>
> ```c++
> double slope = static_cast<double>(j/i);
> ```

`j/i` is an int(by truncation), then converted to double and assigned to slope.

















