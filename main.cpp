#include "ast.h"
#include "tokenizer.h"

int main(int argc, char const *argv[])
{
    std::string str = "14 + sin(274 - sqrt(374 - cos(98 - sin(sqrt(382 + square(1992)) - cos(129)))) - 738)";
    std::vector<std::string> tokens = tokenizeExpression(str);

    //prova
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << tokens[i] << std::endl;
    }
    
    AST * ast = buildAST(tokens);
    ast->stampaNodo();

    FunctionNode* mostNestedFunction = findMostNestedFunction(ast->getRoot());
    std::cout << "\nLa funzione più annidata è: " << mostNestedFunction->getFunction() << std::endl;

    std::vector<FunctionNode*> functionsInOrder;
    collectFunctions(ast->getRoot(), functionsInOrder);
    std::reverse(functionsInOrder.begin(), functionsInOrder.end());
    std::cout << "Funzioni nell'ordine dall'interno verso l'esterno:" << std::endl;
    for(const auto& function : functionsInOrder){
        std::cout << function->getFunction() << std::endl;
    }



    return 0;
}