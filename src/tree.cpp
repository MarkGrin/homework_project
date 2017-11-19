#include "tree.hpp"

namespace Expresser
{

ExprNode::ExprNode ()
    :
        left_  (nullptr),
        right_ (nullptr)
    {
    }        

ExprNode::~ExprNode ()
{
    delete left_;
    delete right_;
}    

void ExprNode::write (std::string& dot, std::size_t& node)
{
    std::size_t rootNode = node;
    node++;
    dot += "node" + std::to_string(rootNode) + " [label=\"" + data_ + "\"];\n";
    if ( left_ )
    {
        std::size_t childNode = node;
        left_->write(dot, node);
        dot += "node" + std::to_string(rootNode) + " -> node" + std::to_string(childNode) + ";\n";
    }
    if ( right_ )
    {
        std::size_t childNode = node;
        right_->write(dot, node);
        dot += "node" + std::to_string(rootNode) + " -> node" + std::to_string(childNode) + ";\n";
    }

}    

} /* namespace Expresser */

