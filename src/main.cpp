#include "Automata.h"

int main() {
    Automata machine = Automata();
    machine.on();
    machine.getMenu();
    machine.coin(120);
    machine.coin(10);
    machine.choice("Espresso");
}