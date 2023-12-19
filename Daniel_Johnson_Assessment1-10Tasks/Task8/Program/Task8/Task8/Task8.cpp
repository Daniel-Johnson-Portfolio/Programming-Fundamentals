#include <iostream>
#include <string> //allows the use of strings
using std::endl;
struct InventorySlot
{
    std::string item_id = "Empty";
};

const int AmountItems = 4; //total Number of items
std::string items[AmountItems] = { "Empty", "Sheild", "Potion", "Gloves" }; //String array of items

int main()
{
    std::cout << "Pre-running conditions: \nPlease specify inventory size (1 - 16)" << endl;
    int length; //Lenght of inventory (Dynamic array)
    std::cin >> length;
    while (length > 16 || length < 1 || !std::cin) //error handling
    {
        std::cout << "Invlaid input, Please specify inventory size (1 - 16)" << endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n'); //Clears input buffer
        std::cin >> length;
    }
    std::cout << "Pre-running conditions complete, \nInventory size = " << length << endl;

    InventorySlot* Inventory = new InventorySlot[length](); //Dynamically allocated array of structs

    std::cout << "Commands unlocked" << endl;

    while (true) //Program loop
    {
        std::string input = "";
        std::getline(std::cin, input);

        //completes command inputs as desired
        if (input == "show_all")
        {
            for (int i = 0; i < length; i++)
            {
                std::cout << "Item slot " << i + 1 << ": " << Inventory[i].item_id << endl;
            }
        }

        else if (input == "items")
        {
            for (int i = 0; i < AmountItems; i++)
            {
                std::cout << "Item " << i + 1 << ": " << items[i] << endl;
            }
        }

        else if (input[0] == 's' && input[1] == 'e' && input[2] == 't')
        {
            int index = (input[4] - '0') - 1;
            int item_id = input[6] - '0';

            Inventory[index].item_id = items[item_id];
        }

        else if (input[0] == 'v' && input[1] == 'i' && input[2] == 'e' && input[3] == 'w')
        {
            int index = (input[5] - '0') - 1;
            std::cout << Inventory[index].item_id << endl;
        }

        else if (input == "exit")
        {
            break;
        }

        else if (input != "")
        {
            std::cout << "command not recognised" << endl;

        }
    }
    std::cout << "Program end";
    delete[] Inventory; //Deletes inventory as to save memory
}
//-Daniel Johnson
