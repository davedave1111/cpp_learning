#include <iostream>
#include <array>
/*
    @author David Bixler 
    This program is a doomsday calculator. No, this doesn't calculate the day when a giant space rock 
    slams into the earth, it uses the doomsday algorithm to calculate the day that any date falls on in history. 
*/

std::string promptInput();
std::array<int,3> parseDate(std::string input);
std::string calculateDay(std::array<int, 3> date);
bool verifyDate(std::array<int, 3> date);


int main()
{
    std::string usrInput = promptInput();

}


//This function is used to interact with the user and verify the input they give is 
//appropriate. 
std::string promptInput()
{
    std::string usrInput; //create a string to store the users input
    std::cout << "Enter a date for which you'd like to know the day it falls on. Must be in a MM/DD/YYYY Format \n Example: \"09/23/1922\" "; //request input
    std::cin >> usrInput; //gather user input 

    return usrInput;

}

//This function is used to check if the user entered a date in the proper format, and, if so,
//parse the month, day, and year, and check to make sure they are valid
//It first splits the month, date, and year by the slashes and then returns them in an array of ints 
std::array<int,3> parseDate(std::string input)
{
    std::string monthString = "" , dateString = "" , yearString = ""; //here are the substrings we will parse from our user input, all initalized to empty
    int monthInt, dateInt, yearInt; //here are the ints that we will parse from the substrings we gather from the user input

    int slashCount = 0; //this is the number of slashes counted in in the string, which should always be 3 after the for loop


    //This for loop iterates through the user input, to parse the date out into 3 different ints, the month, day, year
    for (int count = 0; count < input.length(); count++ ) 
    {
        if (input.at(count) == '/') //When the loop reaches a slash, it counts how many slashes it has, and iterated to the next char
        {
            slashCount++;
            count++;
        }

        switch(slashCount) //Checks which slash it has reached
        {
            case 0: //No slash reached yet, so we are reading the month
            monthString+=input.at(count);
            break;

            case 1: //Passed 1st slash, reading date
            dateString+=input.at(count);
            break;

            case 2: //passed 2nd slash, we are reading the year
            yearString+=input.at(count);
            break;
        }
    }
    
    std::array<int, 3> date; //declare the array we will use to return our 3 different ints 

    if(slashCount !=2)
    {
        return date;
    }
    else
    {
        monthInt = stoi(monthString); //parses an int from the month string
        dateInt = stoi(dateString); //parses an int from the date string
        yearInt = stoi(yearString); //parses an int from the year string

        std::array<int, 3> date; //declare the array we will use to return our 3 different ints 

        date[0] = monthInt;
        date[1] = dateInt;
        date[2] = yearInt;

        return date;
    }
}

//This function takes an array of ints 3 long, for teh date. It then verifies the date is valid, including proper leap year, no dates outside
//of a month, etc. If it is valid, it returns true, meaning the program may continue. Otherwise, it returns false so we know to reprompt the 
//user for a valid date. 
bool verifyDate(std::array<int, 3> date)
{

}

//This function contains the doomsday algorithm. It takesn array of 3 objects of type int. Once we have verified that the date entered is not
//only in the proper format but is actually a valid date (ei no february 31st, or crazy stuff) we pass the array of dates to actually calculate 
//the day. It then returns the day as a string to be printed to the console. 
std::string calculateDay(std::array<int, 3> date)
{

}