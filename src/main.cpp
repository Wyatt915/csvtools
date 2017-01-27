//#include "strtk.h"
#include "dataset.hpp"
#include "histogram.hpp"
#include "exprtk.hpp"

#include <algorithm>
#include <getopt.h>
#include <iostream>
#include <string>
#include <vector>

#include <stdlib.h> //rand
#include <time.h>


std::vector<double> rolldice(int dice, int trials){
    std::vector<double> v;

    srand(time(NULL));
    double sum = 0.0;
    for(int i = 0; i < trials; i++){
        for(int j = 0; j < dice; j++){
            sum += rand() % 6 + 1;
        }
        v.push_back(sum);
        sum = 0.0;
    }
    return v;
}

void test() {
    std::vector<double> v = rolldice(16, 1000000);
    dataset diceTrials(std::begin(v), std::end(v));
    double minimum = diceTrials.sigma(-3);
    double maximum = diceTrials.sigma(3);
    histogram test(diceTrials, minimum, maximum, 40);
    std::cout << "Mean: " << diceTrials.mean() << std::endl;
    std::cout << "Standard Deviation: " << diceTrials.stdev() << std::endl;
    test.printg(20);
}

void exprtest(){
    typedef double T;
    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T>     expression_t;
    typedef exprtk::parser<T>             parser_t;

    std::string expression_string = "e^p - p";
    T e = 2.718281828;
    T p = 3.141592653;

    symbol_table_t syms;
    syms.add_variable("e", e);
    syms.add_variable("p", p);

    expression_t expression;
    expression.register_symbol_table(syms);

    parser_t parser;

    if(!parser.compile(expression_string, expression)){
        printf("Something's donked.\n");
        return;
    }

    std::cout << "The expression (" << expression_string << ") evaluates to " << expression.value() << std::endl;
}

int main(int argc, char const *argv[]) {
    exprtest();
    return 0;
}

// int main(int argc, char* argv[]){
//     static struct option long_options[] = {
//         {"column",          required_argument,  0, 'c'},
//         {"delimeters",      required_argument,  0, 'd'},
//         {"expression",      required_argument,  0, 'e'},
//         {"floating-point",  no_argument,        0, 'F'},
//         {"help",            no_argument,        0, 'h'},
//         {"input-file",      required_argument,  0, 'i'},
//         {"integer",         no_argument,        0, 'I'},
//         {"output-file",     required_argument,  0, 'o'},
//         {"range",           required_argument,  0, 'r'},
//         {"test",            optional_argument,  0, 't'},
//         {0, 0, 0, 0}
//     };
//     char c;
//
//     bool floatFlag =        false;
//     bool integerFlag =      false;
//     bool outputFileFlag =   false; //set to true if the -o option is encountered.
//     bool inputFileFlag =    false;
//
//     int column = -1; //column which will be operated on
//     std::string delimeters;
//     std::string outputFileName;
//     std::string range;
//     std::string expression;
//
//     std::vector<std::string> input_data;
//
//     while ( (c = getopt_long(argc, argv, "d:hi:o:s:t", long_options, NULL)) != -1 ) {
//         int this_option_optind = optind ? optind : 1;
//         switch (c) {
//             case 'd':
//                 delimeters = std::string(optarg);
//                 break;
//             case 'e':
//                 expression = std::string(optarg);
//                 break;
//             case 'F':
//                 floatFlag = true;
//                 break;
//             case 'h':
//                 std::cout << "PLACEHOLDER HELP TEXT" << std::endl;
//                 return 0;
//             case 'i':
//                 inputFileFlag = true;
//                 read(std::string(optarg), input_data);
//                 break;
//             case 'I':
//                 integerFlag = true;
//                 break;
//             case 'o':
//                 outputFileName = std::string(optarg);
//                 outputFileFlag = true;
//                 break;
//             case 's':
//                 read(std::string(optarg), searchTerms);
//                 break;
//             case 't':
//                 test();
//                 break;
//             case ':':   /* missing option argument */
//                 fprintf(stderr, "%s: option `-%c' requires an argument\n",
//                 argv[0], optopt);
//                 return 1;
//             case '?':    /* invalid option */
//                 fprintf(stderr, "%s: option `-%c' is invalid: ignored\n",
//                 argv[0], optopt);
//                 return 2;
//             default:
//                 std::cerr << "Invalid argument." << std::endl;
//                 return 3;
//         }
//     }
//     return 0;
// }
