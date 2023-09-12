//Headers
#include "Checkout.hpp"

double readOrderFile() {
    //Arrays for storing information from textfiles
    string ID[5];
    string list[5];
    double price[5]{};

    ifstream order("Orders.txt"); //reads from Orders.txt File
    int i = 0; //index counter
    if (order.is_open()) { //if order file is open
        while (!order.eof()) { //while order is not at the end of file then
            getline(order, ID[i], ','); //store data into ID array
            getline(order, list[i], ',');  //store data into List array
            order >> price[i];  //store data into Price array
            i++; //increment by one
        }
        order.close(); //Close file
    }
    else {
        logMessage("Error"); //Otherwise Print Error
    }

    double total = 0; //total is 0
    for (int x = 0; x < i - 1; x++) { //loop
        cout << list[x] << " " << price[x] << endl; //prints items and the price
        total += price[x]; //calculates the total of items
    }
    return total;
}

void orders() { //Prints item orders that have been selected
    system("cls"); //clear console screen
    logMessage("You have ordered:"); //You have ordered
}

//prints the total
void printTotal(double total) {
    cout << "Your total: " << total << endl; //couts the total
   
}

char ready() {
    logMessage("Are you ready to proceed to checkout (Y) yes (N) No"); //Checks if user is ready to proceed to checkout
    return validateChar(); //returns validated answer
   
}

char noOrder(double total) {
    if (total == 0.00) { //total is equal to 0 then user has not bought anything
        logMessage("You have not ordered anything.\nWould you like to purchase an item? (Y) yes (N) No");
        return validateChar(); //validates answer
       
    }
    return 0;
}

double moneyAdded() {
    double money;
    logMessage("Select how much money you would like to add"); //asks user for input
    money = validateMoney(0.01); //validate money by setting min to 1p
    cout << "You have added " << char(156) << money << endl; //prints how much money user has added
    return money; 
}

double validateMoney(double min) { //function to validate user input
    double input; //get input
    cin >> input; //get user input

    while (cin.fail() || cin.peek() != '\n' || input < min) { //if user didnt enter number or did not end with enter button
        cout << "Please enter money to purchase items" << endl;
        cin.clear(); //clear error flag
        cin.ignore(INT_MAX, '\n'); //ignore previous input
        cin >> input; //get user input again
    }
    bool play = PlaySound(TEXT("Coins.wav"), NULL, SND_SYNC); //Adds coin audio 
    return input; //return input
}

void money(double total) {

    cout << "Your total: " << total << endl; //prints total
    //Arrays to store data
    string ID[5];
    string list[5];
    double price[5]{};

    ifstream order("Orders.txt");
    int i = 0; //index counter
    if (order.is_open()) { //if order file is open
        while (!order.eof()) { //while order is not at the end of file then
            getline(order, ID[i], ','); //get the code
            getline(order, list[i], ','); // get the item
            order >> price[i]; //get the price
            i++; //increment by one
        }
        order.close();
    }
    else {
        logMessage("Error"); //error message
    }

     srand(time(NULL)); //set random seed

    do {
        double money = moneyAdded(); //stores money from user
        if (money >= total) { //if money is more or equal to total
            money -= total; //get the change
            logMessage("Dispensing: "); //display dispensing message
            int random = randomBreak(); //random function
            if (random == 10) { //random change of item being jammed
                logMessage("Oh no! Your item is jammed... Oh well!");
                break;
            } //dispensing Items
            else {
                bool play = PlaySound(TEXT("dispensingItem.wav"), NULL, SND_SYNC);
                for (int x = 0; x < i - 1; x++) { //loop the amount of items user has selected
                    cout << list[x] << endl; //outputs items
                    Sleep(500); //delays 500ms
                }
                cout << "Your change " << char(156) << money << endl; //prints out change
                break;
            }
        
        }
        total -= money; //minus money off the total
        cout << "Not enough money. Please add the remaining amount: " <<  char(156) << total  << endl; //asks for more money

    } while (total > 0.00); //repeat while total is more than 0
}
    

double charity(double total) { //charity function
    char answer = 0; //answer variable 
    do{
        logMessage("Would you like to donate 10p to charity?\n(Y) Yes, (N) No");
        answer = validateChar(); //validate answer
        answer = toupper(answer); //turns answer into upper case
    
        switch (answer) { //switch statement 
            case 'Y': //in case yes
                total += 0.1; //increase total by 10p
                logMessage("Thank you for helping those in need!"); //thank you message
                break;
            case 'N': //if no then break
                break;
            default: //invalid input 
                logMessage("Not a valid response"); 
        }
           
                
    }while(answer != 'Y' && answer != 'N'); //loop if answers are not Y or N
    return total;
}

void stock(string stockFile, int quantity[5]) {
    ofstream stock(stockFile, ios::app); //Writing in stockfile
    clear(stockFile); //clears the file
    if (stock.is_open()) { //updates the file
        for (int i = 0; i < 5; i++) { //loops 5 times
            stock << quantity[i] << endl;  //stock is stored in quantity array
        }
        stock.close(); //close stock file
    }
}

int randomBreak() { //generates random number 
    return rand() % 20;; //get random number between 0 - 19;
}