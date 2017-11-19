#ifndef H_39249F013CA64163B165AAF8E256098C

#define H_39249F013CA64163B165AAF8E256098C

#include <string>

namespace Expresser
{

class ExprNode
{
    ExprNode (const ExprNode&) = delete;
    ExprNode (ExprNode&&) = delete;
    ExprNode& operator= (const ExprNode&) = delete;
    ExprNode& operator= (ExprNode&&) = delete;

    protected:

    ExprNode* left_;
    ExprNode* right_;

    std::string data_;

    public:

    ExprNode ();

    virtual void write (std::string& dot, std::size_t& node);

    void setLeft (ExprNode* left)
    {
        left_ = left;
    }
    void setRight (ExprNode* right)
    {
        right_ = right;
    }
    ExprNode* getLeft () const
    {
        return left_;
    }
    ExprNode* getRight () const
    {
        return right_;
    }

    void setData (const std::string& data)
    {
        data_ = data;
    }

    virtual ~ExprNode ();

};
    
}

#endif /* H_39249F013CA64163B165AAF8E256098C */
