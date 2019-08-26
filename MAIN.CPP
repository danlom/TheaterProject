/* Sebastian Betancourt && Daniel Lopez
 *
 * COP 1334 C++
 *
 * Theater Seating Group Project Pg 454
 *
 * Prof. Lopez
*/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int ARRAY_SIZE = 15;
const int ARRAY_SUBSCRIPT = 30;

//PROTOTYPES

double menu();
void loadPrices(double []);
void seatGuide();
void displaySeats(char [ARRAY_SIZE][ARRAY_SUBSCRIPT]);
void seatManagement(char [ARRAY_SIZE][ARRAY_SUBSCRIPT], double [], int &);
void sendDataMenuChoice(char [ARRAY_SIZE][ARRAY_SUBSCRIPT], int &);
void loadDataFromAnExternalFile(int &, double[]);
int readTotalPrice();
void test(char arrayName[ARRAY_SIZE][ARRAY_SUBSCRIPT], double rowPrice[], int &totalCount);

int main()
{

    char seats[ARRAY_SIZE][ARRAY_SUBSCRIPT];
    char userInput;
    double loadArrData[ARRAY_SIZE];
    int totalCount = 0;

    do
    {
        double userAnswer = menu();

        if(userAnswer == 1)
        {
            loadPrices(loadArrData); //This function loads the prices from an external file
            seatGuide(); // This function shows the sitting chart of the theater
            displaySeats(seats); // This function intakes the seat the user wishes to purchase and updates the sitting chart
            cout << endl;
            seatManagement(seats, loadArrData, totalCount); // This function checks for input validation and keeps the total of all seats
            sendDataMenuChoice(seats, totalCount);// This function sends the data of the program to external files to keep the progress save

            cout << "Do you want to run the program again (Y/N): ";
            cin >> userInput;
            cout << string(100, '\n');
        }

        else if(userAnswer == 2)
        {
             loadPrices(loadArrData);
            loadDataFromAnExternalFile(totalCount, loadArrData); // This function is going to load any saved progress within the external files done before to the program

            cout << "Do you want to run the program again (Y/N): ";
            cin >> userInput;
            cout << string(100, '\n');
        }

        else if(userAnswer == 3)
        {
            cout << "Thank You Professor Lopez for teaching us C++";
        }

    }while(userInput == 'y' || userInput == 'Y');

    return 0;
}

//BEGINNING MENU, Lets the user pick the option he wants to execute
double menu()
{
    int userMenuInput;

    cout << "------------MENU------------" << endl;
    cout << "1. Add Seats and Display Data" << endl;
    cout << "2. Load an External Theater Seating" << endl;
    cout << "3. Exit" << endl;
    cout << ">> ";
    cin >> userMenuInput;
    cout << endl;

    return userMenuInput;
}


//LOAD THE IFSTREAM PRICE FILE AND STORE IT IN AN ARRAY
void loadPrices(double array[ARRAY_SIZE])
{

    string bringData;

    cout << "\n Enter the row price file: ";
    cin  >> bringData;
    bringData += ".txt";

    ifstream bringDataz;
    bringDataz.open(bringData.c_str());
 // opening the external file for prices
                                    // Prof. Lopez you have to change the path in order to load the external file!!!
    int counting = 0;
    int counting2 = 15;

    while(counting < counting2 && bringDataz >> array[counting])
    {
        counting++;
    }

    bringDataz.close();
}


//SEAT GUIDE FORMAT, this is a guide for the user how to insert the correct seating number
void seatGuide()
{
    cout << setw(26) << "ADD" << endl;
    cout << setw(25) << "|" << endl;
    cout << setw(30) << "-----------" << endl;
    cout << setw(20) << "1" << setw(10) << "2" << endl;
    cout << setw(20) << "|" << setw(10) << "|" << endl;
    cout << setw(20) << "|" << setw(10) << "|" << endl;
    cout << setw(40) << "123456789012345678901234567890" << endl;
}


