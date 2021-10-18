#include <iostream>
 /*

 This is project 1 of the C++ course I'm currently taking on udemy 
 @author David Bixler
 */
 int main()
 {
     std::string usrCountry = "";

     std::cout << "Where do you live?" << std::endl;
     std::cin >> usrCountry;
     std::cout << "I've heard great things about " + usrCountry + ". I'd like to go sometime." << std::endl;

     return 0;



 }