#include "functions.h"

// достаём x и y из строки a+ib
void alg_id(string &num, int &x, int &y)
{
    string helper; // вспомогательная строка
    bool f = true; // для проверки

    for (size_t i = 0; i < num.size() - 1; i++)
        if (!(num[i] == '+' || (num[i] == '-' && i != 0)) && f)
            helper += num[i];
        else if ((num[i] == '+' || (num[i] == '-' && i != 0)) && f)
        {
            f = false;
            x = stoi(helper);
            if (num[i] == '+')
                helper = "";
            else if (num[i] == '-')
                helper = "-";
        }
        else if (!f)
            helper += num[i];

    y = stoi(helper);
}

// считаем аргумент на основе x и y
void arg_func(string &arg, int &x, int &y)
{
    if (x > 0 && y != 0)
        arg = "atan((" + to_string(y) + ")/(" + to_string(x) + "))";
    else if (x < 0 && y > 0)
        arg = "pi+atan((" + to_string(y) + ")/(" + to_string(x) + "))";
    else if (x < 0 && y < 0)
        arg = "-pi+atan((" + to_string(y) + ")/(" + to_string(x) + "))";
    else if (x == 0 && y > 0)
        arg = "pi/2";
    else if (x == 0 && y < 0)
        arg = "-pi/2";
    else if (x > 0 && y == 0)
        arg = "0";
    else if (x < 0 && y == 0)
        arg = "pi";
}

/* ******************** ФУНКЦИИ МЕНЮ ******************** */

// элементарные операции
void elem_ops(string num, string alg, int x1, int y1, int x2, int y2, int x, int y, int key)
{
    cout << "First number: ";
    cin >> num;
    alg_id(num, x1, y1);
    cout << "Second number: ";
    cin >> num;
    alg_id(num, x2, y2);
    switch (key)
    {
    case 1: // сумма
        x = x1 + x2;
        y = y1 + y2;
        break;
    case 2: // произведение
        x = x1 * x2 - y1 * y2;
        y = x1 * y2 + x2 * y1;
        break;
    case 3: // разность
        x = x1 - x2;
        y = y1 - y2;
        break;
    case 4: // деление
        x = (x1 * x2 + y1 * y2) / (x2 * x2 + y2 * y2);
        y = (x2 * y1 - x1 * y2) / (x2 * x2 + y2 * y2);
        break;
    default:
        break;
    }
    alg = to_string(x) + "+" + to_string(y) + "i";
    cout << alg << endl;
}

// переводим числа из алгебраической формы
void from_alg(string num, string mod, string trig, string ex, string arg, int x, int y)
{
    cout << "Number alg: ";
    cin >> num;
    alg_id(num, x, y);
    mod = "sqrt(" + to_string(x * x + y * y) + ")";
    arg_func(arg, x, y);
    trig = mod + "*(cos(" + arg + ")+i*sin(" + arg + "))";
    ex = mod + "*e^(i*(" + arg + "))";
    cout << "\nTrig: " << trig;
    cout << "\nEx: " << ex << endl;
}

// переводим числа из тригонометрической формы
void from_trig(string num, string mod, string trig, string ex, string arg, string alg)
{
    cout << "Number trig: ";
    cin >> num;
    for (size_t i = 0; i < num.size() - 1; i++)
        if (!(num[i] == '*' && num[i + 1] == '('))
            mod += num[i];
        else
            break;

    for (size_t i = mod.size() + 6; i < num.size() - 2; i++)
        if (!(num[i] == ')' && num[i + 1] == '+' && num[i + 2] == 'i'))
            arg += num[i];
        else
            break;

    alg = mod + "*cos(" + arg + ")+i*" + mod + "*sin(" + arg + ")";
    ex = mod + "*e^(i*(" + arg + "))";
    cout << "\nAlg: " << alg;
    cout << "\nEx: " << ex << endl;
}

// переводим числа из экспоненциальной формы
void from_ex(string num, string mod, string trig, string ex, string arg, string alg)
{
    cout << "Number ex: ";
    cin >> num;
    for (size_t i = 0; i < num.size() - 1; i++)
        if (!(num[i] == '*' && num[i + 1] == 'e'))
            mod += num[i];
        else
            break;

    for (size_t i = mod.size() + 6; i < num.size() - 2; i++)
        arg += num[i];

    alg = mod + "*cos(" + arg + ")+i*" + mod + "*sin(" + arg + ")";
    trig = mod + "*(cos(" + arg + ")+i*sin(" + arg + "))";
    cout << "\nAlg: " << alg;
    cout << "\nTrig: " << trig << endl;
}

// возведение в степень
void degree(string num, int ar, string alg, int x, int y)
{
    cout << "Number: ";
    cin >> num;
    alg_id(num, x, y);
    cout << "Degree of number: ";
    cin >> ar;
    int x_clone = x;
    int y_clone = y;
    for (int i = 1; i < ar; i++)
    {
        int x_buffer = x;
        int y_buffer = y;
        x = x_buffer * x_clone - y_buffer * y_clone;
        y = x_buffer * y_clone + x_clone * y_buffer;
    }
    alg = to_string(x) + "+" + to_string(y) + "i";
    cout << endl
         << alg << endl;
}

// поиск n корней заданной степени
void degree_root(string num, string mod, string alg, string arg, int ar, int x, int y)
{
    cout << "Number: ";
    cin >> num;
    alg_id(num, x, y);
    cout << "Root degree: ";
    cin >> ar;
    mod = "sqrt(" + to_string(x * x + y * y) + ")";
    arg_func(arg, x, y);
    cout << endl;
    for (int i = 0; i < ar; i++)
    {
        alg = mod + "*cos((" + arg + "+" + to_string(2 * i) + "*pi)/" +
              to_string(ar) + ")+i*" + mod + "*sin((" + arg + "+" +
              to_string(2 * i) + "*pi)/" + to_string(ar) + ")";
        cout << "For k = " << i << ": " << alg << endl;
    }
}