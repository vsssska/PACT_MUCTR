#include <iostream>
#include <cmath>

using namespace std;

const double PI = 3.141;
const double R = 8.314;
const double ALPHA = 1.1;
const double g = 9.81;

const double L = 37; // Длинна в метрах
const double d_outer = 25 * pow(10, -3); // Диаметр внутренний в метрах
const double delta = 2 * pow(10, -3); // Диаметр внешний в метрах
const double temperature = 40; // Температура в °C
const double m = 3.4 * 1000 / 3600; // Массовый расход жидкости кг/с
const double H = 11; // Высота подъема жидкости в метрах
const double d_0 = 12.24 * pow(10, -3); // Диаметр отверстия в метрах
const double r = 6; // Радиус закругления
const double degree = 90; // Угол закругления
const double count = 6; // Кол-во отводов
const double P2 = 2.2 * 98066.5; // Абсолютное давление
const double P_atm = 740 * 133.322; // Атмосферное давление

// Дихлорэтан, незначительная коррозия
const double e = 0.2 * pow(10, -3); // Абсолютная шероховатость
const double p = 1220.2; // Плотность
const double mu = 0.644 * pow(10, -3); // Вязкость

// Коэффициенты местных сопротивлений стр. 44
const double A = 1;
const double B = 0.09;
const double E_enter = 0.2; // Вход
const double E_diaphragm = 13.1; // Диафрагма
const double E_valve = 7.9; // Вентиль
const double E_exit = 0; // Выход

double get_v() {
    return m / p;
}

double get_d_eq() {
    return d_outer - 2 * delta;
}

double get_S() {
    return PI * pow(get_d_eq(), 2) / 4;
}

double get_velocity() {
    return get_v() / get_S();
}

double get_Re() {
    return get_velocity() * get_d_eq() * p / mu;
}

double get_E() {
    return e / get_d_eq();
}

double get_Darcy_factor() {
    return pow(2 * log10((get_E() / 3.7) + pow(6.81 / get_Re(), 0.9)), -2);
}

double get_m_diaphragm() {
    
    return pow(d_0 / get_d_eq(), 2); // Чтобы узнать кэф диафрагмы
}

double get_E_turn() {
    return A * B;
}

double get_E_sum() {
    return E_enter + E_diaphragm + get_E_turn() * count + E_valve + E_exit;
}

double get_delta_P_velocity() {
    return ALPHA * p * pow(get_velocity(), 2) / 2;
}

double get_delta_P_general() {
    return (ALPHA + get_Darcy_factor() * L / get_d_eq() + get_E_sum()) * p * pow(get_velocity(), 2) / 2;
}

double get_delta_P_H() {
    return p * g * H;
}

double get_delta_P1() {
    return P2 + get_delta_P_H() + get_delta_P_general();
}

double get_P1() {
    return P_atm + get_delta_P1();
}

int main() {
    cout << "1)" << endl;
    cout << "Velocity: " << get_velocity() << endl;
    cout << "Re: " << get_Re() << endl;
    cout << "Darcy: " << get_Darcy_factor() << endl << endl;

    cout << "2)" << endl;
    cout << "E diaphragm: " << E_diaphragm << endl;
    cout << "E sum: " << get_E_sum() << endl << endl;

    cout << "3)" << endl;
    cout << "Delta P_general: " << get_delta_P_general() << endl;
    cout << "Delta P_H: " << get_delta_P_H() << endl << endl;

    cout << "4)" << endl;
    cout << "Delta P1: " << get_delta_P1() << " Pa; " << get_delta_P1() * 0.00750062 << " mm; " << get_delta_P1() * 0.00001019716212978 << " at; " << endl;
    cout << "P1: " << get_P1() << " Pa; " << get_P1() * 0.00750062 << " mm; " << get_P1() * 0.00001019716212978 << " at; " << endl;

    cout << "dia: " << get_m_diaphragm() << endl;
    return 0;
}
