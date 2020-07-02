#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;
const double PI = 2 * acos(0.0);
const int sym = 3;

template <typename Type> // преобразование в строку
string to_str(const Type &t)
{
    ostringstream os;
    os << t;
    return os.str();
}

void after_point(double &num)
{
    int ar = pow(10, sym);                // sym - количество знаков после запятой
    int modulo = (int)(num * ar) % ar;    // остаток от деления - знаки после запятой
    num = (int)num + (double)modulo / ar; // число с заданной точностью
}

// считаем аргумент на основе x и y
double arg_func(double x, double y)
{
    if (x > 0 && y != 0)
        return atan(y / x);
    else if (x < 0 && y > 0)
        return PI + atan(y / x);
    else if (x < 0 && y < 0)
        return -PI + atan(y / x);
    else if (x == 0 && y > 0)
        return PI / 2;
    else if (x == 0 && y < 0)
        return -PI / 2;
    else if (x > 0 && y == 0)
        return 0;
    else if (x < 0 && y == 0)
        return PI;
}

// алгебраическая форма в любом виде
string beauty_alg(double x, double y)
{
    if (x == 0)
    {
        if (y == 0)
            return "0";
        else if (y == 1)
            return "i";
        else if (y == -1)
            return "-i";
        else
            return to_str(y) + "*i";
    }
    else if (x == 1)
    {
        if (y == 0)
            return "1";
        else if (y == 1)
            return "1+i";
        else if (y == -1)
            return "1-i";
        else if (y < 0)
            return "1" + to_str(y) + "*i";
        else
            return "1+" + to_str(y) + "*i";
    }
    else
    {
        if (y == 0)
            return to_str(x);
        else if (y == 1)
            return to_str(x) + "+i";
        else if (y == -1)
            return to_str(x) + "-i";
        else if (y > 0)
            return to_str(x) + "+" + to_str(y) + "*i";
        else
            return to_str(x) + to_str(y) + "*i";
    }
}

/* ******************** ФУНКЦИИ МЕНЮ ******************** */

// элементарные операции
void elem_ops(double x1, double y1, double x2, double y2, double x, double y, int key)
{
    string alg;
    bool flag = true;
    cout << "***First number***\n";
    cout << "ReZ: ";
    cin >> x1;
    cout << "ImZ: ";
    cin >> y1;

    cout << "***Second number***\n";
    cout << "ReZ: ";
    cin >> x2;
    cout << "ImZ: ";
    cin >> y2;

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
        if (x2 == 0 && y2 == 0)
        {
            flag = false;
            cout << "\n----------Result----------";
            cout << "\n||| It can't be complete |||";
            cout << "\nAlg: null" << alg;
            cout << "\n--------------------------";
        }
        else
        {
            x = (x1 * x2 + y1 * y2) / (x2 * x2 + y2 * y2);
            y = (x2 * y1 - x1 * y2) / (x2 * x2 + y2 * y2);
        }
        break;
    default:
        break;
    }

    if (flag)
    {
        after_point(x);
        after_point(y);

        alg = beauty_alg(x, y);

        cout << "\n----------Result----------";
        cout << "\nAlg: " << alg;
        cout << "\n--------------------------";
    }
}

// переводим числа из алгебраической формы
void from_alg(double mod, double arg, double x, double y)
{
    string trig, ex;
    cout << "***Number alg***\n";
    cout << "ReZ: ";
    cin >> x;
    cout << "ImZ: ";
    cin >> y;

    if (x == 0 && y == 0)
    {
        cout << "\n----------Result----------";
        cout << "\nTrig: 0";
        cout << "\nEx: 0";
        cout << "\n--------------------------";
    }
    else
    {
        mod = sqrt(x * x + y * y);
        arg = arg_func(x, y) * 180 / PI;
        after_point(mod);
        after_point(arg);

        trig = to_str(mod) + "*(cos(" + to_str(arg) + ")+i*sin(" + to_str(arg) + "))";
        ex = to_str(mod) + "*e^(" + to_str(arg) + "*i)";

        cout << "\n----------Result----------";
        cout << "\nTrig: " << trig;
        cout << "\nEx: " << ex;
        cout << "\n--------------------------";
    }
}

// переводим числа из тригонометрической формы
void from_trig(double mod, double arg)
{
    string alg, ex;
    double x, y;
    cout << "***Number trig***\n";
    cout << "Mod: ";
    cin >> mod;
    cout << "Arg: ";
    cin >> arg;

    if (mod <= 0)
    {
        cout << "\n----------Result----------";
        cout << "\nAlg: 0";
        cout << "\nEx: 0";
        cout << "\n--------------------------";
    }
    else if (mod < 0)
    {
        cout << "\n----------Result----------";
        cout << "\n||| Mod can't be < 0 |||";
        cout << "\nAlg: null";
        cout << "\nEx: null";
        cout << "\n--------------------------";
    }
    else
    {
        x = mod * cos(arg * PI / 180);
        y = mod * sin(arg * PI / 180);

        after_point(mod);
        after_point(arg);
        after_point(x);
        after_point(y);

        alg = beauty_alg(x, y);
        ex = to_str(mod) + "*e^(" + to_str(arg) + "*i)";

        cout << "\n----------Result----------";
        cout << "\nAlg: " << alg;
        cout << "\nEx: " << ex;
        cout << "\n--------------------------";
    }
}

