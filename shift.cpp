#include <iostream>
#include <string>
#include <map>

/*
/The goal of this program is to utilize a shift cipher to
/encode and decode words provided by the user with a shift
/value also provided by the user
*/

using namespace std;
int Mainshift;  //variable that stores the shift that will be used in the algorithm
std::map<char,int> dictToNumber;    //dictionary for converting a letter to a number
std::map<int,char> dictToLetter;    //dictionary for converting a number to a letter

//initialize dictionaries
void SetDict()
{
  dictToNumber['a']= 1;  dictToNumber['b']= 2;  dictToNumber['c']= 3;  dictToNumber['d']= 4;  dictToNumber['e']= 5; 
  dictToNumber['f']= 6;  dictToNumber['g']= 7;  dictToNumber['h']= 8;  dictToNumber['i']= 9;  dictToNumber['j']= 10;
  dictToNumber['k']= 11; dictToNumber['l']= 12; dictToNumber['m']= 13; dictToNumber['n']= 14; dictToNumber['o']= 15; 
  dictToNumber['p']= 16; dictToNumber['q']= 17; dictToNumber['r']= 18; dictToNumber['s']= 19; dictToNumber['t']= 20;
  dictToNumber['u']= 21; dictToNumber['v']= 22; dictToNumber['w']= 23; dictToNumber['x']= 24; dictToNumber['y']= 25; 
  dictToNumber['z']= 26; dictToNumber[' ']= 0;
  
  dictToLetter[1]= 'a';  dictToLetter[2]= 'b';  dictToLetter[3]= 'c';  dictToLetter[4]= 'd';  dictToLetter[5]= 'e';
  dictToLetter[6]= 'f';  dictToLetter[7]= 'g';  dictToLetter[8]= 'h';  dictToLetter[9]= 'i';  dictToLetter[10]= 'j';
  dictToLetter[11]= 'k'; dictToLetter[12]= 'l'; dictToLetter[13]= 'm'; dictToLetter[14]= 'n'; dictToLetter[15]= 'o';
  dictToLetter[16]= 'p'; dictToLetter[17]= 'q'; dictToLetter[18]= 'r'; dictToLetter[19]= 's'; dictToLetter[20]= 't';
  dictToLetter[21]= 'u'; dictToLetter[22]= 'v'; dictToLetter[23]= 'w'; dictToLetter[24]= 'x'; dictToLetter[25]= 'y';
  dictToLetter[26]= 'z'; dictToLetter[0]= ' ';
}

//sets the shift value to a number less that 26 to speed up calculations and simplify shif
int SetShift(int x)
{
    if(x < 26)
    {
        return x;
    }
    else
    {
        if(x % 26 == 0)
        {
            cout << "Multiple of 26, no shift\n";
             return  0;
        }
        else
        {
             return x % 26;
        }
    }
}

char ToNumber(char letter)  //method to convert a letter to a number
{
       return dictToNumber[letter]; 
}

char ToLetter(int number) //method to convert a number to a letter
{
       return dictToLetter[number]; 
}

//this method takes a string first turns that string into an array of characters
//if encoding: shift is added to each number(type = true), if decoding: shift is subtracted from each number (type = false)
//then the number is converted back to a letter
//char array is converted back to a string and returned
string encode(string arg, bool type)    
{
    
    int length = arg.length();
    int NumArray[length + 1];
    char WordArray[length + 1];
    //turns string into array of characters
    for(int a = 0; a <= length; a++)
    {
        WordArray[a] = arg[a];
    }
    //turns char array into array of integers
    for (int n=0; n<length; n++)
    {
        NumArray[n] = ToNumber(WordArray[n]);
    }

    if(type == true) //encodes word by adding shift to each number
    {
       for (int n=0; n<length; n++)
        {
            //check if a space is present
            if(NumArray[n] != 0)
            {
                //check if shift sends number above 26
                if(NumArray[n] + Mainshift > 26)
                {
                    NumArray[n] = (NumArray[n] + Mainshift) - 26;
                }
                else
                {
                   NumArray[n] += Mainshift; 
                }
            }
        } 
    }
    
    if(type == false) //decodes word by subtracting shift from each number
    {
        for (int n=0; n<length; n++)
        {
            if(NumArray[n] != 0)
            {    
                //check if shift sends number below 1
                if(NumArray[n] - Mainshift < 1)
                {
                    NumArray[n] = (NumArray[n] - Mainshift) + 26;
                }
            else
                {
                   NumArray[n] -= Mainshift; 
                } 
            }    
        }
    }
    
    //converts number array back to character array
    for (int n=0; n<length; n++)
    {
        WordArray[n] = ToLetter(NumArray[n]);
    }
    //turns character array into string and returns
    string Coded(WordArray);
    return Coded;
}


//main method
//asks user for a word or sentence
//asks user if they are encoding or decoding
//if encoding: user is asked for shift, which is divided down to below 26, then input is encoded
//if decoding: user is asked for a range of shifts, then for each shift the decoded input is displayed along with the corresponding shift value
int main()
{
    SetDict();
    int input;
    bool loop;
    string words;
    int max;
    int min;
    bool Continue = true;
    while(Continue)
    {
        cout<<"Enter a Sentence(no caps, no numbers): ";
        getline(cin, words);
        cout << "You entered " << words;
        bool CodeType;
        loop = true;
      while(loop == true)
            {
                input = 0;
                cout << "\nWould you like to encode or decode? (input 1 to encode, input 2 to decode)\n";
                cin >> input;
                //encodes word/sentence
                if(input == 1)
                {
                    cout<<"Enter your shift: ";
                    int shift;
                    cin >> shift;
                    Mainshift = SetShift(shift);
                    cout << "The shift is " << Mainshift << "\n";
                    CodeType = true;
                    cout << "Output" << encode(words, CodeType) << "\n";
                    loop = false;
                }
                //decodes word/sentence
                //asks user for range, then outputs all words with shift in that range
                //outputs include corresponding range
                else if(input == 2)
                {
                    max = 0;
                    min = 1;
                    while(min > max || min == max)
                    {
                        cout<<"Enter highest shift to try(-25 to 26):";
                        cin >> max;
                        Mainshift = SetShift(max);
                        cout<<"Enter lowest shift to try(-26 to 25 and less that highest shift):";
                        cin >> min;
                        if(min > max || min == max)
                        {
                            cout << "invalid input, highest shift is less than or equal lowest shift\n";
                        }
                    }
                    CodeType = false;
                    while(Mainshift >= min)
                    {
                        cout << "Output: " << encode(words, CodeType) << "  Shift: " << Mainshift <<"\n";
                        Mainshift--;
                    }
                    loop = false;
                }
                else
                {
                   cout << "Invalid input, please try again\n";
                }
            }
        loop = true;
        while(loop == true)
        {
        cout << "Would you like to do another? (input 1 for yes, input 2 for no)\n";
        cin >> input;
        if(input == 1)
            {
                Continue = true;
                loop = false;
            }
            else if(input == 2)
            {
                Continue = false;
                loop = false;
            }
            else
            {
               cout << "Invalid input, please try again\n";
            }
        }
        cin.get();
    }

    return 0;
}


