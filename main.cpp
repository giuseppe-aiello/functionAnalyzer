#include "ast.h"
#include "tokenizer.h"

int main(int argc, char const *argv[])
{
    std::string str = "14 + sin(274 - sqrt(374 - cos(129)) - 738) - 40 +3 - sqrt(2 , 329 +29383 ,  33834848)";
    std::vector<std::string> tokens = tokenizeExpression(str);

    //prova
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << tokens[i] << std::endl;
    }
    
    AST * ast = buildAST(tokens);
    ast->printAST();
    /*
    FunctionNode* mostNestedFunction = findMostNestedFunction(ast->getRoot());
    std::cout << "\nLa funzione più annidata è: " << mostNestedFunction->getFunction();
    std::cout << "(";
    for (size_t i = 0; i < mostNestedFunction->getArgs().size(); i++)
    {
        printNode(mostNestedFunction->getArgs()[i]);
    }
    std::cout << ")" << std::endl;

    std::vector<FunctionNode*> functionsInOrder;
    collectFunctions(ast->getRoot(), functionsInOrder);
    std::reverse(functionsInOrder.begin(), functionsInOrder.end());

    std::cout << "Funzioni nell'ordine dall'interno verso l'esterno:" << std::endl;
    for(const auto& function : functionsInOrder){
        std::cout << function->getFunction() << "(";
        printNode(function->getArgs()[0]);
        std::cout << ")" << std::endl;
    }
*/
    return 0;
}