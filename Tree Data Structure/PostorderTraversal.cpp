/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#define pb push_back
 
void PT(TreeNode *root, vector<int> &output){
    if(root == NULL) return;
    
    PT(root->left, output);
    PT(root->right, output);
    output.pb(root->val);
}
 
vector<int> Solution::postorderTraversal(TreeNode* A) {
    vector<int> output;
    PT(A, output);
    return output;
}
