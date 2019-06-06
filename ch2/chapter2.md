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
