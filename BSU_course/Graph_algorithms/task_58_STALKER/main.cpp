#include <cstdint>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int32_t INF = 1e9;
const int32_t dx[4] = {1, -1, 0, 0};
const int32_t dy[4] = {0, 0, 1, -1};

struct Edge {
    int32_t to, cap, cost, rev;
};

// Dijkstra с потенциалами Джонсона для отрицательных стоимостей
bool dijkstra(
    int32_t s, const int32_t t, const vector<vector<Edge>>& g, vector<int32_t>& dist,
    const vector<int32_t>& pot, vector<int32_t>& pv, vector<int32_t>& pe) {
    int32_t n = g.size();
    dist.assign(n, INF);
    pv.assign(n, -1);
    pe.assign(n, -1);

    using pli = pair<int64_t, int32_t>;
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) {
            continue;
        }

        for (int32_t i = 0; i < static_cast<int32_t>(g[v].size()); i++) {
            const Edge& e = g[v][i];
            if (e.cap > 0) {
                int32_t const nd = dist[v] + e.cost + pot[v] - pot[e.to];
                if (dist[e.to] > nd) {
                    dist[e.to] = nd;
                    pv[e.to] = v;
                    pe[e.to] = i;
                    pq.emplace(nd, e.to);
                }
            }
        }
    }

    return dist[t] < INF;
}

pair<int32_t, int32_t> min_cost_flow(
    const int32_t s, const int32_t t, const int32_t max_f, vector<vector<Edge>>& g) {
    int32_t const n = g.size();
    int32_t flow = 0;
    int32_t cost = 0;
    vector<int32_t> pot(n, 0);
    vector<int32_t> dist;
    vector<int32_t> pv;
    vector<int32_t> pe;

    while (flow < max_f && dijkstra(s, t, g, dist, pot, pv, pe)) {
        // Обновляем потенциалы
        for (int32_t v = 0; v < n; v++) {
            if (dist[v] < INF) {
                pot[v] += dist[v];
            }
        }

        // Находим минимальную остаточную пропускную способность на пути
        int32_t f = max_f - flow;
        for (int32_t v = t; v != s; v = pv[v]) {
            f = min(f, g[pv[v]][pe[v]].cap);
        }

        // Пропускаем поток
        for (int32_t v = t; v != s; v = pv[v]) {
            Edge& e = g[pv[v]][pe[v]];
            e.cap -= f;
            g[v][e.rev].cap += f;
            cost += e.cost * f;
        }

        flow += f;
    }

    return {flow, cost};
}

void add_edge(
    vector<vector<Edge>>& g, const int32_t from, const int32_t to, const int32_t cap,
    const int32_t cost) {
    g[from].push_back({to, cap, cost, static_cast<int32_t>(g[to].size())});
    g[to].push_back({from, 0, -cost, static_cast<int32_t>(g[from].size()) - 1});
}

int main() {
    ifstream fin("walk.in");
    ofstream fout("walk.out");

    ios::sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);

    int32_t m = 0;
    int32_t n = 0;
    fin >> m >> n;

    vector<string> lab(m);
    for (int32_t i = 0; i < m; i++) {
        fin >> lab[i];
    }

    int32_t start_x = -1;
    int32_t start_y = -1;
    int32_t key_x = -1;
    int32_t key_y = -1;
    for (int32_t i = 0; i < m; i++) {
        for (int32_t j = 0; j < n; j++) {
            if (lab[i][j] == 'M') {
                start_x = i;
                start_y = j;
            } else if (lab[i][j] == 'G') {
                key_x = i;
                key_y = j;
            }
        }
    }

    // Разбиение: для каждой комнаты (i,j) создаём две вершины:
    // in  = 2*(i*N + j)
    // out = 2*(i*N + j) + 1
    auto in = [&](const int32_t i, const int32_t j) { return 2 * (i * n + j); };
    auto out = [&](const int32_t i, const int32_t j) { return (2 * (i * n + j)) + 1; };

    auto room_is_empty = [&](const int32_t i, const int32_t j) {
        return i >= 0 && i < m && j >= 0 && j < n && lab[i][j] != '*';
    };

    const int32_t k = 2 * m * n;
    vector<vector<Edge>> g(k);

    for (int32_t i = 0; i < m; i++) {
        for (int32_t j = 0; j < n; j++) {
            if (lab[i][j] == '*') {
                continue;
            }

            const int32_t v_in = in(i, j);
            const int32_t v_out = out(i, j);

            // Ребро внутри комнаты: in -> out
            // cap=2 (можно пройти дважды: туда и обратно), cost=0
            add_edge(g, v_in, v_out, 2, 0);

            // Переходы в соседние комнаты: out текущей -> in соседа
            for (int32_t d = 0; d < 4; d++) {
                const int32_t ni = i + dx[d];
                const int32_t nj = j + dy[d];
                if (room_is_empty(ni, nj)) {
                    const int32_t u_in = in(ni, nj);
                    add_edge(g, v_out, u_in, 1, 1);
                }
            }
        }
    }

    const int32_t start_in = in(start_x, start_y);
    const int32_t target_in = in(key_x, key_y);

    // Запускаем поток из start_in в target_in
    // Нужно отправить 2 единицы (два пути: туда и обратно)
    auto [flow, cost] = min_cost_flow(start_in, target_in, 2, g);

    if (flow < 2) {
        fout << -1 << '\n';
    } else {
        fout << cost << '\n';
    }

    fin.close();
    fout.close();
    return 0;
}
