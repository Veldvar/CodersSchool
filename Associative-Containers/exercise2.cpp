#include<map>
#include<iostream>
#include<numeric>
#include<cmath>
#include<functional>

enum class ErrorCode{
    
    Ok,
    BadCharacter,
    BadFormat,
    DivideBy0,
    SqrtOfNegativeNumber,
    ModuleOfNonIntegerValue };

    

int main(){

    std::map<char, std::function<double(double,double)>> core ={
        {'+',[](double a, double b){return a+b;}},
        {'-',[](double a, double b){return a-b;}},
        {'/',[](double a, double b){return a/b;}},
        {'*',[](double a, double b){return a*b;}},
        {'%',[](double a, double b){return static_cast<int>(a) % static_cast<int>(b);}},
        // {"!",[](int a, int b){return a!b;}},
        {'^',[](double a, double b){return std::pow(a,b);}}
        };

        double x,y;
        char op;

        while(true){
        std::cout <<"Please insert numbers\n";
        std::cin>> x>> op>> y;
       
        std::cout <<"Please insert numbers:" << core[op](x,y)<<'\n';
        
        
        }
}