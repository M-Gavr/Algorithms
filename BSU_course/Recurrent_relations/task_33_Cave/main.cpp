#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int32_t kInf = 1e9;

struct SubtreeInfo {
    int32_t min;    // минимальный порядковый номер внешней вершины в поддереве
    int32_t max;    // максимальный порядковый номер внешней вершины в поддереве
    int32_t l_cur;  // минимальная стоимость пути от левого листа до корня
    int32_t cur_r;  // минимальная стоимость пути от корня до правого листа
    int32_t l_r;    // минимальная стоимость пути от левого листа до правого листа
    int32_t min_i;  // левый лист (конкретная внешняя вершина)
    int32_t max_i;  // правый лист (конкретная внешняя вершина)
    int32_t cur_i;  // текущая вершина (корень поддерева)

    SubtreeInfo()
        : min(kInf), max(-kInf), l_cur(kInf), cur_r(kInf), l_r(kInf),
          min_i(-1), max_i(-1), cur_i(-1) {}

    SubtreeInfo(int32_t m, int32_t M, int32_t lc, int32_t cr, int32_t lr,
                int32_t mi, int32_t Mi, int32_t ci)
        : min(m), max(M), l_cur(lc), cur_r(cr), l_r(lr),
          min_i(mi), max_i(Mi), cur_i(ci) {}

    bool operator<(const SubtreeInfo& other) const {
        return min < other.min;
    }
};

struct Vertex {
    int32_t neighbors[3];
    int32_t weights[3];
    bool is_outer[3];
    int32_t deg;

    Vertex() : deg(0) {
        fill(neighbors, neighbors + 3, -1);
        fill(weights, weights + 3, -1);
        fill(is_outer, is_outer + 3, false);
    }
};

struct GraphData {
    int32_t n;
    int32_t k;
    vector<Vertex> vertices;
    vector<bool> is_outer_vertex;
    vector<vector<int32_t>> outer_edge_weight;
    vector<int32_t> outer_cycle_order;
    vector<int32_t> pos_in_cycle;
    vector<pair<int32_t, int32_t>> lr;  // для восстановления ответа lr[v] = {левый_лист, правый_лист}

    GraphData(int32_t n_val, int32_t k_val)
        : n(n_val), k(k_val),
          vertices(n_val),
          is_outer_vertex(n_val, false),
          outer_edge_weight(k_val, vector<int32_t>(k_val, -1)),
          outer_cycle_order(k_val),
          pos_in_cycle(n_val, -1),
          lr(n_val) {}
};

// Вспомогательные функции (принимают данные по ссылке)
int32_t get_inner_edge_weight(const GraphData& g, const int32_t u, const int32_t v) {
    for (int32_t i = 0; i < g.vertices[u].deg; ++i) {
        if (g.vertices[u].neighbors[i] == v && !g.vertices[u].is_outer[i]) {
            return g.vertices[u].weights[i];
        }
    }
    return -1;
}

int32_t get_outer_edge_weight(const GraphData& g, const int32_t u, const int32_t v) {
    return g.outer_edge_weight[u][v];
}

vector<pair<int32_t, int32_t>> get_inner_neighbors(const GraphData& g, const int32_t v, const int32_t p) {
    vector<pair<int32_t, int32_t>> result;
    for (int32_t i = 0; i < g.vertices[v].deg; ++i) {
        int32_t const to = g.vertices[v].neighbors[i];
        if (to != p && !g.vertices[v].is_outer[i]) {
            result.emplace_back(to, g.vertices[v].weights[i]);
        }
    }
    return result;
}

void find_outer_cycle(GraphData& g) {
    int32_t cur = 0;
    int32_t prev = -1;

    for (int32_t i = 0; i < g.k; ++i) {
        g.outer_cycle_order[i] = cur;
        g.pos_in_cycle[cur] = i;

        for (int32_t j = 0; j < g.vertices[cur].deg; j++) {
            int32_t const to = g.vertices[cur].neighbors[j];
            if (g.vertices[cur].is_outer[j] && to != prev) {
                prev = cur;
                cur = to;
                break;
            }
        }
    }
}

