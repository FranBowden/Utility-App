//Header files
#include "Functions.hpp"
#include "Checkout.hpp"

//main function
int main() {
    clear("Orders.txt"); //clear textfile
    system("color 0E"); //changes text colour
    logMessage("Welcome to the Vending Machine!"); //welcoming user to program
    underline(); //underline for neatness

    cout << endl; //break
    system("pause"); //Wait for user response
    
    //arrays to store data
    string itemCode[5]; //code to identify items
    string list[5]; //The list of items
    double price[5]; //the pirce of the items
    int quantity[5]; //stores the stock values
    
    //Variables
    int basket = 0; //stores how many items are in the basket
    bool repeat = false; //boolen to see if a function needs to be repeated
    int categorySelected; //users choice gets stored as a number
    int options; //stores user options
    
    do { //do while loop to select multiple items
       do{
        system("cls"); //clear console screen
        categorySelected = category(basket); //calls category function for a selection of different items
        system("cls"); //clears screen

        //switch statement for choice
            switch (categorySelected) { 
                case 1: { //if user selects 1
                    cout << "CHOCOLATE MENU\t\t\t Basket: " << basket << endl; //Prints title number of items in basket
                    logMessage("ID\t  ITEMS\t\tPRICES\t   STOCK");
                    underline(); //underline for neatness
                    contents("Chocolate.txt", "ChocolateStock.txt", itemCode, list, price, quantity); //tells program what files to read to store data from
                    break;
                }
                case 2:{ //if user selects 2
                    cout << "CANDY MENU\t\t\t Basket: " << basket << endl; 
                    logMessage("ID\t  ITEMS\t\tPRICES\t   STOCK");
                    underline();
                    contents("Candy.txt", "CandyStock.txt", itemCode, list, price, quantity); //what file it needs to gather data from
                    break;
                }
                case 3: {//if user selects 3
                    cout << "CRISPS MENU\t\t\t Basket: " << basket << endl;
                    logMessage("ID\t  ITEMS\t\tPRICES\t   STOCK");
                    underline();
                    contents("Crisps.txt", "CrispsStock.txt", itemCode, list, price, quantity); //what file it needs to gather data from
                    break;
                }
                case 4: { //if user selects 4
                    cout << "COLD DRINKS MENU\t\t\t Basket:" << basket << endl;
                    logMessage("ID\t  ITEMS\t\tPRICES\t   STOCK");
                    underline();
                    contents("Drink.txt", "DrinkStock.txt", itemCode, list, price, quantity); //what file it needs to gather data from
                    break;
                }
            }
            
            //Prints Contents for MENU
            printContent(itemCode, list, price, quantity);
           
            cout << endl; //break

            //prints options for user and stores input in options
            options = optionsMenu(); 
            
            //SWITCH STATEMENT - Depending on what number the user inputted
            switch (options) {
            case 1: //ADD ITEM TO BASKET
            { 
                 //selects the item the user would like to purchase
                char didPurchase = itemSelect(itemCode, list, price, quantity);

                if (didPurchase == 'c') { //if user cancelled purchase
                    repeat = true; //Go back to the start by repeat = true
                    break;
                }
                else { //otherwise user has added item
                    repeat = false;
                    basket++; //increase basket by one
                    break;
                }

               
            }
              case 2: { //USER RETURNS BACK TO MENU
                    system("cls"); //clear console screen
                    repeat = true; //repeat is equal to true
              }
                    break;
               case 3: {
                    //VIEWS ORDER & TAKES TO CHECKOUT
                    repeat = false; //do not repeat
                    double total = readOrderFile();
                    char answer = noOrder(total); //checks if there are items in basket, if there isnt it will ask user if they would like to buy an item
                    
                    switch(answer) {
                        case 'Y':  //if there are items and user wants to keep items then
                            repeat = true; //return to menu
                            break;
                        case 'N':
                            logMessage("Okay, Exiting Vending Machine..."); //Exit Message
                            return 0; //ends program
                    }
               }
                     break;
                case 4: { //USER WANTS TO QUIT PROGRAM
                
                    if (basket > 0) { //if basket is more than 0
                        logMessage("Are you sure you want to exit? You will not recieve your items\n(Y)Yes /(N) No"); //cout question to user
                        char answer = validateChar();  //validates answer
                        switch (answer) { 
                            case 'Y': //user wants to quit
                                break;
                            case 'N': //User does not want to quit
                                repeat = true; //Go back to menu
                                break;
                        }
                    }
                    else {
                        logMessage("Okay, Exiting Vending Machine..."); //goodbye message
                        return 0;
                    }
                }

            } 
        }while (repeat == true); //while loop that only repeats when its equal to true otherwise breaks
        
        //CHECKOUT 
        char answer = addMoreItems(); //Ask user if they want more items
    
        switch (answer) {
        case 'Y': //if yes
            repeat = true; //repeat
            break;
        case 'N': //if no
            repeat = false; //dont repeat
            orders(); // prints order
            double total = readOrderFile();
            char proceed = ready(); //is user ready to continue to checkout?

            switch (proceed) {
            case 'Y': ///if yes then continue
                repeat = false; //dont repeat anything
                system("cls"); //clear console screen
                printTotal(total); //print the total from the items user has selected
                total = charity(total); //ask user if they would like to donate to charity
                system("cls"); //clear console screen
                money(total); //calculates it and gives the change
                Bye(); //thanks user for shopping  
                break;
            case 'N':
                repeat = true;
                break;
            }
        }
    }while (repeat == true); //while loop that only repeats when its equal to true otherwise breaks

     //Stock System
    switch (categorySelected) { //based on what category from the menu they ordered
    case 1:
        stock("ChocolateStock.txt", quantity); //stock file to read data from and write over
        break;
    case 2:
        stock("CandyStock.txt", quantity);
        break;
    case 3:
        stock("CrispsStock.txt", quantity);
        break;
    case 4:
        stock("DrinkStock.txt", quantity);
        break;
    }

    return 0; //end program
}