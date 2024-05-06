#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <sstream> 
#include <algorithm> 
using namespace std;
struct BasicBlock
{
    set<string> gen;
    set<string> kill;
};
vector<BasicBlock> generateBasicBlocks(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error: Unable to open file: " << filename << endl;
        exit(1);
    }
    vector<BasicBlock> basicBlocks;
    BasicBlock currentBlock;
    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        if (line[0] == '#')
        {
            basicBlocks.push_back(currentBlock);
            currentBlock.gen.clear();
            currentBlock.kill.clear();
        }
        else
        {
            stringstream ss(line);
            string op, arg1, arg2, result;
            ss >> op >> arg1 >> arg2 >> result;
            currentBlock.kill.insert(result);
            if (op == "+" || op == "-" || op == "*" || op == "/")
            {
                currentBlock.gen.insert(arg1);
                currentBlock.gen.insert(arg2);
            }
            else if (op == "=")
            {
                currentBlock.kill.erase(result);
                currentBlock.gen.insert(result);
            }
        }
    }
    basicBlocks.push_back(currentBlock);
    file.close();
    return basicBlocks;
}
void printGenKill(const vector<BasicBlock> &basicBlocks)
{
    int blockNum = 0;
    for (const auto &block : basicBlocks)
    {
        cout << "Basic Block " << blockNum++ << ":\n";
        cout << "GEN: ";
        for (const auto &genVar : block.gen)
        {
            cout << genVar << " ";
        }
        cout << "\nKILL: ";
        for (const auto &killVar : block.kill)
        {
            cout << killVar << " ";
        }
        cout << "\n\n";
    }
}
int main()
{
    cout << "Roll No: 21BCS025" << endl;
    cout << "Name: Suhel Khan" << endl;
    string filename = "TAC2.txt"; // Change this to your TAC file     
    vector<BasicBlock> basicBlocks = generateBasicBlocks(filename);     
    printGenKill(basicBlocks);
    return 0;
}
