#include <vector>
#include <string>

#include "leetcode/reader.h"
#include "leetcode/writer.h"

using namespace std;

int main(int argc, char **argv) {
    vector<vector<int>> vector2d;
    vector<string> vector1d;
    string s;
    float f;

    Reader in;
    in.read(vector1d);      // stdin: ["items","goods","c++"]
    in.read(s);             // stdin: "a string"
    in.read(f);             // stdin: 1.234567

    Writer out;
    out.write(vector2d);    // stdout: [[1,2],[2,3],[3,4]]
    out.write(vector1d);    // stdout: ["items","goods","c++"]
    out.write(s);           // stdout: "a string"
    out.write(f);           // stdout: 1.234567

    return 0;
}
