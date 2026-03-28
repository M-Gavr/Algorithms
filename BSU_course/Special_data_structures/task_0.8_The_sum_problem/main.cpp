#include <cstdint>
#include <fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in.close();
    out.close();
    return 0;
}
