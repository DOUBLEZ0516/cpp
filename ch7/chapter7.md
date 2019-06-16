## Chapter 7 Class

##### mutable variable

const object 's const member function

normal object's const member function

can both modify a mutable value



#### inline member function

should be defined in header file

inline can not be passed to subclasses

#### converting constructor

Use explicit to prevent implicit converting

explicit only works for constructors that accept exactly one argument

and it should only be appearing in the declaration body.

```c++
// explicit casting is allowed for explicit constructor
item.combine(static_cast<Sales_data>(cin));  // correct
```



#### aggregate class

+ all public member
+ No constructor
+ no in-class initializer
+ no base class, virtual member function



literal const class

+ a aggregate class with all members are literal type
+ Has at least one constexpr constructor
+ constexpr for any member that has in-class initializer
+ use default deconstructor

Constexpr constructor

+ can use default constructor
+ meet constructor's requirement and constexpr requirement













#### 7.1~7.7, 7.9

are implemented in codes



#### 7.8

Define `read`'s `Sales_data` parameter as plain reference since it's intended to change the `revenue`'s value.

Define `print`'s `Sales_data` parameter as a reference to `const` since it isn't intended to change any member's value of this object.



#### 7.10

```c++
if(read(read(cin, data1), data2))
/*
read(cin, data1) will read in data1 and return is os ref 
the outter read will use os returned above as a input
if will judge if the variable return from outter read valid
*/
```



#### 7.11 - 7.15

Are implemented in codes



#### 7.16

There are no restrictions on how often an access specifier may appear.The specified access level remains in effect until the next access specifier or the end of the class body.

The members which are accessible to all parts of the program should define after a public specifier.

The members which are accessible to the member functions of the class but are not accessible to code that uses the class should define after a private specifier.

#### 7.17

The only difference between using `class` and using `struct` to define a class is the default access level. (`class` : private, `struct` : public)





#### 7.18

encapsulation is the separation of implementation from interface. It hides the implementation details of a type. (In C++, encapsulation is enforced by putting the implementation in the private part of a class)



#### 7.19

- `public` include: constructors, `GetName()`, `GetAddress()`.
- `private` include: `name`, `address`.

the interface should be defined as public, the data shouldn't expose to outside of the class.



#### 7.20

`friend` is a mechanism by which a class grants access to its nonpublic members. They have the same rights as members.

**Pros**:

- the useful functions can refer to class members in the class scope without needing to explicitly prefix them with the class name.
- you can access all the nonpublic members conveniently.
- sometimes, more readable to the users of class.

**Cons**:

- lessens encapsulation and therefore maintainability.
- code verbosity, declarations inside the class, outside the class.



#### 7.21 - 7.24

implemented in code



#### 7.25

The class below can rely on it. It goes in *Section 7.1.5*:

> ..the synthesized versions are unlikely to work correctly for classes that allocate resources that reside outside the class objects themselves.
>
> Moreover, the synthesized versions for copy, assignment, and destruction work correctly for classes that have **vector or string members**.

Hence the class below which used only built-in type and strings can rely on the default version of copy and assignment. 



#### 7.28

The second call to `display` couldn't print `#` among the output, cause the call to `set` would change the **temporary copy**, not myScreen.





#### 7.30

###### Pros

- more explicit
- less scope for misreading
- can use the member function parameter which name is same as the member name.

```c++
void setAddr(const std::string &addr) {this->addr = addr;}
```

###### Cons 

- more to read
- sometimes redundant

```c++
std::string getAddr() const { return this->addr; } // unnecessary
```





#### 7.33

[clang]error: unknown type name 'pos'

fixed:

```c++
Screen::pos Screen::size() const
{
    return height*width;
}
```



#### 7.34

There is an error in

```c++
dummy_fcn(pos height);
           ^
// Unknown type name 'pos'
```



#### 7.35

```c++
typedef string Type;
Type initVal(); // Type = string
class Exercise {
public:
    typedef double Type; 
    Type setVal(Type); // Type = double
    Type initVal(); // Type = double
private:
    int val;
};

Type Exercise::setVal(Type parm) { // first Type = string, second Type = double
    val = parm + initVal();     // using Excercise::initVal() 
    return val; // return type wrong
}


// modification

// first: define Exercise::initVal()

// second: Exercise::Type
Exercise::Type Exercise::setVal(Type parm) { 
    val = parm + initVal();     
    return val; 
}
```



#### 7.36

> In this case, the constructor initializer makes it appear as if `base` is initialized with `i` and then `base` is used to initialize `rem`. However, `base` is initialized first. The effect of this initializer is to initialize `rem` with the undefined value of `base`!

```c++
// fix
struct X {
  X (int i, int j): base(i), rem(base % j) { }
  int base, rem;  // changed the order from "int rem, base;"
};
```



#### 7.37

```c++
Sales_data first_item(cin);   // use Sales_data(std::istream &is) ; 
															// its value are up to your input.

int main() {
  Sales_data next;  // use Sales_data(std::string s = "");
  									// bookNo = "", cnt = 0, revenue = 0.0
  Sales_data last("9-999-99999-9"); // use Sales_data(std::string s = ""); 
  																	// bookNo = "9-999-99999-9", cnt = 0, revenue = 0.0
}
```



