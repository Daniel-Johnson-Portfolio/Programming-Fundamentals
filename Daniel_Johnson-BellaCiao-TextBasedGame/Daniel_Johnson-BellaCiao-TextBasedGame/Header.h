#pragma once

#include <iostream>
#include <string>
#include <windows.h> // used for sleep command
#include <cstdio> // getchar
#include <fstream> // read/write to file

using std::endl;

struct GameSettings // Holds Game Varibles (Settings)
{
    int TypingTime = 25; // Time it takes to out put each character
    int LineTime = 1000;   // Time it takes for each line
    std::string LM_Codes[10] = { "Battery", "Ancient", "Command", "Gateway", "Kingdom", "Liberty", "Mission", "Purpose", "Victory", "Violent" }; //Code words for the Land Mines
    std::string SupplyCrateOptions[4] = { "Grenade", "Rifle Scope", "Medkit", "Nothing" }; //Items in supply crate
    static const int InventorySize = 4; //Size of the players inventory
    char LM_Password; //Varible used to hold the correct char for land mine decativation
    int DecyrptionKey; //Used to hold decyrption key when loading

    int keyGenerator() //Genrates the encryption code (1 - 255) which esnsures random encrytion
    {
        srand(time(NULL));
        return (rand() % 254) + 1;
    }
};

struct GameSettings GameSettings; //Declares the name

struct GameConditions //Curent game conditions 
{
    std::string Chapter; //Current chapter
    bool CurrentEnemyAlive = false; //Is the enemy alive? used in combat event
    bool stop = false; //This is used in the treads to comuncate to the main program when to stop
};

struct GameConditions GameConditions;

struct Player //Holds player data
{
    std::string CurrentItem; //Current item they are holding/using
    int health = 2; //Defualt amount of health
    std::string Inventory[GameSettings.InventorySize] = { "Rifle", "Empty", "Empty", "Empty" }; //Default inventory
    int InfiniteModeScore = 0; //Default Infinate mode score
    struct MajorDecisions
    {
        std::string MajorDecision1 = "0"; //Default major decsion holder
    } MajorDecisions;
};

struct Player Player;

//Pre-instance decleration
void Chapter2();
void Chapter1();
void InventoryInput(std::string in, bool Options);
void title();
void Tutorial();
void CombatEvent(int Combatants);

void PrintText(std::string text) // Function used to output text in a stylistic way
{
    for (int i = 0; i < text.length(); i++) //for loop (lenght of string that has been handed)
    {
        if (text[i] == '|') //Checks for a | if so its means a charcater is nspeaking so it cuts out typing their name making it better for the player
        {
            std::cout << text[i];
            i++;
            for (i = i; i < text.length(); i++)
            {
                std::cout << text[i];
                if (text[i] == '|')
                {
                    i++;
                    Sleep(1000); //Time to wait before outputig what they are saying
                    break;
                }
            }
        }
        if (text[i] == ',') //A pause for a commar
        {
            Sleep(500);
        }
        std::cout << text[i];
        Sleep(GameSettings.TypingTime); //Uses typing time to wait for the next charcater
    }
    std::cout << endl;//end of line
    Sleep(GameSettings.LineTime);//time before next line
}

void Enter()
{
    std::cout << ("Press enter to continue");
    std::cin.ignore(1945, '\n');
    system("CLS");
} //function when player is aksed to press enter

bool addToInventory(std::string add) //Function thats not seen to the player that adds an item to therir highest empty slot when needed
{
    for (int i = 0; i < GameSettings.InventorySize; i++) //For the size of the players inventory
    {
        if (Player.Inventory[i] == "Empty") //if the current index is empty
        {
            Player.Inventory[i] = add;//add the passed item to the slot
            return true;//Return true if sucessful
        }
    }
    return false; //Return false if not
}

void RemoveFromInventory(std::string remove) //Remove an item from inventory
{
    for (int i = GameSettings.InventorySize; i >= 0; i--)//For the size of the players inventory however going backwards
    {
        if (Player.Inventory[i] == remove) //If current item is the passed item (item you want to remove)
        {
            Player.Inventory[i] = "Empty"; //Set it to enpty
            break;
        }
    }
}

