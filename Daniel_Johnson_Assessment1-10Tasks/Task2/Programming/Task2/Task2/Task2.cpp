#include <iostream>
using std::endl;
int main()
{
    std::string name;
    std::string ClanTag;
    std::string username;
    int age;
    //Varible dcleration

    std::cout << "What is your name?" << endl;
    std::cin >> name;

    std::cout << "Hello " << name << "!" << endl;


    std::cout << "What is your clan tag?" << endl;
    std::cin >> ClanTag;

    std::cout << "What is your username?" << endl;
    std::cin >> username;

    std::cout << "What is your age?" << endl;
    std::cin >> age;
    //asks the user for their input that is then assined to the varibles
    //This uses cin and cout, the standard c++ input output system

    while (!std::cin) //while there is an error with the input (in this case the most common issue would be that the input is not an int)
    {
            std::cin.clear();
            std::cin.ignore(123, '\n'); //Clears the input buffer
            std::cout << "Invalid input, please only use whole numbers" << endl;
            std::cin >> age;
    }
    //error checking loop


    std::cout << "Player details:\n"
        "- Name: " << name << endl <<
        "- Username: [" << ClanTag << "]" << username << endl <<
        "- Age: " << age << endl;
        
    //The output first prints a subheading "player details:" Then drops a line with \n and outputs the player name by outputting the text "- name: "
    //followed by the variable, outputting a variable like this will simply output the variable data. This repeats for each variable, I decided to use "endl" here as the line did not end on a text.


}

//-Daniel Johnson