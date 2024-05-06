#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
#include <map> 
using namespace std;
class RegularGrammar
{
public:
    RegularGrammar(string filename)
    {
        ifstream file(filename);
        string line;
        while (getline(file, line))
        {
            vector<string> parts = split(line, "->");
            string non_terminal = parts[0];
            vector<string> productions = split(parts[1], "|");
            for (string production : productions)
            {
                grammar_[non_terminal].push_back(production);
            }
        }
    }
    bool is_acceptable(string input)
    {
        return is_acceptable(input, grammar_["S"]);
    }

private:
    map< string, vector<string> > grammar_;
    bool is_acceptable(string input, vector<string> productions)
    {
        if (input.empty())
        {
            return true;
        }
        for (string production : productions)
        {
            if (input.compare(0, production.length(), production) == 0)
            {
                if (is_acceptable(input.substr(production.length()), grammar_[production.substr(0, 1)]))
                {
                    return true;
                }
            }
        }
        return false;
    }
    vector<string> split(string str, string delimiter)
    {
        vector<string> parts;
        size_t pos = 0;
        while ((pos = str.find(delimiter)) != string::npos)
        {
            parts.push_back(str.substr(0, pos));
            str.erase(0, pos + delimiter.length());
        }
        parts.push_back(str);
        return parts;
    }
};
int main()
{
    RegularGrammar grammar("input.txt");
    cout << "Name: Suhel Khan"<<endl<<"Roll no: 21BCS025"<<endl ;
    string input;
    cout << "Enter a string: ";
    cin >> input;
    if (grammar.is_acceptable(input))
    {
        cout << "The string is acceptable." << endl;
    }
    else
    {
        cout << "The string is not acceptable." << endl;
    }
    return 0;
}