std::string inputCheckerYN(std::string in) //Checkes the users input on a yes/no question
{
    while (in != "Y" && in != "y" && in != "N" && in != "n" || !std::cin) //if its not yes or no they respond with or its an error it will ask them to re enter
    {
        in;
        std::cout << "Invalid input, please renter" << endl;
        std::cin.clear();
        std::cin.ignore(1945, '\n');
        std::cin >> in;
        printf("\33[2K\r");
        printf("\033[A\r");
        printf("\033[A\r");
    }
    return in;
}

std::string inputChecker123(std::string in, bool Inventory) //Checks the users input to a 1,2,3 selction query
{
    if (in == "i" || in == "I" && Inventory == true) // if they are allowed to acsess their inventory at this stage and theyve entered i open their inventory
    {
        InventoryInput("i", true);
        std::cin.clear();
        std::cin.ignore(1945, '\n');
        return in;
    }
    printf("\033[A\r");
    while (in != "1" && in != "2" && in != "3" || !std::cin) //Renter if there is an error
    {
        std::cout << "Invalid input, please renter" << endl;;
        std::getline(std::cin, in);
        printf("\33[2K\r");
    }
    printf("\33[2K\r");
    return in;
}

DWORD WINAPI thread1(LPVOID pm) //When created listens for f to be inputted
{
    int a = getchar();
    while (a != 'f' && a != 'F')
    {
        a = getchar();
    }
    GameConditions.stop = true;
    return 0;
}

DWORD WINAPI thread2(LPVOID pm) //When created listens for the users input for the correct land mine answer
{
    int a = std::tolower(getchar()); //to lower to gie more fairness to the user if they get the answer right but not capitalised
    while (a != GameSettings.LM_Password)
    {
        a = getchar();
        if (a != GameSettings.LM_Password)
        {
            std::cout << "Incorrect" << endl;
            printf("\33[A\r");
        }
    }
    GameConditions.stop = true;
    return 0;
}

void Death(std::string Cause) //Is called when the player dies, is passed a reason for death
{
    Sleep(1000);
    PrintText("*YOU HAVE BEEN " + Cause + "*\n");//tells the user the cause of their death
    if (Cause == "BLOWN UP BY YOUR OWN GRENADE" || Cause == "EXPLODED BY A LAND MINE")
    {
        PrintText("It was a fairly messy ordeal");
        Sleep(1000);
        PrintText("Bella Ciao");
        Sleep(2000);
        system("CLS");
        Player.health = 2;
        title();
    }
    if (Cause == "SHOT TO DEATH BY AN ENEMY")
    {
        PrintText("You will be remembered");
        Sleep(1000);
        PrintText("Bella Ciao");
        Sleep(2000);
        system("CLS");
        Player.health = 2;
        title();
    }
    else
    {
        PrintText("You will be remembered");
        Sleep(1000);
        PrintText("Bella Ciao");
        Sleep(2000);
        system("CLS");
        Player.health = 2;
        title();
    }
}

void LandMine() //landmine function, can happen after the player kills an enemy
{
    std::cin.clear();
    srand(time(NULL));
    int number = (rand() % 10);
    std::string Password = GameSettings.LM_Codes[number]; //Gets a random deactivation code
    std::cout << "YOU HAVE STOOD ON A LAND MINE" << endl;
    std::cout << "The deactivation code will show in: " << endl;
    std::cout << "3" << endl;
    Sleep(1000);
    printf("\33[2K\r");
    std::cout << "2" << endl;
    Sleep(1000);
    printf("\33[2K\r");
    std::cout << "1" << endl;
    Sleep(1000);
    printf("\33[2K\r");
    std::cout << Password << endl;
    Sleep(2000);
    printf("\33[A\r");
    srand(time(NULL));
    int number2 = (rand() % 6);
    GameSettings.LM_Password = std::tolower(Password[number2]);
    std::cout << ("What was character " + std::to_string(number2 + 1) + " of the deactivation code") << endl; //asks for a random specific character
    Sleep(1000);
    std::cin.clear();
    HANDLE handle = CreateThread(NULL, 0, thread2, NULL, 0, NULL); //Creates thread for deactivation character
    for (int i = 5; i >= 0 && !GameConditions.stop; i--)
    {
        std::cout << i << endl;
        Sleep(1000);
        printf("\33[2K\r");
        if (i == 0)
        {
            GameConditions.stop = false;
            GameSettings.LM_Password = NULL;
            Death("EXPLODED BY A LAND MINE");
        }
    }
    std::cout << "Success" << endl;
    Sleep(500);
    GameConditions.stop = false;
    GameSettings.LM_Password = NULL;
}

