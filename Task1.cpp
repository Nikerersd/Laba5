#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const int MAX_ITEMS_PER_CELL = 10;
const int NUM_ZONES = 1;
const int NUM_SHELVES_PER_ZONE = 10;
const int NUM_SECTIONS_PER_SHELF = 7;
const int NUM_SHELVES_PER_SECTION = 4;

// Структура для хранения информации о товаре в ячейке
struct Item {
    string name;
    int quantity;
};

// Класс для управления складом
class Warehouse {
private:
    map<string, vector<Item>> cells; // Контейнер ячеек и содержащихся в них товаров

public:
    void addItem(string itemName, int quantity, string cellAddress) {
        auto& items = cells[cellAddress]; // получаем ссылку на вектор товаров в данной ячейке
        int summ = 0;
        for (auto& item : items) {
            summ += item.quantity;
        }
        // ищем товар с таким же именем
        for (auto& item : items) {
            if (item.name == itemName) {
                // если товар найден, увеличиваем его количество
                if (summ + quantity <= MAX_ITEMS_PER_CELL) {
                    item.quantity += quantity;
                    return;
                } 
                else {
                    cout << "Невозможно добавить товар " << itemName << " в ячейку " << cellAddress << ". Превышен лимит в " << MAX_ITEMS_PER_CELL << " единиц." << endl;
                    return;
                }
            }
        }
        // если товар не найден, добавляем новый
        if (summ + quantity <= MAX_ITEMS_PER_CELL) {
            items.push_back({itemName, quantity});
        } 
        else {
            cout << "Ячейка " << cellAddress << " заполнена. Невозможно добавить товар " << itemName << "." << endl;
        }
    }

    void removeItem(string itemName, int quantity, string cellAddress) {
        for (auto it = cells[cellAddress].begin(); it != cells[cellAddress].end(); it++) {
            if (it->name == itemName) {
                if (it->quantity >= quantity) {
                    it->quantity -= quantity;
                    if (it->quantity == 0) {
                        cells[cellAddress].erase(it);
                    }
                    return;
                }
                else {
                    cout << "В ячейке " << cellAddress << " недостаточно товара " << itemName << "." << endl;
                    return;
                }
            }
        }
        cout << "В ячейке " << cellAddress << " нет товара " << itemName << "." << endl;
    }

    void getInfo() {
        int totalItems = 0;
        int totalCells = NUM_ZONES * NUM_SHELVES_PER_ZONE * NUM_SECTIONS_PER_SHELF * NUM_SHELVES_PER_SECTION;
        int occupiedCells = 0;

        for (const auto& cell : cells) {
            if (!cell.second.empty()) {
                occupiedCells++;
                for (const auto& item : cell.second) {
                    totalItems += item.quantity;
                }
            }
        }

        cout << "Общая загрузка склада: " << (static_cast<double>(totalItems) / (totalCells * MAX_ITEMS_PER_CELL)) * 100 << "%" << endl;
        cout << "Загрузка зоны A: " << (static_cast<double>(totalItems) / (totalCells * MAX_ITEMS_PER_CELL)) * 100 << "%" << endl;

        cout << "Содержимое ячеек:" << endl;
        for (const auto& cell : cells) {
            if (!cell.second.empty()) {
                cout << "Ячейка " << cell.first << ": ";
                for (const auto& item : cell.second) {
                    cout << item.name << " (" << item.quantity << "), ";
                }
                cout << endl;
            }
        }

        cout << "Пустые ячейки:" << endl;
        for (int i = 0; i < NUM_ZONES; i++) {
            for (int j = 0; j < NUM_SHELVES_PER_ZONE; j++) {
                for (int k = 0; k < NUM_SECTIONS_PER_SHELF; k++) {
                    for (int l = 0; l < NUM_SHELVES_PER_SECTION; l++) {
                        string cellAddress = string(1, 'A' + i) + to_string(j + 1) + to_string(k + 1) + to_string(l + 1);
                        if (cells[cellAddress].empty()) {
                            cout << cellAddress << ", ";
                        }
                    }
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Warehouse warehouse;
    string command, itemName;
    int quantity;
    string cellAddress;

    while (true) {
        cout << "Введите команду (ADD, REMOVE, INFO или EXIT): ";
        getline(cin, command);

        if (command == "EXIT") {
            break;
        } else if (command == "ADD") {
            cout << "Введите название товара, количество и адрес ячейки: ";
            getline(cin, command);
            stringstream ss(command);
            ss >> itemName >> quantity >> cellAddress;
            warehouse.addItem(itemName, quantity, cellAddress);
        } else if (command == "REMOVE") {
            cout << "Введите название товара, количество и адрес ячейки: ";
            getline(cin, command);
            stringstream ss(command);
            ss >> itemName >> quantity >> cellAddress;
            warehouse.removeItem(itemName, quantity, cellAddress);
        } else if (command == "INFO") {
            warehouse.getInfo();
        } else {
            cout << "Неизвестная команда. Попробуйте еще раз." << endl;
        }
    }

    return 0;
}
