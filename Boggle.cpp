/*
 * File: Boggle.cpp
 * ----------------
 * Created by Alok K Shukla on July 4th 2012
 * Copyright (C) 2012 MNNIT Allahabad.
 *
 * This code simulates playing of classic "Boggle" word building game.
 * Objective of this project is to effectively use recursive strategies.
 * 
 */


#include <iostream>
#include "gboggle.h"
#include "graphics.h"
#include "grid.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"

using namespace std;

/* English Lexicon, to check for meaningful words. */
Lexicon english("EnglishWords.dat");


/* Constants */
const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;


/* Size of the boggle board*/
int size;


/* The set of words selected by computer */
Set<string> allwords;


/* Set of co-ordinates on board for computer(mypaths) and player(paths)*/
/* Used to rule out returning on same path while recursing. */
Set<string> mypaths;
Set<string> paths;


/* Default configurations for board. */
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

/* The strings that will contain actual contents of the board, i.e the characters which are shown.  */

char boggle[5][5];




/* Function prototypes */

void welcome();
void giveInstructions();
void initRandomBoard();
void initConfBoard();
void humansTurn();
void addWords(string prefix,int i, int j);
void myTurn();
bool wordOnTheBoard(string word);
bool wordThatStartsHere(string word, int row, int col);
/* Main program */

int main() {
    initGraphics(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    welcome();
    giveInstructions();
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

/*
 * Function: initRandomBoard
 * Usage: initRandomBoard();
 * --------------------------
 * Initializes the boggle board for user using default cubes; if user wishes so.
 *
 */


void initRandomBoard(){
    drawBoard(size, size);
    string big_boggle[25],small_boggle[16];
    if (size==5) {
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
                boggle[i][j]=ch;
                k++;
            }
        }
    }
    else {
        for (int i=0; i<16; i++) {
            small_boggle[i]=STANDARD_CUBES[i];
        }
        for (int i=0; i<16; i++) {
            int r=randomInteger(i, 15);
            string temp=small_boggle[r];
            small_boggle[r]=small_boggle[i];
            small_boggle[i] = temp;
        }
        int k=0;
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                char ch=small_boggle[k][randomInteger(0, 4)];
                labelCube(i, j, ch);
                boggle[i][j]=ch;
                k++;
            }
        }
    }
    return;
}

/*
 * Function: initConfBoard
 * Usage: initConfBoard();
 * --------------------------
 * Initializes the boggle board for user using user-defined cubes; if user wishes so.
 *
 */

void initConfBoard(){
    cout<<"Please enter board size i.e 4 or 5: ";
    size=getInteger();
    drawBoard(size, size);
    char ch;
    cout<<"\nNow enter charcters in following format (row-major). \n\n";
    cout<<"  a  b  c  d  \n";
    cout<<"  s  r  r  e  \n";
    cout<<"  a  e  t  y  \n";
    cout<<"  w  e  g  h  \n";
    cout<<"\n*****************************************************\n";
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            cin>>ch;
            labelCube(i, j, ch);
            boggle[i][j]=ch;
        }
    }
    return;
}

/*
 * Function: humansTurn
 * Usage: humansTurn();
 * --------------------------
 * Lets the player choose words and accordingly updates his scores.
 *
 */


void humansTurn(){
    Set<string> words;
    cout<<"\n\nIf you'd like to configure board for you, enter \"C/c\" else press ENTER.\n";
    string s=getLine();
    if (s=="C"||s=="c") {
        initConfBoard();
    }
    else {
        cout<<"Would you like a 4x4 board or 5x5? Choose 4/5: ";
        cin>>size;
        initRandomBoard();
    }
    cout<<"\nNow enter the words that you can think of as long as you like. When exhausted, enter \"I QUIT\"\n\n or simply a BLANK line.";
    getchar();
    string word;
    while(true){
        word=getLine();
        if (word=="I QUIT"||word=="") {
            cout<<"\nSo! now its my turn.\n";
            myTurn();
            break;
        }
        else {
            paths.clear();
            if (word.size()>=4&&english.contains(word)&&wordOnTheBoard(word)) {
                if (!words.contains(word)) {
                    words.add(word);
                    recordWordForPlayer(word, HUMAN);
                }
                else {
                    cout<<"You are not supposed to repeat words.\n";
                }
                
                
                
            }
            else {
                cout<<"\nIllegal word!\n";
                continue;
            }
        }
    }
    return;
}

