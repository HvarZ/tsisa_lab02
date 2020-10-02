#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <typeinfo>
#include <algorithm>
#include <iostream>

using std::cout;
using std::endl;


// Функция заполнения вектора от начала отрезка до конца (от left_edge до right_edge) с разностью difference
void vectorFill (std::vector<double>& vec, double left_edge, double right_edge, double difference){
    if (right_edge <= left_edge) throw std::logic_error("Left edge > right edge");
    if (right_edge - left_edge < difference) throw std::logic_error("The difference is too large");
    for (double i = left_edge; i < right_edge + difference; i += difference){
        vec.push_back(i);
    }
}

//Фунция нахождения количества расчетов от P и q
int Number_of_Tests (double P, double q){
    return static_cast<int>(log(1 - P) / log(1 - q));
}

//Функция для дальнейшего заполнения вектора векторов
template <typename type>
std::vector<type> MultipleN (const std::vector<double>& P,const double q){
    std::vector<type> values;
    for (size_t i = 0; i < P.size(); i++){
        values.push_back(Number_of_Tests(P[i], q));
    }
    return values;
}

//Мультимодальная функция по варианту (15)
double f(double x) {
    return pow(x, 2) * sin(x);
}
//Мультимодальная функция по варианту (15)
double f_m (double x) {
    return f(x) * sin(5*x);
}

//Фунция расчета случайный числел на любом отрезке
double Random (double left_edge, double right_edge){
    return (right_edge - left_edge) * static_cast<double>(rand()) / static_cast<double>(RAND_MAX) + left_edge;
}

//Функция заполнения вектора векторов количеством расчетов N
template <typename type>
std::vector<std::vector<type>> MultipleTests (const std::vector<double>& P, const std::vector<double>& q) {
    std::vector<std::vector<type>> tests;
    for (size_t i = 0; i < q.size(); i++){
        tests.push_back(MultipleN<type>(P, q[i]));
    }
    return tests;
}

//Фунция заполнения вектора векторов минимальными значениями
template <typename type>
std::vector<std::vector<double>> MultipleMin (const std::vector<std::vector<type>>& tests, double left_edge, double right_edge, double f(double x)){
    std::vector<double> values;
    std::vector<std::vector<double>> testsDouble;
    double min_element = 0;
    if (typeid(tests[0][0]) ==  typeid(int) or typeid(tests[0][0]) == typeid(double)){
        testsDouble.resize(tests.size());
        for (size_t i = 0; i < tests.size(); i++){
            for (size_t j = 0; j < tests[i].size(); j++) {
                testsDouble[i].push_back(static_cast<double>(tests[i][j]));
            }
        }
    }
    else throw std::invalid_argument("Unknown type");

    for (size_t i = 0; i < tests.size(); i++){
        for (size_t j = 0; j < tests[i].size(); j++){
            for (size_t k = 0; k < tests[i][j]; k ++){
                values.push_back(f(Random(left_edge,right_edge)));
            }
            min_element = *std::min_element(values.begin(), values.end());
            testsDouble[i][j] = min_element;
            values.clear();
        }
    }
    return testsDouble;
}

// Функия вывода на экран таблицы со всеми расчетами
template <typename type, typename type2>
std::stringstream PrintMultipleTests (const std::vector<std::vector<type2>>& tests, const std::vector<type>& P,
                                      const std::vector<type>& q){
    std::stringstream out;
    int length = 0;
    if (typeid(tests[0][0]) == typeid(int)){
        length = 6;

        out << std::string(78, '-') << endl;
        out << "|" << "q\\P" << std::setw(4) << "|";
        for (size_t i = 0; i < P.size(); i++){
            out << std::setw(length)  <<std::left << P[i] << "|";
        }
        out << endl << std::string(78, '-') << endl;

        for (size_t i = 0; i < q.size(); i++){
            out << "|"<< std::setw(length) << std::left << q[i] << "|" ;
            for (size_t j = 0 ; j < P.size(); j++){
                out << std::setw(length) << std::left << tests[i][j]  << "|";
            }
            out << endl;
        }
        out << std::string(78, '-') << endl;
    }
    else if (typeid(tests[0][0]) == typeid(double)){
        length = 11;
        out << std::string(133, '-') << endl;
        out << "|" << "q\\P" << std::setw(length - 2) << "|";
        for (size_t i = 0; i < P.size(); i++){
            out << std::setw(length) << std::left << P[i] << "|";
        }
        out << endl << std::string(133, '-') << endl;

        for (size_t i = 0; i < q.size(); i++){
            out << "|"<< std::setw(length) << std::left << q[i] << "|" ;
            for (size_t j = 0 ; j < P.size(); j++){
                out << std::setw(length) << std::left << std::setprecision(8) << tests[i][j]  << "|";
            }
            out << endl;
        }
        out << std::string(133, '-') << endl;
    }
    else throw std::invalid_argument("Unknown type");

    return out;
}
