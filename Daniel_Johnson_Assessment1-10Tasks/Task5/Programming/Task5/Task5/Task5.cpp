#include <iostream>
#include <string> //Allows the use of strings
using std::endl;
int main()
{
    while (true) //Full program loop
    {

        std::string userInput;
        std::string lower;
        std::string upper;
        std::string sentence;
        

        bool space = false; //Is a space
        bool end = false; //End of sentence?
        bool Alphabet = false; //Is in the alphabet

        int length;
        //Varible decleration

        std::cout << "Enter text: ";
        std:getline(std::cin, userInput); //Using getline instead of cin as cin dosent ignores everyting after a space


        length = userInput.size(); //Length of the user input



        for (int i = 0; i < length; i++)
        {
            if (isalpha(userInput[i])) //Checks that what the user has inputted is in the alphabet
            {
                Alphabet = true;
            }
            if (userInput[i] == '.') //If the currently selected char is a full stop it will set the end bool to true
            {
                end = true;
            }
            if (isspace(userInput[i])) //If the currently selected char is a space 
            {
                lower = lower + " ";
                upper = upper + " ";
                space = true; //Add a space to each varible and set space to true
            }
            if (i == 0 || (space == true && end == true))//If it is the first char in the input, or it is the first letter after a full stop
            {
                sentence = sentence + char(toupper(userInput[i])); //Then make upper case
            }
            else
            {
                sentence = sentence + char(tolower(userInput[i])); //Make lower case

            }
            if (isspace(userInput[i]) == false) //If the char is not a space
            {
                space = false;
                lower = lower + char(tolower(userInput[i]));
                upper = upper + char(toupper(userInput[i])); //space is false and the varibles continue to increment
            }
            if (isspace(userInput[i]) == false && userInput[i] == '.' == false) //If the varible isnt a space and isnt a full stop then it is no longer the end of a sentence
            {
                end = false;
            }
        }

        if (Alphabet == false) //If there is not alphabetical chars found
        {
            std::cout << "Warning no alphabetical characters detected" << endl;
        }
        else
        {
            std::cout << "lower - " << lower << endl;
            std::cout << "Upper - " << upper << endl;
            std::cout << "Sentence - " << sentence << endl;
            //outputs to the user
        }
    }
}

// - Daniel Johnson
