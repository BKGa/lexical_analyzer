#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>


using namespace std;

void Empty(vector<string>& token);
void Primary(vector<string>& token);
void Factor(vector<string>& token);
void Term(vector<string>& token);
void TermPrime(vector<string>& token);
void Expression(vector<string>& token);
void ExpressionPrime(vector<string>& token);
void Relop(vector<string>& token);
void Condition(vector<string>& token);
void While(vector<string>& token);
void Scan(vector<string>& token);
void Print(vector<string>& token);
void Return(vector<string>& token);
void ifRule(vector<string>& token);
void Assign(vector<string>& token);
void Compound(vector<string>& token);
void Statement(vector<string>& token);
void Statement_List(vector<string>& token);
void IDs(vector<string>& token);
void Declaration(vector<string>& token);
void Declaration_List(vector<string>& token);
void opt_Declaration_List(vector<string>& token);
void Body(vector<string>& token);
void Qualifier(vector<string>& token);
void Parameter(vector<string>& token);
void Parameter_list(vector<string>& token);
void opt_Parameter_List(vector<string>& token);
void Function(vector<string>& token);
void Function_Definition(vector<string>& token);
void opt_FunctionDefinitions(vector<string>& token);
void Rat23s(vector<string>& token);

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



    ///r29
    void Empty(vector<string>& token)
    {
        cout << "<Empty> ::= Epsilon";
    }

    ///r28
    void Primary(vector<string>& token){
      int counter,decimal = 0;
      vector<string> test;
      test = token;
      while (test.empty() == false){
        if (test[0] == ".")
        decimal++;
        counter++;
        test.pop_back();
      }
      if (isKeyword(token[0])){
        token.pop_back();
        if (token[0] == "("){
          IDs(token);
          if (token[0] != ")"){
            cout << "Error! Expected )";
            exit(-1);
          }
        }
      }
      if (isSingleDigit(token[0])){
        token.pop_back();
      }
      if(isSingleDigit(token[0])){
        token.pop_back();
      }
      if (token[0] == "true" || token[0] == "false"){
        token.pop_back();
      }
      if ((isKeyword(token[0]) == false) & (isSingleDigit(token[0]) == false) && (decimal >= 0) && (token[0] != "true") && (token[0] != "false")){
        Expression(token);
      }

    }

    ///r27
    void Factor(vector<string>& token) {
      cout << "<Factor> ::= - <Primary> | <Primary>" << endl;
        if (token[0] == "-")
            cout << "<Primary>";
        else if  (token.empty() == false)
            cout << "<Primary>";
        else{
            cout << "Error! Expected Factor." <<  endl;
            exit(-1);
          }
    }

    //r26
    void Term(vector<string>& token) {
        cout << "<Term> ::= <Factor> <Term’>" << endl;
        Factor(token);
        TermPrime(token);
    }

    void TermPrime(vector<string>& token){
        if (token[0] == "*"){
          token.pop_back();
          Factor(token);
          TermPrime(token);
        }
        else if (token[0] == "/") {
          token.pop_back();
          Factor(token);
          TermPrime(token);
        }
        else{
          Empty(token);
        }
    }

    //r25
    void Expression(vector<string>& token) {
        cout << "<Expression> ::= <Term> <Expression’>" << endl;
        Term(token);
        ExpressionPrime(token);
    }

    void ExpressionPrime(vector<string>& token){
      cout << "<Expression’> ::= + <Term> <Expression’> | - <Term> <Expression’> | <Empty>" << endl;
      if (token[0] == "+"){
        token.pop_back();
        Term(token);
        ExpressionPrime(token);
      }
      else if (token[0] == "-"){
        token.pop_back();
        Term(token);
        ExpressionPrime(token);
      }
      else{
        Empty(token);
      }
    }

    //r24
    void Relop(vector<string>& token)
    {
        if (token[0] == "<" || token[0] == ">" || token[0] == "=" || token[0] == "!") {
          token.pop_back();
          if (token[0] == "="){
            token.pop_back();
          }
          else{
            cout << "Error! Expecting = for Relop." << endl;
            exit(-1);
          }
        }
        else {
          cout  << "Error! Expecting <, >, =, or ! for Relop." << endl;
          exit(-1);
        }
    }

    //r23
    void Condition(vector<string>& token) {
        cout << "<Expression> <Relop> <Expression>";
        Expression(token);
        Relop(token);
        Expression(token);
    }

    //r22
    void While(vector<string>& token)
    {
        cout << "while (<Condition>) <Statement> endwhile" << endl;
        if (token[0] == "while"){
          token.pop_back();
          if  (token[0] == "(") {
            token.pop_back();
            Condition(token);
            if (token[0] == ")"){
              Statement(token);
              if (token[0] != "endwhile"){
                cout << "Error! Expected endwhile" << endl;
                exit(-1);
              }
            }
            else{
              cout << "Error! Expected )" << endl;
              exit(-1);
            }
          }
          else {
            cout << "Error! Expected (" << endl;
          }
        }
        else {
          cout << "Error! Expected Put" << endl;
          exit(-1);
        }
    }

    //r21
    void Scan(vector<string>& token)
    {
      cout << "get(<IDs>);";
      if (token[0] == "get"){
        token.pop_back();
        if  (token[0] == "(") {
          token.pop_back();
          IDs(token);
          if (token[0] == ")"){
            if (token[0] != ";"){
              cout << "Error! Expected ;" << endl;
              exit(-1);
            }
          }
          else{
            cout << "Error! Expected )" << endl;
            exit(-1);
          }
        }
        else {
          cout << "Error! Expected (" << endl;
        }
      }
      else {
        cout << "Error! Expected Put" << endl;
        exit(-1);
      }
    }

    //r20
    void Print(vector<string>& token) {
        cout << "put (<Expression>);";
        if (token[0] == "put"){
          token.pop_back();
          if  (token[0] == "(") {
            token.pop_back();
            Expression(token);
            if (token[0] == ")"){
              if (token[0] != ";"){
                cout << "Error! Expected ;" << endl;
                exit(-1);
              }
            }
            else{
              cout << "Error! Expected )" << endl;
              exit(-1);
            }
          }
          else {
            cout << "Error! Expected (" << endl;
          }
        }
        else {
          cout << "Error! Expected Put" << endl;
          exit(-1);
        }
    }

    //r19
    void Return(vector<string>& token) {
        cout << "return ';' | return <Expression>;";
        if (token[0] == "return") {
            token.pop_back();
            if (token[0] != ";"){
              Expression(token);
            }
            else if (token[0] != ";"){
              cout << "Error! Expected ;" << endl;
              exit(-1);
            }
        }
        else  {
          cout << "Error! Expected return." << endl;
          exit(-1);
        }
    }

    //r18
    void ifRule(vector<string>& token) {
        if (token[0] == "if") {
            token.pop_back();
        }
        else
        {
            cout << "error: 'if' expected";
        }
        if (token[0] == "(") {
            token.pop_back();
        }
        else
        {
            cout << "error: '(' expected";
        }
        Condition(token);
        if (token[0] == "else"){
          token.pop_back();
          Statement(token);
          if (token[0] != "fi"){
            cout << "Error! Expected fi." <<  endl;
          }
        }
        else if (token[0] != "fi"){
          cout << "Error! Expected fi." <<  endl;
        }
    }

    //r17
    void Assign(vector<string>& token) {
        cout << "<Assign> -> <Identifier> = <Expression>;";
        if (isKeyword(token[0]) == true){
          token.pop_back();
        }
        if  (token[0] == "="){
          Expression(token);
        }
        else{
          cout << "Error! Expected =" << endl;
          exit(-1);
        }

    }

    //r16
    void Compound(vector<string>& token) {
        cout << "<Compound> ::= { <Statement List> }" << endl;
        if (token[0] == "{"){
          token.pop_back();
        }
        else{
          cout << "Error! Expected {" << endl;
        }
        Statement_List(token);
        if (token[0] == "}"){
          token.pop_back();
        }
        else{
          cout << "Error! Expected {" << endl;
        }
    }

    //r15
    void Statement(vector<string>& token) {
      int counter = 0;
      vector<string> test;
      string key;
      bool bracket1, bracket2, equal, ifs, returns, put, get, whiles;
      while (test.empty() == false){
        counter++;
        test.pop_back();
        if (test[0] == "{"){
          bracket1 = true;
        }
        if ((test[0] == "}") && (bracket1 == true)){
          bracket2 = true;
        }
        if (test[0] == "="){
          equal = true;
        }
        if (test[0] == "if"){
          ifs = true;
        }
        if (test[0] == "return"){
          returns = true;
        }
        if (test[0] == "put"){
          put = true;
        }
        if (test[0] == "get"){
          get == true;
        }
        if (test[0] == "while"){
          whiles == true;
        }
      }
        if(bracket2 == true){
            cout << "<Statement> -> <Compound>";
            Compound(token);
          }
        if(equal == true){
            cout << "<Statement> -> <Assign>";
            Assign(token);
          }
        if(ifs == true){
            cout << "<Statement> -> <If>";
            ifRule(token);
          }
        if(returns == true){
            cout << "<Statement> -> <Return>";
            Return(token);
          }
        if(put == true){
            cout << "<Statement> -> <Print>";
            Print(token);
          }
        if(get == true){
            cout << "<Statement> -> <Scan>";
            Scan(token);
          }
        if(whiles  == true){
            cout << "<Statement> -> <While>";
            While(token);
          }
        }


    //r14
    void Statement_List(vector<string>& token) {
        cout << " <Statement List> -> <Statement> <Statement List Prime> \n <Statement List Prime> -> , <Statement List> | Epsilon";
        if (token.empty() == false) {
          Statement(token);
          if (token.empty() == false){
            Statement_List(token);
          }
        }
        else {
          cout << "Error! Expected a Statement List." << endl;
        }
    }

    //r13
    void IDs(vector<string>& token) {
        cout << " <IDs> -> <Identifier> <IDs Prime> \n <IDsPrime> -> , <IDS> | Epsilon";
        if(token.empty() == false){
          token.pop_back();
          if (token.empty() == false){
            IDs(token);
          }
        }
        else {
          cout << "Error! Expected an ID." << endl;
        }
    }

    //r12
    void Declaration(vector<string>& token) {
      cout << "<Declaration> ::= <Qualifier > <IDs>" << endl;
        Qualifier(token);
        IDs(token);
    }

    //11
    void Declaration_List(vector<string>& token) {
        cout << " <Declaration List> -> <Declaration> <Declaration List Prime> \n <Declaration List Prime> -> ; <<Declaration List> | Epsilon";
        if (token.empty() == false){
          Declaration(token);
          if (token[0] != ";"){
            cout << "Error! Expected ;" <<  endl;
            exit(-1);
          }
          //DeclarationListPrime();
          if (token.empty() == false){
            Declaration_List(token);
          }
        }
        else{
          cout << "Error! Expected Declaration." << endl;
          exit(-1);
        }

      }

    /*void DeclarationListPrime(vector<string>& token) {
      if (token[0] == ";")
      Declaration_List();
      DeclarationListPrime();
    }*/

    //10
    void opt_Declaration_List(vector<string>& token) {
      cout << "<Opt Declaration List> ::= <Declaration List> | <Empty>" << endl;
        Declaration_List(token);
    }


    //9
    void Body(vector<string>& token) {
      cout << "<Body> ::= { < Statement List> }" << endl;
        if (token[0] == "{") {
            Statement_List(token);
        }
        else {
          cout << "Error! Expected Body." << endl;
          exit(-1);
        }
    }

    //8 END OF A BRANCH
    void Qualifier(vector<string>& token) {
        if (token[0] == "int") {
          cout << " <Qualifier> ::= int" << endl;
        }
        else if (token[0] == "bool") {
          cout << " <Qualifier> ::= bool" << endl;
        }
        else if (token[0] == "real") {
          cout << " <Qualifier> ::= real" << endl;
        }
        else {
          cout << "Error! Expected Qualifier." << endl;
          exit(-1);
        }
        token.pop_back();
    }

    //7
    void Parameter(vector<string>& token) {
      cout << "<Parameter> ::= <IDs > <Qualifier>" << endl;
        IDs(token);
        Qualifier(token);
    }

    //6
    void Parameter_list(vector<string>& token) {
        cout << "<Parameter list> -> <Parameter> <Parameter list Prime> \n <Parameter list Prime> ->  ,<Parameter list> | Epsilon";
        Parameter(token);
        if(token.empty() == false){
          Parameter_list(token);
        }
        else {
          cout << "Error! Expected parameter." <<  endl;
          exit(-1);
        }
    }

    //5
    void opt_Parameter_List(vector<string>& token) {
      cout << "<Opt Parameter List> -> <Parameter List> | <Empty>" << endl;
      Parameter_list(token);
    }

    //4
    void Function(vector<string>& token) {
        cout << "<Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>" << endl;
        //Display ID
        if (isKeyword(token[0]) == true){
          token.pop_back();
        }
        else{
          cout << "Error! Expected Identifier." << endl;
          exit(-1);
        }
        opt_Parameter_List(token);
        opt_Declaration_List(token);
        Body(token);
    }

    ///3
    void Function_Definition(vector<string>& token) {
        cout << " <Function Definition> -> <Function> <Function Definition Prime> \n <Function Definition Prime> ->  ,<Function Definition> | Epsilon";
        if(token.empty() == false){
          Function(token);
          if(token.empty() == false){
            Function_Definition(token);
          }
        }
        else{
          cout << "Error! Expected function." << endl;
          exit(-1);
        }
    }

    //2
    void opt_FunctionDefinitions(vector<string>& token) {
      cout << "<Opt Function Definitions> ::= <Function Definitions> | <Empty>" << endl;
        Function_Definition(token);
        if (token[0] == "#"){
          Empty(token);
        }
    }

    //r1
    void Rat23s(vector<string>& token) {
        if(token.empty() == false){
          cout << "<Rat23S> ::= <Opt Function Definitions> # <Opt Declaration List> # <Statement List>" << endl;
          opt_FunctionDefinitions(token);
          if(token[0] != "#"){
            cout << "Error! Expected #" << endl;
            exit(-1);
          }
          opt_Declaration_List(token);
          if(token[0] != "#"){
            cout << "Error! Expected #" << endl;
            exit(-1);
          }
          Statement_List(token);
        }
        else{
          cout << "Error! There are no valid lexemes." << endl;
          exit(-1);
        }
    }


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
  Rat23s(tokens);
  /*int counter = 0;
  while (tokens.empty() == false) {
    cout << tokens[counter] << endl;
    counter++;
    tokens.pop_back();
  }*/
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
