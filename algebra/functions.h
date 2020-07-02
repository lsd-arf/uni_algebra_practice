#ifndef functions
#define functions

#pragma once
#include <iostream>
#include <string>

using namespace std;

// достаём x и y из строки a+ib
void alg_id(string &num, int &x, int &y);

// считаем аргумент на основе x и y
void arg_func(string &arg, int &x, int &y);

/* ******************** ФУНКЦИИ МЕНЮ ******************** */

// элементарные операции
void elem_ops(string num, string alg, int x1, int y1, int x2, int y2, int x, int y, int key);

// переводим числа из алгебраической формы
void from_alg(string num, string mod, string trig, string ex, string arg, int x, int y);

// переводим числа из тригонометрической формы
void from_trig(string num, string mod, string trig, string ex, string arg, string alg);

// переводим числа из экспоненциальной формы
void from_ex(string num, string mod, string trig, string ex, string arg, string alg);

// возведение в степень
void degree(string num, int ar, string alg, int x, int y);

// поиск n корней заданной степени
void degree_root(string num, string mod, string alg, string arg, int ar, int x, int y);

#endif