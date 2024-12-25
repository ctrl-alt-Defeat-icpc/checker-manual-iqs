# Manual converted chekcer file (domjudge to quera)
domjudge chekcer is based on [Mike Mirzayanov testlib](https://github.com/MikeMirzayanov/testlib) and I conveted that manually.

### list
| folder name | uses |
|:---:|:---:|
| [sut2024](./sut2024/) | icpc 2024 (asia west - onsite - Tehran) |

<br><details><summary>quera test case checker example</summary>

```cpp
/*
 * tester.cpp
 */
 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char const *argv[])
{
 
	ifstream test_in(argv[1]);    /* This stream reads from test's input file   */
	ifstream test_out(argv[2]);   /* This stream reads from test's output file  */
	ifstream user_out(argv[3]);   /* This stream reads from user's output file  */
 
	/* Your code here */
	/* If user's output is correct, return 0, otherwise return 1       */
 
	...
 
}
```
</details>