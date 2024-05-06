#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map> 
#include <stdlib.h> 
using namespace std;
// Function to identify leaders in the TAC
void identifyLeaders(const vector<string> &tac, unordered_set<int> &leaders)
{
    leaders.insert(0); // First statement is always a leader
    for (int i = 1; i < tac.size(); i++)
    {
        if (tac[i].find(":") != string::npos) // Labelled statement             
        leaders.insert(i); // Labelled statement is a leader
            else if (tac[i - 1].find("goto") != string::npos || tac[i - 1].find("if") != string::npos)
                leaders.insert(i); // Statement after a goto or if is a leader
    }
}
// Function to identify blocks in the TAC
void identifyBlocks(const vector<string> &tac, const unordered_set<int> &leaders, unordered_map< int, vector<int> > &blocks)
{
    int start = 0;
    int end = 0;
    for (int i = 0; i < tac.size(); i++)
    {
        if (leaders.find(i) != leaders.end())
        {
            end = i - 1;
            vector<int> blockStatements;
            for (int j = start; j <= end; j++)
            {
                blockStatements.push_back(j); // Store statement numbers in the block
            }
            blocks[start] = blockStatements;
            start = i;
        }
    }
    // Last block     
    end = tac.size() - 1;     
    vector<int> blockStatements;     
    for (int j = start; j <= end; j++) {
    blockStatements.push_back(j); // Store statement numbers in the block
}
blocks[start] = blockStatements;
}
int main()
{
    ifstream inputFile("TAC.txt");
    vector<string> tac;
    string line;
    // Read TAC from file     
    while (getline(inputFile, line)) {
    tac.push_back(line);
}
inputFile.close();
// Identify leaders    
 unordered_set<int> leaders;     
 identifyLeaders(tac, leaders);
// Identify blocks
unordered_map<int, vector<int> > blocks;
identifyBlocks(tac, leaders, blocks);
// Display leaders
cout << "Leader Statements:" << endl;
for (int leader : leaders)
{
    cout << "Statement " << leader + 1 << ": " << tac[leader] << endl;
}
// Display blocks     
cout << "\nBlocks:" << endl;     
for (const auto& block : blocks) {
cout << "Block starting at statement " << block.first + 1 << ":" << endl;
for (int statement : block.second)
{
    cout << statement + 1 << ": " << tac[statement] << endl;
}
cout << endl;
}
return 0;
}
