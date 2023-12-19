#include <iostream>
#include <string>

using std::endl;

float Percentage(float In, float Max) //Percentage calculator
{
    return((In * 100.0f) / Max); //Percentage equasion
}

void CRG(int In, float Component, std::string Criterion) //CRG band calculator
{
    float per = Percentage(In, Component);
    //Gets the percentage and applys a criterion to it
    if (per >= 70)
    {
        std::cout << Criterion << " is in criterion 70+" << endl;
    }
    else if (per >= 60)
    {
        std::cout << Criterion << " is in criterion 60-69" << endl;
    }
    else if (per >= 50)
    {
        std::cout << Criterion << " is in criterion 50-59" << endl;
    }
    else if (per >= 40)
    {
        std::cout << Criterion << " is in criterion 40-49" << endl;
    }
    else if (per >= 30)
    {
        std::cout << Criterion << " is in criterion 30-39" << endl;
    }
    else if (per < 30)
    {
        std::cout << Criterion << " fail" << endl;
    }
}
float result1 = 0;
float result2 = 0;

void AssessmentCalcultor(std::string assessment, int components)
{
    float* Grades = new float[components](); //Creates a new dynamic array called grades
   

    for (int i = 0; i < components; i++) //enter each component for the assessment
    {
        std::cout << "Please enter grade for Assessment: " << assessment << " Component: " << i + 1 << endl;
        std::cin >> Grades[i];
        while (Grades[i] > 100 || 0 > Grades[i] || !std::cin) //error handling
        {
            std::cin.clear();
            std::cin.ignore(1945, '\n');
            std::cout << "Invlaid input, please reinput" << endl;
            std::cin >> Grades[i];
        }
    }

    if (assessment == "1") //If it is assessment 1
    {
        CRG(Grades[0], 100, "Component 1");
        CRG(Grades[1], 100, "Component 2");// CRG for each component
        CRG((Grades[0] * 0.7f) + (Grades[1] * 0.3f), 100, "Assessment 1"); //CRG for assessment
        result1 = Percentage((Grades[0] * 0.7f) + (Grades[1] * 0.3f), 100);
        std::cout << "Relative percent for assessment 1: " << result1 << "%\n"; //Percantage for assessment 1
        std::cout << "Weighted percent for assessment 1: " << result1/2 << "%\n"; //Percantage for module
    }

    if (assessment == "2")//If it is assessment 2
    {
        CRG(Grades[0], 100, "Component 1");
        CRG(Grades[1], 100, "Component 2");
        CRG(Grades[2], 100, "Component 3");// CRG for each component
        CRG((Grades[0] * 0.6f) + (Grades[1] * 0.2f) + (Grades[2] * 0.2f), 100, "Assessment 2");//CRG for assessment
        result2 = Percentage((Grades[0] * 0.6f) + (Grades[1] * 0.2f) + (Grades[2] * 0.2f), 100);
        std::cout << "Relative percent for assessment 2: " << result2 << "%\n"; //Percantage for assessment 2
        std::cout << "Weighted percent for assessment 2: " << result2 / 2 << "%\n";//Percantage for module
        std::cout << "The overall grade for this Module is: " << Percentage(result1 + result2, 200) << "% \n"; //Total moudle grade
        CRG(Percentage((result1 + result2), 200), 100, "Module"); //Total module percentage
    }
    delete[] Grades; //Deletes array to save space
}

int main()
{
    AssessmentCalcultor("1", 2); //Runs the function for each assessment and the amount of component in each
    AssessmentCalcultor("2", 3);
}

//-Daniel Johnson