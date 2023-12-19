#include <iostream>
using std::endl;
int main()
{
    while (true)
    {
        float Number; //User input
        float Answer; //Answer (Number squared)

        std::cout << "What number do you want to Square?" << endl; //Output question
        std::cin >> Number; //Input answer
        while (!std::cin)
        {
                std::cin.clear();
                std::cin.ignore(123, '\n'); //Clears the input buffer
                std::cout << "Invalid input, please only use numbers" << endl;
                std::cin >> Number;
        }

        //Answer = Number * Number; - While this techinally workd using the pow function is better practice
        Answer = pow(Number, 2); //Number to the power of 2 (Squared)
        std::cout << Number << " Squared is " << Answer << endl; //Outputs the answer to user

    }
}

