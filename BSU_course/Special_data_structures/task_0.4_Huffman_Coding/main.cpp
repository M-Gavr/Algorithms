#include <climits>
#include <cstdint>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

class Binary_Heap {
   public:
    Binary_Heap() {
    }

    Binary_Heap(const int32_t capacity) : values(vector<int64_t>(capacity)), size(0) {
    }

    explicit Binary_Heap(const vector<int64_t>& numbers) {
        values = numbers;
        size = numbers.size();
        // sieve_tree();
    }

    Binary_Heap(const Binary_Heap& other_heap) : values(other_heap.values), size(other_heap.size) {
    }

    Binary_Heap(Binary_Heap&& other_heap) noexcept
        : values(std::move(other_heap.values)), size(other_heap.size) {
        other_heap.size = 0;
    }

    Binary_Heap& operator=(const Binary_Heap& other_heap) {
        if (this != &other_heap) {
            values = other_heap.values;
            size = other_heap.size;
        }
        return *this;
    }

    Binary_Heap& operator=(Binary_Heap&& other_heap) noexcept {
        if (this != &other_heap) {
            values = std::move(other_heap.values);
            size = other_heap.size;
            other_heap.size = 0;
        }
        return *this;
    }

    void insert(const int64_t key) {
        values.push_back(key);
        ++size;
        sieve_up(size - 1);
    }

    int64_t get_min() const {
        return values[0];
    }

    int64_t extract_min() {
        const int64_t result = values[0];
        values[0] = values[size - 1];
        values.pop_back();
        --size;
        sieve_down(0);
        return result;
    }

    int64_t huffman_coding() {
        int64_t result = 0;
        while (size > 1) {
            int64_t temp = 0;
            temp += extract_min();
            temp += extract_min();
            insert(temp);
            result += temp;
        }
        return result;
    }

    void sieve_tree() {
        for (int32_t i = (size / 2) - 1; i >= 0; --i) {
            sieve_down(i);
        }
    }

    void sieve_down(int32_t index) {
        int32_t left = 0;
        int32_t right = 0;
        int32_t smallest = 0;

        while (true) {
            left = get_left_child_index(index);
            right = get_right_child_index(index);
            smallest = index;

            if (left < size && values[left] < values[smallest]) {
                smallest = left;
            }

            if (right < size && values[right] < values[smallest]) {
                smallest = right;
            }

            if (smallest == index) {
                break;
            }

            swap(values[index], values[smallest]);
            index = smallest;
        }
    }

