#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip> // Для форматирования вывода

using namespace std;

// Структура для хранения информации о посетителе
struct Visitor {
    string id; // Номер талона
    int duration; // Продолжительность посещения
    Visitor(const string& _id, int _duration) : id(_id), duration(_duration) {}
};

// Функция для сортировки посетителей по продолжительности
bool compareVisitor(const Visitor &a, const Visitor &b) {
    return a.duration < b.duration;
}

int main() {
    int numWindows;
    cout << "Введите количество окон: ";
    cin >> numWindows;

    vector<queue<Visitor>> windows(numWindows); // Вектор очередей для каждого окна

    random_device rd; // Инициализация генератора случайных чисел
    mt19937 gen(rd()); // Мерсенн Твист
    uniform_int_distribution<> dis(0, 999); // Равномерное распределение в диапазоне от 0 до 999

    string command;
    while (true) {
        cout << "<<< ";
        cin >> command;
        
        if (command == "ENQUEUE") {
            int duration;
            cin >> duration;
            
            string visitorID = "T" + to_string(dis(gen)); // Генерация случайного номера талона
            
            Visitor visitor(visitorID, duration);

            // Поиск окна с минимальной очередью
            auto minWindow = min_element(windows.begin(), windows.end(),
                [](const queue<Visitor> &a, const queue<Visitor> &b) {
                    return a.size() < b.size();
                });
            
            // Добавление посетителя в очередь выбранного окна
            minWindow->push(visitor);
            
            // Вывод номера талона
            cout << ">>> " << visitor.id << endl;
        } else if (command == "DISTRIBUTE") {
            // Сортировка посетителей в каждой очереди по продолжительности
            for (auto &window : windows) {
                vector<Visitor> visitors;
                while (!window.empty()) {
                    visitors.push_back(window.front());
                    window.pop();
                }
                sort(visitors.begin(), visitors.end(), compareVisitor);
                for (const auto &visitor : visitors) {
                    window.push(visitor);
                }
            }
            
            // Вывод распределения посетителей на окна
            for (int i = 0; i < numWindows; ++i) {
                int totalDuration = 0;
                cout << ">>> Окно " << i + 1 << ": ";
                while (!windows[i].empty()) {
                    totalDuration += windows[i].front().duration;
                    cout << setw(4) << windows[i].front().id << ", ";
                    windows[i].pop();
                }
                cout << "(" << totalDuration << " минут): " << endl;
            }
            break;
        }
    }

    return 0;
}
