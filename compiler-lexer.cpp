#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>


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
void WhileRule(vector<string>& token);
void Scan(vector<string>& token);
void PrintRule(vector<string>& token);
void Return(vector<string>& token);
void ifRule(vector<string>& token);
void Assign(vector<string>& token);
void Compound(vector<string>& token);
void Statement(vector<string>& token);
void Statement_List(vector<string>& token);
void StatementListPrime(vector<string>& token);
void IDs(vector<string>& token);
void IDsPrime(vector<string>& token);
void Declaration(vector<string>& token);
void Declaration_List(vector<string>& token);
void DeclarationListPrime(vector<string>& token);
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
    if ((current == '<' || current == '>' || current == '=' || current  == '!') && (next == '=')) {
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
        cout << "<Empty> -> Epsilon" << endl;
        token.erase(token.begin());
    }

    ///r28
    void Primary(vector<string>& token){
      if (isKeyword(token[0])){
        if (token[1][0] == '('){
          cout << "<Primary> -> <Identifier>(IDs)" << endl;
          token.erase(token.begin());
          token.erase(token.begin());
          IDs(token);
          token.erase(token.begin());
        }
      }
      else if (isSingleDigit(token[0])){
        if (find(token[0].begin(), token[0].end(), '.') != token[0].end()){
          cout << "<Primary> -> <Real>" << endl;
          token.erase(token.begin());
        }
        else{
          cout << "<Primary> -> <Integer>" << endl;
          token.erase(token.begin());
        }
      }
      else if (token[0] == "true"){
        cout << "<Primary> -> true" << endl;
        token.erase(token.begin());
      }
      else if (token[0] == "false"){
        cout << "<Primary> -> false" << endl;
        token.erase(token.begin());
      }
      else{
        Expression(token);
      }

    }

    ///r27
    void Factor(vector<string>& token) {
      cout << "<Factor> ::= - <Primary> | <Primary>" << endl;
        if (token[0] == "-")
            cout << "<Primary>" <<  endl;
        else if  (token.empty() == false)
            cout << "<Primary>" << endl;
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
        if (token[0][0] == '*'){
          cout << "<Term'> -> *<Factor><Term'>" << endl;
          token.erase(token.begin());
          Factor(token);
          TermPrime(token);
        }
        else if (token[0][0] == '/') {
          cout << "<Term'> -> /<Factor><Term'>" << endl;
          token.erase(token.begin());
          Factor(token);
          TermPrime(token);
        }
        else if (token[0][0] == ' '){
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
      cout << "<Expression’> -> + <Term> <Expression’>" << endl;
      if (token[0] == "+"){
        cout << "<Expression’> -> + <Term> <Expression'>" << endl;
        token.erase(token.begin());
        Term(token);
        ExpressionPrime(token);
      }
      else if (token[0] == "-"){
        cout << "<Expression’> -> - <Term> <Expression'>" << endl;
        token.erase(token.begin());
        Term(token);
        ExpressionPrime(token);
      }
      else if (token[0][0] == ' '){
        cout << "<Expression’> -> <Empty>" << endl;
        Empty(token);
      }
    }

    //r24
    void Relop(vector<string>& token)
    {
        if (token[0] == "<" || token[0] == ">" || token[0] == "=" || token[0] == "!") {
          token.erase(token.begin());
          if (token[0] == "="){
            token.erase(token.begin());
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
        cout << "<Expression> <Relop> <Expression>" << endl;
        Expression(token);
        Relop(token);
        Expression(token);
    }

    //r22
    void WhileRule(vector<string>& token)
    {
        cout << "<While> -> while (<Condition>) <Statement> endwhile" << endl;
        if (token[0] == "while"){
          token.erase(token.begin());
          if  (token[0][0] == '(') {
            token.erase(token.begin());
            Condition(token);
            if (token[0][0] == ')'){
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
          cout << "Error! Expected While" << endl;
          exit(-1);
        }
    }

    //r21
    void Scan(vector<string>& token)
    {
      cout << "<Scan> -> get(<IDs>);" << endl;
      if (token[0] == "get"){
        token.erase(token.begin());
        if  (token[0][0] == '(') {
          token.erase(token.begin());
          IDs(token);
          if (token[0][0] == ')'){
            if (token[0][0] != ';'){
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
        cout << "Error! Expected Get" << endl;
        exit(-1);
      }
    }

    //r20
    void PrintRule(vector<string>& token) {
        cout << "<Print> -> put(<Expression>);" << endl;
        if (token[0] == "put"){
          token.erase(token.begin());
          if  (token[0] == "(") {
            token.erase(token.begin());
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
          cout << token[0] << endl;
          cout << token[1] << endl;
          cout << token[2] << endl;
          exit(-1);
        }
    }

    //r19
    void Return(vector<string>& token) {
        cout << "return ';' | return <Expression>;" << endl;
        if (token[0] == "return") {
            token.erase(token.begin());
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
            token.erase(token.begin());
        }
        else
        {
            cout << "error: 'if' expected" << endl;
            exit(-1);
        }
        if (token[0] == "(") {
            token.erase(token.begin());
        }
        else
        {
            cout << "error: '(' expected" << endl;
            exit(-1);
        }
        Condition(token);
        if (token[0] == "else"){
          token.erase(token.begin());
          Statement(token);
          if (token[0] != "fi"){
            cout << "Error! Expected fi." <<  endl;
            exit(-1);
          }
        }
        else if (token[0] != "fi"){
          cout << "Error! Expected fi." <<  endl;
          exit(-1);
        }
    }

    //r17
    void Assign(vector<string>& token) {
        cout << "<Assign> -> <Identifier> = <Expression>;" << endl;
        token.erase(token.begin());
        if  (token[0][0] == '='){
          Expression(token);
        }
        else{
          cout << "Error! Expected =" << endl;
          cout << token[0] << endl;
          exit(-1);
        }

    }

    //r16
    void Compound(vector<string>& token) {
        cout << "<Compound> ::= { <Statement List> }" << endl;
        if (token[0] == "{"){
          token.erase(token.begin());
        }
        else{
          cout << "Error! Expected {" << endl;
        }
        Statement_List(token);
        if (token[0] == "}"){
          token.erase(token.begin());
        }
        else{
          cout << "Error! Expected {" << endl;
        }
    }

    //r15
    void Statement(vector<string>& token) {
      if (token[0][0] == '{'){
        cout << "<Statement> -> <Compound>" << endl;
        Compound(token);
      }
      else if (token[1][0] == '='){
        cout << "<Statement> -> <Assign>" << endl;
        Assign(token);
      }
      else if (token[0] == "if"){
        cout << "<Statement> -> <If>" << endl;
        ifRule(token);
      }
      else if (token[0] == "return"){
        cout << "<Statement> -> <Return>" << endl;
        Return(token);
      }
      else if (token[0] == "put"){
        cout << "<Statement> -> <Print>" << endl;
        PrintRule(token);
      }
      else if (token[0] == "get"){
        cout << "<Statement> -> <Scan>" << endl;
        Scan(token);
      }
      else if (token[0] == "while"){
        cout << "<Statement> -> <While>" << endl;
        WhileRule(token);
      }
    }


    //r14
    void Statement_List(vector<string>& token) {
        cout << " <Statement List> -> <Statement> <Statement List Prime>" << endl;
        Statement(token);
        StatementListPrime(token);
        }

    void StatementListPrime(vector<string>& token){
      if ((token[0][0] == ' ') || (token.empty() == true)){
        cout << "<Statement List Prime> -> <Empty>" << endl;
        Empty(token);
      }
      else {
        cout << "<Statement List Prime> -> <Statement List>" << endl;
        Statement_List(token);
      }
    }

    //r13
    void IDs(vector<string>& token) {
        if (isalpha(token[0][0])){
          cout << "IDs -> <Identifier> <IDs Prime>" << endl;
          token.erase(token.begin());
          IDsPrime(token);
        }
        else {
          cout  << "Error! Expecting an Identifier." << endl;
          cout << token[0] << endl;
          exit(-1);
        }
    }

    void  IDsPrime(vector<string>& token){
      if (token[0][0] == ' '){
        cout << "<IDs Prime> -> <Empty>" << endl;
        Empty(token);
      }
      else if (token[0][0] == ','){
        token.erase(token.begin());
        cout << "<IDsPrime> -> , <IDs>" << endl;
        IDs(token);
      }
    }

    //r12
    void Declaration(vector<string>& token) {
      cout << "<Declaration> -> <Qualifier > <IDs>" << endl;
        Qualifier(token);
        IDs(token);
    }

    //11
    void Declaration_List(vector<string>& token) {
        cout << "<Declaration List> -> <Declaration> <Declaration List Prime>" << endl;
        if (token.empty() == false){
          Declaration(token);
          if (token[0][0] != ';'){
            cout << token[0] << endl;
            cout << "Error! Expected ;" <<  endl;
            exit(-1);
          }
          else {
            token.erase(token.begin());
          }
          DeclarationListPrime(token);

      }
    }

    void DeclarationListPrime(vector<string>& token) {
      if (token[0][0] == ' '){
        cout << "<Declaration List Prime> -> <Empty>" << endl;
        Empty(token);
      }
      else{
        cout << "<Declaration List Prime> -> ; <<Declaration List>" << endl;
        Declaration_List(token);
      }
    }

    //10
    void opt_Declaration_List(vector<string>& token) {
      if (token[0][0] == ' '){
        cout << "<Opt Declaration List> -> <Empty>" << endl;
        cout << token[0] << endl;
        Empty(token);
      }
      else {
        cout << "<Opt Declaration List> -> <Declaration List>" << endl;
        Declaration_List(token);
      }
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
        token.erase(token.begin());
    }

    //7
    void Parameter(vector<string>& token) {
      cout << "<Parameter> ::= <IDs > <Qualifier>" << endl;
        IDs(token);
        Qualifier(token);
    }

    //6
    void Parameter_list(vector<string>& token) {
        cout << "<Parameter list> -> <Parameter> <Parameter list Prime> \n <Parameter list Prime> ->  ,<Parameter list> | Epsilon" << endl;
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
      if ((token[0][0] == ' ') || (token.empty() == true)){
        cout << "<Opt Parameter List> -> <Empty>" << endl;
        Empty(token);
      }
      else{
        cout << "<Opt Parameter List> -> <Parameter List>" << endl;
        Parameter_list(token);
      }
    }

    //4
    void Function(vector<string>& token) {
        cout << "<Function> ::= function <Identifier> ( <Opt Parameter List> ) <Opt Declaration List> <Body>" << endl;
        //Display ID
        if (isalpha(token[0][0])){
          cout << "<Function> -> function <Identifier>" << endl;
          token.erase(token.begin());
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
        cout << "<Function Definition> -> <Function>" << endl;
        if(token.empty() == false){
          Function(token);
          if(token.empty() == false){
            cout << "<Function Definition> -> <Function Definition Prime>" << endl;
            Function_Definition(token);
          }
        }
        else{
          cout << "Error! Expected function." << endl;
          exit(-1);
        }
    }

    void Function_Prime(vector<string>& token) {
      if (token[0][0] == ' '){
        cout << "<Function Definition Prime> -> <Empty>" << endl;
        Empty(token);
      }
      else {
        cout << "<Function Definition Prime> -> <Function Definition>" << endl;
        Function(token);
      }
    }

    //2
    void opt_FunctionDefinitions(vector<string>& token) {
        if ((token[0][0] == ' ') || (token.empty() == true)){
          cout << "<Opt Function Definitions> -> <Empty>" << endl;
          Empty(token);
        }
        else {
          cout << "<Opt Function Definitions> -> <Function Definitions>" << endl;
          Function_Definition(token);
        }
    }

    //r1
    void Rat23s(vector<string>& token) {
      cout << token.size() << endl;
        if(token.empty() == false){
          cout << token.back() << endl;
          if(token[0][0] != '#'){
            cout << "<Rat23S> -> <Opt Function Definitions>" << endl;
            opt_FunctionDefinitions(token);
          }
          //Get rid of '#'
          if(token[0][0] == '#'){
            token.erase(token.begin());
          }
          else{
            cout << "Error! Expected # (first instance)" << endl;
            exit(-1);
          }
          //Get rid of excess ' '
          if ((token[0][0] == ' ') || (token.empty() == true)){
            cout << "<Opt Function Definitions> -> <Empty>" << endl;
            Empty(token);
          }
          if(token[0][0] != '#'){
            cout << "<Rat23S> -> <Opt Declaration List>" << endl;
            opt_Declaration_List(token);
          }
          //Get rid of '#'
          if(token[0][0] == '#'){
            token.erase(token.begin());
          }
          else{
            cout << "Error! Expected # (second instance)" << endl;
            cout << token[0] <<  endl;
            exit(-1);
          }
          //Get rid of excess ' '
          if ((token[0][0] == ' ') || (token.empty() == true)){
            cout << "<Opt Function Definitions> -> <Empty>" << endl;
            Empty(token);
          }
          if((token.empty() == false) && (token[0][0] != '#')){
            cout << "<Rat23S> -> <Statement List>" << endl;
            Statement_List(token);
          }
        }
    }


    void lexer(string input, string name_of_output, vector<string>& words, vector<string>& statement) {
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
                        cout << "Done" << endl;
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
                    statement.push_back("Token: Keyword   Lexeme: " + current_token);

                }
                else {
                    outputFile << "Identifier      " << current_token << endl;
                    words.push_back(current_token);
                    statement.push_back("Token: Identifier   Lexeme: " + current_token);

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
                    statement.push_back("Token: Real   Lexeme: " + current_token);

                    decimals = 0;
                }
                else if (isSingleDigit(current_token) == true) {
                    outputFile << "Integer         " << current_token << endl;
                    words.push_back(current_token);
                    statement.push_back("Token: Integer   Lexeme: " + current_token);

                }
                current_token = "";
            }
            else if (isOperator(current_char) == true) {
                if (isLogicalOperator(current_char, next_char) == true) {
                    current_token += current_char;
                    current_token += next_char;
                    outputFile << "Operator        " << current_token << endl;
                    words.push_back(current_token);
                    statement.push_back("Token: Operator   Lexeme: " + current_token);

                    i++;
                }
                else {
                    current_token = current_char;
                    outputFile << "Operator        " << current_token << endl;
                    words.push_back(current_token);
                    statement.push_back("Token: Operator   Lexeme: " + current_token);

                }
                current_token = "";
            }
            else if (isSeparator(current_char) == true) {
                current_token = current_char;
                outputFile << "Separator       " << current_token << endl;
                words.push_back(current_token);
                statement.push_back("Token: Separator   Lexeme: " + current_token);



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
                statement.push_back("Token: Unknown   Lexeme: " + current_token);
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
    ofstream outputFile,lexFile;
    vector <string> test, statement;
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
          lexer(input, name_of_output, test, statement);
          test.push_back(" ");
          }
        }

        cout  << "Size of statements" << statement.size() << endl;
        syntaxAnalyzer(test);
        lexFile.open("lexemelist.txt",ios::app);
        while(!statement.empty()){
          lexFile << statement[0] << endl;
        }
        lexFile.close();


    myfile.close();

    cout << name_of_output + ".txt" << " created" << endl;

    return 0;
}

/* while not finished(i.e. not end of the source file) do
    call the lexer for a token
    print the tokenand lexeme
    endwhile
}*/
