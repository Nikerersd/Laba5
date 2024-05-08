#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "functions.h"

using namespace std;

int main() {
    string command;
    cout << "Для ввода команд используйте следующий формат:" << endl;
    cout << "CREATE_TRL trl stop1 .... stopn" << endl;
    cout << "TRL_IN_STOP stop" << endl;
    cout << "STOPS_IN_TRL trl" << endl;
    cout << "TRLS" << endl;
    cout << "Для завершения работы введите 'exit'" << endl;

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

        if (args[0] == "exit")
            break;
        else if (args[0] == "CREATE_TRL")
            create_Trl(args);
        else if (args[0] == "TRL_IN_STOP")
            trl_In_Stop(args);
        else if (args[0] == "STOPS_IN_TRL")
            stops_In_Trl(args);
        else if (args[0] == "TRLS")
            Trls();
        else
            cout << "Неверная команда" << endl;
    }

    return 0;
}
