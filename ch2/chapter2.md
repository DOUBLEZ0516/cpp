#### 2.1
C++ guarantees *shrot* and *int* is at least 16 bits, *long* at least 32 bits, 
*long long* at least 64 bits

*signed* can represents positive, negative and zero, where unsigned can only
represents numbers no less than zero

In most compliers, float is indeed single-precision floating point number
(binary32), and a double is double-precision floating point number(binary64) 

#### 2.2
double (better) or float


#### 2.3
```c++
unsigned u=10, u2 = 42;
auto ans1 = u2 - u; // ans1 = 32;
auto ans2 = u - u2; // ans2 = 
```
