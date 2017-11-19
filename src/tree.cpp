#include "tree.hpp"
#include <boost/lexical_cast.hpp>
#include <cmath>

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

void ExprNode::write (std::string& dot, std::size_t& node) const
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

void ExprNode::evaluate ()
{
    if ( left_ )
        delete left_;
    if ( right_ )
        delete right_;
    left_ = right_ = nullptr;
}

void Operation::evaluate ()
{
    if ( !left_ || !right_ )
    {
        if ( left_ )
            delete left_;
        if ( right_ )
            delete right_;
        left_ = right_ = nullptr;
    }
    left_->evaluate ();
    right_->evaluate ();
    long int left = boost::lexical_cast<long int>(left_->getData());
    long int right = boost::lexical_cast<long int>(right_->getData());
    long int result = 0;
    if (data_ == "+")
        result = left + right;
    if (data_ == "-")
        result = left - right;
    if (data_ == "*")
        result = left * right;
    if (data_ == "/")
        result = right ? left / right : 0;

    data_ = boost::lexical_cast<std::string>(result);
    delete left_;
    delete right_;
    left_ = nullptr;
    right_ = nullptr;

}

void Call::evaluate ()
{
    if ( !left_ || !right_ )
        return ;
    right_->evaluate ();
    long int right = boost::lexical_cast<long int>(right_->getData());
    long int result = 0;
    if (left_->getData() == "cos")
        result = cos(right);
    else if (left_->getData() == "sin")
        result = cos(right);
    else
        result = right;

    data_ = boost::lexical_cast<std::string>(result);
    delete left_;
    delete right_;
    left_ = right_ = nullptr;
}



} /* namespace Expresser */

