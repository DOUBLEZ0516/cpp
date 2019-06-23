## Chapter 13 Copy & Move





##### synthesized constructor & destructor

use `=default`



##### synthesized delete constructor & copy

use `=delete`

deconstructor can not be `delete`

`when we can not copy, assign, destruct class members', class's synthesized copy control memberis defined as delete`



 ##### value like class

copy and origin are identical but independent

##### ptr like class

copy and origin shared same data



##### swap operation



#### 13.1

> What is a copy constructor? When is it used?

A copy constructor is a constructor which first parameter is a **reference** to the class type and any additional parameters have **default values**.

When copy initialization happens and that copy initialization requires either the copy constructor or the move constructor.

- Define variables using an `=`
- Pass an object as an argument to a parameter of non-reference type
- Return an object from a function that has a non-reference return type
- Brace initialize the elements in an array or the members of an aggregate class
- Some class types also use copy initialization for the objects they allocate.





#### 13.2

> Explain why the following declaration is illegal:
>
> ```c++
> Sales_data::Sales_data(Sales_data rhs);
> ```

If declaration like that, the call would never succeed to call the copy constructor, `Sales_data rhs` is an argument to a parameter, thus, we'd need to use the copy constructor to copy the argument, but to copy the argument, we'd need to call the copy constructor, and so on indefinitely.



#### 13.3







#### 13.4

```c++
Point global;
Point foo_bar(Point arg) // 1
{
    Point local = arg, *heap = new Point(global); // 2, 3
    *heap = local;
    Point pa[ 4 ] = { local, *heap }; // 4, 5
    return *heap; // 6
}
```



#### 13.6

> What is a `copy-assignment` operator? When is this operator used? What does the synthesized `copy-assignment`operator do? When is it synthesized?

The `copy-assignment` operator is function named `operator=`.

This operator is used when assignment occurred.

The synthesized `copy-assignment` operator assigns each non-static member of the right-hand object to corresponding member of the left-hand object using the `copy-assignment` operator for the type of that member.

It is synthesized when the class does not define its own.



#### 13.7

> What happens when we assign one `StrBlob` to another? What about `StrBlobPtrs`?

In both cases, shallow copy will happen. All pointers point to the same address. The `use_count` changed the same as 13.3.



#### 13.9

> What is a destructor? What does the synthesized destructor do? When is a destructor synthesized?

The destructor is a member function with the name of the class prefixed by a tilde(`~`).

As with the copy constructor and the copy-assignment operator, for some classes, the synthesized destructor is defined to disallow objects of the type from being destroyed. Otherwise, the synthesized destructor has an empty function body.

The compiler defines a synthesized destructor for any class that does not define its own destructor.



#### 13.10

> What happens when a `StrBlob` object is destroyed? What about a `StrBlobPtr`?

When a `StrBlob` object destroyed, the `use_count` of the dynamic object will decrement. It will be freed if no `shared_ptr` to that dynamic object.

When a `StrBlobPter` object is destroyed the object dynamically allocated will not be freed.



#### 13.12

> How many destructor calls occur in the following code fragment?
>
> ```c++
> bool fcn(const Sales_data *trans, Sales_data accum)
> {
>     Sales_data item1(*trans), item2(accum);
>     return item1.isbn() != item2.isbn();
> }
> ```

3 times. There are `accum`, `item1` and `item2`.



#### 13.14

> Assume that `numbered` is a class with a default constructor that generates a unique serial number for each object, which is stored in a data member named `mysn`. Assuming numbered uses the synthesized copy-control members and given the following function:
>
> ```
> void f (numbered s) { cout << s.mysn << endl; }
> ```
>
> what output does the following code produce?
>
> ```
> numbered a, b = a, c = b;
> f(a); f(b); f(c);
> ```

Three identical numbers.



#### 13.15

> Assume `numbered` has a copy constructor that generates a new serial number. Does that change the output of the calls in the previous Exercise? If so, why? What output gets generated?

