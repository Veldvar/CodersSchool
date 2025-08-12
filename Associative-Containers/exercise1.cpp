#include<vector>
#include<iostream>
#include<algorithm>
#include<numeric>
#include<cmath>

// Implement an ArithmeticAverage() function, which takes 2 vectors - const std::vector<int>& first, const std::vector<int>& second and calculates an arithemetic average of all values.

// Input: {1, 2, 3, 4} {1, 2, 3, 4} Output: 2.5

// Implement a Distance() function, which takes 2 vectors const std::vector<int>& first, const std::vector<int>& second and calculates the distance between 2 points in n-dimentional space.

// Input: {7, 4, 3} {17, 6, 2} Output: 10.247

void mesos(const std::vector<int> &x,const std::vector<int> &y){

auto const i = accumulate(x.begin(),x.end(),0);
auto const j = accumulate(y.begin(),y.end(),0);
auto const sum = x.size()+y.size(); // All elements 
double average = static_cast<double>(i+j)/sum;
std::cout<<average<<'\n';
}


void distance (const std::vector<int> &x,const std::vector<int> &y){

    const double i = std::inner_product(x.begin(),x.end(),y.begin(),0,std::plus<int>(),[](int a, int b){

        double diff=static_cast<double> (a-b);

        return diff*diff;
        }
        
    );
        double distance=std::sqrt(i);
        
        std::cout<<distance<<'\n';

} 




int main(){

    const std::vector <int>v1 {7,4,3};
    const std::vector <int>v2 {17,6,2};

    mesos(v1,v2);

    distance(v1,v2);
    

}