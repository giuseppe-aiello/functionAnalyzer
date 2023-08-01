#include <string>
#include <vector>
#include <algorithm>
#include "prova.cpp"

//Funzioni ausiliarie
bool isOperator(std::string val)
{
    if(val == "+" || val == "-" || val == "*" || val == "/") return true;
    else return false;
}

bool isFunction(std::string val)
{
    if(val == "sin" || val == "sqrt" || val == "cos" || val == "square") return true;
    else return false;
}

bool isNumber(std::string val)
{
    return !val.empty() && std::all_of(val.begin(), val.end(), ::isdigit);
}

enum class NodeType {
    Number,
    BinaryOperator,
    Function
};

// Struttura Nodo
class ASTNode {
public:
    virtual ~ASTNode() {}
    virtual NodeType getType() const = 0;
};

class NumberNode : public ASTNode {
public:
    NumberNode(std::string value) : value(value) {}   
    NodeType getType() const override {return NodeType::Number; }

    std::string getValue() const {return value;}

private:
    std::string value;

};

class BinaryOperatorNode : public ASTNode {
public:
    BinaryOperatorNode(std::string operazione, ASTNode * sx, ASTNode* dx)
    : op(operazione), left(sx), right(dx) {}

    NodeType getType() const override {return NodeType::BinaryOperator; }

    std::string getOp() const {return op;}

    ASTNode * getLeft(){
        return left;
    }

    ASTNode * getRight(){
        return right;
    }

private:
    std::string op;
    ASTNode * left;
    ASTNode * right;
};

class FunctionNode : public ASTNode {
public:
    FunctionNode(std::string& nome, std::vector<ASTNode *>& args)
    : name(nome), arguments(args) {}

    NodeType getType() const override {return NodeType::Function; }

    std::string getFunction() const {return name;}

    std::vector<ASTNode *> getArgs() const {return arguments;}

private:
    std::string name;
    std::vector<ASTNode *> arguments;
};

//Struttura Abstract Syntax Tree
class AST {
public:
    AST(ASTNode * radice) : root(radice) {}
    AST() : root(nullptr) {}
   
    void aggiungiNodo(ASTNode * node){
        root = node;
    }

    void stampaNodo(){
        stampaNodo(this->root);
    }

private:
    ASTNode * root;

    void stampaNodo(ASTNode * node){
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
                //std::cout << argomenti[i] << std::endl;
            }
            std::cout << ")";
        }

    }
};

//FUnzioni per l'analisi sintattica
ASTNode * parseNumber(const std::vector<std::string>& tokens, size_t &pos){
    //size_t startPos= pos;
    while (pos<tokens.size() && (isNumber(tokens[pos])))
    {
        pos ++;
    }
    return new NumberNode(tokens[pos]);
    
}

ASTNode* parseTokens(std::vector<std::string> tokens, size_t& pos); //per scope

ASTNode * parseFunction(const std::vector<std::string> tokens, size_t &pos){

    std::string function = tokens[pos];
    std::vector<ASTNode *> args;

    //std::cout << "ARGOMENTI DI " << function << std::endl;

    int openParenthesisCount = 1;
    pos = pos + 2;
    //std::cout << "ALLERT->" << tokens[pos] << std::endl;

    while (pos < tokens.size() && openParenthesisCount > 0) { //trova posizione della parentesi chiusa corrispondente       
        if(tokens[pos] == "(") {openParenthesisCount++;}
        else if(tokens[pos] == ")") {
            openParenthesisCount--;
        } else {
            ASTNode * argomento = parseTokens(tokens, pos);
            args.push_back(argomento);
            }
        pos++;
    }
    return new FunctionNode(function, args);
}

// ASTNode * parseParenthesis(const std::vector<std::string> tokens, size_t &pos){
//     ASTNode * argSuccessivo;
//     int openParenthesisCount = 1;
//     pos = pos+1;
//     argSuccessivo = parseTokens(tokens, pos);
//     while (pos < tokens.size() && openParenthesisCount > 0) { //trova posizione della parentesi chiusa corrispondente       
//         if(tokens[pos] == "(") openParenthesisCount++;
//         else if(tokens[pos] == ")") {
//             openParenthesisCount--;
//         }
//         pos++;
//     }
//     return argSuccessivo;
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

int main(int argc, char const *argv[])
{
    std::string str = "14 + sin(274 + sqrt(374 - cos(98)) - 738)";
    std::vector<std::string> tokens = tokenizeExpression(str);

    //prova
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << tokens[i] << std::endl;
    }
    
    AST * ast = buildAST(tokens);
    ast->stampaNodo();
    return 0;
}
