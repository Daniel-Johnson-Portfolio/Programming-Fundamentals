#include <iostream>
#include <string>
#include <windows.h> // used for sleep command
#include <cstdio> // getchar
#include <fstream> //read/wrtie to file
#include "Header.h"


using std::endl;


struct Combat //Combat data
{
    int ShotOdds = 0;
    int SupplyCrateOffset = 5;
    int SupplyCrateChance = 0;
};
struct Combat Combat;
void Tutorial();
void title();
class Enemy
{
public:
    int ShootingSkill;
    Enemy(int Upper_Skill); //The lower the Upper_Skill int is the lower the range of their skill could be = a higher skill
};

Enemy::Enemy(int Upper_Skill)
{
    srand(time(NULL));
    ShootingSkill = (rand() % Upper_Skill) + 2; //Lowest possible number 5, highest 11 (highest skill = a 12.5% chance to land shot : Lowest skill = a 9.090909***% chnace of landning a shot)
    if (Upper_Skill < 6)
    {
        PrintText("The enemy is highly skilled");
    }
    if (Upper_Skill > 5 && Upper_Skill < 9)
    {
        PrintText("The enemy is semi-skilled");
    }
    if (Upper_Skill > 8)
    {
        PrintText("The enemy is unskilled");
    }
}

Enemy* NewEnemy() //Creates a new enemy
{
    PrintText("A new enemy has appeard");
    srand(time(NULL));
    int number = (rand() % 7) + 3;
    Enemy* enemy = new Enemy(number);
    GameConditions.CurrentEnemyAlive = true;
    PrintText("The enemy is aimming at you!");
    Event_shot(enemy->ShootingSkill);
    return reinterpret_cast<Enemy*>(enemy);
}

Enemy* OldEnemy(Enemy* Ref) //The current enemy action
{
    PrintText("The enemy is aimming at you!");
    Event_shot(Ref->ShootingSkill);
    return reinterpret_cast<Enemy*>(Ref);
}

void CombatEvent(int Combatants) //MAIN COMBAT LOOP
{
    std::cout << ("*YOU HAVE ENTERED COMBAT*") << endl;
    std::cout << ("*INVENTORY UNLOCKED*") << endl;

    for (Combatants; 0 < Combatants;) //for the amount of combatants left
    {
        std::cout << Combatants;
        PrintText(" ENEMIES REMANING");
        Enemy* Ref = NewEnemy(); //new enemy instance
        Enemy* Properties = reinterpret_cast<Enemy*>(Ref); //enimes class properites

        while (GameConditions.CurrentEnemyAlive == true)
        {
            std::string input;

            while (input != "1" && input != "2")
            {
                std::cout << ("[1] SHOOT BACK") << endl;
                std::cout << ("[2] COVER (THIS WILL LOWER THE ENEMIES ACCURACY)") << endl;
                std::cout << ("[i] OPEN INVENTORY") << endl;
                std::getline(std::cin, input);

                while (input != "1" && input != "2" && input != "i")
                {
                    std::cout << "Invalid input, please renter" << endl;
                    std::cin.clear();
                    std::getline(std::cin, input);
                }

                if (input == "i" || input == "I")
                {
                    inputChecker123(input, true);
                }

                if (GameConditions.CurrentEnemyAlive == false) //If enemy is killed by other means than the rifle (Grenade)
                {
                    PrintText("ENEMY NEUTRALISED");
                    Combatants--;
                    system("CLS");
                    srand(time(NULL));
                    int number = (rand() % 3) + 1;
                    if (number == 1)
                    {
                        SupplyCrate("Nothing");
                        return;
                    }
                    if (number == 2)
                    {
                        LandMine();
                        return;
                    }

                    return;
                }
            }

            int Result = stoi(inputChecker123(input, true));
            switch (Result)
            {
            case 1:
                if (Rifle() == true)
                {
                    GameConditions.CurrentEnemyAlive = false;

                    delete Ref;

                    Ref = nullptr;

                    //PrintText("ENEMY NEUTRALISED");
                    Combatants--;
                    system("CLS");
                    srand(time(NULL));

                    int number = (rand() % 3) + 1;
                    //Random chance of a supplycreat/landmin
                    if (number == 1)
                    {
                        SupplyCrate("Nothing");
                        return;
                    }

                    if (number == 2)
                    {
                        LandMine();
                        return;
                    }

                    return;
                }
                break;

            case 2:
                Properties->ShootingSkill++; //Increasing this increases the range that the random number will generate
                break;
            }

            OldEnemy(Ref);
        }
    }
}

