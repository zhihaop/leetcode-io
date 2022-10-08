# Leetcode-io

Leetcode-io: An Leetcode input/output utilities. The purpose of the project is to bring convenience to user who use leetcode, runtime efficiency is not our design goal.

## Compatibility

Leetcode-io is developed under C++ 20, compatible with GCC (>= 10), MSVC (>= v143) and Clang (>= 10).

## Quick Start

### Basic usage

```c++
vector<vector<int>> vector2d;
vector<string> vector1d;
map<string, int> m;
pair<int, int> p;
string s;
float f;

Reader in;
in.read(vector2d);      // stdin: [[1,2],[2,3],[3,4]]
in.read(vector1d);      // stdin: ["items","goods","c++"]

// stdin: {"hello": 1, "world": 2}
// stdin: (1, 2)
// stdin: (1, "2")
// stdin: "a string"
// stdin: 1.234567
in.read(m, p, t, s, f);

Writer out;
out.write(vector2d);    // stdout: [[1,2],[2,3],[3,4]]
out.write(vector1d);    // stdout: ["items","goods","c++"]
out.write(m);           // stdout: {"hello": 1, "world": 2}
out.write(p);           // stdout: (1, 2)
out.write(s);           // stdout: "a string"
out.write(f);           // stdout: 1.234567

// read from std::string
from_string(R"(["items","goods","c++"])", vector1d);
```

### Binding std::iostream

```c++
#include <leetcode/iostream.h>
...

vector<vector<int>> v;
string s;

cin >> v;               // stdin: [[],[2,3],[3,4]]
cout << v << endl;      // stdout: [[],[2,3],[3,4]]

cin >> s;               // stdin: "hello world"
cout << s << endl;      // stdout: "hello world"

if (s == "hello world") {
    cout << "ok!\n";    // stdout: ok!
}
```

### Read from file

#### data.in

```c
[[1,2],[2,3],[3,4]]
1.0
```

#### source code

```c++
vector<vector<int>> vector2d;
double d;

std::ifstream ifs("data.in");

Reader in(ifs);
in.read(vector2d);  // vector2d = {{1, 2}, {2, 3}, {3, 4}}
in.read(d);         // d = 1.0
```

### Output to file

#### source code

```c++
string s = "hello world!";
vector<vector<int>> vector2d = {vector<int>{1, 2},
                                vector<int>{2, 3}, 
                                vector<int>{3, 4}};

std::ofstream ofs("data.out");

Writer out(ofs);
out.write(vector2d);
out.write(s);
```

#### data.out

```c
[[1,2],[2,3],[3,4]]
"hello world!"
```

### Error handling

```c++
vector<vector<int>> vector2d;
vector<int> vector1d;
int x;

in.read(vector2d);  // stdin: [1, 2, 3]     stderr: "format error: read(std::vector<std::vector<int>>)"
in.read(vector1d);  // stdin: [1, "2", 3]   stderr: "format error: read(std::vector<int>)"
in.read(x);         // stdin: "hello"       stderr: "format error: read(int)"
```
