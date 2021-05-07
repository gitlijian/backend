#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode
{
    int data;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};

//前序遍历
void preOrderVisit(TreeNode *root)
{
    if (root == nullptr)
        return;
    stack<TreeNode *> nodeStack;
    nodeStack.push(root);
    while (!nodeStack.empty())
    {
        cout << nodeStack.top()->data << " ";
        TreeNode *temp = nodeStack.top();
        nodeStack.pop();
        //前序遍历一定要注意先压入当前节点的右孩子，因为栈是先进后出的结构
        if (temp->right)
            nodeStack.push(temp->right);
        if (temp->left)
            nodeStack.push(temp->left);
    }
}

//中序遍历
void inOrderVisit(TreeNode *root)
{
    if (root == nullptr)
        return;
    stack<TreeNode *> nodeStack;
  
    bool traceback = false; //用来标记当前节点是否是回溯访问的

    nodeStack.push(root);

    while (!nodeStack.empty())
    {
        //如果不是回溯访问，那么不断将栈顶节点的左孩子压入栈，直到叶子节点
        while (nodeStack.top()->left != nullptr && !traceback)
            nodeStack.push(nodeStack.top()->left);

        TreeNode *temp = nodeStack.top();
        cout << temp->data << " ";
        nodeStack.pop();

        if (temp->right)
        {
            traceback = false; //若存在右孩子则将其压入栈，并标记为不是回溯访问
            nodeStack.push(temp->right);
        }
        else
            traceback = true; //若不存在右孩子，则标记为回溯返回
    }
}

//后序遍历
void postOrderVisit(TreeNode *root)
{
    if (root == nullptr)
        return;
    stack<TreeNode *> nodeStack;
    TreeNode *prev = nullptr; //记录上一次从栈中弹出的节点
    bool traceback = false;   //用来标记当前节点是否是回溯访问的

    nodeStack.push(root);
    while (!nodeStack.empty())
    {
        //如果不是回溯访问，则一直将栈顶节点的左孩子压入栈
        while (nodeStack.top()->left != nullptr && !traceback)
            nodeStack.push(nodeStack.top()->left);

        //如果当前节点没有右孩子或者右孩子已经被访问则弹出该节点
        if (nodeStack.top()->right == nullptr || prev == nodeStack.top()->right)
        {
            cout << nodeStack.top()->data << " ";
            prev = nodeStack.top();
            nodeStack.pop();
            traceback = true; //标记回溯返回
        }
        else if (nodeStack.top()->right != nullptr)
        {
            nodeStack.push(nodeStack.top()->right);
            traceback = false; //标记非回溯返回
        }
    }
}

// bfs
void bfs(TreeNode* root) 
{
    if(root == nullptr) return ;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()) 
    {
        TreeNode *node = q.front();
        cout << node->data << " ";

        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);

        q.pop();
    }
}

// dfs 递归实现
void dfs_recursive(TreeNode* root) 
{
    if(root == nullptr) return ;
    cout << root->data << " ";

    if(root->left) dfs_recursive(root->left);
    if(root->right) dfs_recursive(root->right);
}

// dfs 迭代实现
void dfs_iterative(TreeNode* root) 
{
    if(root == nullptr) return ;
    
    stack<TreeNode*> stk;
    stk.push(root);

    while(!stk.empty()) 
    {
        TreeNode* node = stk.top();
        cout << node->data << " ";
        stk.pop();

        if(node->right) stk.push(node->right);
        if(node->left) stk.push(node->left);
    }
}

int main()
{
    /***************构建二叉树*****************/
    TreeNode *n1 = new TreeNode;
    TreeNode *n2 = new TreeNode;
    TreeNode *n3 = new TreeNode;
    TreeNode *n4 = new TreeNode;
    TreeNode *n5 = new TreeNode;
    TreeNode *n6 = new TreeNode;
    TreeNode *n7 = new TreeNode;
    n1->data = 1;
    n1->left = n2;
    n1->right = n3;
    n2->data = 2;
    n2->left = n4;
    n2->right = n5;
    n3->data = 3;
    n3->left = n6;
    n3->right = n7;
    n4->data = 4;
    n5->data = 5;
    n6->data = 6;
    n7->data = 7;
    /****************************************/

    //前序遍历
    cout << "preOrderVisit: ";
    preOrderVisit(n1);
    cout << endl;

    //中序遍历
    cout << "midOrderVisit: ";
    inOrderVisit(n1);
    cout << endl;

    //后序遍历
    cout << "postOrderVisit: ";
    postOrderVisit(n1);
    cout << endl;

    // bfs
    cout << "bfs: ";
    bfs(n1);
    cout << endl;

    // dfs 递归
    cout << "dfs_recursive: ";
    dfs_recursive(n1);
    cout << endl;

    // dfs 迭代
    cout << "dfs_iterative: ";
    dfs_iterative(n1);
    cout << endl;

    system("pause");
    return 0;
}