//SET AND DISPLAY SEATS
void displaySeats(char seats[][ARRAY_SUBSCRIPT])
{

    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        for (int b = 0; b < ARRAY_SUBSCRIPT; b++)
        {
            seats[i][b] = '#';
        }
    }

    for(int c = 0; c < ARRAY_SIZE; c++)
    {

        if(c < 9)
        {
            cout << "Row " << c + 1 << setw(6);
        }
        else
        {
            cout << "Row " << c + 1 << setw(5);
        }

        for (int d = 0; d < ARRAY_SUBSCRIPT; d++)
        {
            cout << seats[c][d];
        }
        cout << endl;
    }
}


//CHANGE THE SEAT DISPLAY(AVAILABLE - NOT-AVAILABLE) AND UPDATE THE USER TOTAL PRICE
void seatManagement(char arrayName[ARRAY_SIZE][ARRAY_SUBSCRIPT], double rowPrice[], int &totalCount)
{
    //VARIABLES
    int userRowInput, userColumnInput, rowModifier, columnModifier, miniMenu;
    int counter = 0;
    int soldSeats = 0;
    int availableSeats = 0;
    int rowSeatAvailability = 0;
    char userAddSeat;

    do
    {
        cout << "Enter the seat you want to reserve -(type the row # first and followed by a space then the column # ex: 2 2): ";
        cin >> userRowInput >> userColumnInput;
        counter += rowPrice[userRowInput - 1];
        cout << endl;

        rowModifier = userRowInput - 1;
        columnModifier = userColumnInput - 1;


        if(userRowInput > 0 && userRowInput < 16 && userColumnInput > 0 && userColumnInput < 31) // Seat Input Validation
        {

            if (arrayName[rowModifier][columnModifier] == '#')
            {
                arrayName[rowModifier][columnModifier] = '*';
                seatGuide();

                for (int c = 0; c < ARRAY_SIZE; c++) {
                    if (c < 9)
                    {
                        cout << "Row " << c + 1 << setw(6);
                    } else {
                        cout << "Row " << c + 1 << setw(5);
                    }

                    for (int d = 0; d < ARRAY_SUBSCRIPT; d++)
                    {
                        cout << arrayName[c][d];
                    }
                    cout << endl;
                }

                counter += rowPrice[counter]; // Seat Price Counter

                cout << endl;
                // The total ticket price works but for Mac and Ubunut.

                cout << "The total of all your tickets is: $" << counter << endl;
                cout << endl;

                cout << "Do you want to add another seat (Y/N):";
                cin >> userAddSeat;

            }
            else if (arrayName[rowModifier][columnModifier] == '*')
            {
                cout << "sorry, that seat is already taken!" << endl;
                continue;
            }
        }
        else
        {
            cout << "You did not type a correct seat number! " << endl;
            userAddSeat = 'Y';
            continue;
        }
    }while(userAddSeat == 'y' || userAddSeat == 'Y');


    //User Option to add another seat
    if(userAddSeat == 'n' || userAddSeat == 'N')
    {
        cout << endl;
        cout << "What would you like to do next:" << endl;
        cout << "1. See how many seats have been sold\n";
        cout << "2. See how many seats are available in each row\n";
        cout << "3. See how many seats are available in the entire auditorium\n\n";
        cout << "Enter your answer: ";
        cin >> miniMenu;


        //Litle Menu for the user to see
        //1.How many seats has been sold
        //2.Display Seats that are available and not available in each row
        //3.Display how many seats are left in the entire auditorium

        switch(miniMenu)
        {
            case 1:

                for(int i = 0; i < ARRAY_SIZE; i++)
                {
                    for (int j = 0; j < ARRAY_SUBSCRIPT; j++)
                    {
                        if (arrayName[i][j] == '*')
                        {
                            soldSeats += 1;
                        }
                    }
                }
                cout << "There are " << soldSeats << " seats sold\n\n";
                break;

            case 2:

                for(int z = 0; z < ARRAY_SIZE; z++)
                {
                    if(z < 9)
                    {
                        cout << "In Row " << setw(2) << z + 1 << " there are ";
                    }
                    else
                    {
                        cout << "In Row " << z + 1 << " there are ";
                    }

                    for (int g = 0; g < ARRAY_SUBSCRIPT; g++)
                    {
                        if(arrayName[z][g] == '#')
                        {
                            rowSeatAvailability += 1;
                        }
                    }
                    cout << rowSeatAvailability;
                    cout << endl;
                    rowSeatAvailability = 0;
                }
                break;

            case 3:

                for (int e = 0; e < ARRAY_SIZE; e++)
                {
                    for (int f = 0; f < ARRAY_SUBSCRIPT; f++)
                    {
                        if(arrayName[e][f] == '#')
                        {
                            availableSeats += 1;
                        }
                    }
                }
                cout << "There are " << availableSeats << " available\n\n";
                break;
        }


    }

    totalCount = counter; // Save total for the first menu option
}