void Chapter2() //Chapter 2
{
    system("CLS");
    FileSave("Chapter2");

    std::string title = "  ____   _                       _                         ____  \n"
        " / ___| | |__     __ _   _ __   | |_    ___   _ __   _    |___ \\ \n"
        "| |     | '_ \\   / _` | | '_ \\  | __|  / _ \\ | '__| (_)     __) |\n"
        "| |___  | | | | | (_| | | |_) | | |_  |  __/ | |     _     / __/ \n"
        " \\____| |_| |_|  \\__,_| | .__/   \\__|  \\___| |_|    (_)   |_____|\n"
        "                        |_|                                      \n";

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

    PrintText("10:24pm");
    PrintText("Heavy rain continues to pour down on the campsite");
    PrintText("Night approaches");
    Enter();

    PrintText("|General Soprano| GOOD EVENING SOLDIERS");
    PrintText("|General Soprano| OUR ATTACK ON MONTRE CASSINO WILL COMMENCE TONIGHT");

    if (Player.MajorDecisions.MajorDecision1 == "1")
    {
        PrintText("|General Soprano| YOU WILL ASSUALT THE FORTRESS WITH A HEAD ON ATTACK");
        PrintText("|General Soprano| EXPECT MACHINE GUN FIRE, LAND MINES AND LOTS OF MUD");
        PrintText("|Commander| SOLDIERS!!!");
        PrintText("|Commander| LEAD ON");
        Enter();

        PrintText("You line up in a trench facing the fortress");
        PrintText("Water drowns your legs");
        PrintText("Do you wish to flash back to your training before you go over the top Y/N?");
        std::cout << ("(This will restart the tutorial and return you here once complete)") << endl;
        std::cout << ("Y/N?") << endl;

        std::string input;
        std::cin >> input;
        inputCheckerYN(input);

        if (input == "Y" || input == "y")
        {
            system("CLS");
            Tutorial();
            PrintText("You are intensively waiting for the signal to charge the fortress");
        }

        if (input == "N" || input == "n")
        {
            PrintText("You are intensively waiting for the signal to charge the fortress");
        }

        std::cin.clear();
        std::cin.ignore(1945, '\n');
        Enter();

        PrintText("|General Soprano| GO GO GO...");
        PrintText("Machine guns open fire like fireworks coming from all directions");
        PrintText("You charge forward through the mud");
        Enter();

        CombatEvent(3);
        system("CLS");

        PrintText("You slam forwards through a no man's land");
        PrintText("You see Vincent injured in a crater");

        int Response = Dialogue("Defend Vincent and attempt to save him", "Go and find first aid", "Leave him");

        switch (Response)
        {
        case 1:
            PrintText("You decide to defend Vincent");
            Enter();
            CombatEvent(3);
            system("CLS");
            PrintText("You have successfully defended Vincent");
            PrintText("He is no longer able to fight but he will survive");
            break;

        case 2:
            PrintText("You decide to go out and attempt to find Vincent first aid");
            Enter();
            CombatEvent(3);
            system("CLS");

            for (int i = 0; i < GameSettings.InventorySize; i++)
            {
                if (Player.Inventory[i] == "Medkit")
                {
                    PrintText("You have a medkit in your inventory, would you like to use it on Vincent Y/N?");
                    std::string input;
                    std::cin >> input;
                    inputCheckerYN(input);

                    if (input == "y" || input == "Y")
                    {
                        PrintText("You use your medkit on Vincent, he will survive");
                        RemoveFromInventory("Medkit");
                        break;
                    }

                    if (input == "n" || input == "N")
                    {
                        PrintText("You don't use your medkit on Vincent, he will survive but he will remember");
                        break;
                    }
                }
            }

            PrintText("You don't have a medkit for Vincent, he is no longer able to fight but he will survive");
            break;

        case 3:
            PrintText("You leave Vincent to die");
            PrintText("Bella Ciao");
            Enter();
            CombatEvent(3);
            system("CLS");
            break;
        }

        PrintText("You push forwards towards a pillbox");
        PrintText("You are close");

        CombatEvent(2);
        system("CLS");

        PrintText("You break into the pillbox");
        PrintText("An enemy was waiting for you");

        CombatEvent(1);
        system("CLS");

        PrintText("You have secured the pillbox where Luca joins you");

        system("CLS");
        PrintText("This is the end for now, feel free to test the main combat loop in the infinate mode in the main menu");
        PrintText("Type 69 in the main menu for the development console");
        PrintText("Bella Ciao");
        Sleep(1000);


    }

    if (Player.MajorDecisions.MajorDecision1 == "2")
    {
        PrintText("|General Soprano| YOU ARE APART OF THE TEAM THAT WILL FLANK THE FORTRESS");
        PrintText("|General Soprano| YOU LEAVE SHORTLY AFTER THE MAIN ASSUALT BEGINS");
        PrintText("|General Soprano| PRIVATE, LUCA, VINCENT");
        PrintText("|General Soprano| FOLLOW ME");
        Enter();

        PrintText("You begin the long walk through the Apennine mountain range");
        PrintText("You prepare yourselves with flashlights to traverse the dark path ahead");
        Enter();

        PrintText("|General Soprano| WE WILL USE THE MOUNTAINS TO HIDE OUR MOVEMENT");

        system("CLS");
        PrintText("This is the end for now, i recommend going back and choosing option one as there is more there");
        PrintText("Type 69 in the main menu for the development console");
        PrintText("Bella Ciao");
        Sleep(1000);

    }
}

