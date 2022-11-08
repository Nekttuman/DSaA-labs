#include <iostream>
#include <vector>

#include "MyBinaryTree.h"

enum Notation{
    Prefix,
    Infix,
    Postfix,
};


class MathExpression: public BinaryTree<char> {

public:
    MathExpression() = default;


    void parseExpr(const std::string& expr, Notation n){
        deleteTree(root);
        if (n == Prefix) {
            root = new Node{nullptr, nullptr, nullptr, expr[0]};
            for (int i = 1; i < expr.size(); ++i) {
                insert(expr[i]);
            }
        } else if (n == Postfix){
            root = new Node{nullptr, nullptr, nullptr, expr[expr.size()-1]};
            for (int i = expr.size()-2; i >=0 ; --i) {
                insert(expr[i]);
            }
        }
    }

    void insert(char symbol) override {
        auto iter = root;
        auto newNode = new Node{iter, nullptr, nullptr, symbol};

        // find free place
        while (true){
            if (is_operation(iter->data)){
                if (iter->left == nullptr){
                    iter->left = new Node{iter, nullptr, nullptr, symbol};
                    return;
                } else if(is_operation(iter->left->data)){
                    iter = iter ->left;
                    continue;
                }
                else if (iter->right == nullptr){
                    iter->right = new Node{iter, nullptr, nullptr, symbol};
                    return;
                } else if (is_operation(iter->right->data)){
                    iter = iter->right;
                    continue;
                } else{
                    if (iter->parent->right == nullptr) {
                        iter->parent->right = newNode;
                        return;
                    } else {
                        iter = iter->parent->right;
                    }
                }
            } else{
                if (iter->parent->right == nullptr) {
                    iter->parent->right = newNode;
                    return;
                } else {
                    iter = iter->parent->right;
                }
            }
        }
    }


    void printPrefix(){
        preorderPrint();
    }
    void printPostfix(){
        backwardPreorderPrint();
    }
    void printInfix(){
        inorderPrint();
    }

    void backwardPreorderPrint(){
        backwardPreorder(root);
        std::cout << "\n";
    }

private:
    void backwardPreorder(Node *n) {
        if (n != nullptr) {
            backwardPreorder(n->right);
            backwardPreorder(n->left);
            std::cout << n->data << " ";
        }
    }

    bool is_operation(char operand){
        return ((operand == '*') || (operand == '+') || (operand == '-') || (operand == '/'));
    }
    bool is_bracket(char operand){
        return ((operand == '(') || (operand == ')'));
    }

};

void mathExrpExample(){
    MathExpression expr;
    expr.parseExpr("-+/ABC*DE", Prefix);


    std::cout<<"Infix  :    ";
    expr.printInfix();
    std::cout<<"Prefix :    ";
    expr.printPrefix();
    std::cout<<"Postfix:    ";
    expr.printPostfix();

    std::cout<<"\ntree:\n";
    expr.beautyPrint();


    expr.parseExpr("KCDE**AB---", Postfix);

    std::cout<<"Infix  :    ";
    expr.printInfix();
    std::cout<<"Prefix :    ";
    expr.printPrefix();
    std::cout<<"Postfix:    ";
    expr.printPostfix();

    std::cout<<"\ntree:\n";
    expr.beautyPrint();

}

int main() {
    std::vector<int> v {5,1,8,3,-10,23,55};

    BinarySearchTree<int> tree(v.begin(), v.end());
    std::cout<<"min: "<<tree.getMin()<<"\nmax: "<<tree.getMax()<<"\n";

    tree.inorderPrint();
    tree.preorderPrint();
    tree.preorderPrint();

    std::cout << "is 1 in tree: " << bool(tree.contains(1)) <<"\n";
    std::cout << "is 4 in tree: " << bool(tree.contains(4))<<"\n";

    std::cout<<"next after 5"<<tree.findPreorderSuccessor(5)<<"\n";
    std::cout<<"next before 5"<<tree.findInorderSuccessor(5)<<"\n";

    std::cout<<"bfs:\n";
    tree.bfsPrint();
    tree.remove(5);
    std::cout<<"beauty print after 5 removed:\n";
    tree.beautyPrint();

    return 0;
}
