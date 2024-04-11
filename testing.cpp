#include <iostream>
#include <fstream>    //file handling library
#include<sstream>     // string handling library
using namespace std;

string user_name = "Person"; //declaring password and username
string pass = "123";

bool checkLuhn(const string& cardNo) //luhn's algorithm
{
    int nDigits = cardNo.length();

    int nSum = 0, isSecond = false;
    for (int i = nDigits - 1; i >= 0; i--) {

        int d = cardNo[i] - '0';

        if (isSecond == true)
            d = d * 2;

        nSum += d / 10;
        nSum += d % 10;

        isSecond = ~isSecond; //interchanging values
    }
    return (nSum % 10 == 0);
}


class item {
public:

    string name; //creating class item with its relevant characteristics
    int quantity;
    float price;
};

int main() {
    string username;
    string password;

    bool running = true;
    while (running) { //taking input of username and passsword unless provided the correct credentials
        cout << "Enter your username: " << endl;
        cin >> username;
        cout << "Enter your password: " << endl;
        cin >> password;
        if (username == user_name && password == pass) {
            cout << "You are logged in" << endl;
            system("cls");
            running = false;
            bool shopping = true;
            while (shopping) {

                int choice;
                cout << "1.Create an entry" << endl;
                cout << "2.View an entry" << endl;
                cout << "3.Exit" << endl;
                cin >> choice;
                system("cls");
                switch (choice) {           //interface of the shop
                case 1: {
                    cout << "Create an Entry" << endl;
                    int sizeofarray = 100;
                    item array_of_items[100];
                    int total_items;
                    float total_price = 0;
                    cout << "Enter the total number of the items" << endl;
                    cin >> total_items;
                    for (int i = 0; i < total_items; i++) {
                        string i_name;
                        int n_item;
                        float i_price;
                        cout << "\nEnter the name of item" << i + 1 << ":";
                        cin >> i_name;
                        cout << "Enter number of each item:";
                        cin >> n_item;
                        cout << "Enter price per item" << i + 1 << ":";
                        cin >> i_price;
                        system("cls");
                        array_of_items[i].name = i_name;
                        array_of_items[i].quantity = n_item;
                        array_of_items[i].price = i_price;
                        total_price += i_price * n_item;
                    }
                    cout << "The total amount is " << total_price << "." << endl;
                    int payment_option;
                    cout << "Choose a payment option: \n 1. By Credit or Debit Card \n 2. By Cash" << endl;
                    cin >> payment_option;
                    switch (payment_option) {    //payment selection, will ask for card or cash
                    case 1:
                    {
                        int card;
                        cout << "Choose your card: \n 1. Debit Card \n 2. Credit Card" << endl;
                        cin >> card;
                        switch (card) {  //nested switch to ask either debit or credit card
                        case 1: {
                        restart:
                            cout << "Enter your Debit Card number" << endl;
                            string dbCard;
                            string exp;
                            string cvv;
                            cin >> dbCard;
                            bool flag = checkLuhn(dbCard);    //calling luhns algorithm
                            if (flag) {     //will work only if a card is valid
                                cout << "Enter the Expire Date of Debit Card" << endl;
                                cin >> exp;
                                cout << "Enter the CVV of Debit Card" << endl;
                                cin >> cvv;
                                cout << "Processing transaction... \n " << total_price << "PKR has been debited." << endl;
                            }
                            else {
                                cout << "Please enter a valid debit card number" << endl;
                                goto restart;
                            }
                            break;
                        }
                        case 2:
                        {
                        hello:
                            cout << "Enter your Credit card number" << endl;
                            string ccard;
                            string exp;
                            string cvv;
                            cin >> ccard;
                            bool flag = checkLuhn(ccard); //calling luhns alogrithm
                            if (flag) {
                                cout << "Enter the Expire Date of Credit Card" << endl;
                                cin >> exp;
                                cout << "Enter the CVV of Credit Card" << endl;
                                cin >> cvv;
                                cout << "Processing transaction... \n " << total_price << "PKR has been debited." << endl;
                            }
                            else {
                                cout << "Please enter a valid credit card number" << endl;
                                goto hello;
                            }
                            break;
                        }
                        }
                        break;
                    }


                    case 2: {
                        cout << "Enter the amount of cash" << endl;
                        int cash;
                        cin >> cash;
                        cout << "You will be returned " << cash - total_price << "PKR" << endl;
                        break;
                    }
                    }
                    ofstream prep("prev.txt");    //creating a file with with the prev. text. It will save all the entries.
                    string s = "";
                    for (int i = 0; i < total_items; i++) {
                        s += array_of_items[i].name;
                        s += "\t";
                        stringstream stream;    //convert other data types into string
                        stream << array_of_items[i].quantity;
                        string qty_items;
                        stream >> qty_items;
                        s += qty_items;
                        s += "\t";
                        stringstream stream1;
                        stream1 << array_of_items[i].price;
                        string item_price;
                        stream1 >> item_price;
                        s += item_price;
                        s += "\n";
                    }
                    s += "total items\t";
                    stringstream stream2;
                    stream2 << total_items;
                    string items_total;
                    stream2 >> items_total;
                    s += items_total;
                    s += "\n";
                    stringstream stream3;
                    stream3 << total_price;
                    string price_total;
                    stream3 >> price_total;
                    s += "total price:\t";
                    s += price_total;
                    prep << s;
                    prep.close();   //closing file
                    break;
                }

                case 2: {
                    string entry;
                    ifstream prep("prev.txt");
                    while (getline(prep, entry)) {  //get a whole line of text into variable entry
                        cout << entry << endl;

                    }
                }


                      break;
                case 3:
                    cout << "Exit" << endl;
                    shopping = false;   //ending loop of selection of choices namely creating an entry, previous entry and exit
                    break;
                }
            }

        }
        else {
            cout << "Your username or password is wrong" << endl;
        }
    }

}