// This function is use to read the total price stored in the external file called TotalPrice.txt if the user wishes to
// saved progress
int readTotalPrice()
{
    int totalPrice = 0;
    ifstream readTotalPricez;

    string readTotalPrice ;

    cout << "\n Enter the total price file name: ";
    cin  >> readTotalPrice ;
    readTotalPrice  += ".txt";

    readTotalPricez.open(readTotalPrice .c_str());

           // Prof. Lopez you have to change the path in order to load the external file!!!

    readTotalPricez >> totalPrice;
    readTotalPricez.close();

    return totalPrice;
}

// This function is use to read the seating chart from the external file if the user wishes to continue with the previous progress
void loadFileSeating(char arrayName[ARRAY_SIZE][ARRAY_SUBSCRIPT], double rowPrice[], int &totalCount)
{
    //VARIABLES
    int userRowInput, userColumnInput, rowModifier, columnModifier, miniMenu;
    int priceCounter = readTotalPrice();
    int priceCounter2 = 0;
    int soldSeats = 0;
    int availableSeats = 0;
    int rowSeatAvailability = 0;
    char userAddSeat;

    do
    {
        cout << "Enter the seat you want to reserve - (type the row # fist and followed by column #): ";
        cin >> userRowInput >> userColumnInput;
        cout << endl;

        rowModifier = userRowInput - 1;
        columnModifier = userColumnInput - 1;

        if(userRowInput > 0 && userRowInput < 16 && userColumnInput > 0 && userColumnInput < 31) // Seat Input Validation
        {

            if (arrayName[rowModifier][columnModifier] == '#')
            {
                arrayName[rowModifier][columnModifier] = '*';
                seatGuide();

                for (int c = 0; c < ARRAY_SIZE; c++)
                {
                    if (c < 9) {
                        cout << "Row " << c + 1 << setw(6);
                    } else {
                        cout << "Row " << c + 1 << setw(5);
                    }

                    for (int d = 0; d < ARRAY_SUBSCRIPT; d++)
                    {
                        cout << arrayName[c][d];
                    }
                    cout << endl;
                }

                priceCounter += rowPrice[priceCounter2];  //Price Counter

                cout << endl;
                cout << "The total of all your tickets is: $" << priceCounter << endl;
                cout << endl;

                cout << "Do you want to add another seat (Y/N):";
                cin >> userAddSeat;

            }
            else if (arrayName[rowModifier][columnModifier] == '*')
            {
                cout << "sorry, that seat is already taken!" << endl;
                continue;
            }
        }
        else
        {
            cout << "You did not type a correct seat number! " << endl;
            userAddSeat = 'Y';
            continue;
        }
    }while(userAddSeat == 'y' || userAddSeat == 'Y');


    //////////////////////////////////////////////////////////////////////////////////////////
    if(userAddSeat == 'n' || userAddSeat == 'N')
    {
        cout << endl;
        cout << "What would you like to do next:" << endl;
        cout << "1. See how many seats have been sold\n";
        cout << "2. See how many seats are available in each row\n";
        cout << "3. See how many seats are available in the entire auditorium\n\n";
        cout << "Enter your answer: ";
        cin >> miniMenu;


        //Litle Menu for the user to see
        //1.How many seats has been sold
        //2.Display Seats that are available and not available in each row
        //3.Display how many seats are left in the entire auditorium

        switch(miniMenu)
        {

            case 1:

                for(int i = 0; i < ARRAY_SIZE; i++)
                {
                    for (int j = 0; j < ARRAY_SUBSCRIPT; j++)
                    {
                        if (arrayName[i][j] == '*')
                        {
                            soldSeats += 1;
                        }
                    }
                }
                cout << "There are " << soldSeats << " seats sold\n\n";
                break;

            case 2:

                for(int z = 0; z < ARRAY_SIZE; z++)
                {
                    if(z < 9)
                    {
                        cout << "In Row " << setw(2) << z + 1 << " there are ";
                    }
                    else
                    {
                        cout << "In Row " << z + 1 << " there are ";
                    }

                    for (int g = 0; g < ARRAY_SUBSCRIPT; g++)
                    {
                        if(arrayName[z][g] == '#')
                        {
                            rowSeatAvailability += 1;
                        }
                    }
                    cout << rowSeatAvailability;
                    cout << endl;
                    rowSeatAvailability = 0;
                }
                break;

            case 3:

                for (int e = 0; e < ARRAY_SIZE; e++)
                {
                    for (int f = 0; f < ARRAY_SUBSCRIPT; f++)
                    {
                        if(arrayName[e][f] == '#')
                        {
                            availableSeats += 1;
                        }
                    }
                }
                cout << "There are " << availableSeats << " available\n\n";
                break;
        }


    }

    totalCount = priceCounter;  //Save total price for the second menu option
}