// переводим числа из экспоненциальной формы
void from_ex(double mod, double arg)
{
    string alg, trig;
    double x, y;
    cout << "***Number ex***\n";
    cout << "Mod: ";
    cin >> mod;
    cout << "Arg: ";
    cin >> arg;

    if (mod == 0)
    {
        cout << "\n----------Result----------";
        cout << "\nAlg: 0" << alg;
        cout << "\nTrig: 0" << trig;
        cout << "\n--------------------------";
    }
    else if (mod < 0)
    {
        cout << "\n----------Result----------";
        cout << "\n||| Mod can't be < 0 |||";
        cout << "\nAlg: null";
        cout << "\nEx: null";
        cout << "\n--------------------------";
    }
    else
    {
        x = mod * cos(arg * PI / 180);
        y = mod * sin(arg * PI / 180);

        after_point(mod);
        after_point(arg);
        after_point(x);
        after_point(y);

        alg = beauty_alg(x, y);
        trig = to_str(mod) + "*(cos(" + to_str(arg) + ")+i*sin(" + to_str(arg) + "))";

        cout << "\n----------Result----------";
        cout << "\nAlg: " << alg;
        cout << "\nTrig: " << trig;
        cout << "\n--------------------------";
    }
}

// возведение в степень
void degree(int ar, double x, double y)
{
    string alg;
    bool flag = true;
    cout << "***Number alg***\n";
    cout << "ReZ: ";
    cin >> x;
    cout << "ImZ: ";
    cin >> y;
    cout << "Degree of number: ";
    cin >> ar;

    if (ar == 0)
    {
        x = 1;
        y = 0;
    }
    else if (ar > 0)
    {
        double x_clone = x;
        double y_clone = y;
        for (int i = 1; i < ar; i++)
        {
            double x_buffer = x;
            double y_buffer = y;
            x = x_buffer * x_clone - y_buffer * y_clone;
            y = x_buffer * y_clone + x_clone * y_buffer;
        }
    }
    else if (ar < 0)
    {
        if (x == 0 && y == 0)
        {
            flag = false;
            cout << "\n----------Result----------";
            cout << "\n||| Denominator equal 0 |||";
            cout << "\nAlg: null";
            cout << "\n--------------------------";
        }
        else
        {
            double x_clone = x;
            double y_clone = y;
            for (int i = 1; i < abs(ar); i++)
            {
                double x_buffer = x;
                double y_buffer = y;
                x = x_buffer * x_clone - y_buffer * y_clone;
                y = x_buffer * y_clone + x_clone * y_buffer;
            }
            x = (1 * x_clone + 0 * y_clone) / (x_clone * x_clone + y_clone * y_clone);
            y = (x_clone * 0 - 1 * y_clone) / (x_clone * x_clone + y_clone * y_clone);
        }
    }

    if (flag)
    {
        after_point(x);
        after_point(y);

        alg = beauty_alg(x, y);

        cout << "\n----------Result----------";
        cout << "\nAlg: " << alg;
        cout << "\n--------------------------";
    }
}

// поиск n корней заданной степени
void degree_root(double mod, double arg, int ar, double x, double y)
{
    string alg;
    double arg_k;
    double x_local, y_local;

    cout << "***Number alg***\n";
    cout << "ReZ: ";
    cin >> x;
    cout << "ImZ: ";
    cin >> y;
    cout << "Root degree: ";
    cin >> ar;

    if (ar <= 0)
    {
        cout << "\n----------Result----------";
        cout << "\n||| Degree root can't be <= 0 |||";
        cout << "\nAlg: null";
        cout << "\n--------------------------";
    }
    else if (x == 0 && y == 0)
    {
        cout << "\n----------Result----------";
        cout << "\nAlg: 0";
        cout << "\n--------------------------";
    }
    else
    {
        mod = pow(x * x + y * y, 1 / (2 * (double)ar));
        arg = arg_func(x, y);
        after_point(mod);

        cout << "\n----------Result----------\n";
        for (int i = 0; i < ar; i++)
        {
            arg_k = (arg + 2 * i * PI) / ar;
            x_local = mod * cos(arg_k);
            y_local = mod * sin(arg_k);
            after_point(x_local);
            after_point(y_local);

            alg = beauty_alg(x_local, y_local);

            cout << "For k = " << i << ": " << alg << endl;
        }
        cout << "--------------------------";
    }
}

int main()
{
    double x1, y1, x2, y2, x, y; // координаты числа в форме x+iy
    int op, ar;                  // операция и степень
    double mod, arg;             // модуль и аргумент
    do
    {
        system("cls");
        cout << "/* ******************** Menu ******************** */\n";
        cout << "1) Calculate amount\n";
        cout << "2) Calculate product\n";
        cout << "3) Calculate difference\n";
        cout << "4) Calculate quotient\n";
        cout << "5) Translation from algebraic form\n";
        cout << "6) Translation from trigonometric form\n";
        cout << "7) Translation from exponential form\n";
        cout << "8) Exponentiation\n";
        cout << "9) Calculate N roots\n";
        cout << "10) Exit\n";
        cout << "\nOperation number (1-10): ";
        cin >> op;

        switch (op)
        {
        case 1:
            elem_ops(x1, y1, x2, y2, x, y, op);
            break;

        case 2:
            elem_ops(x1, y1, x2, y2, x, y, op);
            break;

        case 3:
            elem_ops(x1, y1, x2, y2, x, y, op);
            break;

        case 4:
            elem_ops(x1, y1, x2, y2, x, y, op);
            break;

        case 5:
            from_alg(mod, arg, x1, y1);
            break;

        case 6:
            from_trig(mod, arg);
            break;

        case 7:
            from_ex(mod, arg);
            break;

        case 8:
            degree(ar, x1, y1);
            break;

        case 9:
            degree_root(mod, arg, ar, x1, y1);
            break;

        default:
            break;
        }
        cout << '\n';
        if (op != 10)
            system("pause");
    } while (op != 10);
}