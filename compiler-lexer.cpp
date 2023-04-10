#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>


using namespace std;

bool isComment(char current, char next) {
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
    if (current == '(' || current == ')' || current == '{' || current == '}' || current == ';' ||
        current == ':' || current == '#' || current == '|' || current == ',') {
        return true;
    }
    return false;
}

/*
    void Rat23s(vector<string>& token) {
        if(token.empty() == false){
          cout << "<Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>" << endl;
          opt_FunctionDefinitions();
          opt_Declaration_List();
          Statement_List();
        }
        else{
          cout << "Error! There are no valid lexemes." << endl;
        }
    }
    //2
    void opt_FunctionDefinitions(vector<string>& token) {
      cout << "<Opt Function Definitions> ::= <Function Definitions> | <Empty>" << endl;
        Function_Definition();
    }
    //3
    void Function_Definition(vector<string>& token) {
        //cout << " <Function Definition> -> <Function> <Function Definition Prime> \n <Function Definition Prime> ->  ,<Function Definition> | Epsilon";
        Function();
    }
    //4
    void Function(vector<string>& token) {
        if (token == "function")
        {
            cout << "<Identifier>";
        }
        if (token == "(")
        {
            opt_Parameter_List();
        }
        else {
            opt_Declaration_List();
            Body();
        }
    }
    //5
    void opt_Parameter_List(vector<string>& token) {
        Parameter_list();
    }
    //6
    void Parameter_list(vector<string>& token) {
        // cout << "<Parameter list> -> <Parameter> <Parameter list Prime> \n <Parameter list Prime> ->  ,<Parameter list> | Epsilon";
        Parameter();
    }
    //7
    void Parameter(vector<string>& token) {
        IDs();
        Qualifier();
    }
    //8
    void Qualifier(vector<string>& token) {
        if (token == "int") {}
        if (token == "bool") {}
        if (token == "real") {}
    }
    //9
    void Body(vector<string>& token) {
        if (token == "{") {
            Statement_List();
        }
    }
    //10
    void opt_Declaration_List(vector<string>& token) {
        Declaration_List();
    }
    //11
    void Declaration_List(vector<string>& token) {
        // cout << " <Declaration List> -> <Declaration> <Declaration List Prime> \n <Declaration List Prime> -> ; <<Declaration List> | Epsilon";
        Declaration();
      }

    void DeclarationListPrime(vector<string>& token) {
      if (token == ";")
      Declaration_List();
      DeclarationListPrime();
    }

    //r12
    void Declaration() {
        Qualifier();
        IDs();
    }
    //r13
    void IDs() {
        cout << " <IDs> -> <Identifier> <IDs Prime> \n <IDsPrime> -> , <IDS> | Epsilon";
    }
    //r14
    void Statement_List() {
        // cout << " <Statement List> -> <Statement> <Statement List Prime> \n <Statement List Prime> -> , <Statement List> | Epsilon";
        Statement();
    }
    //r15
    void Statement() {
        switch (token) {
        case "<Compound>":
            cout << "<Statement> -> <Compound>";
        case "<Assign>":
            cout << "<Statement> -> <Assign>";
        case "<If>":
            cout << "<Statement> -> <If>";
        case "<Return>":
            cout << "<Statement> -> <Return>";
        case "<Print>":
            cout << "<Statement> -> <Print>";
        case "<Scan>":
            cout << "<Statement> -> <Scan>";
        case "<While>":
            cout << "<Statement> -> <While>";
        }
    }
    //r16
    void Compound() {
        if (token == "{") {
            Statement_List();
        }
    }
    //r17
    void Assign() {
        cout << "<Assign> -> <Identifier> = <Expression>;";
    }
    //r18
    void ifRule() {
        if (token == "if") {
            lexer()
        }
        else
        {
            cout << "error: 'if' expected";
        }
        if (token == "(") {
            lexer();
        }
        else
        {
            cout << "error: '(' expected";
        }
        Condition();
    }
    //r19
    void Return() {
        cout << "return ';' | return <Expression>;";
        if (token == ";") {
            cout << "return ';'";
        }
        else {
            cout << " return <Expression>;";
        }
    }
    //r20
    void Print() {
        cout << "put (<Expression>);";
    }
    //r21
    void Scan()
    {
        cout << "get (<IDs>);";
    }
    //r22
    void While()
    {
        cout << "while (<Condition>) <Statement> endwhile";
    }
    //r23
    void Condition() {
        cout << "<Expression> <Relop> <Expression>";
    }
    //r24
    void Relop()
    {
        switch (token) {
        case '==':
            cout << "==";
        case '!=':
            cout << "!=";
        case '>':
            cout << ">";
        case '<':
            cout << "<";
        case '<=':
            cout << "<=";
        case '>=':
            cout << ">=";
        }
    }
    void T() {
        if (token == "identifier")
        {
            lexer();
        }
        else
            cout << "Identifier expected";
    }
    void EPrime() {
        if (token == "+" || token == "-")
        {
            lexer();
            T();
            EPrime();
        }
    }
    //r25
    void Expression() {
        T();
        EPrime();
        if (!eof)
        {
            cout << "error";
        }
    }
    void F() {
        if (token == "identifier")
        {
            lexer();
        }
        else
            cout << "Identifier expected";
    }
    void TPrime() {
        if (token == "*" || == "/")
        {
            lexer();
            F();
            TPrime();
        }
    }
    //r26
    void Term() {
        F();
        TPrime();
        if (!eof)
        {
            cout << "error";
        }
    }
    //r27
    void Factor() {
        if (token == "-")
            cout << "<Primary>";
        else
            cout << "<Primary>";
    }
    //r28
    void Primary()
    {
    }
    //r29
    void Empty()
    {
        cout << "epsilon";
    }
    */

    void lexer(string input, string name_of_output, vector<string>& words) {
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
                while (input[i] != ']')
                {
                    i++;
                    if (endOfComment(current_char, next_char) == true) {
                        cout << "Done";
                    }
                }
                if (endOfComment(current_char, next_char) == true) {
                    commentChecker = 0;
                }
            }

            if (commentChecker == 1) {
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
                    words.push_back(current_token);

                }
                else {
                    outputFile << "Identifier      " << current_token << endl;
                    words.push_back(current_token);

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
                    words.push_back(current_token);

                    decimals = 0;
                }
                else if (isSingleDigit(current_token) == true) {
                    outputFile << "Integer         " << current_token << endl;
                    words.push_back(current_token);

                }
                current_token = "";
            }
            else if (isOperator(current_char) == true) {
                if (isLogicalOperator(current_char, next_char) == true) {
                    current_token += current_char;
                    current_token += next_char;
                    outputFile << "Operator        " << current_token << endl;
                    words.push_back(current_token);

                    i++;
                }
                else {
                    current_token = current_char;
                    outputFile << "Operator        " << current_token << endl;
                    words.push_back(current_token);

                }
                current_token = "";
            }
            else if (isSeparator(current_char) == true) {
                current_token = current_char;
                outputFile << "Separator       " << current_token << endl;
                words.push_back(current_token);



            }
            else if (current_char == '[') {
                while ((input[i] != ']') && i < input.length() - 1) {
                    i++;
                }
            }
            else {
                current_token = current_char;
                outputFile << "Unknown:         " << current_token << endl;
                words.push_back(current_token);
                current_token = "";

                continue;
            }
            current_token = "";
        }
        outputFile.close();
    }

