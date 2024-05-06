#include <iostream>
#include <fstream>
#include <vector>
#include <map>
 #include <sstream> 
 using namespace std;
struct ProductionRule
{
    char lhs;
    string rhs;
};
class CFG
{
public:
    CFG(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Could not open file " << filename << endl;
            exit(1);
        }
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            ProductionRule rule;
            iss >> rule.lhs;
            string arrow;
            iss >> arrow;
            getline(iss, rule.rhs);
            production_rules_.push_back(rule);
        }
    }
    bool IsAcceptable(const string &str)
    {
        vector<char> stack;
        stack.push_back('$');
        stack.push_back(production_rules_[0].lhs);
        for (int i = 0; i < str.length(); i++)
        {
            char ch = str[i];
            while (!stack.empty())
            {
                char top = stack.back();
                if (top == ch)
                {
                    stack.pop_back();
                    break;
                }
                bool found = false;
                for (const ProductionRule &rule : production_rules_)
                {
                    if (rule.lhs == top && rule.rhs[0] == ch)
                    {
                        stack.pop_back();
                        for (int j = rule.rhs.size() - 1; j >= 0; j--)
                        {
                            if (rule.rhs[j] != ' ')
                            {
                                stack.push_back(rule.rhs[j]);
                            }
                        }
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    return false;
                }
            }
        }
        return stack.size() == 1 && stack.back() == '$';
    }

private:
    vector<ProductionRule> production_rules_;
};
int main()
{
    CFG cfg("input.txt");
    cout << "Name:Suhel Khan "<<endl<<"Roll no: 21BCS025"<<endl ;
    string str;
    cout << "Enter a string: ";
    getline(cin, str);
    if (cfg.IsAcceptable(str))
    {
        cout << "The string is acceptable by the given CFG." << endl;
    }
    else
    {
        cout << "The string is not acceptable by the given CFG." << endl;
    }
    return 0;
}


// *********************************************
