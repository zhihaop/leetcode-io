#include <vector>
#include <string>

#include "leetcode/reader.h"
#include "leetcode/writer.h"
#include "leetcode/debugs.h"

using namespace std;

int main(int argc, char **argv) {
    vector<vector<int>> vector2d;
    tuple<int, string> t;
    vector<string> vector1d;
    map<string, int> m;
    pair<int, int> p;
    string s;
    float f;

    Reader in;
    in.read(vector2d);      // stdin: [[1,2],[2,3],[3,4]]
    // stdin: {"hello": 1, "world": 2}
    // stdin: (1, 2)
    // stdin: (1, "2")
    // stdin: "a string"
    // stdin: 1.234567
    in.read(m, p, t, s, f);
    from_string(R"(["items","goods","c++"])", vector1d);

    Writer out;
    out.write(vector2d);    // stdout: [[1,2],[2,3],[3,4]]
    out.write(vector1d);    // stdout: ["items","goods","c++"]
    out.write(m);           // stdout: {"hello": 1, "world": 2}
    out.write(p);           // stdout: (1, 2)
    out.write(t);           // stdout: (1, "2")
    out.write(s);           // stdout: "a string"
    out.write(f);           // stdout: 1.234567

    return 0;
}
