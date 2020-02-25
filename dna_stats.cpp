/**
 * Assignment 1 - working with DNA sequences
 * @param  argc - - number of arguments taken in on command line
 * @param  argv - array of actual arguments on command line
 * @return - prints all of the summary stats and new DNA strings onto "mayamistry.out"
 */
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int main (int argc, char**argv) {
  //declaration of all variables that will be used
  string userInput = "";
  ifstream inFS;
  string dnaSequence = "";
  string fileName = "";
  ofstream outFS;
  int userCount = 0; //number of times user runs the program until they exit
  int sum = 0;
  int lineCount = 0;
  float mean = 0;
  int varianceNumerator = 0;
  int currentLineLength = 0;
  float variance = 0;
  float stdev = 0;
  int countA = 0; //these variables will be used to calculate probability
  int countG = 0;
  int countT = 0;
  int countC = 0;
  //variables to calculate the probability for each nucleotide
  float probA = 0;
  float probC = 0;
  float probG = 0;
  float probT = 0;
  //these variables will be used to calculate probability (bigram)
  int countAA = 0;
  int countAC = 0;
  int countAT = 0;
  int countAG = 0;
  int countCA = 0;
  int countCC = 0;
  int countCT = 0;
  int countCG = 0;
  int countGA = 0;
  int countGC = 0;
  int countGT = 0;
  int countGG = 0;
  int countTA = 0;
  int countTC = 0;
  int countTT = 0;
  int countTG = 0;
  float probAA = 0;
  float probAC = 0;
  float probAG = 0;
  float probAT = 0;
  float probCA = 0;
  float probCC = 0;
  float probCG = 0;
  float probCT = 0;
  float probGA = 0;
  float probGC = 0;
  float probGG = 0;
  float probGT = 0;
  float probTA = 0;
  float probTC = 0;
  float probTG = 0;
  float probTT = 0;

  //Gaussian distribution variables
  double a = 0.0;
  double b = 0.0;
  int const NUM_STRINGS = 1000;
  string gaussianSequence = "";
  double cValue = 0;
  double dValue = 0;

  double tempCountA = 0.0;
  double tempCountC = 0.0;
  double tempCountG = 0.0;
  double tempCountT = 0.0;

  char bigram1 = '\0';
  char bigram2 = '\0';
  int bigramSum = 0;

  //while loop is to keep program running until user asks
  while (userInput != "done") {
    //take in the fileName as a command line argument
    if (argc > 1) {
      //read in the file of characters
      if (userCount == 0) {
        fileName = argv[1];
      }

      cout << "Opening file of DNA sequences..." << endl;
      inFS.open(fileName);

      //check if the file can be opened
      if (!inFS.is_open()) {
        cout << "Could not open file with DNA sequences" << endl;
        return 1;
      }

      //start reading the file
      while (!inFS.eof()) {
        inFS >> dnaSequence;
        if (!inFS.fail()){
          lineCount++;
          for (int i = 0; i < dnaSequence.size(); ++i) {
            char currentChar = dnaSequence[i];
            currentChar = toupper(currentChar);
            //make sure character is valid
            switch (currentChar) {
              case 'A':
              case 'G':
              case 'T':
              case 'C':
                sum++;
                break;
              default:
                break;
            }
          }
        }
      }

      //Calculate the mean
      mean = (float)sum / lineCount;

      //Close file and then re-open to find variance
      inFS.close();

      //Calculate the variance
      inFS.open(fileName);

      //check if the file can be opened
      if (!inFS.is_open()) {
        cout << "Could not open file with DNA sequences" << endl;
        return 1;
      }

      //start reading the file
      while (!inFS.eof()) {
        inFS >> dnaSequence;
        if (!inFS.fail()){
          for (int i = 0; i < dnaSequence.size(); ++i) {
            char currentChar = dnaSequence[i];
            toupper(currentChar);
            //make sure character is valid
            switch (currentChar) {
              case 'A':
              case 'G':
              case 'T':
              case 'C':
                currentLineLength++;
                break;
              default:
                break;
            }
          }
          varianceNumerator += ((currentLineLength - mean) * (currentLineLength - mean));
          currentLineLength = 0;
        }
      }

      variance = varianceNumerator / lineCount;
      stdev = sqrt(variance);

      //close the file
      inFS.close();

      //calculation for relative probability
      inFS.open(fileName);

      //check if the file can be opened
      if (!inFS.is_open()) {
        cout << "Could not open file with DNA sequences" << endl;
        return 1;
      }

      //start reading the file
      while (!inFS.eof()) {
        inFS >> dnaSequence;
        if (!inFS.fail()){
          for (int i = 0; i < dnaSequence.size(); ++i) {
            char currentChar = dnaSequence[i];
            toupper(currentChar);
            //make sure character is valid
            switch (currentChar) {
              case 'A':
                countA++;
                break;
              case 'G':
                countG++;
                break;
              case 'T':
                countT++;
                break;
              case 'C':
                countC++;
                break;
              default:
                break;
            }
          }
        }
      }

      //calculate probabilities of each nucleotide
      probA = (float) countA / sum;
      probG = (float) countG / sum;
      probT = (float) countT / sum;
      probC = (float) countC / sum;

      inFS.close();

      //calculation for probability of each nucelotide biagram
      inFS.open(fileName);
      if (!inFS.is_open()) {
        cout << "Could not open file with DNA sequences (BIOGRAM ONE)" << endl;
        return 1;
      }


      //start reading the file
      while (!inFS.eof()) {
        inFS >> dnaSequence;
        if (!inFS.fail()){
          for (int i = 0; i < dnaSequence.size(); i++) {
            if (i == dnaSequence.size() - 1) {
              break;
            }
            bigram1 = dnaSequence[i];
            bigram2 = dnaSequence[i + 1];
            toupper(bigram1);
            toupper(bigram2);
            if (bigram1 == 'A' && bigram2 == 'A') {
              countAA++;
            } else if (bigram1 == 'A' && bigram2 == 'C') {
              countAC++;
            } else if (bigram1 == 'A' && bigram2 == 'G') {
              countAG++;
            } else if (bigram1 == 'A' && bigram2 == 'T') {
              countAT++;
            } else if (bigram1 == 'C' && bigram2 == 'A') {
              countCA++;
            } else if (bigram1 == 'C' && bigram2 == 'C') {
              countCC++;
            } else if (bigram1 == 'C' && bigram2 == 'G') {
              countCG++;
            } else if (bigram1 == 'C' && bigram2 == 'T') {
              countCT++;
            } else if (bigram1 == 'G' && bigram2 == 'A') {
              countGA++;
            } else if (bigram1 == 'G' && bigram2 == 'C') {
              countGC++;
            } else if (bigram1 == 'G' && bigram2 == 'G') {
              countGG++;
            } else if (bigram1 == 'G' && bigram2 == 'T') {
              countGT++;
            } else if (bigram1 == 'T' && bigram2 == 'A') {
              countTA++;
            } else if (bigram1 == 'T' && bigram2 == 'C') {
              countTC++;
            } else if (bigram1 == 'T' && bigram2 == 'G') {
              countTG++;
            } else if (bigram1 == 'T' && bigram2 == 'T') {
              countTT++;
            }
            bigramSum++;
          }
        }
      }

      //solve for the actual probability
      probAA = (float)countAA / bigramSum;
      probAC = (float)countAC / bigramSum;
      probAG = (float)countAG / bigramSum;
      probAT = (float)countAT / bigramSum;
      probCA = (float)countCA / bigramSum;
      probCC = (float)countCC / bigramSum;
      probCG = (float)countCG / bigramSum;
      probCT = (float)countCT / bigramSum;
      probGA = (float)countGA / bigramSum;
      probGC = (float)countGC / bigramSum;
      probGG = (float)countGG / bigramSum;
      probGT = (float)countGT / bigramSum;
      probTA = (float)countTA / bigramSum;
      probTC = (float)countTC / bigramSum;
      probTG = (float)countTG / bigramSum;
      probTT = (float)countTT / bigramSum;

      inFS.close();

      //output the information onto mayamistry.out

      if (userCount == 0) {
        outFS.open("mayamistry.out");
        outFS << "Maya Mistry" << endl;
        outFS << "Student ID: 2287039" << endl;
        outFS << "CPSC 350-02" << endl;
      }

      outFS << "List #: " << (userCount + 1) << endl;
      outFS << "Summary Statistics for DNA sequences - " << endl;
      outFS << endl;
      outFS << "Sum: " << sum << endl;
      outFS << "Number of DNA sequences: " << lineCount << endl;
      outFS << "Mean: " << mean << endl;
      outFS << "Variance: " << variance << endl;
      outFS << "STDEV: " << stdev << endl;
      outFS << endl;
      outFS << "Relative probability statistics for each nucleotide: " << endl;
      outFS << "A: " << probA << endl;
      outFS << "G: " << probG << endl;
      outFS << "T: " << probT << endl;
      outFS << "C: " << probC << endl;
      outFS << endl;
      outFS << "Probability for each bigram: " << endl;
      outFS << "AA: " << probAA << endl;
      outFS << "AC: " << probAC << endl;
      outFS << "AG: " << probAG << endl;
      outFS << "AT: " << probAT << endl;
      outFS << "CA: " << probCA << endl;
      outFS << "CC: " << probCC << endl;
      outFS << "CG: " << probCG << endl;
      outFS << "CT: " << probCT << endl;
      outFS << "GA: " << probGA << endl;
      outFS << "GC: " << probGC << endl;
      outFS << "GG: " << probGG << endl;
      outFS << "GT: " << probGT << endl;
      outFS << "TA: " << probTA << endl;
      outFS << "TC: " << probTC << endl;
      outFS << "TG: " << probTG << endl;
      outFS << "TC: " << probTT << endl;
      outFS << endl;


      for (int i = 0; i < NUM_STRINGS; ++i) {
          //creates the two random values from [0,1)
        a = (rand())/(double)(RAND_MAX);
        b = (rand())/(double)(RAND_MAX);
        cValue = abs((sqrt(-2 * log(a)) * cos(2 * M_PI * b)));
        dValue = (double)stdev * cValue + mean;
        dValue = round(dValue);
        //use thr probability and dValue to get length counts for each nucleotide
        tempCountA = dValue * probA;
        tempCountC = dValue * probC;
        tempCountG = dValue * probG;
        tempCountT = dValue * probT;
        //loop through to print the correct amount of nucleotides for each string
        for (int i = 0; i < tempCountA; ++i) {
          gaussianSequence += "A";
        }
        for (int i = 0; i < tempCountC; ++i) {
          gaussianSequence += "C";
        }
        for (int i = 0; i < tempCountG; ++i) {
          gaussianSequence += "G";
        }
        for (int i = 0; i < tempCountT; ++i) {
          gaussianSequence += "T";
        }
        //output onto the .out file and reset the string variable
        outFS << gaussianSequence << endl;
        gaussianSequence = "";
      }
      outFS << endl;
      outFS << "---------------------------------------------------------------" << endl;
      cout << "Program worked successfully! Check mayamistry.out for statistics." << endl;
    } else {
      cout << "Invalid: please provide the name of the file with the DNA sequences" << endl;
      cout << "Example: ./mayamistry.out dna.txt" << endl;
      return 1;
    }

    //reset all of the variables back to 0.
    sum = 0;
    lineCount = 0;
    mean = 0;
    varianceNumerator = 0;
    currentLineLength = 0;
    variance = 0;
    stdev = 0;
    countA = 0; //these variables will be used to calculate probability
    countG = 0;
    countT = 0;
    countC = 0;
    //variables to calculate the probability for each nucleotide
    probA = 0;
    probC = 0;
    probG = 0;
    probT = 0;
    //these variables will be used to calculate probability (bigram)
    countAA = 0;
    countAC = 0;
    countAT = 0;
    countAG = 0;
    countCA = 0;
    countCC = 0;
    countCT = 0;
    countCG = 0;
    countGA = 0;
    countGC = 0;
    countGT = 0;
    countGG = 0;
    countTA = 0;
    countTC = 0;
    countTT = 0;
    countTG = 0;
    probAA = 0;
    probAC = 0;
    probAG = 0;
    probAT = 0;
    probCA = 0;
    probCC = 0;
    probCG = 0;
    probCT = 0;
    probGA = 0;
    probGC = 0;
    probGG = 0;
    probGT = 0;
    probTA = 0;
    probTC = 0;
    probTG = 0;
    probTT = 0;

    //Gaussian distribution variables
    a = 0.0;
    b = 0.0;
    cValue = 0;
    dValue = 0;

    tempCountA = 0;
    tempCountC = 0;
    tempCountG = 0;
    tempCountT = 0;

    bigram1 = '\0';
    bigram2 = '\0';
    bigramSum = 0;

    //Ask user if they want to process another list. If they do, they can enter the name of the next .txt file they want to process.
    cout << "Would you like to process another list? If not, type 'done.' If so, type in a new .txt file name.'" << endl;
    cout << "Example: dna.txt" << endl;
    cin >> userInput;
    fileName = userInput;
    userCount++;
  }
  //if the user wants to end the program, then the output stream will close
  outFS.close();
  return 0;
}
