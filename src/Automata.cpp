// Copyright 2022 UNN-IASR
#include "Automata.h"
#include <iostream>

Automata::Automata() {
    cash = 0;
    state = OFF;
    menu = {"Black Coffee", "Green Tea", "Hot Chocolate", "Double Espresso"};
    prices = {80, 70, 90, 100};
}

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        std::cout << "Automata is now ON.\n";
    } else {
        std::cout << "Automata is already running.\n";
    }
}

void Automata::off() {
    if (state == WAIT) {
        returnChange();
        state = OFF;
        std::cout << "Automata is now OFF.\n";
    } else {
        std::cout << "Cannot turn off during operation.\n";
    }
}

void Automata::coin(int amount) {
    if (state == WAIT || state == ACCEPT) {
        cash += amount;
        state = ACCEPT;
        std::cout << "Current balance: " << cash << "\n";
    } else {
        std::cout << "Cannot insert coins now.\n";
    }
}

void Automata::choice(const std::string &drink) {
    if (state == ACCEPT) {
        auto it = std::find(menu.begin(), menu.end(), drink);
        if (it == menu.end()) {
            std::cout << "Invalid selection.\n";
            cancel();
        } else {
            state = CHECK;
            check(drink);
        }
    }
}

void Automata::cancel() {
    if (state != OFF) {
        returnChange();
        state = WAIT;
    }
}

STATES Automata::getState() {
    return state;
}

void Automata::getMenu() {
    std::cout << "----- MENU -----\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        std::cout << menu[i] << " - " << prices[i] << " coins\n";
    }
    std::cout << "----------------\n";
}

int Automata::getCash() {
    return cash;
}

void Automata::check(const std::string &drink) {
    auto it = std::find(menu.begin(), menu.end(), drink);
    size_t index = std::distance(menu.begin(), it);
    int price = prices[index];

    if (cash >= price) {
        cash -= price;
        cook();
    } else {
        std::cout << "Insufficient funds.\n";
        cancel();
    }
}

void Automata::cook() {
    state = COOK;
    std::cout << "Preparing your drink...\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    finish();
}

void Automata::finish() {
    std::cout << "Enjoy your drink!\n";
    returnChange();
    state = WAIT;
}

void Automata::returnChange() {
    if (cash > 0) {
        std::cout << "Returning " << cash << " coins as change.\n";
        cash = 0;
    }
}