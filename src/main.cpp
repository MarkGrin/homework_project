#include "tokenizer.hpp"
#include "construct.hpp"

#include <iostream>
#include <fstream>
#include <graphviz/gvc.h>

void draw (const Expresser::ExprNode* node, const std::string& name)
{
    std::string graphString = "digraph {\n";
    std::size_t i = 0;
    node->write (graphString, i);
    graphString += "\n}";

    std::cout << ".dot result\n";
    std::cout << graphString << "\n";

    Agraph_t* graph = agmemread(const_cast<char*>(graphString.data()));

    GVC_t* gvc;
    gvc = gvContext();

    gvLayout (gvc, graph, "dot");

    gvRenderFilename (gvc, graph, "png", name.data());

    gvFreeLayout(gvc, graph);
    agclose (graph); 
    gvFreeContext(gvc);
}

Expresser::ExprNode* findLow (Expresser::ExprNode* node)
{
    if ( node->isLeaf() )
        return node;
    Expresser::ExprNode* left  = node->getLeft();
    Expresser::ExprNode* right = node->getRight();
    if ( left )
    {
        if ( left->isLeaf() )
            return left;
        else
            return findLow (left);
    }
    if ( right )
    {
        if ( right->isLeaf() )
            return right;
        else
            return findLow (right);
    }
    return nullptr;
}

void evaluate (Expresser::ExprNode* node, const char* name)
{
    std::string fileName = name;
    Expresser::ExprNode* lowNode = nullptr;
    std::size_t i = 0;
    while ( lowNode != node )
    {
        draw (node, name + std::to_string(i) + ".png");
        lowNode = findLow (node);
        lowNode->evaluate();
    }
    draw (node, name + std::to_string(i) + ".png");
}

int main (int argc, char** argv)
{
    if ( argc != 2 )
    {
        std::cout << "Usage: expresser $1\n$1 - filename with expression\n";
        return 1;
    }

    std::ifstream file;
    file.open (argv[1], std::ios::in);
    if ( !file.is_open() )
    {
        std::cout << "Error: Can't open file\n";
        return 1;
    }

    std::string expression;
    file.seekg(0, std::ios::end);   
    expression.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    expression.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    std::cout << expression;

    std::list<Expresser::Token> tokens = Expresser::tokenize(expression);
    std::cout << "token result:\n";
    for (const auto& token : tokens)
        std::cout << "{" << token.value << "}:[" << token.type << "], ";
    std::cout << "\n";

    if ( tokens.empty() )
        return 1;

    Expresser::ExprNode* node = constructTree (tokens);

    if ( !node )
    {
        std::cout << "node:" << node << "\n";
        return 1;
    }

    evaluate (node, argv[1]);

    if (node)
        delete node;

    return 0;
}
