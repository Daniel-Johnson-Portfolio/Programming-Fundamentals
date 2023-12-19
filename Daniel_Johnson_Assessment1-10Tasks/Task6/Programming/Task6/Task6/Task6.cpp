#include <iostream>
using std::endl;

int main()
{
	srand(time(NULL)); //This "seeds" the random number, this ensures everytime the program is run it is a new random number
	int number = rand() & 100; //Random number between 0 and 100

	int guess; //The users guess
	int guesses = 1; //The amount of guesses

	std::cout << "Enter a guess between 0 and 100" << endl;
	std::cin >> guess; //Output/Input

	do //A do while, will run once without condition and then again if condition is met
	{
		while (!std::cin || guess > 100 || guess < 0) //error hanbdling
		{
			std::cin.clear();
			std::cin.ignore(123, '\n'); //Clears buffer

			std::cout << "Invalid input, Please guess again" << endl;
			std::cin >> guess;
		}
	

		int difference = guess - number; //The diffrence between the answer and the guess
		guesses++; //Increment the amount of guesses by one

		if (guess == number) //If input is correct
		{
			break;
		}
	
		//if the diffrence is X either side of the number then output the corresponding output 
		if (difference <= 2 && difference > 0 || difference >= -2 && difference < 0)
		{
			std::cout << "Boiling" << std::endl;
		}
		else if (difference <= 5 && difference > 0 || difference >= -5 && difference < 0)
		{
			std::cout << "Hot" << std::endl;
		}
		else if (difference <= 10 && difference > 0 || difference >= -10 && difference < 0)
		{
			std::cout << "Warmer" << std::endl;
		}
		else if (difference <= 15 && difference > 0 || difference >= -15 && difference < 0)
		{
			std::cout << "Warm" << std::endl;
		}
		else if (difference <= 25 && difference > 0 || difference >= -25 && difference < 0)
		{
			std::cout << "Cold" << std::endl;
		}
		else if (difference <= 35 && difference > 0 || difference >= -35 && difference < 0)
		{
			std::cout << "Colder" << std::endl;
		}
		else if (difference <= 100 && difference > 0 || difference >= -100 && difference < 0)
		{
			std::cout << "Freezing" << std::endl;
		}

		if (number != guess && number <= 100 && number > 0) //prompts the user to guess again if they are wrong
		{
			std::cout << "Incorrect enter another guess" << endl;
			std::cin >> guess;

		}
	
	} while (guess != number);


	if (guess == number) //Outputs the number and the amount of guesses to the user
	{
		std::cout << "You got it! The number is: " << number << endl;
		std::cout << "Total number of guesses: " << guesses << endl;
	}
}



// - Daniel Johnson