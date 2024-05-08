#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Stop {
    string name;
    vector<string> buses;
};

// Структура троллейбуса
struct Trolleybus {
    string name;
    vector<string> stops;
};

// Хранилище данных
unordered_map<string, Trolleybus> trolleys;
unordered_map<string, Stop> stops;

// Создание троллейбуса с указанными остановками
void create_Trl(const vector<string>& args) {
    if (args.size() < 4) {
        cout << "Ошибка: недостаточно аргументов для команды CREATE_TRL" << endl;
        return;
    }

    string name = args[1];
    // Проверяем, существует ли уже троллейбус с таким именем
    if (trolleys.find(name) != trolleys.end()) {
        cout << "Такой троллейбус уже существует" << endl;
        return;
    }

    // Создаем список остановок для нового троллейбуса
    vector<string> newStops;
    for (size_t i = 2; i < args.size(); ++i) {
        newStops.push_back(args[i]);
    }

    // Проверяем, не существует ли уже троллейбуса с теми же остановками
    for (const auto& trolley : trolleys) {
        if (trolley.second.stops == newStops) {
            cout << "Троллейбус с такими же остановками уже существует (" << trolley.second.name << ")" << endl;
            return;
        }
    }

    // Очищаем данные об остановках, если троллейбус создается заново
    trolleys[name].stops.clear();

    trolleys[name].name = name;
    for (const string& stop : newStops) {
        trolleys[name].stops.push_back(stop);
        stops[stop].buses.push_back(name);
    }

    cout << "Троллейбус " << name << " создан" << endl;
}

// Вывод всех троллейбусов, проходящих через указанную остановку
void trl_In_Stop(const vector<string>& args) {
    if (args.size() != 2) {
        cout << "Ошибка: недостаточно аргументов для команды TRL_IN_STOP" << endl;
        return;
    }

    string stopName = args[1];
    if (stops.find(stopName) == stops.end()) {
        cout << "Остановка " << stopName << " не найдена" << endl;
        return;
    }

    cout << "Троллейбусы, проходящие через остановку " << stopName << ":" << endl;
    for (const string& bus : stops[stopName].buses) {
        cout << bus << endl;
    }
}

// Вывод всех остановок, которые проезжает указанный троллейбус
void stops_In_Trl(const vector<string>& args) {
    if (args.size() != 2) {
        cout << "Ошибка: недостаточно аргументов для команды STOPS_IN_TRL" << endl;
        return;
    }

    string trolleyName = args[1];
    if (trolleys.find(trolleyName) == trolleys.end()) {
        cout << "Троллейбус " << trolleyName << " не найден" << endl;
        return;
    }

    cout << "Остановки, которые проезжает троллейбус " << trolleyName << ":" << endl;
    for (const string& stop : trolleys[trolleyName].stops) {
        cout << stop << " (";
        for (const string& bus : stops[stop].buses) {
            if (bus != trolleyName) {
                cout << bus << " ";
            }
        }
        cout << ")" << endl;
    }
}

// Вывод всех троллейбусов с указанием остановок
void Trls() {
    cout << "Список всех троллейбусов с указанием остановок:" << endl;
    for (const auto& trolley : trolleys) {
        cout << "Троллейбус " << trolley.second.name << ": ";
        for (const string& stop : trolley.second.stops) {
            cout << stop << " ";
        }
        cout << endl;
    }
}
