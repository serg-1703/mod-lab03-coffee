// Copyright 2022 UNN-IASR
#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>

enum STATES { 
    OFF, 
    WAIT, 
    ACCEPT, 
    CHECK, 
    COOK 
};

class Automata {
 public:
    Automata();
    void on();
    void off();
    void coin(int amount);
    void choice(const std::string &drink);
    void cancel();
    STATES getState();
    void getMenu();
    int getCash();

 private:
    int cash;
    std::vector<std::string> menu;
    std::vector<int> prices;
    STATES state;

    void check(const std::string &drink);
    void cook();
    void finish();
    void returnChange();
};

#endif  // INCLUDE_AUTOMATA_H_