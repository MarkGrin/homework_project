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
    std::size_t nodeNumber = node;
    node++;
    dot += "node" + std::to_string(nodeNumber) + "[label=\"" + data_ + "\"];\n";
    if ( left_ )
    {
        dot += "node" + std::to_string(nodeNumber) + " -> node" + std::to_string(node);
        left_->write(dot, node);
    }
    if ( right_ )
    {
        dot += "node" + std::to_string(nodeNumber) + " -> node" + std::to_string(node) + ";";
        right_->write(dot, node);
    }

}    

}

#endif /* H_39249F013CA64163B165AAF8E256098C */