    void sieve_up(int32_t index) {
        int32_t parent = 0;
        while (index > 0) {
            parent = get_parent_index(index);

            if (values[index] < values[parent]) {
                swap(values[index], values[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Binary_Heap& bt) {
        os << "Binary_Heap: [";

        for (int32_t i = 0; i < bt.size; ++i) {
            os << bt.values[i];
            if (i < bt.size - 1) {
                os << " ";
            }
        }

        os << "]\n";
        return os;
    }

   private:
    vector<int64_t> values;
    int32_t size = 0;  // logic
    const int32_t DEFAULT_SIZE = 8;

    static int32_t get_left_child_index(const int32_t index) {
        return (index * 2 + 1);
    }

    static int32_t get_right_child_index(const int32_t index) {
        return (index * 2 + 2);
    }

    static int32_t get_parent_index(const int32_t index) {
        return (index - 1) / 2;
    }
};

int64_t solve(const vector<int64_t>& values) {
    int32_t n = values.size() - 2;
    int64_t result = 0;
    deque<int64_t> dq;
    int64_t first = values[0];
    int64_t second = values[1];

    int32_t index = 2;

    while (dq.size() + (first > 0) + (second > 0) > 1) {
        int64_t val1 = LONG_LONG_MAX;
        int64_t val2 = LONG_LONG_MAX;
        int64_t val3 = LONG_LONG_MAX;

        if (first != 0 && second != 0) {
            val1 = first + second;
        }

        if (first != 0 && !dq.empty()) {
            val2 = dq[0] + first;
        }

        if (dq.size() > 1) {
            val3 = dq[0] + dq[1];
        }

        if (val1 <= min(val2, val3)) {
            result += val1;
            dq.push_back(val1);
            first = second = 0;

            if (n != 0) {
                first = values[index];
                n--;
                index++;
            }

            if (n != 0) {
                second = values[index];
                n--;
                index++;
            }

        } else if (val2 <= min(val1, val3)) {
            result += val2;
            dq.push_back(val2);
            dq.pop_front();
            swap(first, second);
            second = 0;
            if (n != 0) {
                second = values[index];
                n--;
                index++;
            }
        } else {
            result += val3;
            dq.push_back(val3);
            dq.pop_front();
            dq.pop_front();
        }
    }

    return result;
}

// int64_t solve(const vector<int64_t>& values) {
//     size_t n = values.size();
//     vector<int64_t> b;
//     b.reserve(n);
//
//     size_t i = 0;
//     size_t j = 0;
//     int64_t ans = 0;
//
//     while (i < n || j < b.size()) {
//         if (i >= n && j + 1 >= b.size()) break;
//
//         int64_t first = 0, second = 0;
//
//         if (i >= n) {
//             first = b[j]; j++;
//         } else if (j >= b.size()) {
//             first = values[i]; i++;
//         } else {
//             if (values[i] <= b[j]) {
//                 first = values[i]; i++;
//             } else {
//                 first = b[j]; j++;
//             }
//         }
//
//         if (i >= n) {
//             second = b[j]; j++;
//         } else if (j >= b.size()) {
//             second = values[i]; i++;
//         } else {
//             if (values[i] <= b[j]) {
//                 second = values[i]; i++;
//             } else {
//                 second = b[j]; j++;
//             }
//         }
//
//         int64_t sum = first + second;
//         ans += sum;
//         b.push_back(sum);
//     }
//
//     return ans;
// }

// int64_t solve(const vector<int64_t>& values) {
//     size_t n = values.size();
//
//     vector<int64_t> heap = values;
//     make_heap(heap.begin(), heap.end(), greater<int64_t>());
//
//     int64_t ans = 0;
//     size_t size = n;
//
//     while (size > 1) {
//         pop_heap(heap.begin(), heap.begin() + size, greater<int64_t>());
//         int64_t first = heap[size - 1];
//         size--;
//
//         pop_heap(heap.begin(), heap.begin() + size, greater<int64_t>());
//         int64_t second = heap[size - 1];
//         size--;
//
//         int64_t sum = first + second;
//         ans += sum;
//
//         heap[size] = sum;
//         size++;
//         push_heap(heap.begin(), heap.begin() + size, greater<int64_t>());
//     }
//
//     return ans;
// }

int main() {
    ios_base::sync_with_stdio(false);

    ifstream in("huffman.in");
    ofstream out("huffman.out");

    in.tie(nullptr);
    out.tie(nullptr);

    // int32_t k = 0;
    // in >> k;
    //
    // for (int32_t j = 0; j < k; ++j) {
    //     int32_t n = 0;
    //     in >> n;
    //     vector<int64_t> numbers(n, 0);
    //
    //     for (int32_t i = 0; i < n; ++i) {
    //         in >> numbers[i];
    //     }
    //
    //     out << n << "\n";
    //     for (int32_t i = 0; i < n; ++i) {
    //         out << numbers[i] << ' ';
    //     }
    //     out << '\n';
    //
    //     Binary_Heap heap = Binary_Heap(numbers);
    //     const int64_t result = heap.huffman_coding();
    //     out << result << ' ';
    //
    //     const int64_t result_2 = solve(numbers);
    //     out << result_2 << ' ';
    //
    //     int64_t ans = 0;
    //     in >> ans;
    //     out << ans << '\n' << '\n';
    // }

    int32_t n = 0;
    in >> n;
    vector<int64_t> numbers(n, 0);

    for (int32_t i = 0; i < n; ++i) {
        in >> numbers[i];
    }

    // out << n << "\n";
    // for (int32_t i = 0; i < n; ++i) {
    //     out << numbers[i] << ' ';
    // }
    // out << '\n' << '\n';

    // Binary_Heap heap = Binary_Heap(numbers);

    // out << heap;

    // heap.insert(0);
    // heap.insert(-1);
    // out << heap;
    //
    // out << heap.extract_min() << ' ' << heap.extract_min() << '\n';
    // out << heap;
    // out << '\n';

    // int32_t const result = heap.huffman_coding();
    // out << result << '\n';
    // out << '\n';

    const int64_t result_2 = solve(numbers);
    out << result_2 << '\n';
    // out << '\n';

    in.close();
    out.close();
    return 0;
}
