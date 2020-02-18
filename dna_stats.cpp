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

    //these variables will be used to calculate probability (biogram)
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

    char biogram1;
    char biogram2;
    int biogramSum = 0;
    //start reading the file
    while (!inFS.eof()) {
      inFS >> dnaSequence;
      if (!inFS.fail()){
        for (int i = 0; i < dnaSequence.size(); i++) {
          if (i == dnaSequence.size() - 1) {
            break;
          }
          biogram1 = dnaSequence[i];
          biogram2 = dnaSequence[i + 1];
          toupper(biogram1);
          toupper(biogram2);
          if (biogram1 == 'A' && biogram2 == 'A') {
            countAA++;
          } else if (biogram1 == 'A' && biogram2 == 'C') {
            countAC++;
          } else if (biogram1 == 'A' && biogram2 == 'G') {
            countAG++;
          } else if (biogram1 == 'A' && biogram2 == 'T') {
            countAT++;
          } else if (biogram1 == 'C' && biogram2 == 'A') {
            countCA++;
          } else if (biogram1 == 'C' && biogram2 == 'C') {
            countCC++;
          } else if (biogram1 == 'C' && biogram2 == 'G') {
            countCG++;
          } else if (biogram1 == 'C' && biogram2 == 'T') {
            countCT++;
          } else if (biogram1 == 'G' && biogram2 == 'A') {
            countGA++;
          } else if (biogram1 == 'G' && biogram2 == 'C') {
            countGC++;
          } else if (biogram1 == 'G' && biogram2 == 'G') {
            countGG++;
          } else if (biogram1 == 'G' && biogram2 == 'T') {
            countGT++;
          } else if (biogram1 == 'T' && biogram2 == 'A') {
            countTA++;
          } else if (biogram1 == 'T' && biogram2 == 'C') {
            countTC++;
          } else if (biogram1 == 'T' && biogram2 == 'G') {
            countTG++;
          } else if (biogram1 == 'T' && biogram2 == 'T') {
            countTT++;
          }
          biogramSum++;
        }
      }
    }

    //solve for the actual probability
    float probAA = (float)countAA / biogramSum;
    float probAC = (float)countAC / biogramSum;
    float probAG = (float)countAG / biogramSum;
    float probAT = (float)countAT / biogramSum;
    float probCA = (float)countCA / biogramSum;
    float probCC = (float)countCC / biogramSum;
    float probCG = (float)countCG / biogramSum;
    float probCT = (float)countCT / biogramSum;
    float probGA = (float)countGA / biogramSum;
    float probGC = (float)countGC / biogramSum;
    float probGG = (float)countGG / biogramSum;
    float probGT = (float)countGT / biogramSum;
    float probTA = (float)countTA / biogramSum;
    float probTC = (float)countTC / biogramSum;
    float probTG = (float)countTG / biogramSum;
    float probTT = (float)countTT / biogramSum;

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
    outFS << "Probability for each Biogram: " << endl;
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

    //close the stream for mayamistry.out
    outFS.close();

    cout << "Program worked successfully! Check mayamistry.out for statistics." << endl;

  } else {
     cout << "Invalid: please provide the name of the file with the DNA sequences" << endl;
     cout << "Example: ./mayamistry.out dna.txt" << endl;
  }
  return 0;
}