#### 7.38

```c++
Sales_data(std::istream &is = std::cin) { read(is, *this); }
```



#### 7.39

illegal. cause the call of overloaded 'Sales_data()' is **ambiguous**.



#### 7.40

```c++
class Book {
public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubdate) : no_(no), name_(name), author_(author), pubdate_(pubdate) { }
    Book(std::istream &in) { in >> no_ >> name_ >> author_ >> pubdate_; }

private:
    unsigned no_;
    std::string name_;
    std::string author_;
    std::string pubdate_;
};
```



#### 7.43

```c++
#include <vector>

class NoDefault {
public:
    NoDefault(int i) {}
};

class C {
public:
    C() : def(0) {} // define the constructor of C.
private:
    NoDefault def;
};

int main()
{
    C c;

    std::vector<C> vec(10);
    return 0;
}
```



#### 7.44

> Is Vector<NoDefault> vec10; legal?

illegal, cause there are ten elements, each would be value initialized. But no default constructor for `NoDefault` type.



#### 7.45

it legal

#### 7.46

- a) A class must provide at least one constructor. (**untrue**, "The compiler-generated constructor is known as the synthesized default constructor.")
- b) A default constructor is a constructor with an empty parameter list. (**untrue**, A default constructor is a constructor that is used if no initializer is supplied.What's more, A constructor that supplies default arguments for all its parameters also defines the default constructor)
- c) If there are no meaningful default values for a class, the class should not provide a default constructor. (**untrue**, the class should provide.)
- d) If a class does not define a default constructor, the compiler generates one that initializes each data member to the default value of its associated type. (**untrue**, only if our class does not explicitly define **any constructors**, the compiler will implicitly define the default constructor for us.)



#### 7.47

Whether the conversion of a `string` to `Sales_data` is desired **depends on how we think our users will use the conversion**. In this case, it might be okay. The `string` in null_book probably represents a nonexistent ISBN.

Benefits:

- prevent the use of a constructor in a context that requires an implicit conversion
- we can define a constructor which is used only with the direct form of initialization

Drawbacks:

- meaningful only on constructors that can be called with a single argument



#### 7.48

###### for non-explicit

all correct

###### for explicit

All correct



"9-999-99999-9" will first be converted to string, then call Sales_data's constructor that

accepts a string



#### 7.49

```c++
(a) Sales_data &combine(Sales_data); // ok
(b) Sales_data &combine(Sales_data&); // [Error] no matching function for call to
																			//'Sales_data::combine(std::string&)' 
																			//(`std::string&` can not convert 
																			// to `Sales_data` type.)

(c) Sales_data &combine(const Sales_data&) const; // The trailing const mark can't be put 
																									//here, as it forbids any mutation on data 
																									//members. This conflicts with combines 	
																									//semantics.
```

Some detailed explanation about problem (b) :

It's wrong.

Because `combine`’s parameter is a non-const reference , we can't pass a temporary to that parameter. If `combine`’s parameter is a reference to `const` , we can pass a temporary to that parameter. Like this :`Sales_data &combine(const Sales_data&);` Here we call the `Sales_data` `combine` member function with a string argument. This call is perfectly legal; the compiler automatically creates a `Sales_data` object from the given string. That newly generated (temporary) `Sales_data` is passed to `combine`.(check on page 295(English Edition))



#### 7.51

Such as a function like that:

```c++
int getSize(const std::vector<int>&);
```

if vector has not defined its single-argument constructor as explicit. we can use the function like:

```c++
getSize(34);
```

What is this mean? It's very confused.

But the `std::string` is different. In ordinary, we use `std::string` to replace `const char *`(the C language). so when we call a function like that:

```c++
void setYourName(std::string); // declaration.
setYourName("pezy"); // just fine.
```

it is very natural.





#### 7.52 

the example should not have in-class initializers

```c++
struct Sales_data {
    std::string bookNo;
    unsigned units_sold;
    double revenue;
};
```



#### 7.54

shouldn't, cause a `constexpr` function must contain exactly one **return** statement.

#### 7.55

no.

#### 7.56

> What is a static class member?

A class member that is **associated with the class**, rather than with individual objects of the class type.

> What are the advantages of static members?

each object can no need to store a common data. And if the data is changed, each object can use the new value.

> How do they differ from ordinary members?

- a static data member can have **incomplete type**.
- we can use a static member **as a default argument**.



#### 7.58

```c++
static double rate = 6.5;
                ^
            rate should be a constant expression.

static vector<double> vec(vecSize);
                            ^
            we may not specify an in-class initializer inside parentheses.
```

Fixed:

```c++
// example.h
class Example {
public:
    static constexpr double rate = 6.5;
    static const int vecSize = 20;
    static vector<double> vec;
};

// example.C
#include "example.h"
constexpr double Example::rate;
vector<double> Example::vec(Example::vecSize);
```