void Chapter1() //Chapter 1
{
    std::cin.clear();
    system("CLS");
    FileSave("Chapter1");

    std::string title = "  ____   _                       _                          _ \n"
        " / ___| | |__     __ _   _ __   | |_    ___   _ __   _     / |\n"
        "| |     | '_ \\   / _` | | '_ \\  | __|  / _ \\ | '__| (_)    | |\n"
        "| |___  | | | | | (_| | | |_) | | |_  |  __/ | |     _     | |\n"
        " \\____| |_| |_|  \\__,_| | .__/   \\__|  \\___| |_|    (_)    |_|\n"
        "                        |_|                                    \n";

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

    PrintText("Campsite delta, south east of Monte Cassino");
    PrintText("January 16th 1944");
    PrintText("9:44pm");
    Enter();
    PrintText("Heavy rain is pouring down on the campsite");
    PrintText("Mud entrenches you");
    PrintText("You see light coming from the commanders tent");
    PrintText("You decide to sneak up and investigate");
    Enter();
    PrintText("As you begin moving towards the tent you see it");
    PrintText("Monte Cassino");
    PrintText("Sitting high on a mountain in the far distance");
    PrintText("Once a great medieval landmark now a fortress for Nazism in the mediterranean");
    PrintText("This night an attack on this fortress is to take place");
    Enter();
    PrintText("As you approach you hear General Soprano and the commander discussing the plan of attack");
    PrintText("As if his sixth sense knew you where there General Soprano reaches out and pulls you into the tent");
    PrintText("\n|General Soprano| WHAT DO YOU THINK YOU ARE DOING PRIVATE!?");

    int Responce = Dialogue("I wAs JuSt WaLkInG bY", "I was sneaking up on you", "I brought tea??");

    switch (Responce)
    {
    case 1:
        PrintText("|General Soprano| HMMM WHATEVER YOU SAY PRIVATE");
        break;
    case 2:
        PrintText("|General Soprano| IF THAT WAS WHAT YOU WOULD CALL STEALTH IM SCARED FOR THIS ARMY");
        break;
    case 3:
        PrintText("|General Soprano| EVEN IF I DID BELIEVE THAT YOUR TEA SUCKS");
        break;
    }

    PrintText("\n|General Soprano| ANYWAY PRIVATE YOU'RE HERE NOW SO I SUPPOSE WE WILL SHOW YOU WHAT WE'VE COME UP WITH");
    Enter();
    PrintText("More rain bashes down creating pools of water throughout the camp");
    PrintText("\n|Commander| LATER THIS NIGHT WE WILL LAUNCH OUR ATTACK ON MONTE CASSINO");
    PrintText("|Commander| WE WILL SPLIT OUR FORCES, THE MAIN FORCE WILL ATTACK WITH A BRUTE FORCE ASSUALT");
    PrintText("|Commander| A MUCH SMALLER SECONDARY DIVISION WILL GO AROUND THE MOUNTAINS AND ATTACK THE FORTRESS FROM ITS REAR BASEMENT ENTRANCE");
    PrintText("|General Soprano| I'LL LEAVE THIS DECISION UP TO YOU PRIVATE");
    Enter();
    PrintText("In [Bella Ciao] important decisions are marked as such:");
    PrintText("*{IMPORTANT}*");
    PrintText("Decisions marked with this WILL effect the outcome of your story");
    PrintText("This is not to say that other decisions wont leave an impact");
    Enter();
    PrintText("|General Soprano| SO WHAT WILL IT BE PRIVATE?");
    PrintText("*{IMPORTANT}*");
    PrintText("[WHILE THERE IS A SHORT DIALOUGE SECTION VIA ROUTE 2 I HIGHLY RECOMMEND YOU STICK WIHT ROUTE 1 FOR NOW]");
    Responce = Dialogue("I'll join the main force on the battlefield with a brute force attack", "I'll use my ability to sneak and attack from the rear", "I want you to decide general (Random)");

    srand(time(NULL));
    int number = rand() % 2;

    switch (Responce)
    {
    case 1:
        PrintText("|General Soprano| THAT'S VERY BRAVE OF YOU PRIVATE");
        Player.MajorDecisions.MajorDecision1 = 1;
        break;
    case 2:
        PrintText("|General Soprano| YOU MIGHT WANT TO GET BETTER AT SNEAKING UP ON PEOPLE BUT I TRUST YOU PRIVATE");
        Player.MajorDecisions.MajorDecision1 = 2;
        break;
    case 3:
        srand(time(NULL));
        if (number == 0)
        {
            PrintText("|General Soprano| BRUTE ASSUALT IT IS THEN");
            Player.MajorDecisions.MajorDecision1 = 1;
        }
        if (number == 1)
        {
            PrintText("|General Soprano| YOU MIGHT WANT TO GET BETTER AT SNEAKING, YOU'LL BE ATTACKING FROM THE REAR IN THAT CASE");
            Player.MajorDecisions.MajorDecision1 = 2;
        }
        break;
    }

    PrintText("|Commander| YOU MUST LEAVE US NOW PRIVATE");
    PrintText("|Commander| GO TO THE MESS TENT AND GET YOURSELF SOME FOOD");
    PrintText("|Commander| IT'S GOING TO BE A LONG NIGHT");
    Enter();
    PrintText("General Soprano shoves you out of the tent");
    PrintText("Your feet sink into the deep mud and you collapse into it");
    PrintText("You find you way to the mess tent, you see two other soidlers from your regiment already sat down");
    Enter();
    PrintText("|Luca| Woahhh there private! have you been beach boarding in the mud!?");
    PrintText("|Vincent| You are an absolute mess");
    Responce = Dialogue("Yeah alright, alright i get it", "I was beach boarding actually", "Ermmm...");

    switch (Responce)
    {
    case 1:
        PrintText("|Vincent| The only thing you need to get is some food you haven't eaten for hours");
        break;
    case 2:
        PrintText("|Vincent| Alright children settle down, private go get some food you haven't eaten for hours");
        break;
    case 3:
        PrintText("|Vincent| Alright children settle down, private go get some food you haven't eaten for hours");
        break;
    }

    Enter();
    PrintText("You walk over to the counter where they are serving food");
    PrintText("|Chef| we've got slop, slop and some more slop");
    Responce = Dialogue("I'll take some slop please", "Has to be better than the mouth full of mud a just had", "got anything else?");

    switch (Responce)
    {
    case 1:
        PrintText("|Chef| Here you go");
        break;
    case 2:
        PrintText("|Chef| Probably not by alot");
        break;
    case 3:
        PrintText("|Chef| Do you wanna eat or not?");
        break;
    }

    PrintText("You take the 'food' and walk back to Luca and Vincent");
    Enter();
    PrintText("|Luca| So where have you been?");
    Responce = Dialogue("I was speaking with the commander", "I was bringing the general some tea", "I was eavesdropping on the commander and the general");

    switch (Responce)
    {
    case 1:
        PrintText("|Vincent| Anything intresting?");
        PrintText("|Luca| Yeah do tell");
        break;
    case 2:
        PrintText("|Vincent| Your tea sucks");
        PrintText("|Vincent| Did they say anything intresting");
        break;
    case 3:
        PrintText("|Vincent| That was stupid, were you caught?");
        PrintText("|Luca| Hear anything intresting");
        break;
    }

    if (Player.MajorDecisions.MajorDecision1 == "1")
    {
        Responce = Dialogue("We are launching a brute force attack tonight", "We're all probably going to die", "Somthing about an assualt on Monte Cassino");

        switch (Responce)
        {
        case 1:
            PrintText("|Vincent| Sounds wonderful");
            break;
        case 2:
            PrintText("|Vincent| I already knew that");
            PrintText("|Vincent| I suppose we should prepare our selves");
            break;
        case 3:
            PrintText("|Vincent| Brilliant");
            PrintText("|Vincent| I suppose we should prepare our selves in that case");
            break;
        }
    }

    if (Player.MajorDecisions.MajorDecision1 == "2")
    {
        Responce = Dialogue("Us three and the General are going to sneak behind Monte Cassino and attack from the rear", "We're all probably going to die", "We are going separate from the main brute force attack and attacking from the flank");

        switch (Responce)
        {
        case 1:
            PrintText("|Vincent| Better than attacking from the front");
            PrintText("|Luca| Ugghhh does the general have to come");
            break;
        case 2:
            PrintText("|Vincent| I already knew that");
            PrintText("|Vincent| I suppose we should prepare our selves");
            break;
        case 3:
            PrintText("|Vincent| Better than attacking from the front");
            break;
        }
    }

    PrintText("You finish your 'food' when the General enters the mess tent");
    PrintText("|General Soprano| I WANT EVERYONE OUT IN 5 MINUTES");
    Enter();
    Chapter2();
}

