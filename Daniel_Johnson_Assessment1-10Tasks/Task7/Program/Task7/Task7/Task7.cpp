#include <iostream>
using std::endl;

const int arrayLength = 3; //Total length of array
char Characters[arrayLength][10] = { "Assault", "Tank", "Support" }; //Char array

struct PlayerDetails //Struct holding the players details
{
    std::string name;
    std::string character;
};

int main()
{
    struct PlayerDetails ID; //Defines the struct

    std::cout << "Select a character: " << endl;
    for (int i = 0; i < arrayLength; i++) //uses a for loop of the arrays length to output the array
    {
        std::cout << i + 1 << ": " << Characters[i] << endl;
    }

    int Selection; //Defines the user input
    std::cin >> Selection; //gets the users input

    while (Selection > arrayLength || Selection <= 0 || !std::cin) //error handling
    {
        std::cout << "Invalid choice, Please select a character" << endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');//Clears buffer
        std::cin >> Selection;
    }

    ID.character = Characters[Selection - 1]; //sets their charracter to the correct character in the array (-1 because arrays start at 0)
    std::cout << "You have selected: " << ID.character << endl; //Outputs their character
    std::cout << "Please enter your name" << endl; //asks for their name
    std::cin >> ID.name; //gets their name

    std::cout << "Player Details: \n -Name: " << ID.name << "\n -Class: " << ID.character << endl; //Outputs to the user
}
//-Daniel Johnson