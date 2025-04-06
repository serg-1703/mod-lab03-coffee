// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

TEST(AutomataTest, InitialStateIsOFF) {
    Automata a = Automata();
    ASSERT_EQ(STATES::OFF, a.getState());
}
  
TEST(AutomataTest, CannotInsertCoinWhenOFF) {
    Automata a = Automata();
    a.coin(10);
    ASSERT_EQ(STATES::OFF, a.getState());
    ASSERT_EQ(0, a.getCash());
}
  
TEST(AutomataTest, CannotChooseDrinkWhenOFF) {
    Automata a = Automata();
    a.choice("Cappucino");
    ASSERT_EQ(STATES::OFF, a.getState());
}
  
TEST(AutomataTest, CannotCancelWhenOFF) {
    Automata a = Automata();
    a.cancel();
    ASSERT_EQ(STATES::OFF, a.getState());
    ASSERT_EQ(0, a.getCash());
}
  
TEST(AutomataTest, TurnONTheAutomata) {
    Automata a = Automata();
    a.on();
    ASSERT_EQ(STATES::WAIT, a.getState());
}
  
TEST(AutomataTest, InsertFirstCoinInWAITState) {
    Automata a = Automata();
    a.on();
    a.coin(50);
    ASSERT_EQ(STATES::ACCEPT, a.getState());
    ASSERT_EQ(50, a.getCash());
}
  
TEST(AutomataTest, InsertMultipleCoinsInWAITState) {
    Automata a;
    a.on();
    a.coin(20);
    a.coin(30);
    ASSERT_EQ(STATES::ACCEPT, a.getState());
    ASSERT_EQ(50, a.getCash());
}
  
TEST(AutomataTest, CancelInWAITStateNoCoins) {
    Automata a = Automata();
    a.on();
    a.cancel();
    ASSERT_EQ(STATES::WAIT, a.getState());
    ASSERT_EQ(0, a.getCash());
}
  
TEST(AutomataTest, CancelInWAITStateWithCoins) {
    Automata a = Automata();
    a.on();
    a.coin(50);
    a.cancel();
    ASSERT_EQ(STATES::WAIT, a.getState());
    ASSERT_EQ(50, a.getCash());
}
  
TEST(AutomataTest, ChooseDrinkInWAITStateNoCoins) {
    Automata a = Automata();
    a.on();
    a.choice("Cappucino");
    ASSERT_EQ(STATES::WAIT, a.getState());
}
  
TEST(AutomataTest, InsertCoinAfterTurnONGoesToACCEPT) {
    Automata a = Automata();
    a.on();
    a.coin(70);
    ASSERT_EQ(STATES::ACCEPT, a.getState());
    ASSERT_EQ(70, a.getCash());
}
  
TEST(AutomataTest, InsertMoreCoinsInACCEPTState) {
    Automata a = Automata();
    a.on();
    a.coin(60);
    a.coin(40);
    ASSERT_EQ(STATES::ACCEPT, a.getState());
    ASSERT_EQ(100, a.getCash());
}
  
TEST(AutomataTest, CancelInACCEPTState) {
    Automata a = Automata();
    a.on();
    a.coin(80);
    a.cancel();
    ASSERT_EQ(STATES::WAIT, a.getState());
    ASSERT_EQ(80, a.getCash());
}
  
TEST(AutomataTest, ChooseValidDrinkInACCEPTState) {
    Automata a = Automata();
    a.on();
    a.coin(150);
    a.choice("Latte");
    a.change();
    ASSERT_EQ(STATES::WAIT, a.getState());
    ASSERT_EQ(0, a.getCash());
}
  
TEST(AutomataTest, ChooseInvalidDrinkInACCEPTState) {
    Automata a = Automata();
    a.on();
    a.coin(100);
    a.choice("Americcano");
    ASSERT_EQ(STATES::WAIT, a.getState());
    ASSERT_EQ(100, a.getCash());
}
  
TEST(AutomataTest, CheckBalanceSufficientFundsGoesToCOOK) {
    Automata a = Automata();
    a.on();
    a.coin(130);
    a.choice("Cappucino");
    ASSERT_EQ(STATES::WAIT, a.getState());
    ASSERT_EQ(10, a.getCash());
}

TEST(AutomataTest, FullCycleExactChangeEspresso) {
    Automata a = Automata();
    a.on();
    a.coin(80);
    a.choice("Espresso");
    ASSERT_EQ(STATES::WAIT, a.getState());
    ASSERT_EQ(80, a.getCash());
}
  
TEST(AutomataTest, TurnOFFFromWAITState) {
    Automata a = Automata();
    a.on();
    a.off();
    ASSERT_EQ(STATES::OFF, a.getState());
    ASSERT_EQ(0, a.getCash());
}
  
TEST(AutomataTest, TryTurnOFFFromACCEPTState) {
    Automata a = Automata();
    a.on();
    a.coin(100);
    a.off();
    ASSERT_EQ(STATES::ACCEPT, a.getState());
    ASSERT_EQ(100, a.getCash());
}
  
TEST(AutomataTest, TryTurnOFFFromOFFState) {
    Automata a = Automata();
    a.off();
    ASSERT_EQ(STATES::OFF, a.getState());
}

TEST(AutomataTest, FullCycle) {
    Automata a = Automata();
    a.on();
    a.coin(90);
    a.choice("Espresso");
    a.off();
    ASSERT_EQ(STATES::OFF, a.getState());
}