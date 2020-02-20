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
  //take in the fileName as a command line argument
  if (argc > 1) {
    //read in the file of characters
    string fileName = argv[1];
    ifstream inFS;
    string dnaSequence = "";

    int sum = 0;
    int lineCount = 0;

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
          toupper(currentChar);
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
    float mean = 0;
    mean = (float)sum / lineCount;

    //Close file and then re-open to find variance
    inFS.close();

    //Calculate the variance
    inFS.open(fileName);
    int varianceNumerator = 0;

    //check if the file can be opened
    if (!inFS.is_open()) {
      cout << "Could not open file with DNA sequences" << endl;
      return 1;
    }

    //start reading the file
    int currentLineLength = 0;
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

    float variance = varianceNumerator / lineCount;
    float stdev = sqrt(variance);

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

    int countA = 0; //these variables will be used to calculate probability
    int countG = 0;
    int countT = 0;
    int countC = 0;

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
    float probA = (float) countA / sum;
    float probG = (float) countG / sum;
    float probT = (float) countT / sum;
    float probC = (float) countC / sum;

    inFS.close();

    //calculation for probability of each nucelotide biagram
    inFS.open(fileName);
    if (!inFS.is_open()) {
      cout << "Could not open file with DNA sequences (BIOGRAM ONE)" << endl;
      return 1;
    }

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

    char bigram1;
    char bigram2;
    int bigramSum = 0;
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
    float probAA = (float)countAA / bigramSum;
    float probAC = (float)countAC / bigramSum;
    float probAG = (float)countAG / bigramSum;
    float probAT = (float)countAT / bigramSum;
    float probCA = (float)countCA / bigramSum;
    float probCC = (float)countCC / bigramSum;
    float probCG = (float)countCG / bigramSum;
    float probCT = (float)countCT / bigramSum;
    float probGA = (float)countGA / bigramSum;
    float probGC = (float)countGC / bigramSum;
    float probGG = (float)countGG / bigramSum;
    float probGT = (float)countGT / bigramSum;
    float probTA = (float)countTA / bigramSum;
    float probTC = (float)countTC / bigramSum;
    float probTG = (float)countTG / bigramSum;
    float probTT = (float)countTT / bigramSum;

    inFS.close();

    //output the information onto mayamistry.out
    ofstream outFS;

    outFS.open("mayamistry.out");

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


    //Gaussian distribution
    float a = 0.0;
    float b = 0.0;
    int const NUM_STRINGS = 1000;
    string gaussianSequence = "";
    float cValue = 0;
    float dValue = 0;

    int tempCountA = 0;
    int tempCountC = 0;
    int tempCountG = 0;
    int tempCountT = 0;

    for (int i = 0; i < NUM_STRINGS; ++i) {
      //creates the two random values from [0,1)
      a = (float)(rand())/RAND_MAX;
      b = (float)(rand())/RAND_MAX;
      cValue = sqrt(-2 * log(a)) * cos(2 * M_PI * b);
      dValue = (stdev * cValue) + mean;
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

    //close the stream for mayamistry.out
    outFS.close();
    cout << "Program worked successfully! Check mayamistry.out for statistics." << endl;

  } else {
     cout << "Invalid: please provide the name of the file with the DNA sequences" << endl;
     cout << "Example: ./mayamistry.out dna.txt" << endl;
  }
  return 0;
}
