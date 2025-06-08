// Copyright 2022 UNN-IASR
#include "Automata.h"

int main() {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.getMenu();

    vendingMachine.coin(50);
    vendingMachine.coin(50);

    vendingMachine.choice("Double Espresso");

    vendingMachine.off();
    return 0;
}