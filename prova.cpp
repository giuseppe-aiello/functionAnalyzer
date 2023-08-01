#include <iostream>
#include <string>
#include <vector>
#include <stack>

bool isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/') return true;
    else return false;
}


std::vector<std::string> tokenizeExpression(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string currentToken;

    for(size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];

        if(ch == ' '){
            continue; //ignora spazi
        }else if(isOperator(ch)) {
            if(!currentToken.empty()){
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, ch));
        }else if(ch == '(' || ch == ')' || ch == ',') {
            if(!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }
            tokens.push_back(std::string(1, ch));
        // }else if(ch == '(') {

        //     std::cout << "ALLERTA" << std::endl;
        //     //CASO CON (
        //     if(!currentToken.empty()){
        //         tokens.push_back(currentToken);
        //         currentToken.clear();
        //     }

        //     int openParenthesisCount = 1;
        //     size_t closeParenthesisIndex = i + 1;
        //     while (closeParenthesisIndex < expression.length()) { //trova posizione della parentesi chiusa corrispondente
        //         if(openParenthesisCount == 0) break;
        //         else{
                    
        //         if(expression[closeParenthesisIndex] == '(') openParenthesisCount++;
        //         else if(expression[closeParenthesisIndex] == ')') {
        //             openParenthesisCount--;
        //         }
        //         closeParenthesisIndex++;
        //         }
        //     }

        //     //analizza la sotto-espressione in modo ricorsivo
        //     std::string nestedExpression = expression.substr(i+1, closeParenthesisIndex - i - 2);
        //     std::vector<std::string> nestedTokens = tokenizeExpression(nestedExpression); //ricorsione
        //     tokens.insert(tokens.end(), nestedTokens.begin(), nestedTokens.end());

        //     i = closeParenthesisIndex - 1; // aggiorna indice i alla fine della sottoespressione
        }else{
            //CASO operandi e funzioni
            currentToken += ch; //Costruisce token per operandi e funzioni
        }
    }


    if(!currentToken.empty()) {
        tokens.push_back(currentToken);
    }


    return tokens;
}


// int main(int argc, char const *argv[])
// {
//     std::string expression = "13+sin(274 + sqrt(374 - cos(98)) - 738)";

//     std::vector<std::string> tokens = tokenizeExpression(expression);

//     for (const std::string& token : tokens)
//     {
//         std::cout << token << std::endl;
//     }
    
//     return 0;
// }
