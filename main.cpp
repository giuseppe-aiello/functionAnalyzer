#include "ast.h"
#include "tokenizer.h"

int main(int argc, char const *argv[])
{
    std::string str = "14 + sin(274 + sin(2392 * cos(192)) - sqrt(374 - cos(98)) - 738)";
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