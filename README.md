# leetcode-formatter

Leetcode-formatter: An input/output formatter designed for Leetcode. The purpose of the project is to bring convenience to developer who use leetcode, runtime efficiency is not our design goal.

## Compatibility

Leetcode-formatter is developed under C++ 20, compatible with GCC (>= 10), MSVC (>= v143) and Clang (>= 10).

## Quick Start

### Basic usage

#### source code

```c++
vector<vector<int>> vector2d;
vector<string> vector1d;
string s;
float f;

Reader in;
in.read(vector2d);      // stdin: [[1,2],[2,3],[3,4]]
in.read(vector1d);      // stdin: ["items","goods","c++"]
in.read(s);             // stdin: "a string"
in.read(f);             // stdin: 1.234567

Writer out;
out.write(vector2d);    // stdout: [[1,2],[2,3],[3,4]]
out.write(vector1d);    // stdout: ["items","goods","c++"]
out.write(s);           // stdout: "a string"
out.write(f);           // stdout: 1.234567
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

### Error handing

```c++
vector<vector<int>> vector2d;
vector<int> vector1d;
int x;

in.read(vector2d);  // stdin: [1, 2, 3],    stderr: "format error: read(std::vector<T>)"
in.read(vector1d);  // stdin: [1, "2", 3],  stderr: "format error: read(std::vector<T>)"
in.read(x);         // stdin: "hello",      stderr: "format error: read(int)"
```