// This function is use if the user wishes to update the saved information found within the external file of the program
void sendDataMenuChoice(char seats[][ARRAY_SUBSCRIPT], int &totalCount)
{
    char user_Answer2;

    cout << endl;
    cout << "Do you want to save the file [Y/n]:";
    cin >> user_Answer2;

    if(user_Answer2 == 'Y' || user_Answer2 == 'y')
    {
        ofstream senddataz;

         string senddata ;

            cout << "\nEnter file name: ";
            cin  >> senddata ;
        senddata  += ".txt";

        senddataz.open(senddata .c_str());
        //senddata.open("/home/danielglm/Desktop/v3/EndSemesterProject/seats.txt");
        //senddata.open("/Users/sebastianbetancourt/CLionProjects/FinalProject/cmake-build-debug/seats.txt");
                   // Prof. Lopez you have to change the path in order to load the external file!!!


        for(int aa = 0; aa < 15 ; aa++)
        {
            for (int a = 0; a < 30; a++)
            {
                senddataz << seats[aa][a];
            }
            senddataz << endl;
        }
        senddataz.close();

        ofstream sendPrice;

        //sendPrice.open("/home/danielglm/Desktop/v3/EndSemesterProject/TotalPrice.txt");
        //sendPrice.open("/Users/sebastianbetancourt/CLionProjects/FinalProject/cmake-build-debug/TotalPrice.txt");
                 // Prof. Lopez you have to change the path in order to load the external file!!!

        sendPrice << totalCount;
        sendPrice.close();
    }

}

