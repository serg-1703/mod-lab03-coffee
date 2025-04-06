#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

enum STATES { OFF, WAIT, ACCEPT, CHECK, COOK };

class Automata {
    public:
        void on();
        void off();
        void coin(int money);
        void choice(std::string drink);
        void cancel();
        STATES getState();
        void getMenu();
        int getCash();
        void change();
        Automata() {
            cash = 0;
            state = OFF;
            menu = {"Cappucino", "Americano", "Latte", "Espresso"};
            prices = {120, 100, 130, 90};
        }

    private:
        int cash;
        std::vector<std::string> menu;
        std::vector<int> prices;
        STATES state;
        void check(std::string drink);
        void cook();
        void finish();
};
#endif 