Yes, the output will be changed. cause we don't use the synthesized copy-control members rather than own defined.The output will be three different numbers.



#### 13.16

> What if the parameter in `f` were `const numbered&`? Does that change the output? If so, why? What output gets generated?

Yes, the output will be changed. cause the function `f` haven't any copy operators. Thus, the output are the same when pass the each object to `f`.

#### 13.19

No, there is no need to copy a exclusive employee



#### 13.20

The member (smart pointer and container) will be copied.

#### 13.21

As synthesized version meet all requirements for this case, no custom version control members need to define. Check [#304](https://github.com/Mooophy/Cpp-Primer/issues/304#issuecomment-124081395) for detail.

#### 13.24

> What would happen if the version of `HasPtr` in this section didn’t define a destructor? What if `HasPtr` didn’t define the copy constructor?

If `HasPtr` didn't define a destructor, memory leak will happened. If `HasPtr` didn't define the copy constructor, when assignment happened, just points copied, the string witch `ps` points haven't been copied.

#### 13.29

> Explain why the calls to swap inside swap(HasPtr&, HasPtr&) do not cause a recursion loop.

`swap(lhs.ps, rhs.ps);` feed the version : `swap(std::string*, std::string*)` and `swap(lhs.i, rhs.i);` feed the version : `swap(int, int)`. Both them can't call `swap(HasPtr&, HasPtr&)`. Thus, the calls don't cause a recursion loop.



#### 13.31

> Would the pointer-like version of `HasPtr` benefit from defining a swap function? If so, what is the benefit? If not, why not?

@Mooophy:

Essentially, the specific avoiding memory allocation is the reason why it improve performance. As for the pointer-like version, no dynamic memory allocation anyway. Thus, a specific version for it will not improve the performance. 

#### 13.33

> Why is the parameter to the `save` and `remove` members of Message a Folder&? Why didn’t we define that parameter as `Folder`? Or `const Folder&`?

Because these operations must also update the given `Folder`. Updating a `Folder` is a job that the `Folder` class controls through its `addMsg` and `remMsg` members, which will add or remove a pointer to a given `Message`, respectively.

#### 13.35

> What would happen if `Message` used the synthesized versions of the copy-control members?

some existing `Folders` will out of sync with the `Message` after assignment.

#### 13.38

> We did not use copy and swap to define the Message assignment operator. Why do you suppose this is so?

@Mooophy The copy and swap is an elegant way when working with dynamically allocated memory. In the Message class ,nothing is allocated dynamically. Thus using this idiom makes no sense and will make it more complicated to implement due to the pointers that point back.

@pezy In this case, `swap` function is special. It will be clear two `Message`'s folders , then swap members, and added themselves to each folders. But, `Message` assignment operator just clear itself, and copy the members, and added itself to each folders. The `rhs` don't need to clear and add to folders. So, if using copy and swap to define, it will be very inefficiency.



#### 13.51

> Although `unique_ptrs` cannot be copied, in 12.1.5 (p. 471) we wrote a clone function that returned a `unique_ptr`by value. Explain why that function is legal and how it works.

In the second assignment, we assign from the result of a call to `getVec`. That expression is an `rvalue`. In this case, both assignment operators are viable—we can bind the result of `getVec` to either operator’s parameter. Calling the copy-assignment operator requires a conversion to `const`, whereas `StrVec&&` is an exact match. Hence, the second assignment uses the move-assignment operator.

```c++
unique_ptr<int> clone(int p) {
    // ok: explicitly create a unique_ptr<int> from int*
    return unique_ptr<int>(new int(p));
}
```

the result of a call to `clone` is an **rvalue**, so it uses the move-assignment operator rather than copy-assignment operator. Thus, it is legal and can pretty work.

#### 13.56

recursion



#### 13.57

call && version, as `Foo(*this)` is rvalue

















