#ifndef H_39249F013CA64163B165AAF8E256098C

#define H_39249F013CA64163B165AAF8E256098C

namespace Expresser
{

class ExprNode
{
    ExprNode ();
    ExprNode (const ExprNode&) = delete;
    ExprNode (ExprNode&&) = delete;
    ExprNode& operator= (const ExprNode&) = delete;
    ExprNode& operator= (ExprNode&&) = delete;

    protected:

    ExprNode* left_;
    ExprNode* right_;

    public:

    void setLeft (ExprNode* left)
    {
        left_ = left;
    }
    void setRight (ExprNode* right)
    {
        right_ = right;
    }

};
    
}

#endif /* H_39249F013CA64163B165AAF8E256098C */