void syntaxAnalyzer(vector<string>& tokens){
  //Rat23s(vector<string>& tokens);
  int counter = 0;
  while (tokens.empty() == false) {
    cout << tokens[counter] << endl;
    counter++;
    tokens.pop_back();
  }
}

int main(int argc, char* argv[]) {

    string input, name_of_output, complete_input, name_of_input;
    ifstream myfile;
    ofstream outputFile;
    vector <string> test;
    int counter = 0;
    cout << "Which file do you want to access: ";
    cin >> name_of_input;


    myfile.open(name_of_input + ".txt");
    if (!myfile.is_open()) {
        cout << "Could not open file: " << argv[1] << endl;
        cin.ignore();
        return 0;
    }
    cout << "What do you want to name output file: ";
    cin >> name_of_output;
    if (myfile.is_open()) {
        outputFile.open(name_of_output + ".txt", ios::app);
        outputFile << "Token           " << "Lexeme" << endl;
        outputFile << "______________________" << endl << endl;
        outputFile.close();
        while (getline(myfile, input)) {
          lexer(input, name_of_output, test);

          }
        }
        syntaxAnalyzer(test);


    myfile.close();

    cout << name_of_output + ".txt" << " created" << endl;

    return 0;
}

/* while not finished(i.e. not end of the source file) do
    call the lexer for a token
    print the tokenand lexeme
    endwhile
}*/