void Tutorial() //Tutorial
{
    system("CLS");
    std::string input = "";

    PrintText("1st January 1944");
    PrintText("You are a member of the Resistenza italiana (The Italian resistance movement)");
    PrintText("Your training begins");

    std::cin.clear();
    std::cin.ignore(1945, '\n');
    Enter();


    while (true)
    {
        PrintText("|Sargent Banes|: ATTENTION!!!");
        PrintText("|Sargent Banes|: TODAY IS RIFLE TRAINING");
        PrintText("|Sargent Banes|: BEGIN BY EQUIPPING YOUR RIFLE");
        PrintText("Press [i] to open inventory");
        std::cin.clear();
        std::cin >> input;
        InventoryInput(input, false);
        PrintText("Press [1] to equip the rifle");
        std::cin >> input;

        while (input != "1" || !std::cin)
        {
            std::cin.clear();
            std::cin.ignore(1945, '\n');
            std::cout << "Press [1] to equip the rifle" << std::endl;
            std::cin >> input;
            printf("\33[2K\r");
            printf("\033[A\r");
            printf("\033[A\r");
        }

        PrintText("|Sargent Banes|: NOW AIM AT THE TARGET AND PULL THE TRIGGER");
        PrintText("In [Bella Ciao] shooting accuracy works by chance");
        PrintText("Enter 1, 2 or 3 one of these will hit the target and the other two will miss");
        PrintText("1: X\n2: X\n3: X");

        srand(time(NULL));
        int number = rand() & 2 + 1;
        std::cin >> input;
        inputChecker123(input, false);
        PrintText("BANG...");
        int result = std::stoi(input);

        if (result == number)
        {
            PrintText("|Sargent Banes|: NICE SHOT CADET YOU HIT THE TARGET");
        }

        if (result != number)
        {
            PrintText("|Sargent Banes|: UNLUCKY BETTER LOOK NEXT TIME CADET");
        }

        PrintText("Would you like to restart rifle training? Y/N");
        std::cin >> input;
        input = inputCheckerYN(input);

        if (input == "Y" || input == "y")
        {
            system("CLS");
        }

        if (input == "N" || input == "n")
        {
            break;
        }
    }

    while (true)
    {
        system("CLS");
        int result;

        PrintText("|Sargent Banes|: WE WILL NOW MOVE FORWARDS WITH GRENADES");
        addToInventory("Grenade");
        PrintText("Press [i] to open your inventory");
        std::cin >> input;
        InventoryInput(input, false);
        PrintText("Press [2] to equip the Grenade");
        std::cin >> input;

        while (input != "2" || !std::cin)
        {
            std::cin.clear();
            std::cin.ignore(1945, '\n');
            std::cout << "Press [2] to equip the Grenade" << std::endl;
            std::cin >> input;
            printf("\33[2K\r");
            printf("\033[A\r");
            printf("\033[A\r");
        }

        PrintText("|Sargent Banes|: NOW THROW THE GRENADE AT THE TARGET");
        PrintText("In [Bella Ciao] Grenades work on a timer");
        PrintText("This timer can be from 5 to 7 seconds long");
        PrintText("You can not see this timer");
        PrintText("The later you throw the grenade the more likely it is to successfully neutralise your target");
        PrintText("Don't let the timer run out");
        result = Grenade();

        if (result == 0)
        {
            PrintText("You let the timer run out!");
            PrintText("If this were a real grenade you would be dead");
        }

        if (result == 1)
        {
            PrintText("Bang on, you released the grenade at the right moment and neutralised the target");
        }

        if (result == 2)
        {
            PrintText("You relased the grenade too early and failed to neutralise the target");
            PrintText("Not to worry atleast you still have all your limbs attached together");
        }

        PrintText("Would you like to restart grenade training? Y/N");
        std::cin >> input;
        input = inputCheckerYN(input);

        if (input == "Y" || input == "y")
        {
            system("CLS");
            result = NULL;
        }

        if (input == "N" || input == "n")
        {
            break;
        }
    }

    while (true)
    {
        system("CLS");
        PrintText("|Sargent Banes|: IN THE BATTLEFIELD YOU MAY STUMBLE ACROSS LANDMINES");
        PrintText("|Sargent Banes|: HOWEVER DEACTIVATING THEN IS EASY, ALL YOU NEED TO DO IS INPUT THE CORRECT PASSKEY");
        PrintText("In [Bella Ciao] Landmines work be giving you a 7 letter word");
        PrintText("The word will then disappear and you'll need to input a letter in a specific position in the word");

        std::cin.clear();
        std::cin.ignore(1945, '\n');
        Enter();

        std::cin.clear();

        srand(time(NULL));
        int number = (rand() % 10);

        std::string Password = GameSettings.LM_Codes[number];

        std::cout << "YOU HAVE STOOD ON A LAND MINE" << endl;
        std::cout << "The deactivation code will show in: " << endl;

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

        std::cout << ("What was character " + std::to_string(number2 + 1) + " of the deactivation code");
        Sleep(2000);
        std::cin.clear();

        bool Exploded = false;
        HANDLE handle = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
        for (int i = 5; i >= 0 && !GameConditions.stop; i--)
        {
            std::cout << i;
            Sleep(1000);
            printf("\33[2K\r");
            if (i == 0)
            {
                GameConditions.stop = false;
                GameSettings.LM_Password = NULL;
                PrintText("|Sargent Banes|: IF THIS WAS A REAL LANDMINE YOU'D BE DEAD");
                Exploded = true;
            }
        }
        if (Exploded == false)
        {
            std::cout << "Success" << endl;
            PrintText("|Sargent Banes|: GOOD WORK PRIVATE");
            GameConditions.stop = false;
            GameSettings.LM_Password = NULL;
        }
        PrintText("Would you like to restart landmine training? Y/N");
        std::cin >> input;
        input = inputCheckerYN(input);
        if (input == "Y" || input == "y")
        {
            system("CLS");
        }

        if (input == "N" || input == "n")
        {
            break;
        }

    }

    while (true)
    {
        system("CLS");
        PrintText("|Sargent Banes|: BEING ABLE TO DO YOUR OWN FIRST AID WILL SAVE YOU IN THE BATTLEFIELD");
        PrintText("|Sargent Banes|: DODGE THIS PRIVATE");
        PrintText("BANG...");

        Sleep(500);
        std::cin.clear();

        PrintText("*YOU HAVE BEEN SHOT*");
        PrintText("In [Bella Ciao] you can be hit twice before dying, once you'll be in an injured state");
        PrintText("In this injured state you can use a medkit to take your self out of the injured state");
        PrintText("But if you are hit twice without using a medkit you will die");
        PrintText("Press [i]");
        std::cin >> input;
        addToInventory("Medkit");
        InventoryInput(input, false);
        PrintText("Press [2] to use the Medkit");
        std::cin >> input;

        while (input != "2" || !std::cin)
        {
            std::cin.clear();
            std::cin.ignore(1945, '\n');
            std::cout << "Press [2] to use the Medkit" << std::endl;
            std::cin >> input;
            printf("\33[2K\r");
            printf("\033[A\r");
            printf("\033[A\r");
        }

        PrintText("You have healed your wound");
        RemoveFromInventory("Medkit");
        PrintText("Would you like to restart medkit training? Y/N");
        std::cin >> input;
        input = inputCheckerYN(input);
        if (input == "Y" || input == "y")
        {
            system("CLS");
        }

        if (input == "N" || input == "n")
        {
            break;
        }
    }

    /*  while (true)
      {
          system("CLS");
          PrintText("|Sargent Banes|: MOVING LIGHT IS A KEY FACTOR TO AVOIDING THE ENEMY");
          PrintText("|Sargent Banes|: WE WILL NOW LEARN HOW TO MANAGE WHAT YOU ARE CARRYING");
          PrintText("In [Bella Ciao] you can open your inventory at any interaction point by pressing [i]");
          PrintText("Press [i] and select the teddy bear, when selected drop the bear and press [i] to close the inventory");
          addToInventory("Teddy bear");
          std::cin.clear();
          std::cin.ignore(1945, '\n');
          std::cin >> input;
          InventoryInput(input, true);

          for (int i = 0; i < GameSettings.InventorySize; i++)
          {
              if (Player.Inventory[i] == "Teddy bear")
              {
                  PrintText("|Sargent Banes|: IF YOU DON'T HAVE THE HEART TO DROP A TEDDY BEAR YOU'LL BE NO USE IN THE BATTLEFIELD");
              }
          }

          PrintText("|Sargent Banes|: NOW EQUIP YOUR RIFLE AGAIN");
          PrintText("Press [i] and select the rifle, equip it and press [i] again to close the inventory");
          std::cin >> input;
          InventoryInput(input, true);
          PrintText("Would you like to restart inventory training? Y/N");
          std::cin >> input;
          inputCheckerYN(input);

          if (input == "Y" || input == "y")
          {
              system("CLS");
              RemoveFromInventory("Teddy bear");
          }

          if (input == "N" || input == "n")
          {
              break;
          }
      }
      */
    while (true)
    {
        system("CLS");
        PrintText("|Sargent Banes|: FINALLY, IN THE BATTLEFIELD YOU MAY FIND SUPPLY CRATES, THESE WILL ALLOW YOU TO RESTOCK ON GRENADES, WEAPON ATTACHMENTS AND OTHER SPECIAL ITEMS");
        PrintText("|Sargent Banes|: ALL YOU NEED TO DO IS LEARN HOW TO OPEN THEM");
        PrintText("In [Bella Ciao] you may come across supply crates at any location randomly");
        PrintText("You can choose to open them or leave them");
        PrintText("But remember you only have a limited inventory space");
        PrintText("Here is a supply crate now...");
        Enter();
        SupplyCrate("Nothing");
        PrintText("Would you like to restart supply crate training? Y/N");
        std::cin >> input;
        input = inputCheckerYN(input);

        if (input == "Y" || input == "y")
        {
            system("CLS");
        }

        if (input == "N" || input == "n")
        {
            break;
        }
    }

    PrintText("|Sargent Banes|: WELL DONE SOILDER YOU HAVE COMPLETED BASIC TRAINING AND ARE NOW READY TO FIGHT FOR THE RESISTENZA ITALIANA");
    Enter();

    // Other tutorials if needed
    Chapter1();
}

int main()
{
    while (true)
    {
        title();
    }

}



//-Daniel Johnson