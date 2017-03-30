/////////////////////////////////////////////////////////////////////////////////////////////////
// This program creates a haiku by reading a file made of haiku's that are missing a noun,
// a two syllable verb, and a gerund. The program uses a random number generator to determine
// which haiku will be used, then asks the user for the missing data. Once the data has been
// input the program then prints the completed haiku and asks the user if they want to 
// do it again.
////////////////////////////////////////////////////////////////////////////////////////////////



#include <cstdlib>
#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

//constants used to keep max lengths of arrays
const int MAXCOL = 51;
const int MAXROW = 84;

//Prototypes for all functions
void readFile(ifstream& input, char[], char[][MAXCOL], int&);
void randomHaiku(int, int&);
int findAsterisk(char[]);
void changeline(char[], char[], char[]);
void getUserInput(char[], char[], char[]);
void printHaiku(char[], char[][MAXCOL], char[], int, char[], char[], char[]);
void askUser(char&);

int main(){
    ifstream input; // input stream object name
    int numHaikus;
    int hChoice=0;
    char answer = 'y';
    char haikuArray[MAXROW][MAXCOL];
    char tempArray[MAXCOL];
    char newArray[MAXCOL];
    char verb[MAXCOL];
    char noun[MAXCOL];
    char gerund[MAXCOL];
    
    
    readFile(input, tempArray, haikuArray, numHaikus);
    input.close();
    while(answer == 'y'){
    getUserInput(verb, noun, gerund);
    randomHaiku(numHaikus, hChoice);
    printHaiku(tempArray, haikuArray, newArray, hChoice, noun, verb, gerund);
    askUser(answer);
    }
    
    cout << "Thanks for Playing.";

}

/////////////////////////////////////////////////////////////////
// This function asks the user if they want to play again
/////////////////////////////////////////////////////////////////
void askUser(char& answer){
    cout << "Would you like to play again? ";
    cin >> answer;
    char temp = answer;
    answer = tolower(temp);
}


///////////////////////////////////////////////////////////////////////////////////
// This function makes sure the file exists and is not empty. Once those criteria 
// are met reads in each line of the data and copies it into a 2d array.
///////////////////////////////////////////////////////////////////////////////////
void readFile(ifstream& input, char array[], char array1 [][MAXCOL], int& i){
    char c;
    string fileName = "haikus.txt";
    input.open(fileName.c_str());
    
    if(input.fail()){
        cout << "File does not exist." << endl;
        cout << "Thanks for using this program!" << endl;
        exit(1);
    }
    
    input.get(c);
    if(input.eof()){
        cout << "The file is empty." << endl;
        cout << "Thanks for using this program!" << endl;
        exit(1);
    }
    input.putback(c);
    
    i = 0;
    input.getline(array, MAXCOL);
    while(!input.eof()){
        strcpy(array1[i], array);
        i++;
        input.getline(array, MAXCOL);
        
    }
    i = i/3;
}

//////////////////////////////////////////////////////////////////////////////////
// This function gets the noun, verb, and gerund from the user and copies it to 
// their respective arrays. The only difference is that the beginning letter of
// the gerund is capitalized because its the first word of the last line of the
// haiku.
//////////////////////////////////////////////////////////////////////////////////
void getUserInput(char verb[], char noun[], char gerund[]){
    cout << "Please enter a noun: ";
    cin >> noun;
    cout << endl;
    cout << "Please enter a two syllable verb: ";
    cin >> verb;
    cout << endl;
    cout << "Please enter a two syllable gerund: ";
    cin >> gerund;
    cout << endl;
    char temp = gerund[0];
    gerund[0] = toupper(temp);
}

////////////////////////////////////////////////////////////////
// This function chooses the haiku via random number.
////////////////////////////////////////////////////////////////
void  randomHaiku(int numHaikus, int& num){
    srand(time(NULL));
    num = ((rand() % numHaikus)*3);
}


///////////////////////////////////////////////////////////////////////////
// This function finds the asterisks within the haiku and
// returns the position of the asterisks to the changeline function.
///////////////////////////////////////////////////////////////////////////
int findAsterisk(char array[]){
    for(int i = 0; array[i] != '\0'; i++){
        if(array[i] == '*')
            return i;
    }
    return -1;
}

///////////////////////////////////////////////////////////////////////////
// This method changes arrays according to where an asterisk is found
// within the array. Once that is done it copies the array and
// concatenates the new word into the array. If no asterisk is found
// an error message will propogate.
///////////////////////////////////////////////////////////////////////////
void changeline(char array[], char cArray[], char word[]){
    int i = findAsterisk(array);
    if(i != -1){
        strncpy(cArray, array, i);
        strcat(cArray, word);
        strcat(cArray, &array[i + 1]);
    }
    else{
        cout << "No * in line: " << array << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This function calls the changeline function which makes the changes to the arrays and then prints the haiku.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printHaiku(char array[], char hArray[][MAXCOL], char nArray[], int hChoice, char noun[], char verb[], char gerund[]){
        for(int i = 0; i < MAXCOL; i++){
        nArray[i] = '\0';
        array[i]= '\0';
    }
    //changes first line of haiku and prints it
    strcpy(array, hArray[hChoice]);
    changeline(array, nArray, noun);
    cout << nArray;
    cout << endl;
    for(int i = 0; i < MAXCOL; i++){
        nArray[i] = '\0';
        array[i]= '\0';
    }
    //changes second line of haiku and prints
    strcpy(array, hArray[hChoice +1]);
    changeline(array, nArray, verb);
    cout << nArray;
    cout << endl;
    for(int i = 0; i < MAXCOL; i++){
        nArray[i] = '\0';
        array[i]= '\0';
    }
    //changes third line of haiku and then prints.
    strcpy(array, hArray[hChoice +2]);
    changeline(array, nArray, gerund);
    cout << nArray;
    cout << endl;
    for(int i = 0; i < MAXCOL; i++){
        nArray[i] = '\0';
        array[i]= '\0';
    }
}