//Author: Kyle Frohlich
//Name: EncodeDNA
//Purpose: Encode Malware into DNA
//Date: 04Oct2024

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

int gatherCode(ifstream&, char*);
string toBinary(char*, int);
string toDNA(string, int);
void writeDNA(ofstream&, string);

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Please enter command line as follows..." << endl << "./encode yourcode.txt dnaoutput.txt" << endl;
    }

    ifstream inputCodeFile(argv[1]);
    if(!inputCodeFile.good())
    {
        cout << "Error opening input file." << endl;
        return 0;
    }
    char codeArray[1000];
    int charAmount = gatherCode(inputCodeFile, codeArray);
    cout << charAmount << " character(s) gathered" << endl;
    int binaryLength = charAmount * 8;
    int binaryArray[binaryLength];
    inputCodeFile.close();

    string fullBinary = toBinary(codeArray, charAmount);
    cout << "Characters converted to binary" << endl;

    string DNAsequence = toDNA(fullBinary, binaryLength);
    cout << "Binary converted to DNA" << endl;
    cout << "DNA Sequence: " << DNAsequence << endl;

    ofstream outputDNAFile(argv[2]);
    if(!outputDNAFile.good())
    {
        cout << "Error opening output file" << endl;
    }
    writeDNA(outputDNAFile, DNAsequence);
    cout << "DNA written to " << argv[2] << endl;

    return 0;
}

int gatherCode(ifstream& codeFile, char* codeArray)
{
    int length = 0;
    char tempChar;

    while(codeFile.get(tempChar))
    {
        codeArray[length] = tempChar;
        length++;
    }
    return length;
}

string toBinary(char* codeArray, int charAmount)
{
    string binaryString = "";

    for(int index = 0; index < charAmount; index++)
    {
        binaryString += bitset<8>(codeArray[index]).to_string();
    }
    return binaryString;
}

string toDNA(string binarySequence, int binaryLength)
{
    string DNAsequence = "";

    int index = 0;

    while(index < binaryLength)
    {
        if(binarySequence[index] == '0' && binarySequence[index + 1] == '0')
        {
            DNAsequence.append("A");
        }
        if(binarySequence[index] == '0' && binarySequence[index + 1] == '1')
        {
            DNAsequence.append("T");
        }
        if(binarySequence[index] == '1' && binarySequence[index + 1] == '0')
        {
            DNAsequence.append("C");
        }
        if(binarySequence[index] == '1' && binarySequence[index + 1] == '1')
        {
            DNAsequence.append("G");
        }
        index += 2;
    }
    return DNAsequence;
}

void writeDNA(ofstream& outputFile, string DNAsequence)
{
    outputFile << DNAsequence;
}