// This function is use if the user wishes to use the data saved from before as soon as the program is launched
void loadDataFromAnExternalFile(int &totalCount, double rowPrice[])
{
    char fileData[450];
    char seatFileData[ARRAY_SIZE][ARRAY_SUBSCRIPT];
    double prices[ARRAY_SIZE];
    int counting = 0;
    int counting2 = 450;
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    int counter4 = 0;
    int counter5 = 0;
    int counter6 = 0;
    int counter7 = 0;
    int counter8 = 0;
    int counter9 = 0;
    int counter10 = 0;
    int counter11 = 0;
    int counter12 = 0;
    int counter13 = 0;
    int counter14 = 0;

    ifstream bringdata;


         string senddata ;

            cout << "\n Enter a seating chart file name: ";
            cin  >> senddata ;
            senddata  += ".txt";

    //bringdata.open("/home/danielglm/Desktop/v3/EndSemesterProject/seats.txt");
        bringdata.open(senddata .c_str());
         // Prof. Lopez you have to change the path in order to load the external file!!!

    while(counting < counting2 && bringdata >> fileData[counting])
    {
        counting++;
    }

    // This big loop is to get the seating from the array fileData[counting] and save in it on the seatFileData[][] array to have the same format as the first menu option array
    for(int el = 0 ; el < 1; el++ )
    {
        for( int a = 0; a < 30 ; a++)
        {
            seatFileData[el][a] = fileData[a];
        }

        for(int b = 30; b < 60; b++) {
            seatFileData[el + 1][counter] = fileData[b];
            counter += 1;
        }

        for(int c = 60; c < 90; c++){
            seatFileData[el + 2][counter2] = fileData[c];
            counter2 += 1 ;
        }

        for(int d = 90; d < 120; d++){
            seatFileData[el+3][counter3] = fileData[d];
            counter3 += 1 ;
        }

        for(int e = 120; e < 150; e++){
            seatFileData[el+4][counter4] = fileData[e];
            counter4 += 1 ;
        }

        for(int f = 150; f < 180; f++){
            seatFileData[el+5][counter5] = fileData[f];
            counter5 += 1 ;
        }

        for(int g = 180; g < 210; g++){
            seatFileData[el+6][counter6] = fileData[g];
            counter6 += 1 ;
        }

        for(int h = 210; h < 240; h++){
            seatFileData[el+7][counter7] = fileData[h];
            counter7 += 1 ;
        }

        for(int i = 240; i < 270; i++){
            seatFileData[el+8][counter8] = fileData[i];
            counter8 += 1 ;
        }

        for(int j = 270; j < 300; j++){
            seatFileData[el+9][counter9] = fileData[j];
            counter9 += 1 ;
        }

        for(int k = 300; k < 330; k++){
            seatFileData[el+10][counter10] = fileData[k];
            counter10 += 1 ;
        }

        for(int l = 330; l < 360; l++){
            seatFileData[el+11][counter11] = fileData[l];
            counter11 += 1 ;
        }

        for(int m = 360; m < 390; m++){
            seatFileData[el+12][counter12] = fileData[m];
            counter12 += 1 ;
        }

        for(int n = 390; n < 420; n++){
            seatFileData[el+13][counter13] = fileData[n];
            counter13 += 1 ;
        }

        for(int o = 420; o < 450; o++){
            seatFileData[el+14][counter14] = fileData[o];
            counter14 += 1 ;
        }
    }

    //loadPrices(prices);  // Load the prices stored in the file prices.
    seatGuide();        // Seat Guide

    for(int c = 0; c < ARRAY_SIZE; c++)
    {

        if(c < 9)
        {
            cout << "Row " << c + 1 << setw(6);
        }
        else
        {
            cout << "Row " << c + 1 << setw(5);
        }

        for (int d = 0; d < ARRAY_SUBSCRIPT; d++)
        {
            cout << seatFileData[c][d];
        }
        cout << endl;
    }

    test(seatFileData,rowPrice, totalCount); // Load the seating chart, add seats, and view the mini menu
    sendDataMenuChoice(seatFileData,totalCount); // Send the data to an external File
}

