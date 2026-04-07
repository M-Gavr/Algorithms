#include <cstdint>
#include <fstream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

std::pair<int, int> get_point(int n, int value) {
    if (value < 0) {
        return {-1, -1};
    }
    return {value / n, value % n};
}

void bfs(const Matrix& matrix, Matrix& used, Matrix& parents) {
    std::vector<int> dx = {0, 1, 0, -1};
    std::vector<int> dy = {1, 0, -1, 0};
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
        std::pair coords = get_point(matrix[0].size(), q.front());

    }
}

int main() {
    std::ifstream in("walk.in");
    std::ofstream out("walk.out");

    int m, n;
    in >> m >> n;
    Matrix matrix(m, std::vector<int> (n, m * n + 1));
    Matrix used(m, std::vector<int> (n, 0));
    Matrix parents(m, std::vector<int> (n, -1));
    return 0;
}