#include <iostream>
 
 int main()
 {
     std::string usrCountry = "";

     std::cout << "Where do you live?" << std::endl;
     std::cin >> usrCountry;
     std::cout << "I've heard great things about " + usrCountry + ". I'd like to go sometime." << std::endl;

     return 0;



 }