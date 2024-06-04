#include <string>
#include <exprtk.hpp>
#include <iostream>
#include <typeinfo>
#include <QVector>
#include <QDebug>
#include "../../devices/base/command.hpp"

int main()
{
    setlocale(LC_ALL, "Russian");
    
    std::string str_expression = "5 * t * pi";

    exprtk::expression<double> expression;

    exprtk::symbol_table<double> symbol_table;

    QVector<double> args;
    args.push_back(100);
    args.push_back(200);
    args.push_back(300);

    QVector<double> args1(3);
    args1 = args;
    qDebug() << args1[0] << " " << args1[1] << " " << args1[2];

    symbol_table.add_variable("t", args.front());
    symbol_table.add_constants();

    expression.register_symbol_table(symbol_table);
    exprtk::parser<double> parser;
    parser.compile(str_expression, expression);

    auto a = expression.value();
    std::cout << a << std::endl;

    Command * cmd = new Command("Интервал", 0x01, {8}, 4);
    //cmd->setArgumentName(0,"t");
    //cmd->setTransformFunction(0,"5 * t * pi");
    //cmd->setArguments({100});
    QByteArray ba = cmd->buildCommand({100});
    std::cout << ba.toHex().toStdString() << '\n';
    return 0;
}

// template <typename T>
// void trig_function()
// {
//    typedef exprtk::symbol_table<T> symbol_table_t;
//    typedef exprtk::expression<T>   expression_t;
//    typedef exprtk::parser<T>       parser_t;

//    const std::string expression_string =
//                      "clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";

//    T x;

//    symbol_table_t symbol_table;
//    symbol_table.add_variable("x",x);
//    symbol_table.add_constants();

//    expression_t expression;
//    expression.register_symbol_table(symbol_table);

//    parser_t parser;
//    parser.compile(expression_string,expression);

//    for (x = T(-5); x <= T(+5); x += T(0.001))
//    {
//       const T y = expression.value();
//       printf("%19.15f\t%19.15f\n", x, y);
//    }
// }

// int main()
// {
//    trig_function<double>();
//    return 0;
// }