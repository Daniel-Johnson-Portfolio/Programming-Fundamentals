#include <iostream>
using std::endl;
int main()
{
    while (true) //Full program loop
    {
        std::string TopBottomLine; //The top and bottom line are always going to be the same
        std::string MiddleLine = "*"; //The middle line will alwyas start with an * and end with one
        std::string UserInput; //User input

        int length; //Length of the middle line is used to define the legnth of the top and bottom line

        std::cout << "Enter text: ";
        std::cin >> UserInput; //Output/Input

        MiddleLine = MiddleLine + UserInput + "*"; //Set the middle line to = *USERINPUT*
        length = MiddleLine.length(); //Gets the length of the middle line

        for (int i = 0; i < length; i++) //For loop for the size of the legnth
        {
            TopBottomLine = TopBottomLine + "*"; //Set the top and bottom line to the correct amout of *
        }

        std::cout << TopBottomLine << endl;
        std::cout << MiddleLine << endl;
        std::cout << TopBottomLine << endl;
        //Outputs all the lines

    }

}
//-Daniel Johnson


