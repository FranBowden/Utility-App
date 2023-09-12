#pragma once //only store headers once, if file already has these headers, dont repeat
#include <iostream>
#include <iomanip>
#include <windows.h> 
#include <algorithm>
#include <stdio.h>
#include <string>
#include <fstream> 
using namespace std;

//Declaring functions
void logMessage(string msg);
int category(int basket);
int validate(int min, int max);
int optionsMenu();
string addToBasket();
void contents(string textfile, string stockfile, string id[5], string itemList[5], double price[5],int quantity[5]);
void printContent(string id[5], string itemList[5], double price[5], int quantity[5]);
char itemSelect(string id[5],string itemList[5], double price[5], int quantity[5]);
void Bye();
void clear(string textfile);
char addMoreItems();
void underline();
char validateChar();

