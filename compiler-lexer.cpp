#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

bool isComment(char current, char next){
  if (current == '[' && next == '*') {
    return true;
  }
  return false;
}

bool endOfComment(char current, char next) {
  if (current == '*' && next == ']') {
    return true;
  }
  return false;
}

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

bool isLogicalOperator(char current, char next) {
    if ((current == '<' || current == '>' || current == '=') && (next == '=')) {
        return true;
    }
    return false;
}

bool isSeparator(char current) {
    if (current == '(' || current == ')' || current == '{' || current == '}' || current == ';'||
        current == ':' || current == '#' || current == '|' || current == ',') {
        return true;
    }
    return false;
}

void lexer(string input, string name_of_output) {
    string current_token = "";
    string current_type = "";
    int decimals = 0;
    int commentChecker = 0;
    bool comment;
    ofstream outputFile;

    outputFile.open(name_of_output + ".txt", ios::app);
    for (size_t i = 0; i < input.length(); i++) {
        char current_char = input[i];
        char next_char = input[i + 1];

        if (isComment(current_char, next_char) == true) {
          commentChecker = 1;
          if(endOfComment(current_char, next_char) == true) {
            commentChecker = 0;
          }
        }

        if (commentChecker ==1) {
          continue;
        }
        else if (isspace(current_char)) {
            continue;
        }
        else if (isalpha(current_char)) {
            current_token += current_char;
            while (isalnum(input[i + 1])) {
                current_token += input[++i];
            }
            if (isKeyword(current_token) == true) {
                current_type = current_token;
                outputFile << "Keyword         " << current_token << endl;
            }
            else {
                outputFile << "Identifier      " << current_token << endl;
            }
            current_token = "";
        }
        else if (isdigit(current_char) || current_char == '.') {

            current_token += current_char;
            if (current_char == '.') {
                decimals++;
            }
            while (isdigit(input[i + 1]) || input[i + 1] == '.') {
                current_token += input[++i];
                if (input[i + 1] == '.') {
                    decimals++;
                }
            }
            if (decimals == 1) {
                outputFile << "Real            " << current_token << endl;
                decimals = 0;
            }
            else if (isSingleDigit(current_token) == true) {
                outputFile << "Integer         " << current_token << endl;
            }
            current_token = "";
        }
        else if (isOperator(current_char) == true) {
            if (isLogicalOperator(current_char, next_char) == true) {
                current_token += current_char;
                current_token += next_char;
                outputFile << "Operator        " << current_token << endl;
                i++;
            }
            else {
                outputFile << "Operator        " << current_char << endl;
            }
            current_token = "";
        }
        else if (isSeparator(current_char) == true) {
            outputFile << "Separator       " << current_char << endl;
        }
        else if (current_char == '[') {
            while ((input[i] != ']') && i < input.length() - 1) {
                i++;
            }
        }
        else {
            outputFile << "Unknown:         " << current_char << endl;
            continue;
        }
    }

    outputFile.close();
}

int main(int argc, char* argv[]) {

    string input, name_of_output;
    ifstream myfile;
    ofstream outputFile;

    cout << "What do you want to name output file: ";
    cin >> name_of_output;



    myfile.open("case1.txt");
    if (!myfile.is_open()) {
        cout << "Could not open file: " << argv[1] << endl;
        return 1;
    }

    if (myfile.is_open()) {
        outputFile.open(name_of_output + ".txt", ios::app);
        outputFile << "Token           " << "Lexeme" << endl;
        outputFile << "______________________" << endl << endl;
        outputFile.close();
        while (getline(myfile, input)) {
            lexer(input, name_of_output);
        }
    }
    myfile.close();

}

/* while not finished(i.e. not end of the source file) do
    call the lexer for a token
    print the tokenand lexeme
    endwhile
}*/