void Event_shot(int odds) //Random chance to be shot, || odds come from the skill level of the enemy
{
    srand(time(NULL));
    int number = (rand() % odds) + 1;
    if (number > 1)
    {
        PrintText("Enemy has missed\n");
    }
    if (number == 1)
    {
        PrintText("*YOU HAVE BEEN SHOT*\n");
        Player.health--;
        if (Player.health == 0)
        {
            Death("SHOT TO DEATH BY AN ENEMY");
        }
    }
}

void Medkit() //Medkit function
{
    switch (Player.health)
    {
    case 1:
        Player.health++;
        PrintText("You have applied first aid");
        PrintText("Health recovered");
        RemoveFromInventory("Medkit");
        break;
    case 2:
        PrintText("Your health is already full");
        break;
    }
}

bool Rifle() //Player shoots rifle at enemy
{
    for (int i = 0; i < GameSettings.InventorySize; i++)
    {
        if (Player.Inventory[i] == "Rifle Scope") //If you have a rifle scope you have better accuracy
        {
            srand(time(NULL));
            int number = rand() & 1 + 1;
            std::string input;
            std::cout << ("Accuracy improved by Rifle Scope") << endl;
            std::cout << ("1: X\n2: X") << endl;
            std::getline(std::cin, input);
            while (input == "3")
            {
                std::cout << "Invalid input please select 1 or 2" << endl;
                std::cin.clear();
                std::getline(std::cin, input);
            }
            inputChecker123(input, false);
            PrintText("BANG...");
            int result = std::stoi(input);
            if (result == number)
            {
                PrintText("YOU'VE SHOT AND NEUTRALISED THE ENEMY");
                return true;
            }
            if (result != number)
            {
                PrintText("YOU'VE MISSED THE ENEMY");
                return false;
            }
        }
    }
    srand(time(NULL));
    int number = rand() & 2 + 1;

    std::string input;

    std::cout << ("1: X\n2: X\n3: X") << endl;
    std::getline(std::cin, input);
    inputChecker123(input, false);
    PrintText("BANG...");
    int result = std::stoi(input);
    if (result == number)
    {
        PrintText("YOU'VE SHOT AND NEUTRALISED THE ENEMY");
        return true;
    }
    if (result != number)
    {
        PrintText("YOU'VE MISSED THE ENEMY");
        return false;
    }
}

enum GrenadeActions
{
    Exploded, //exploded in hand
    Thrown_Hit, //have hit enemy
    Thrown_Miss //have missed
};

enum GrenadeActions Grenade() //grenade fucntion
{
    PrintText("Press [Enter] to pull the grenade pin (Timer will start)"); //begins timer
    std::cin.clear();
    std::cin.ignore(1945, '\n');
    std::cin;
    std::getchar();
    srand(time(NULL));
    int number = (rand() % 3) + 5; //random timer
    int currant = 0;
    std::cout << "Enter [f] to throw the grenade" << std::endl;
    RemoveFromInventory("Grenade");
    HANDLE handle = CreateThread(NULL, 0, thread1, NULL, 0, NULL); //Creates thread that listens for f input
    for (int i = number; i >= 0 && !GameConditions.stop; i--)
    {
        currant = i;
        std::cout << ".";
        Sleep(250);
        std::cout << ".";
        Sleep(250);
        std::cout << ".";
        Sleep(250);
        std::cout << ".";
        Sleep(250);
        std::cout << ".";
        printf("\33[2K\r");
        if (i == 0)
        {
            GameConditions.stop = false;
            return Exploded; // Timer ran out
        }
    }
    GameConditions.stop = false;
    int hitTarget;
    switch (currant - 1) //How close was the timer to 0
    {
    case -1:
        return Thrown_Hit;
    case 0:
        return Thrown_Hit;
    case 1:
        return Thrown_Hit;
    case 2:
        hitTarget = (rand() % 4);
        if (hitTarget < 3)
        {
            return Thrown_Hit;
        }
        if (hitTarget == 3)
        {
            return Thrown_Miss;
        }
    case 3:
        hitTarget = (rand() % 2);
        if (hitTarget == 1)
        {
            return Thrown_Hit;
        }
        if (hitTarget == 0)
        {
            return Thrown_Miss;
        }
    case 4:
        hitTarget = (rand() % 4);
        if (hitTarget < 3)
        {
            return Thrown_Miss;
        }
        if (hitTarget == 3)
        {
            return Thrown_Hit;
        }
    default:
        return Thrown_Miss;
    }
    return Thrown_Miss;
}

