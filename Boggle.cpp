/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */
 
#include <iostream>
#include "gboggle.h"
#include "graphics.h"
#include "grid.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"

using namespace std;

/* Lexicon */
Lexicon english("EnglishWords.dat");

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* These strings will contain actual contents of the board
 * i.e the characters which are shown
 */

char boggle5[25];
char boggle4[16];

/* Function prototypes */

void welcome();
void giveInstructions();
void initRandomBoard();
void humansTurn();
bool wordOnTheBoard(string word);
/* Main program */

int main() {
   initGraphics(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
   welcome();
   giveInstructions();
   drawBoard(5, 5);
    
    humansTurn();
   return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
   cout << "Welcome!  You're about to play an intense game ";
   cout << "of mind-numbing Boggle.  The good news is that ";
   cout << "you might improve your vocabulary a bit.  The ";
   cout << "bad news is that you're probably going to lose ";
   cout << "miserably to this little dictionary-toting hunk ";
   cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
   cout << endl;
   cout << "The boggle board is a grid onto which I ";
   cout << "I will randomly distribute cubes. These ";
   cout << "6-sided cubes have letters rather than ";
   cout << "numbers on the faces, creating a grid of ";
   cout << "letters on which you try to form words. ";
   cout << "You go first, entering all the words you can ";
   cout << "find that are formed by tracing adjoining ";
   cout << "letters. Two letters adjoin if they are next ";
   cout << "to each other horizontally, vertically, or ";
   cout << "diagonally. A letter can only be used once ";
   cout << "in each word. Words must be at least four ";
   cout << "letters long and can be counted only once. ";
   cout << "You score points based on word length: a ";
   cout << "4-letter word is worth 1 point, 5-letters ";
   cout << "earn 2 points, and so on. After your puny ";
   cout << "brain is exhausted, I, the supercomputer, ";
   cout << "will find all the remaining words and double ";
   cout << "or triple your paltry score." << endl << endl;
   cout << "Hit return when you're ready...";
   getLine();
}

// [TODO: Fill in the rest of the code]
void initRandomBoard(){
    /* Copy the constant array into a vector vec so you can modify it. Shuffle vec using the following approach:
     for (int i = 0; i < vec.size(); i++) {
     Choose a random index r between i and the last element position, inclusive. Swap the element at positions i and r.
     }
     Fill the Boggle grid by choosing the elements of vec in order.*/
    string big_boggle[25];
    for (int i=0; i<25; i++) {
        big_boggle[i]=BIG_BOGGLE_CUBES[i];
    }
    for (int i=0; i<25; i++) {
        int r=randomInteger(i, 24);
        string temp=big_boggle[r];
        big_boggle[r]=big_boggle[i];
        big_boggle[i] = temp;
    }
    int k=0;
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            char ch=big_boggle[k][randomInteger(0, 5)];
            labelCube(i, j, ch);
            boggle5[k]=ch;
            k++;
        }
        
    }
    
}

void humansTurn(){
    cout<<"Think up of words and write them here as long as you can. When exhausted type \"I QUIT\" as it is.";
    initRandomBoard();
    string word;
    while(true){
        getline(cin, word);
        if (word=="I QUIT") {
            break;
        }
        else {
            if (word.size()>=4&&english.contains(word)&&wordOnTheBoard(word)) {
                recordWordForPlayer(word, HUMAN);
            }
        }
    }
    return;
}

void wordOnTheBoard