SubtreeInfo dfs(GraphData& g, const int32_t v, const int32_t parent) {
    vector<pair<int32_t, int32_t>> const inner_neighbors = get_inner_neighbors(g, v, parent);

    if (inner_neighbors.empty()) {
        g.lr[v] = {v, v};
        return {g.pos_in_cycle[v], g.pos_in_cycle[v], 0, 0, 0, v, v, v};
    }

    vector<SubtreeInfo> children_info;
    for (auto [child, w] : inner_neighbors) {
        children_info.push_back(dfs(g, child, v));
    }

    if (children_info.size() == 2) {
        if (children_info[0].min > children_info[1].min) {
            swap(children_info[0], children_info[1]);
        }
    }

    SubtreeInfo const l = children_info[0];
    SubtreeInfo const r = children_info[1];

    g.lr[v] = {l.cur_i, r.cur_i};

    const int32_t l_cur = l.l_r + r.l_cur + get_outer_edge_weight(g, l.max_i, r.min_i) +
                          get_inner_edge_weight(g, v, r.cur_i);

    const int32_t cur_r = r.l_r + l.cur_r + get_outer_edge_weight(g, l.max_i, r.min_i) +
                          get_inner_edge_weight(g, v, l.cur_i);

    const int32_t l_r = l.l_cur + r.cur_r + get_inner_edge_weight(g, v, l.cur_i) +
                  get_inner_edge_weight(g, v, r.cur_i);

    return {l.min, r.max, l_cur, cur_r, l_r, l.min_i, r.max_i, v};
}

void gen_ans(GraphData& g, const int32_t v, const int32_t from, const int32_t to, ofstream& out) {
    if (g.lr[v].first == v && g.lr[v].second == v) {
        out << v + 1 << " ";
        return;
    }

    int32_t const left_child = g.lr[v].first;
    int32_t const right_child = g.lr[v].second;

    if (from == 0 && to == 1) {
        // Путь от левого листа к правому листу через v
        gen_ans(g, left_child, 0, 2, out);
        out << v + 1 << " ";
        gen_ans(g, right_child, 2, 1, out);
    }
    else if (from == 0 && to == 2) {
        // Путь от левого листа к v
        gen_ans(g, left_child, 0, 1, out);
        gen_ans(g, right_child, 0, 2, out);
        out << v + 1 << " ";
    }
    else if (from == 2 && to == 1) {
        // Путь от v к правому листу
        out << v + 1 << " ";
        gen_ans(g, left_child, 2, 1, out);
        gen_ans(g, right_child, 0, 1, out);
    }
}

int main() {
    ifstream in("input.in");
    ofstream out("output.out");

    int32_t n = 0;
    int32_t k = 0;
    in >> n >> k;

    GraphData g(n, k);

    for (int32_t i = 0; i < k; ++i) {
        g.is_outer_vertex[i] = true;
    }

    const int32_t edges_count = 3 * n / 2;
    for (int32_t e = 0; e < edges_count; e++) {
        int32_t u = 0;
        int32_t v = 0;
        int32_t w = 0;
        in >> u >> v >> w;
        --u; --v;

        // Добавляем ребро в вершину u
        int32_t const du = g.vertices[u].deg;
        g.vertices[u].neighbors[du] = v;
        g.vertices[u].weights[du] = w;
        g.vertices[u].is_outer[du] = (u < k && v < k);
        g.vertices[u].deg++;

        // Добавляем ребро в вершину v
        int32_t const dv = g.vertices[v].deg;
        g.vertices[v].neighbors[dv] = u;
        g.vertices[v].weights[dv] = w;
        g.vertices[v].is_outer[dv] = (u < k && v < k);
        g.vertices[v].deg++;

        // Если оба конца внешние - сохраняем в матрицу
        if (u < k && v < k) {
            g.outer_edge_weight[u][v] = w;
            g.outer_edge_weight[v][u] = w;
        }
    }

    find_outer_cycle(g);

    int32_t root = -1;
    for (int32_t i = 0; i < g.vertices[0].deg; i++) {
        if (!g.vertices[0].is_outer[i]) {
            root = g.vertices[0].neighbors[i];
            break;
        }
    }

    SubtreeInfo const info = dfs(g, root, 0);

    int32_t const cost1 = get_outer_edge_weight(g, 0, info.min_i) +
                    get_outer_edge_weight(g, 0, info.max_i) + info.l_r;

    int32_t const cost2 = info.l_cur + get_outer_edge_weight(g, 0, info.min_i) +
                    get_inner_edge_weight(g, 0, root);

    int32_t const cost3 = info.cur_r + get_outer_edge_weight(g, 0, info.max_i) +
                    get_inner_edge_weight(g, 0, root);

    int32_t const best = min({cost1, cost2, cost3});

    out << "1 ";

    if (best == cost1) {
        gen_ans(g, root, 0, 1, out);
    }
    else if (best == cost2) {
        gen_ans(g, root, 0, 2, out);
    }
    else {
        gen_ans(g, root, 2, 1, out);
    }

    out << '\n';

    in.close();
    out.close();
    return 0;
}
