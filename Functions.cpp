
#include "Functions.hpp"

//defining functions
void logMessage(string msg) { //function to print messages
    cout << msg << endl;
}

void underline() {
    logMessage("------------------------------------------------"); //underline for neatness
}
int category(int basket) { 
    cout << "Amount of Items in Basket: " << basket << endl; //displays basket
    logMessage("Select a category:\n1. Chocolate\n2. Candy\n3. Crisps\n4. Cold Drinks"); //gives user selection of categories
    return validate(1,4); //validate answer between 1 and 4
}

int optionsMenu() { 
    logMessage("Please select one of the following numbers:"); //tells user to select a number
    logMessage("1. Add an Item\n2. Go back to menu\n3. View Order/Checkout\n4. Exit"); //gives user an option list
    return validate(1,4); //validate answer between 1 and 4
}

string addToBasket() { //adds item to basket
    logMessage("Please Select an Item Using the Codes Above... if you would like to cancel your order, press 1");
    string item; //string to store user input
    cin >> item; //gets user input
    item[0] = toupper(item[0]); //turns first character of user input into upper case
    bool play = PlaySound(TEXT("buttonBeeps.wav"), NULL, SND_SYNC); //plays audio
    return item;
}

void contents(string textfile, string stockfile, string id[5], string itemList[5], double price[5], int quantity[5]) {
    ifstream item = ifstream(textfile); // textfile user has selected through the category
    ifstream stock(stockfile); //stock file information
    int i = 0; //variable to store count

    //if item and stock file are open then
    if (item.is_open() && stock.is_open() ) { 
        while (!item.eof() && !stock.eof()) { //while item and stock file are not at the end of file then
            getline(item, id[i], '\t'); //store line from item into ID array until tab space
            getline(item, itemList[i], '\t'); //store line from item into itemList array until tab space
            item >> price[i]; //gains data from item and stores in price array
            item.ignore(1, '\t'); //ignore 
            stock >> quantity[i]; //gain data from stock and store it in the quantity 
            i++; //increment by one
        }
        //close files
        item.close(); 
        stock.close();
    } else {
        cout << "Could not access file" << endl; //error message
    }
}

void printContent(string id[5], string itemList[5], double price[5], int quantity[5]) {
    for (int i = 0; i < 5; i++) { //for loop that repeats 5 times
        cout << fixed << showpoint; 
        cout << setprecision(2); //sets two decimal places
        cout << id[i] << "\t " << itemList[i] << "\t " << char(156) << price[i] << "\t  Stock x" << quantity[i] << endl; //lists the items
        underline(); //underline for neatness
        Sleep(200); //delay printing every 200ms
    }
}

char itemSelect(string id[5], string itemList[5], double price[5], int quantity[5]) {
    bool isValid = false; //stores if item selected is valid
    do{
        string selectedItem = addToBasket(); //stores the item user inputted into selectedItem
        if(selectedItem == "1"){ //if they inputted 1
            return 'c'; //return c and cancel order
        } 
        else { //ELSE
            for (int i = 0; i < 5; i++) { //for loop 5 times
                if (selectedItem == id[i]) { //if selected item is equal to any of the IDs that were stored in the array

                    if (quantity[i] > 0) { //if stock is more than 0
                        quantity[i]--; // remove one from stock

                        cout << "You have ordered: " << itemList[i] << endl; //output users order

                        //Writing orders
                        ofstream orders("Orders.txt", ios::app); //file for ORDERS

                        if (orders.is_open()) { //if order file is open
                            isValid = true; //then the selected item is valid
                            orders << id[i] << ", " << itemList[i] << ", " << price[i] << endl; //writes the selected order into textfile
                            orders.close(); //closes file
                            break;
                        }
                    }
                    else {
                        logMessage("Out of stock!"); //otherwise out of stock
                        break;
                    }
                }
                if (i == 4) {
                    logMessage("Invalid Code, Try again."); //or invalid code
                }
                
            }
        }
    } while (!isValid); //only loop while item is not valid
        
    return 'p'; //return p for purchase
}

void Bye() {
    Sleep(1000); //delay by 1000ms
    logMessage("Thank you for shopping with us!"); //thank you & goodbye message
}

void clear(string textfile) { //clear function
    ofstream clear(textfile,  ofstream::trunc); //clear what was previously in the file
}

char addMoreItems() { 
    char answer = 0; //variable to store input
    do{
        logMessage("Would you like to add anything else to basket? (Y) Yes (N) No"); //asks for user input
        answer = validateChar(); //validates user input
    }while(answer != 'Y' && answer != 'N'  ); //repeat while answer is not equal to Y or N
    return answer; //return answer
}


int validate(int min, int max) { //function to validate int inputs
    int input; //get input
    cin >> input; //get user input
   
    while (cin.fail() || cin.peek() != '\n' || input < min || input > max) { //if user didnt enter number or did not end with enter button
        cout << "Please enter a valid number" << endl;
        cin.clear(); //clear error flag
        cin.ignore(INT_MAX, '\n'); //ignore previous input
        cin >> input; //get user input again
    }
    bool play = PlaySound(TEXT("Beep.wav"), NULL, SND_ASYNC); //plays audio
    return input; //return input
}

char validateChar() { //validates char variables
    char input;
    cin >> input; //get user input
    input = toupper(input);
    while (cin.fail() || cin.peek() != '\n' || (input != 'Y' && input != 'N')) { //if user didnt enter number or did not end with enter button
        cout << "Please enter a valid input" << endl;
        cin.clear(); //clear error flag
        cin.ignore(INT_MAX, '\n'); //ignore previous input
        cin >> input; //get user input again
        input = toupper(input);
    }
    bool play = PlaySound(TEXT("beep.wav"), NULL, SND_ASYNC); //plays audio
    return input; //return input
}
