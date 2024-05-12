#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "functions.h"

using namespace std;

enum trlstops {      //перечислимый тип, ввод с консоли числа
    CREATE_TRL = 1,  
    TRL_IN_STOP,
    STOPS_IN_TRL,
    TRLS,
    EXIT
};

int main() {
    string command;
    cout << "Для ввода команд используйте следующий формат:" << endl;
    cout << "(1): CREATE_TRL trl stop1 .... stopn" << endl;
    cout << "(2): TRL_IN_STOP stop" << endl;
    cout << "(3): STOPS_IN_TRL trl" << endl;
    cout << "(4): TRLS" << endl;
    cout << "(5): Завершение работы" << endl;

    while (true) {
        cout << "> ";
        getline(cin, command);

        stringstream ss(command);
        vector<string> args;
        string arg;
        while (ss >> arg) {
            args.push_back(arg);
        }

        if (args.empty())
            continue;

        int commandNum;
        try {
            commandNum = stoi(args[0]);
        } catch (const exception& e) {
            cout << "Ошибка: " << endl;
            continue;
        }

        if (commandNum == trlstops::EXIT)
            break;
        else if (commandNum == trlstops::CREATE_TRL)
            create_Trl(args);
        else if (commandNum == trlstops::TRL_IN_STOP)
            trl_In_Stop(args);
        else if (commandNum == trlstops::STOPS_IN_TRL)
            stops_In_Trl(args);
        else if (commandNum == trlstops::TRLS)
            Trls();
        else
            cout << "Неверная команда" << endl;
    }

    return 0;
}
