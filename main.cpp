#include "RandomSearch.h"

const double LEFT_EDGE_P = 0.9;
const double RIGHT_EDGE_P = 0.99;
const double LEFT_EDGE_q = 0.005;
const double RIGHT_EDGE_q = 0.1;

int main() {
    std::vector <double> P (0);
    std::vector <double> q (0);
    vectorFill(P, LEFT_EDGE_P, RIGHT_EDGE_P, 0.01);
    vectorFill(q, LEFT_EDGE_q, RIGHT_EDGE_q, 0.005);

    std::vector<std::vector<int>> values = MultipleTests<int>(P, q);
    std::stringstream out = PrintMultipleTests(values, P, q);
    cout << "Вывод таблицы зависимости N от p и q" << endl;
    cout << out.str() << endl;
    std::vector<std::vector<double>> val = MultipleMin(values, 9, 12 , f);
    out = PrintMultipleTests(val, P, q);

    cout << "Вывод таблицы для унимодальной фунции " << endl;
    cout << out.str() << endl;

    std::vector<std::vector<double>> multiple_function_tests = MultipleMin(values, 9, 12 , f_m);
    out = PrintMultipleTests(multiple_function_tests, P, q);

    cout << "Вывод таблицы для мультимодальной фунции" << endl;
    cout << out.str() << endl;
    return 0;
}