int SupplyCrate(std::string Special_Item) //supply crate function, special item by deault is nothing
{
    PrintText("You have found a supply crate");

    std::cout << ("Enter [1] to open the crate or [2] to ignore it") << endl;;

    std::string Result = "0";

    int input;

    std::cin >> input;

    while (input != 1 && input != 2) //Error handling
    {

        std::cout << "Invalid input" << endl;

        std::cout << ("Enter [1] to open the crate or [2] to ignore it") << endl;

        std::cin.clear();

        std::cin.ignore(1945, '\n');

        std::cin >> input;
    }

    if (input == 1)
    {

        std::cout << ("Press [f] to select item") << endl;

        HANDLE handle = CreateThread(NULL, 0, thread1, NULL, 0, NULL);

        GameConditions.stop = false;

        GameSettings.SupplyCrateOptions[3] = Special_Item;

        while (!GameConditions.stop)
        {
            if (GameConditions.stop)
            {
                break;

            }

            int i = 0;

            std::cout << GameSettings.SupplyCrateOptions[i];

            Result = GameSettings.SupplyCrateOptions[i];

            i++;

            Sleep(50);

            printf("\33[2K\r");

            if (GameConditions.stop)
            {
                break;
            }

            std::cout << GameSettings.SupplyCrateOptions[i];

            Result = GameSettings.SupplyCrateOptions[i];

            i++;

            Sleep(50);

            printf("\33[2K\r");

            if (GameConditions.stop)
            {
                break;
            }

            std::cout << GameSettings.SupplyCrateOptions[i];

            Result = GameSettings.SupplyCrateOptions[i];

            i++;

            Sleep(50);

            printf("\33[2K\r");

            if (GameConditions.stop)
            {
                break;
            }

            std::cout << GameSettings.SupplyCrateOptions[i];

            Result = GameSettings.SupplyCrateOptions[i];

            i++;

            Sleep(50);

            printf("\33[2K\r");

            if (GameConditions.stop)
            {
                break;

            }

            std::cout << GameSettings.SupplyCrateOptions[i];

            Result = GameSettings.SupplyCrateOptions[i];

            i++;

            Sleep(50);

            printf("\33[2K\r");
        }

        printf("\33[2K\r");

        printf("\33[2K\r");

        if (Result != "Nothing")
        {

            std::cout << ("Would you like to add this item to your inventory Y/N?") << endl;
            std::string input;
            std::cin.clear();
            std::cin.ignore(1945, '\n');

            std::getline(std::cin, input);

            if (inputCheckerYN(input) == "y" || inputCheckerYN(input) == "Y")
            {

                bool Checker = addToInventory(Result);

                while (Checker == false) //If there is no room in invetory ask the user if they want to raplce another item
                {
                    std::string input1;
                    std::cout << "No room in inventory" << endl;

                    std::cout << "Would you like to replace an item in you inventory Y/N?" << endl;

                    std::getline(std::cin, input1);


                    if (inputCheckerYN(input1) == "y" || inputCheckerYN(input1) == "Y")
                    {
                        std::cout << "What item would you like to drop?" << endl;
                        InventoryInput("i", false);
                        int input2;
                        std::cin >> input2;
                        while (input2 > GameSettings.InventorySize || input2 < 1 || input2 == 1 && !std::cin)
                        {
                            if (input2 == 1)
                            {
                                std::cout << "You cannot drop this item" << endl;
                            }
                            else
                            {
                                std::cout << "Invalid input" << endl;
                            }
                            std::cin.clear();
                            std::cin >> input2;

                        }

                        Player.Inventory[input2] = "Empty";



                        if (addToInventory(Result) == true)
                        {
                            PrintText("Item added to inventory");
                            return 0;
                        }
                    }

                    if (inputCheckerYN(input1) == "n" || inputCheckerYN(input1) == "N")
                    {
                        PrintText("Item discarded");
                        return 1;
                    }
                }
                if (Checker == true)
                {
                    PrintText("Item added to inventory");
                    return 0;
                }
            }

            if (inputCheckerYN(input) == "n" || inputCheckerYN(input) == "N")
            {
                PrintText("Item discarded");
                return 1;
            }
        }

        Sleep(1000);
    }

    if (input == 2)
    {
        PrintText("You ignored the supply crate");
        return 2;
    }
}

