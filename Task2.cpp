#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

struct Visitor {
    string ticket;
    int duration;
};

class ClinicQueue {
private:
    int num_windows;
    vector<queue<Visitor>> windows;
    vector<Visitor> visitors;
    int visitorCounter = 0;

    string generateTicket() {
        return "T" + to_string(100 + (visitorCounter++ % 900));
    }

public:
    ClinicQueue(int numWindows): num_windows(numWindows), windows(numWindows) {}

    void enqueue(int duration) {
        string ticket = generateTicket();
        visitors.push_back({ticket, duration});
        cout << ticket << endl;
    }

    void distribute() {
        vector<int> load(num_windows, 0);

        // Сортировка посетителей по убыванию продолжительности для оптимизации распределения максимальной нагрузки
        sort(visitors.begin(), visitors.end(), [](Visitor &a, Visitor &b) {
            return a.duration > b.duration;
        });

        for (Visitor &v : visitors) {
            int minWindow = distance(load.begin(), min_element(load.begin(), load.end()));
            load[minWindow] += v.duration;
            windows[minWindow].push(v);
        }

        for (int i = 0; i < num_windows; ++i) {
            cout << "Окно " << (i + 1) << " (";
            int totalTime = 0;
            bool first = true;
            while (!windows[i].empty()) {
                if (!first) cout << ", ";
                first = false;
                Visitor v = windows[i].front(); 
                windows[i].pop();
                cout << v.ticket;
                totalTime += v.duration;
            }
            cout << ") " << totalTime << " минут" << endl;
        }
    }
};

int main() {
    int num_windows;
    cout << "Введите кол-во окон: ";
    cin >> num_windows;
    ClinicQueue queue(num_windows);

    string command;
    while (true) {
        cin >> command;
        if (command == "ENQUEUE") {
            int duration;
            cin >> duration;
            queue.enqueue(duration);
        } else if (command == "DISTRIBUTE") {
            queue.distribute();
            break;
        }
    }
    return 0;
}
