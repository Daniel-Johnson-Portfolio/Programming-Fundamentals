#include <iostream>
using std::endl;

float Vector_A[2] = { 0.0f, 0.0f }; //Varible decleration
float Vector_B[2] = { 0.0f, 0.0f };

float GetDistanceBetweenPoints(float X1, float Y1, float X2, float Y2) //Euclidean Distance function
{
	float result = sqrtf(powf((X1 - X2), 2) + powf((Y1 - Y2), 2)); //Distacne between two Vetcor2's equasion
	return result;
}

int main()
{
	std::cout << "Euclidean Distance" << endl;
	std::cout << "Press enter to begin" << endl;
	std::cin;

	//Gets each component of the vectors with error handling
	do
	{
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << "Please enter the X component of Vector 1" << endl;
		std::cin >> Vector_A[0];
		
	} while (!std::cin);

	do
	{
		std::cout << "Please enter the Y component of Vector 1" << endl;
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cin >> Vector_A[1];
	} while (!std::cin);

	do
	{
		std::cout << "Please enter the X component of Vector 2" << endl;
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cin >> Vector_B[0];
	} while (!std::cin);

	do
	{
		std::cout << "Please enter the Y component of Vector 2" << endl;
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cin >> Vector_B[1];
	} while (!std::cin);
	

	std::cout << GetDistanceBetweenPoints(Vector_A[0], Vector_A[1], Vector_B[0], Vector_B[1]); //Runs function based on inputs of the user
}

//-Daniel Johnson