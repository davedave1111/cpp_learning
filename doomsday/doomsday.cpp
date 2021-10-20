#include <iostream>
#include <array>
/*
    @author David Bixler 
    This program is a doomsday calculator. No, this doesn't calculate the day when a giant space rock 
    slams into the earth, it uses the doomsday algorithm to calculate the day that any date falls on in history. 
*/

std::string promptInput();
std::array<int,3> parseDate(std::string input);
int calculateDoomsday(int year);
bool verifyDate(int month, int date, int year);
bool isLeapYear(int year);
int calculateDay(int doomsday, int month, int date, int year);


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
            std::cout << calculateDay(calculateDoomsday(year), month, date, year) << std::endl; 
        }

        else //else, we tell them the date they entered wasn't valid
        {
            std::cout << "Date invalid" << std::endl;
        }
    }

}


//This function is used to interact with the user to get their date input
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

        std::array<int, 3> date; //declare the array we will use to return our 3 different ints 

        //add month, day, and year to our array
        date[0] = monthInt; 
        date[1] = dateInt;
        date[2] = yearInt;

        return date; //return our array to verify the date in the main function  
    }
}


//This function takes an array of ints 3 long, for the date. It then verifies the date is valid, including proper leap year, no dates outside
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
int calculateDoomsday(int year)
{
    //first portion of the algorithm (atleast the way I'm implementing it here) is to determine the day of the week the doomsdays will be for 
    //the given year. This goes by century, and we can find it using some simple math. WE find the remainder (mod) of the year by 400, as our calendar repeats 
    //every 400 years. There are 4 days the doomsdays of a given year will fall on, Sunday, Tuesday, Wednesday or Friday. Days of the week are represented as 
    //integers 0-6, with 0 starting on Sunday, 1 being Monday, and so on. 

    //Find the remainder of the year mod 400
    int remainder = year%400;

    //this is the "code", we will use this to calculate the doomsdays for any given year, by determining the doomsday the first year of the century
    int centuryCode;

    if(remainder >= 0 && remainder <= 99)
    {
        centuryCode = 2; 
    }
    
    else if(remainder >= 100 && remainder <= 199)
    {
        centuryCode = 0; 
    }

    else if(remainder >= 200 && remainder <= 299)
    {
        centuryCode = 5; 
    }
    
        else if(remainder >= 300 && remainder <= 399)
    {
        centuryCode = 3; 
    }


    //Next, we need to know which year in the century we are dealing with. First, we find the century, then subract it
    //from the year to find which year in the century we are in (from 0-99, ie if the century is 2000, 2000-2099)

    int yearTensPlace = year - ((year/100)*100);

    //find how many times 12 goes into the year
    int quotientYear = yearTensPlace/12;

    //find the remainder of 12 going into the year
    int remainderYear = yearTensPlace%12;

    //find how many times 4 goes into the year remainder 
    int remainder2 = remainderYear%4;

    //Next, we can calculate the doomsday in the given year using the numbers we've calculated, adding them, then 
    //finding the remainder when divided by 7. This remainder is the day code. This is the day all doomsdays in the given
    //year will be on. (So if the doomsday code is 0, then all the doomsdays in a year will be on a sunday.)

    int doomsday = (centuryCode+quotientYear+remainderYear+remainder2)%7;

    //return the doomsday day code
    return doomsday;
    
}

//This function takes three ints, the doomsday in the year that we calculated, the month and date of of which we are trying to determine 
//the day of the week of. Using the month, it determines what doomsday we need to base our calculations off of. Each month has a doomsday, and each doomsday is the same for that year.
//the doomsdays fall on the following dates by month 1/3 (or 1/4 on leap year), 2/28 (or 2/29 on leap year), 3/14, 4/4, 5/9, 6/6, 7/11, 8/8, 9/5, 10/10, 11/7, 12/12. All of these dates fall on 
// the same doomsday, which we have already calculated 
int calculateDay(int doomsday, int month, int date, int year)
{
    //we determine if the year we are in is a leap year, as that changes our doomsday dates for january and february 
    bool yearIsLeap = isLeapYear(year);
    //this is the int that we will use to store the date of our doomsday in the month, so we can do some math to figure out what day out input date is on
    int doomsdayDate;
    //this switch uses the month to determine that date we need to work off of to calculate our day of the week;
    switch(month)
    {
        case 1:
            if(yearIsLeap)
            {
                doomsdayDate = 4;
            }
            else 
            {
                doomsdayDate = 3;
            }
            break;
        
        case 2:
            if(yearIsLeap)
            {
                doomsdayDate = 29;
            }
            else 
            {
                doomsdayDate = 28;
            }
            break; 
        
        case 3:
            doomsdayDate = 14;
            break;

        case 4:
            doomsdayDate = 4;
            break;

        case 5:
            doomsdayDate = 9;
            break;
        
        case 6:
            doomsdayDate = 6;
            break;
        
        case 7:
            doomsdayDate = 11;
            break;
        
        case 8:
            doomsdayDate = 8;
            break;
        
        case 9:
            doomsdayDate = 5;
            break;
        
        case 10:
            doomsdayDate = 10;
            break;
        
        case 11:
            doomsdayDate = 7;
            break; 
        
        case 12:
            doomsdayDate = 12;
            break;

    }

    //Now we know the date of a day in the same month as the date we are given, so it just a simple calculation of 
    //finding how far our given date is from the doomsday in that month, then calculating the day

    int day = ((date-doomsdayDate)+doomsday) % 7;
    return day;

}

//This function is pretty straight forward. It takes an int, year, and returns a boolean. If the year is a leap year, it returns true. Otherwise, false
bool isLeapYear(int year)
{
    if(year%4 == 0) //if it is divisable by 4, it might be a leap year
    { 
        if(year%100 == 0) // if divisable by 4 and by 100, it also must be divisable by 400 to be a leap year       
        {
            if(year%400 == 0) // if divisable by 4, 100, and 400, it is a leap year
            {
                return true;
            }
            else //if divisable by 4 and 100, but not 400, its not a leap year
            {
                return false;
            }
        }
        else // if its divisable by 4, but not 100, its a leap year
        {
            return true;
        }
    }
    else //if not divisable by 4, its not a leap year
    {
        return false;
    }

}
