#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int find_block(set<int> leaders, int line_number) {
  vector<int> leaders_vector;
  for (auto it = leaders.begin(); it != leaders.end(); it++) {
    leaders_vector.push_back(*it);
  }
  for (size_t i = 1; i < leaders_vector.size(); i++) {
    if (leaders_vector[i - 1] <= line_number && leaders_vector[i] > line_number)
      return i;
  }
  return leaders.size();
}

int main() {
  ifstream file("input_copy.txt", ios::in);
  if (!file.is_open()) {
    cerr << "File opening failed\n";
    return 1;
  }

  vector<string> code_lines;
  string line = "";
  set<int> leaders;
  leaders.insert(1);

  while (getline(file, line)) {
    string keyword = "goto";
    int j = 0;
    for (size_t i = 0; i <= line.size(); i++) {
      if (line[i] == keyword[j])
        j++;
      else
        j = 0;
      if (j == 4) {
        int target = 0;
        i += 2;
        while (line[i] != ')') {
          target = target * 10 + line[i] - '0';
          i++;
        }
        leaders.insert(target);
        leaders.insert(code_lines.size() + 2);
        break;
      }
    }
    code_lines.push_back(line);
  }
  file.close();

  auto it = leaders.begin();
  size_t i = 0, j = 1, end = *it;
  size_t num_blocks = leaders.size();
  vector<vector<int> > adjacency_matrix(num_blocks, vector<int>(num_blocks, 0));

  while (i < code_lines.size()) {
    int start = end;
    int m = 0;
    it++;
    if (it != leaders.end())
      end = *it;
    else
      end = code_lines.size() + 1;
    bool has_goto = true;
    for (size_t k = start; k < end; k++) {
      string keyword = "goto";
      m = 0;
      for (size_t p = 0; p < code_lines[k - 1].size(); p++) {
        if (code_lines[k - 1][p] == keyword[m])
          m++;
        else
          m = 0;
        if (m == 4) {
          int target = 0;
          p += 2;
          while (code_lines[k - 1][p] != ')') {
            target = target * 10 + code_lines[k - 1][p] - '0';
            p++;
          }
          adjacency_matrix[j - 1][find_block(leaders, target) - 1] = 1;
          if (code_lines[k - 1][0] == 'g') {
            has_goto = false;
          }
          break;
        }
      }
    }
    if (has_goto)
      adjacency_matrix[j - 1][j] = 1;

    cout << j << endl;
    j++;
    i = end;
  }

  for (size_t i = 0; i < num_blocks; i++) {
    for (size_t j = 0; j < num_blocks; j++) {
      cout << adjacency_matrix[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
