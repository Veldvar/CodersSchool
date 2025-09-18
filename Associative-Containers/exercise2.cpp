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
    FactorialFromUnsigned,
    None
};

bool BadFormat (const std::string &input_)
{
    if (input_[0] == '+' && '/' && '*' && '%'){return true;}
    return false;
}

bool DivideByZero (const std::string &input_)
{
   std::stringstream input_stream(input_);
   double x,y;
   char op;
   if(!(input_stream>>x)){return false;}
   if(!(input_stream>>op)){return false;}
   if(!(input_stream>>y)){return false;}

   return (op ==  '/' && y ==0.0);
}

ErrorCode process(std::string input, double *out)
{

    std::map<char, std::function<double(double, double)>> core = {
        {'+', [](double a, double b){ return a + b; }},
        {'-', [](double a, double b){ return a - b; }},
        {'/', [](double a, double b){ return a / b; }},
        {'*', [](double a, double b){ return a * b; }},
        {'%', [](double a, double b){ return static_cast<int>(a) % static_cast<int>(b); }},
        {'^', [](double a, double b){ return std::pow(a, b); }},
        {'$', [](double a, double b){return pow(a,1 / b);}},
        {'!', [](double a, double b)
            {   
                double factorial;
                for(int i = 2;i<static_cast<int>(a);++i){
                    factorial*=i;
                }
                return factorial;
            }
        }
    };

    std::stringstream input_stream(input);
    double x;
    input_stream >> x;
    char op;
    input_stream >> op;
    double y;
    input_stream >> y;
    //check if input is divided by zero
    if (DivideByZero(input)) {return ErrorCode::DivideBy0;}
    //check if input has bad format
    if (BadFormat(input)) {return ErrorCode::BadFormat;}
    //check if radicand is unsigned
    if (op == '$' && x<0){return ErrorCode::SqrtOfNegativeNumber;}
    //check if factorial is unsigned
    if (op == '!' && x<0){return ErrorCode::FactorialFromUnsigned;}
    
    *out = core[op](x, y);

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
        assert(std::fabs(out -10.0 )<0.001);
    }

    //Test #2
    {
        // given
        double out;
        ErrorCode error_code;
        std::string input{"5 ^ 2"};
        // when
        error_code = process(input, &out);
        // then
        assert(error_code == ErrorCode::Ok);
        assert(std::fabs(out -25.0 )<0.001);
    }

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
        error_code = process(input,&out);
        // then
        assert(error_code == ErrorCode::DivideBy0);
    }
    
    //Test #5
    {
        //given
        double out;
        std::string input{"-5 $ 5"};
        ErrorCode error_code;
        //when
        error_code = process(input,&out);
        //then
        assert(error_code == ErrorCode::SqrtOfNegativeNumber);

    }

    //Test #6
    {    //given
        double out;
        std::string input {"-5!"};
        ErrorCode error_code;
        //when
        error_code = process(input,&out);
        //then
        assert(error_code == ErrorCode::FactorialFromUnsigned);
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