void InventoryOptions() //Input options, this is only accessed frominventoy input
{
    //this function allows the user to drop and use items from their inventory

    while (true)
    {
        std::cout << "Please select an inventory item or [i] to exit inventory" << std::endl;
        std::string selection;
        std::cin >> selection;
        int I_selection;
        try
        {
            I_selection = stoi(selection);
        }
        catch (...)
        {
            if (selection == "i" || selection == "I")
            {
                return;
            }
            std::cout << "Invalid input, please select a valid inventory option or enter [i] to exit inventory" << std::endl;
            continue;
        }
        if (I_selection <= 0 || I_selection > GameSettings.InventorySize)
        {
            std::cout << "Invalid inventory option" << std::endl;
            continue;
        }
        if (Player.Inventory[I_selection - 1] == "Empty")
        {
            std::cout << "You cannot select empty inventory slots" << std::endl;
            continue;
        }
        std::cout << ("Press [1] to equip item or [2] to drop item") << std::endl;
        std::string input;
        std::cin >> input;
        int I_input;
        try
        {
            I_input = stoi(input);
        }
        catch (...) {
            if (input == "i" || input == "I")
            {
                return;
            }
            std::cout << "Invalid input, please input option [1], [2], or [i] to exit inventory" << std::endl;
            continue;
        }
        if (I_input != 1 && I_input != 2)
        {
            std::cout << "Invalid option" << std::endl;
            continue;
        }
        I_selection--;
        if (I_input == 1)
        {
            std::cout << Player.Inventory[I_selection] << " equipped" << std::endl;
            Player.CurrentItem = Player.Inventory[I_selection];
            if (Player.CurrentItem == "Medkit")
            {
                Medkit();
            }
            if (Player.CurrentItem == "Grenade")
            {
                GrenadeActions Result = Grenade();
                if (Result == Thrown_Hit)
                {
                    GameConditions.CurrentEnemyAlive = false;
                    return;
                }
                if (Result == Thrown_Miss)
                {
                    PrintText("You released the grenade too early and failed to neutralize the target");
                    return;
                }
                if (Result == Exploded)
                {
                    Death("BLOWN UP BY YOUR OWN GRENADE");
                }
            }
            InventoryInput("i", false);
        }
        else if (I_input == 2)
        {
            if (Player.Inventory[I_selection] == "Rifle")
            {
                std::cout << "This item cannot be dropped" << std::endl;
                InventoryInput("i", false);
                continue;
            }
            std::cout << Player.Inventory[I_selection] << " dropped" << std::endl;
            Player.Inventory[I_selection] = "Empty";
            InventoryInput("i", false);
        }
    }
}

void InventoryInput(std::string in, bool Options)
{
    //this function displays the user their inventory

    while (in != "i" && in != "I" || !std::cin)
    {
        std::cin.clear();
        std::cin.ignore(1945, '\n');
        std::cout << "Invalid input, please re-enter" << std::endl;
        std::cin >> in;
        std::cout << in;
        printf("\33[2K\r");
        printf("\033[A\r");
        printf("\033[A\r");
    }
    std::cout << "Inventory:" << std::endl;
    for (int i = 0; i < GameSettings.InventorySize; i++)
    {
        std::cout << i + 1 << ": " << Player.Inventory[i] << std::endl;;
    }
    if (Options == true)
    {
        InventoryOptions();
    }
}

