#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

bool isSingleDigit(string current) {
  if (current == "0" || "1" || "2" || "3" || "4" || "5" || "6" || "7" || "8" || "9") {
    return true;
  }
  return false;
}

bool isKeyword(string st) {
  if (st == "int" || st == "function" || st == "int" || st == "bool" || st == "real" || st == "if" ||
      st == "else" || st == "fi" || st == "return" || st == "put" || st == "get" || st == "while"
      || st == "endwhile" || st == "true" || st == "false") {
        return true;
      }
  return false;
}

bool isOperator(char current) {
  if (current == '=' || current == '!' || current == '>' || current == '<' || current == '*' ||
      current == '/' || current == '-' || current == '+') {
        return true;
      }
  return false;
}

bool isLogicalOperator(char current, char next){
  if ((current == '<' || current == '>' || current == '=') && (next == '=')) {
    return true;
  }
  return false;
}

bool isSeparator(char current){
  if (current == '(' || current == ')' || current == '{' || current == '}' || current == ';' || current == ':') {
    return true;
  }
  return false;
}

void lexer(string input){

    string current_token = "";
    string current_type = "";
    for (size_t i = 0; i < input.length(); i++) {
        char current_char = input[i];
        char next_char = input[i+1];

        if (isspace(current_char)) {
            continue;
        }
        else if (isalpha(current_char)) {
            current_token += current_char;
            while (isalnum(input[i + 1])) {
                current_token += input[++i];
            }
            if (isKeyword(current_token) == true) {
                current_type = current_token;
                cout << "Keyword         " << current_token << endl;
            }
            else {
                cout << "Identifier      " << current_token << endl;
            }
            current_token = "";
        }
        else if (isdigit(current_char) || current_char == '.') {
            int decimals;
            current_token += current_char;
            if (current_char == '.') {
              decimals++;
            }
            while (isdigit(input[i + 1]) || input[i + 1] == '.') {
                current_token += input[++i];
                if (input[i+1] == '.') {
                  decimals++;
                }
            }
            if (decimals == 1) {
                cout << "Real            " << current_token << endl;
            }
            else if (isSingleDigit(current_token) == true){
                cout << "Integer         " << current_token << endl;
            }
            current_token = "";
        }
        else if (isOperator(current_char) == true) {
          if (isLogicalOperator(current_char, next_char) == true) {
            current_token += current_char;
            current_token += next_char;
            cout << "Operator        " << current_token << endl;
            i++;
          }
          else {
            cout << "Operator        " << current_char << endl;
          }
          current_token = "";
        }
        else if (isSeparator(current_char) == true) {
            cout << "Separator       " << current_char << endl;
        }
        else if (current_char == '[') {
            while (input[i + 1] != ']' && i < input.length() - 1) {
                i++;
            }
        }
        else {
            // Ignore other characters
            continue;
        }
    }


}

int main(int argc, char* argv[]) {
    cout << "Token           " << "Lexeme" << endl;
    cout << "______________________" << endl << endl;
    string input;
    ifstream myfile;
    myfile.open("case1.txt");
    if (!myfile.is_open()) {
        cout << "Could not open file: " << argv[1] << endl;
        return 1;
    }

    if (myfile.is_open()) {
      while (getline(myfile, input)) {
        lexer(input);
      }
    }
  }

    /* while not finished(i.e. not end of the source file) do
        call the lexer for a token
        print the tokenand lexeme
        endwhile

    }*/
