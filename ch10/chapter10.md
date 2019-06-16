## Chapter10 Generic Algorithm



#### lambda

```c++
[capture list] (parameter list) -> return type {function body}
```

if in function body there are any 

+ statements except return statement
+ the return type is not defined

the return type is void. 



capture by value:

​	copy happens when lambda is defined, not when it is called



capture by reference





[&] implicit capture by ref

[=] implicit capture by value



#### binding

```c++
auto newCallable = bind(callable, arglist);
```





#### 10.23

Assuming the function to be bound have `n` parameters, bind take  `n + 1` parameters. The additional one is for the function to be bind itself.