int Dialogue(std::string one, std::string two, std::string three)
{
    //This function outputs dialouge option and returns the palyers choice
    std::cout << "[1] " << one << std::endl;
    std::cout << "[2] " << two << std::endl;
    std::cout << "[3] " << three << std::endl;
    std::string input;
    std::getline(std::cin, input);
    return stoi(inputChecker123(input, false));
}

std::string Encrypt(std::string in) //this function encrypts using the random key
{
    for (int i = 0; i < in.length(); i++)
    {
        in[i] = in[i] + GameSettings.keyGenerator();
    }
    return in;
}

std::string Decrypt(std::string in) //this function deycrpts using the key in the save file
{
    for (int i = 0; i < in.length(); i++)
    {
        in[i] = in[i] - GameSettings.DecyrptionKey;
    }
    return in;
}

void FileSave(std::string Chapter) //This function saves all the nessery data
{
    std::ofstream file;
    file.open("SaveData.txt");
    if (file)
    {
        file << Player.InfiniteModeScore << endl;
        file << GameSettings.keyGenerator() << endl;
        file << (Player.health) << endl;
        file << Encrypt(Chapter) << endl;
        for (int i = 0; i < GameSettings.InventorySize; i++)
        {
            file << Encrypt(Player.Inventory[i]) << endl;
        }
        file << Encrypt(Player.MajorDecisions.MajorDecision1) << endl;
    }
    file.close();
}