/*
 * Function: wordOnTheBoard
 * Usage: wordOnTheBoard(string word);
 * --------------------------
 * Decides if the user chosen word is a valid word according to Boggle rules.
 *
 */

bool wordOnTheBoard(string word){
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (boggle[i][j]==word[0]) {
                if (wordThatStartsHere(word, i, j)) {
                    return true;
                }
                continue ;
            }
        }
    }
    return false;
}

/*
 * Function: wordThatStartsHere
 * Usage: wordThatStartsHere(string word, int row, int col);
 * --------------------------
 * Helper for wordOnTheBoard.
 *
 */

bool wordThatStartsHere(string word, int row, int col){
    
    if (word=="") {
        foreach(string s in paths){
            highlightCube(stringToInteger(s.substr(1,1)), stringToInteger(s.substr(3,1)), true);
        }
        return true;
    }
    else if(row>=size||col>=size||row<0||col<0){
        return false;
    }
    else {
        if (boggle[row][col]==word[0]) {
            string path="("+integerToString(row)+","+integerToString(col)+")";
            if (!paths.contains(path)) {
                paths.add(path);
            }
            else {
                
                return false;
            }
            return (wordThatStartsHere(word.substr(1), row+1, col)||wordThatStartsHere(word.substr(1), row, col+1)||wordThatStartsHere(word.substr(1), row+1, col+1)||wordThatStartsHere(word.substr(1), row-1, col)||wordThatStartsHere(word.substr(1), row, col-1)||wordThatStartsHere(word.substr(1), row-1, col-1)||wordThatStartsHere(word.substr(1), row-1, col+1)||wordThatStartsHere(word.substr(1), row+1, col-1));
        }
        else {
            return false;
        }
        
    }
}

/*
 * Function: myTurn
 * Usage: myTurn();
 * --------------------------
 * Plays the computer's part.
 *
 */

void myTurn(){
    Set<string> modified;
    string s;
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            s[0]=boggle[i][j];
            mypaths.clear();
            addWords(s, i, j);        
        }
    }
    foreach(string word in allwords){
        recordWordForPlayer(word, COMPUTER);
        
    }
    return;
}

/*
 * Function: addWords
 * Usage: addWords(string prefix,int i, int j;
 * --------------------------
 * Adds valid words for computer.
 *
 */

void addWords(string prefix,int i, int j){
    
    if (i<0||i>=size||j<0||j>=size||(!english.containsPrefix(prefix))) {
        return;
    }
    else {
        if (english.contains(prefix)&&prefix.size()>=4) {
            allwords+=prefix;
            for (int i=0; i<size; i++) {
                for (int j=0; j<size; j++) {
                    highlightCube(i, j, false);
                }
            }
            
        }
        string path="("+integerToString(i)+","+integerToString(j)+")";
        if (!mypaths.contains(path)) {
            mypaths.add(path);
        }
        else {
            return;
        }
        addWords(prefix+boggle[i-1][j], i-1, j);
        addWords(prefix+boggle[i-1][j+1], i-1, j+1);
        addWords(prefix+boggle[i-1][j-1], i-1, j-1);
        addWords(prefix+boggle[i][j+1], i, j+1);
        addWords(prefix+boggle[i][j-1], i, j-1);
        addWords(prefix+boggle[i+1][j+1], i+1, j+1);
        addWords(prefix+boggle[i+1][j], i+1, j);
        addWords(prefix+boggle[i+1][j-1], i+1, j-1);
    }
}
