#include "tokenizer.hpp"

#include <iostream>
#include <fstream>
#include <graphviz/gvc.h>

int main (int argc, char** argv)
{
    const char* charGraph = "graph{\na -- b;\n}\0";
    Agraph_t* graph = agmemread(const_cast<char*>(charGraph));
    if (graph)
        std::cout << "GRAPH\n";

    GVC_t* gvc;
    gvc = gvContext();
    if (gvc)
        std::cout << "GVC\n";

    gvLayout (gvc, graph, "dot");

    gvRenderFilename (gvc, graph, "png", "a.png");

    gvFreeLayout(gvc, graph);
    agclose (graph); 
    gvFreeContext(gvc);

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
    for (const auto& token : tokens)
        std::cout << token.value << ":" << token.type << ",";
    std::cout << "\n";

    return 0;
}