void test(char arrayName[ARRAY_SIZE][ARRAY_SUBSCRIPT], double rowPrice[], int &totalCount)
{
    //VARIABLES
    int userRowInput, userColumnInput, rowModifier, columnModifier, miniMenu;
    int priceCounter = readTotalPrice();
    int priceCounter2 = 0;
    int soldSeats = 0;
    int availableSeats = 0;
    int rowSeatAvailability = 0;
    char userAddSeat;
    int testVar = 0;

   //cout << "The current price is: " << priceCounter << '\n';
   //cout << rowPrice[0] << '\n';
   // testVar = readTotalPrice();
    //cout <<"HELLO HELLO end \n\n\n";

    do
    {
        cout << "Enter the seat you want to reserve - (type the row # fist and followed by column #): ";
        cin >> userRowInput >> userColumnInput;
        cout << endl;

        rowModifier = userRowInput - 1;
        columnModifier = userColumnInput - 1;

        if(userRowInput > 0 && userRowInput < 16 && userColumnInput > 0 && userColumnInput < 31) // Seat Input Validation
        {

            if (arrayName[rowModifier][columnModifier] == '#')
            {
                arrayName[rowModifier][columnModifier] = '*';
                seatGuide();

                for (int c = 0; c < ARRAY_SIZE; c++)
                {
                    if (c < 9) {
                        cout << "Row " << c + 1 << setw(6);
                    } else {
                        cout << "Row " << c + 1 << setw(5);
                    }

                    for (int d = 0; d < ARRAY_SUBSCRIPT; d++)
                    {
                        cout << arrayName[c][d];
                    }
                    cout << endl;
                }

                priceCounter += rowPrice[userRowInput - 1];  //Price Counter
                testVar += priceCounter;
                cout << endl;
                cout << "The total of all your tickets is: $" << testVar << endl;
                cout << endl;

                cout << "Do you want to add another seat (Y/N):";
                cin >> userAddSeat;

            }
            else if (arrayName[rowModifier][columnModifier] == '*')
            {
                cout << "sorry, that seat is already taken!" << endl;
                continue;
            }
        }
        else
        {
            cout << "You did not type a correct seat number! " << endl;
            userAddSeat = 'Y';
            continue;
        }
    }while(userAddSeat == 'y' || userAddSeat == 'Y');


    //////////////////////////////////////////////////////////////////////////////////////////
    if(userAddSeat == 'n' || userAddSeat == 'N')
    {
        cout << endl;
        cout << "What would you like to do next:" << endl;
        cout << "1. See how many seats have been sold\n";
        cout << "2. See how many seats are available in each row\n";
        cout << "3. See how many seats are available in the entire auditorium\n\n";
        cout << "Enter your answer: ";
        cin >> miniMenu;


        //Litle Menu for the user to see
        //1.How many seats has been sold
        //2.Display Seats that are available and not available in each row
        //3.Display how many seats are left in the entire auditorium

        switch(miniMenu)
        {

            case 1:

                for(int i = 0; i < ARRAY_SIZE; i++)
                {
                    for (int j = 0; j < ARRAY_SUBSCRIPT; j++)
                    {
                        if (arrayName[i][j] == '*')
                        {
                            soldSeats += 1;
                        }
                    }
                }
                cout << "There are " << soldSeats << " seats sold\n\n";
                break;

            case 2:

                for(int z = 0; z < ARRAY_SIZE; z++)
                {
                    if(z < 9)
                    {
                        cout << "In Row " << setw(2) << z + 1 << " there are ";
                    }
                    else
                    {
                        cout << "In Row " << z + 1 << " there are ";
                    }

                    for (int g = 0; g < ARRAY_SUBSCRIPT; g++)
                    {
                        if(arrayName[z][g] == '#')
                        {
                            rowSeatAvailability += 1;
                        }
                    }
                    cout << rowSeatAvailability;
                    cout << endl;
                    rowSeatAvailability = 0;
                }
                break;

            case 3:

                for (int e = 0; e < ARRAY_SIZE; e++)
                {
                    for (int f = 0; f < ARRAY_SUBSCRIPT; f++)
                    {
                        if(arrayName[e][f] == '#')
                        {
                            availableSeats += 1;
                        }
                    }
                }
                cout << "There are " << availableSeats << " available\n\n";
                break;
        }


    }

    totalCount = priceCounter;  //Save total price for the second menu option
}
















