void FileLoad() //this function loads all of the data
{
    std::ifstream file;
    file.open("SaveData.txt");
    if (!file)
    {
        std::cout << "No save file found" << endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    Player.InfiniteModeScore = stoi(line);
    std::getline(file, line);
    GameSettings.DecyrptionKey = stoi(line);
    std::getline(file, line);
    Player.health = stoi(line);
    std::getline(file, line);
    GameConditions.Chapter = Decrypt(line);
    for (int i = 0; i < GameSettings.InventorySize; i++)
    {
        std::getline(file, line);
        Player.Inventory[i] = Decrypt(line);
    }
    std::getline(file, line);
    Player.MajorDecisions.MajorDecision1 = Decrypt(line);;
    int F_Chapter;
    F_Chapter = GameConditions.Chapter[7] - '0';
    switch (F_Chapter)
    {
    case 1:
        Chapter1();
        break;
    case 2:
        Chapter2();
        break;
    default:
        Chapter1();
        break;
    }
    file.close();
}

void Game_New() //Function that runs when the player makes a new game
{
    std::cout << "Would you like to complete the tutorial? (Recommended) Y/N?" << std::endl;
    std::string input;
    std::cin >> input;
    input = inputCheckerYN(input);

    if (input == "Y" || input == "y")
    {
        Tutorial();
    }
    if (input == "N" || input == "n")
    {
        Chapter1();
    }
}

void InfiniteMode() //Loops the combat event untill they die
{
    PrintText("It is not recommended to play infinate mode without first playing the tutorial");
    std::cout << "Do you wish to proceed? Y/N" << endl;
    std::string input;
    std::cin >> input;
    input = inputCheckerYN(input);
    system("CLS");
    if (input == "y" || input == "Y")
    {
        while (true)
        {
            CombatEvent(1);
            Player.InfiniteModeScore++;
        }
    }
    if (input == "n" || input == "N")
    {
        return;
    }

}

void DevTesting() //A COLLECTION OF ALL FUNCTIONS AVALIBLE TO TEST
{
    system("CLS");
    std::cin.clear();
    std::string input;
    std::string Options[12] = { "Combat", "Supply Crate drops", "Landmine", "Medkit", "Being shot", "Inventory", "Death", "Add to inventory", "Remove from inventory", "Print Text", "Encryption", "Exit" };
    for (int i = 0; i < 12; i++)
    {
        std::cout << i + 1 << ": " << Options[i] << std::endl;
    }

    std::cin >> input;
    int inputI;
    while (true)
    {
        try
        {
            inputI = stoi(input);
            break;
        }
        catch (...)
        {
            std::cout << "Invalid input" << endl;
            std::cin >> input;
        }

    }


    std::string input2;
    switch (inputI)
    {
    case 1:
        CombatEvent(1);
        break;
    case 2:
        SupplyCrate("Nothing");
        break;
    case 3:
        LandMine();
        break;
    case 4:
        Medkit();
        break;
    case 5:
        Event_shot(1);
        break;
    case 6:
        InventoryInput("i", true);
        break;
    case 7:
        Death("KILLED BY DEV CONSOLE");
        break;
    case 8:
        std::cout << "Input what you would like to add to your inventory" << std::endl;
        std::cin >> input2;
        addToInventory(input2);
        break;
    case 9:
        std::cout << "Input what you would like to remove from your inventory" << std::endl;
        std::cin >> input2;
        RemoveFromInventory(input2);
        break;
    case 10:
        std::cout << "Input what you would like to print" << std::endl;
        std::cin >> input2;
        PrintText(input2);
        break;
    case 11:
        std::cout << "Input what you would like to encrypt" << std::endl;
        std::cin >> input2;
        std::cout << Encrypt(input2) << std::endl;
        break;
    case 12:
        return;
    }
    Sleep(1000);
    DevTesting();
}

void title() //the function that runs as the game begins
{

    //loads some inportant information that the main menu will need (infinate mode high score)
    std::ifstream file;
    file.open("SaveData.txt");
    if (file)
    {
        std::string line;
        std::getline(file, line);
        if (stoi(line) < Player.InfiniteModeScore)
        {
            std::ofstream file;
            file.open("SaveData.txt");
            file << Player.InfiniteModeScore << endl;
        }
        if (stoi(line) > Player.InfiniteModeScore)
        {
            Player.InfiniteModeScore = stoi(line);
        }
    }
    if (!file)
    {
        std::ofstream file;
        file.open("SaveData.txt");
        file << Player.InfiniteModeScore << endl;

    }

    file.close();
    Player.health = 2;

    //prints title and shows options
    while (true)
    {
        std::string title = " _____                                                     _____ \n"
            "( ___ )                                                   ( ___ )\n"
            " |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   |\n"
            " |   |  ____         _  _           ____  _                |   |\n"
            " |   | | __ )   ___ | || |  __ _   / ___|(_)  __ _   ___   |   |\n"
            " |   | |  _ \\  / _ \\| || | / _` | | |    | | / _` | / _ \\  |   |\n"
            " |   | | |_) ||  __/| || || (_| | | |___ | || (_| || (_) | |   |\n"
            " |   | |____/  \\___||_||_| \\__,_|  \\____||_| \\__,_| \\___/  |   |\n"
            " |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___|\n"
            "(_____)                                                   (_____)   \n  \n";
        for (int i = 0; i < title.length(); i++)
        {
            std::cout << title[i];
            i++;
            std::cout << title[i];
            i++;
            Sleep(1);
            std::cout << title[i];
            i++;
            std::cout << title[i];
        }
        std::cout << "|1: New Game|" << endl;
        std::cout << "|2: Load Game|" << endl;
        std::cout << "|3: Infinite mode||High Score: " << Player.InfiniteModeScore << '|' << endl;
        std::cout << "|4: Exit|" << endl;
        std::string input;
        std::cin >> input;
        while (!std::cin)
        {
            std::cout << "Invalid option" << endl;
            std::cin.clear();
            std::cin >> input;
        }


        if (input == "Breaking_The_Bad")
        {
            DevTesting();
        }

        while (input != "1" && input != "2" && input != "3" && input != "4" || !std::cin)
        {
            std::cout << "Invalid input, please renter" << endl;;
            // std::cin.clear();
            // std::cin.ignore(1945, '\n');
            //in = "0";
            std::getline(std::cin, input);
            printf("\33[2K\r");
            // printf("\033[A\r");
            // printf("\033[A\r");
        }

        if (input == "1")
        {
            system("CLS");
            Game_New();
        }
        else if (input == "2")
        {
            system("CLS");
            FileLoad();
        }
        else if (input == "3")
        {
            InfiniteMode();
        }
        else if (input == "4")
        {
            exit(0);
        }
    }
}

//-Daniel Johnson
