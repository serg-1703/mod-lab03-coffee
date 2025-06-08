// Copyright 2022 GHA Test Team
#include <gtest/gtest.h>
#include "Automata.h"

// 1. Проверка начального состояния
TEST(AutomataTest, InitialStateIsOff) {
    Automata machine;
    EXPECT_EQ(OFF, machine.getState());
}

// 2. Включение автомата
TEST(AutomataTest, TurnsOnCorrectly) {
    Automata machine;
    machine.on();
    EXPECT_EQ(WAIT, machine.getState());
}

// 3. Попытка вставить монету в выключенный автомат
TEST(AutomataTest, NoCoinInsertionWhenOff) {
    Automata machine;
    machine.coin(50);
    EXPECT_EQ(OFF, machine.getState());
    EXPECT_EQ(0, machine.getCash());
}

// 4. Внесение денег в состоянии WAIT
TEST(AutomataTest, AcceptsCoinsInWaitState) {
    Automata machine;
    machine.on();
    machine.coin(30);
    EXPECT_EQ(ACCEPT, machine.getState());
    EXPECT_EQ(30, machine.getCash());
}

// 5. Несколько монет подряд
TEST(AutomataTest, MultipleCoinsInAcceptState) {
    Automata machine;
    machine.on();
    machine.coin(20);
    machine.coin(50);
    EXPECT_EQ(ACCEPT, machine.getState());
    EXPECT_EQ(70, machine.getCash());
}

// 6. Отмена операции без внесения денег
TEST(AutomataTest, CancelWithoutMoney) {
    Automata machine;
    machine.on();
    machine.cancel();
    EXPECT_EQ(WAIT, machine.getState());
}

// 7. Отмена операции с деньгами (должна вернуть сдачу)
TEST(AutomataTest, CancelWithMoney) {
    Automata machine;
    machine.on();
    machine.coin(100);
    machine.cancel();
    EXPECT_EQ(WAIT, machine.getState());
    EXPECT_EQ(0, machine.getCash());  // Сдача возвращена
}

// 8. Выбор несуществующего напитка
TEST(AutomataTest, InvalidDrinkSelection) {
    Automata machine;
    machine.on();
    machine.coin(50);
    machine.choice("Fanta");  // Нет такого напитка
    EXPECT_EQ(WAIT, machine.getState());
}

// 9. Недостаточно денег для напитка
TEST(AutomataTest, NotEnoughMoneyForDrink) {
    Automata machine;
    machine.on();
    machine.coin(50);
    machine.choice("Double Espresso");  // Стоит 100
    EXPECT_EQ(WAIT, machine.getState());
}

// 10. Успешная покупка (точно хватает денег)
TEST(AutomataTest, ExactAmountForDrink) {
    Automata machine;
    machine.on();
    machine.coin(80);
    machine.choice("Black Coffee");  // Стоит 80
    EXPECT_EQ(WAIT, machine.getState());
    EXPECT_EQ(0, machine.getCash());
}

// 11. Покупка с остатком (должна вернуть сдачу)
TEST(AutomataTest, DrinkPurchaseWithChange) {
    Automata machine;
    machine.on();
    machine.coin(150);
    machine.choice("Green Tea");  // Стоит 70
    EXPECT_EQ(WAIT, machine.getState());
    EXPECT_EQ(80, machine.getCash());  // 150 - 70 = 80 сдачи
}

// 12. Попытка выбора напитка без денег
TEST(AutomataTest, ChooseDrinkWithoutMoney) {
    Automata machine;
    machine.on();
    machine.choice("Hot Chocolate");
    EXPECT_EQ(WAIT, machine.getState());
}

// 13. Выключение автомата в состоянии WAIT
TEST(AutomataTest, TurnOffFromWaitState) {
    Automata machine;
    machine.on();
    machine.off();
    EXPECT_EQ(OFF, machine.getState());
}

// 14. Попытка выключения во время приготовления
TEST(AutomataTest, CannotTurnOffWhileCooking) {
    Automata machine;
    machine.on();
    machine.coin(100);
    machine.choice("Double Espresso");
    machine.off();  // Должно проигнорироваться
    EXPECT_NE(OFF, machine.getState());
}

// 15. Проверка меню (количество позиций)
TEST(AutomataTest, MenuHasFourItems) {
    Automata machine;
    machine.on();
    testing::internal::CaptureStdout();
    machine.getMenu();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(4, std::count(output.begin(), output.end(), '\n'));
}

// 16. Проверка состояния после приготовления
TEST(AutomataTest, ReturnsToWaitAfterCooking) {
    Automata machine;
    machine.on();
    machine.coin(100);
    machine.choice("Double Espresso");
    EXPECT_EQ(WAIT, machine.getState());
}

// 17. Попытка выбора напитка в состоянии OFF
TEST(AutomataTest, NoDrinkSelectionWhenOff) {
    Automata machine;
    machine.choice("Black Coffee");
    EXPECT_EQ(OFF, machine.getState());
}

// 18. Внесение нулевой суммы
TEST(AutomataTest, InsertZeroCoins) {
    Automata machine;
    machine.on();
    machine.coin(0);
    EXPECT_EQ(WAIT, machine.getState());  // Не переходит в ACCEPT
    EXPECT_EQ(0, machine.getCash());
}

// 19. Попытка отмены в состоянии OFF
TEST(AutomataTest, CancelWhenOffDoesNothing) {
    Automata machine;
    machine.cancel();
    EXPECT_EQ(OFF, machine.getState());
}

// 20. Полный цикл работы (включение, внесение денег, покупка, выключение)
TEST(AutomataTest, FullWorkCycle) {
    Automata machine;
    machine.on();
    machine.coin(90);
    machine.choice("Hot Chocolate");  // Стоит 90
    machine.off();
    EXPECT_EQ(OFF, machine.getState());
}

// 21. Проверка баланса после отмены
TEST(AutomataTest, BalanceResetAfterCancel) {
    Automata machine;
    machine.on();
    machine.coin(200);
    machine.cancel();
    EXPECT_EQ(0, machine.getCash());
}