#include "ast.h"

void AST::stampaNodo(ASTNode * node){
        if(node->getType() == NodeType::Number) {
            NumberNode * numero = static_cast<NumberNode*>(node);
            std::cout << numero->getValue();
        } else if (node->getType() == NodeType::BinaryOperator) {
            BinaryOperatorNode * operatore = static_cast<BinaryOperatorNode*>(node);
            std::cout << ""; //parentesi
            stampaNodo(operatore->getLeft());
            std::cout << " " << operatore->getOp() << " ";
            stampaNodo(operatore->getRight());
            std::cout << "";
        } else if (node->getType() == NodeType::Function) {
            FunctionNode* funzione = static_cast<FunctionNode*>(node);
            std::cout << funzione->getFunction() << "(";
            size_t tot = funzione->getArgs().size();
            std::vector<ASTNode *> argomenti = funzione->getArgs();
            //std::cout<< "\n";
            //std::cout << "ARGOMENTI DI " << funzione->getFunction() << std::endl;
            for (size_t i = 0; i < tot; i++)
            {
                stampaNodo(argomenti[i]);
                std::cout << ")";
            }
        }

}


ASTNode * parseFunction(const std::vector<std::string> tokens, size_t &pos){

    std::string function = tokens[pos];
    std::vector<ASTNode *> args;

    //std::cout << "ARGOMENTI DI " << function << std::endl;

    int openParenthesisCount = 1;
    pos = pos + 2;
    //std::cout << "ALLERT->" << tokens[pos] << std::endl;
    std::vector<std::string> nestedTokens;

    while (pos < tokens.size() && openParenthesisCount > 0) { //trova posizione della parentesi chiusa corrispondente       
        if(tokens[pos] == "(") {openParenthesisCount++;}
        else if(tokens[pos] == ")") {
            openParenthesisCount--;
        } 
        //std::cout << "TOKEN: " << tokens[pos] << std::endl;
        nestedTokens.push_back(tokens[pos]); //Creo un sub-vector di Tokens contenente la sotto-espressione/funzione
        pos++;
    }
    size_t pos2 = 0;
    ASTNode * argomento = parseTokens(nestedTokens, pos2);  //
    args.push_back(argomento);

    return new FunctionNode(function, args);
}

// ASTNode * parseNumber(const std::vector<std::string>& tokens, size_t &pos){
//     //size_t startPos= pos;
//     while (pos<tokens.size() && (isNumber(tokens[pos])))
//     {
//         pos ++;
//     }
//     return new NumberNode(tokens[pos]);
// }

// ASTNode * parseOperator(const std::vector<std::string>& tokens, size_t &pos){
//     size_t startPos= pos;
//     while (pos<tokens.size() && (isOperator(tokens[pos])))
//     {
//         pos ++;
//     }
//     return new BinaryOperatorNode(tokens[pos]);
// }

ASTNode* parseTokens(std::vector<std::string> tokens, size_t& pos){

    std::string token = tokens[pos];
    ASTNode * leftOperand;
    if(isNumber(token)){
        leftOperand= new NumberNode(token);
        pos++;
    } else if(isFunction(token)){
        leftOperand = parseFunction(tokens, pos);
    } 
    // else if(isOperator(token)){
    //     std::cout << "ALLERTA" << std::endl;
    //     leftOperand = new NumberNode(token);
    //     pos++;
    // } 
    // else if(token == "("){
    //     leftOperand = parseParenthesis(tokens, pos);
    // }

    while (pos < tokens.size() && isOperator(tokens[pos]))
    {
        std::string op = tokens[pos];
        ASTNode * rightOperand = parseTokens(tokens, ++pos);
        leftOperand = new BinaryOperatorNode(op, leftOperand, rightOperand);
    }
    return leftOperand;
} 

AST* buildAST (std::vector<std::string> tokens){
    size_t pos = 0;
    return new AST(parseTokens(tokens, pos));
}