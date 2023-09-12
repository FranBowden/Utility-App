#pragma once
#include "Functions.hpp"
#include <time.h> //included for random generation

void money(double total);
char noOrder(double total);
void orders();
double moneyAdded();
double validateMoney(double min);
void printTotal(double total);
double charity(double total);
char ready();
double readOrderFile();
void stock(string textfile, int quantity[5]);
int randomBreak();
