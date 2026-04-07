#include <fstream>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int32_t n = 0;
    int32_t m = 0;
    int32_t k = 0;
    in >> n >> m >> k;

    int32_t retrovirus = 0;

    string clipboard = "";

    struct Window {
        string full_text;
        string displayed_text;
    };

    vector<Window> windows(n);
    int32_t current_window = 0;

    for (int32_t i = 0; i < m; i++) {
        string command;
        in >> command;

        if (command == "Next") {
            current_window = (current_window + 1) % n;
        }
        else if (command == "Copy") {
            clipboard = windows[current_window].displayed_text;
        }
        else if (command == "Paste") {
            if (!clipboard.empty()) {
                windows[current_window].full_text += clipboard;

                if (windows[current_window].full_text.length() <= k) {
                    windows[current_window].displayed_text = windows[current_window].full_text;
                } else {
                    windows[current_window].displayed_text = windows[current_window].full_text.substr(
                        windows[current_window].full_text.length() - k
                    );
                }
            }
        }
        else if (command == "Backspace") {
            if (!windows[current_window].full_text.empty()) {
                windows[current_window].full_text.pop_back();

                if (windows[current_window].full_text.length() <= k) {
                    windows[current_window].displayed_text = windows[current_window].full_text;
                } else {
                    windows[current_window].displayed_text = windows[current_window].full_text.substr(
                        windows[current_window].full_text.length() - k
                    );
                }
            }
        }
        else {
            windows[current_window].full_text += command;

            if (windows[current_window].full_text.length() <= k) {
                windows[current_window].displayed_text = windows[current_window].full_text;
            } else {
                windows[current_window].displayed_text = windows[current_window].full_text.substr(
                    windows[current_window].full_text.length() - k
                );
            }
        }
    }

    if (windows[current_window].displayed_text.empty()) {
        out << "Empty" << '\n';
    } else {
        out << windows[current_window].displayed_text << '\n';
    }

    in.close();
    out.close();
    return 0;
}
