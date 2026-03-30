#include <iostream>
#include <string>
#include <vector>

void doBuild(std::vector<long long>& a, std::vector<long long>& t, int v, int tl, int tr) {
    if (tr - tl == 1) {
        t[v] = a[tl];
    } else {
        int m = (tl + tr) / 2;
        doBuild(a, t, 2 * v, tl, m);
        doBuild(a, t, 2 * v + 1, m, tr);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

std::vector<long long> build(std::vector<long long>& numbers, int n) {
    std::vector<long long> tree(4 * n + 4, 0);
    doBuild(numbers, tree, 1, 0, n);
    return tree;
}

void doAdd(std::vector<long long>& t, int v, int tl, int tr, int i, int x) {
    if (tr - tl == 1) {
        t[v] += x;
        return;
    }

    int m = (tl + tr) / 2;
    if (i < m) {
        doAdd(t, 2 * v, tl, m, i, x);
    } else {
        doAdd(t, 2 * v + 1, m, tr, i, x);
    }
    t[v] = t[2 * v] + t[2 * v + 1];
}

void add(std::vector<long long>& t, int n, int i, int x) {
    doAdd(t, 1, 0, n, i, x);
}

int findSum(std::vector<long long>& t, int v, int tl, int tr, int l, int r) {
    if (l >= r) {
        return 0;
    }
    if (r <= tl || l >= tr) {
        return 0;
    }

    if (l <= tl && tr <= r) {
        return t[v];
    }

    int tm = (tl + tr) / 2;
    return findSum(t, 2 * v, tl, tm, l, r) + findSum(t, 2 * v + 1, tm, tr, l, r);
}

int main() {
    int n;
    std::cin >> n;

    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    std::vector<long long> tree = build(a, n);

    int q;
    std::cin >> q;
    std::string req;

    for (int i = 0; i < q; i++) {
        std::cin >> req;
        if (req == "FindSum") {
            int l, r;
            std::cin >> l >> r;
            std::cout << findSum(tree, 1, 0, n, l, r) << std::endl;
        } else if (req == "Add") {
            int j, x;
            std::cin >> j >> x;
            add(tree, n, j, x);
        }
    }

    return 0;
}
