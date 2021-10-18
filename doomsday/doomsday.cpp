#include <iostream>
#include <array>
/*
    @author David Bixler 
    This program is a doomsday calculator. No, this doesn't calculate the day when a giant space rock 
    slams into the earth, it uses the doomsday algorithm to calculate the day that any date falls on in history. 
*/

std::string promptInput();
std::array<int,3> parseDate(std::string input);
std::string calculateDay(int month, int date, int year);
bool verifyDate(int month, int date, int year);
bool isLeapYear(int year);


int main()
{
    //These ints will be used once we've asked the user for a date, parsed and verfied it in order to do the doomsday algorithm calculation
    int month; //create month int 
    int date; //create date int
    int year; // create year int

    std::string usrInput = promptInput(); //prompt the user for the date, which returns a string we store in usrInput
    std::array<int, 3> dateArray = parseDate(usrInput); //we parse the 3 different ints from month, date, and year from the usrInput, which gets returned as an array

    if(dateArray.empty()) //if the array is empty, then the user input was an invalid format
    {
        std::cout << "Invalid Input, please try again!" << std::endl;
    }

    else //otherwise, we know they entered a valid date format, and we check to make sure the date date itself makes sense 
    {
        month = dateArray[0]; //grab month int from the array
        date = dateArray[1]; //grab date int from the array
        year = dateArray[2]; //grab year int from the array
        
        bool dateValid = verifyDate(month, date, year); //create a variable that will store the results of our date verification, call the verifyDate method passing in the date values

        if(dateValid) //this is for testing purposes ATM, if its valid, we print that it is and print the date back to them. This shows the parsing and verifaction process worked
        {
            std::cout << "Valid day:   " + std::to_string(month) + "/" + std::to_string(date) + "/" + std::to_string(year) << std::endl; 
        }

        else //else, we tell them the date they entered wasn't valid
        {
            std::cout << "Date invalid" << std::endl;
        }
    }

}


//This function is used to interact with the user and verify the input they give is 
//appropriate. 
std::string promptInput()
{
    std::string usrInput; //create a string to store the users input
    std::cout << "Enter a date for which you'd like to know the day it falls on. Must be in a MM/DD/YYYY Format \n Example: \"09/23/1922\" " <<std::endl; //request input
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


    //This if statement checks to make sure we encountered 2 slashes in our entered date
    if(slashCount !=2)//If not, we know we didn't get valid input, so we return the array empty, so we know to tell the user they didn't give valid input 
    {
        return date;
    }
    else //otherwise, we assume they entered a valid date, add all of the dates to the array, and return the array.
    {
        monthInt = stoi(monthString); //parses an int from the month string
        dateInt = stoi(dateString); //parses an int from the date string
        yearInt = stoi(yearString); //parses an int from the year string

        std::array<int, 3> date; //declare the array we will use to return our 3 different ints \

        //add month, day, and year to our array
        date[0] = monthInt; 
        date[1] = dateInt;
        date[2] = yearInt;

        return date; //return our array to verify the date in the main function  
    }
}


//This function takes an array of ints 3 long, for teh date. It then verifies the date is valid, including proper leap year, no dates outside
//of a month, etc. If it is valid, it returns true, meaning the program may continue. Otherwise, it returns false so we know to reprompt the 
//user for a valid date. 
bool verifyDate(int monthInt, int dateInt, int yearInt)
{
    int month = monthInt;
    int date = dateInt;
    int year = yearInt;

    //checking to make sure we don't have a month before january or after december 
    if(month > 12 && month <= 0)
    {
        return false;
    }
    else //if it is a valid month, we now move on to make sure the day is valid 
    {
        //Now we check to make sure the entered date entered is greater then 0. If not, we return false, if so we move on
        if(date <= 0)
        {
            return false;
        }

        //we now need to have verification for each individual months, as they have different lengths
        else
        {
            //First we check for the months that are 31 days, that being Jan, Mar, May, July, Aug, Oct, Dec
            if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && date <= 31)
            {
                return true;
            }

            //Next, we check if it is a month that has 30 days, that being April, June, Sep, Nov
            if((month == 4 || month == 6 || month == 9 || month == 11) && date <= 30)
            {
                return true;
            }
            
            //If the month is february, we need to account for leap year to determine if it should be 28 days or 29 days
            else if(month == 2)
            {
                //this statement checks for a leap year
                if(isLeapYear(year) && date <= 29)
                {
                    return true;
                }
                
                //non leap year
                if (date <= 28)
                {
                    return true;
                }

            }

            //Otherwise, we don't meet any of the proper conditions, so we return false
            else
            {
                return false; 
            }


        }

    }

}


//This function contains the doomsday algorithm. It takesn array of 3 objects of type int. Once we have verified that the date entered is not
//only in the proper format but is actually a valid date (ei no february 31st, or crazy stuff) we pass the array of dates to actually calculate 
//the day. It then returns the day as a string to be printed to the console. 
std::string calculateDay(int month, int date, int year)
{

}

//This function is pretty straight forward. It takes an int, year, and returns a boolean. If the year is a leap year, it returns true. Otherwise, false
bool isLeapYear(int year)
{
    if(year%4 == 0)
    { 
        if(year%100 == 0)
        {
            if(year%400 == 0)
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }

}
