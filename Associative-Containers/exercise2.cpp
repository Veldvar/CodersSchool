#include <map>
#include <iostream>
#include <numeric>
#include <cmath>
#include <functional>
#include <cassert>
#include <iomanip>
enum class ErrorCode
{
    Ok,
    BadCharacter,
    BadFormat,
    DivideBy0,
    SqrtOfNegativeNumber,
    ModuleOfNonIntegerValue,
    None
};
bool BadFormat (const std::string &input_)
{
    if (input_[0] == '+' && '/' && '*' && '%'){return true;}
    return false;
}


bool DivideByZero (const std::string &input_)
{
    for(size_t i = 0;i<input_.size();i++)
        {
            // std::cout<<input_[i];
            if (input_[i] == '/' && input_[i+2] == '0'){return true;}
        }   
        return false;
}
ErrorCode process(std::string input, double *out)
{

    std::map<char, std::function<double(double, double)>> core = {
        {'+', [](double a, double b)
         { return a + b; }},
        {'-', [](double a, double b)
         { return a - b; }},
        {'/', [](double a, double b)
         { return a / b; }},
        {'*', [](double a, double b)
         { return a * b; }},
        {'%', [](double a, double b)
         { return static_cast<int>(a) % static_cast<int>(b); }},
        // {"!",[](int a, int b){return ;}},
        {'^', [](double a, double b)
         { return std::pow(a, b); }}};
    std::stringstream streaminput(input);
    double x;
    streaminput >> x;
    // std::cout << x << std::endl;
    char op;
    streaminput >> op;
    // std::cout << op << std::endl;
    double y;
    streaminput >> y;
    //check if integer is divided by zero
    if (DivideByZero(input)) {return ErrorCode::DivideBy0;}
    //check if input has bad format
    if (BadFormat(input)) {return ErrorCode::BadFormat;}
    // std::cout << y << std::endl;
    *out = core[op](x, y);
    // *out =10.0; //sztuczna
    return ErrorCode::Ok;
}
void run_tests()
{
    std::cout << "Run tests\n";

    //Test #1
    {
        // given
        double out;
        ErrorCode error_code;
        std::string input{"5 + 5"};
        // when
        error_code = process(input, &out);
        // then
        assert(error_code == ErrorCode::Ok);
        std::cout<<'\n'<<std::setprecision(15)<<out<<std::endl;
        assert(std::fabs(out -10.0 )<0.001);
    }

    // //Test #2
    // {
    //     // given
    //     double out;
    //     ErrorCode error_code;
    //     std::string input{"5 ^ 2"};
    //     // when
    //     error_code = process(input, &out);
    //     // then
    //     assert(error_code == ErrorCode::Ok);
    //     assert(std::fabs(out -25.0 )<0.001);
    // }

    // Test #3
    {
        // given
        double out;
        ErrorCode error_code;
        std::string input{"+ 5 4"};
        // when
        error_code = process(input, &out);
        // then
        assert(error_code == ErrorCode::BadFormat);
    }
    // Test #4
    {
        // given
        double out;
        ErrorCode error_code;
        std::string input {"6 / 0"};
        // when
        error_code=process(input,&out);
        // then
        assert(error_code == ErrorCode::DivideBy0);
    }

    std::cout << "Tests passed\n";
}

// void run_application(){
//     double x,y;
//     char op;

//         while(true){
//         std::cout <<"Please insert numbers:";

//         // std::cout <<"\n";

//         std::cin>> x>> op>> y;

//         // IsBadCharacter(op);

//         }
// }

int main()
{
    run_tests();
    // run_application();
}