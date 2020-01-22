// BTree.java
// Lizhuo You
// this is a binary tree class that store integers in order (from low to high). It can get in new values or values
// from another tree. It can be examined for its properties.  It also can be print out in different orders.
public class BTree {
    private BNode root;
    private static int IN = 0;      // IN, PRE, & POST are for display, which denotes in-order, pre-order & post-order.
    private static int PRE = -1;
    private static int POST = 1;

    public BTree(){
        root = null;
    }

    public void add(int v){
        // add a value to the binary tree
        if(root == null){
            root = new BNode(v);
        }
        else{
            add(v,root);        // call recursive add function
        }
    }

    public void add(int v,BNode k){
        // this is a recursive method that add a value to the tree.
        if(v>k.getVal()){       // check if the value is greater than current node's value.
            if(k.getRight()==null){
                k.setRight(new BNode(v));
            }
            else {
                add(v,k.getRight());
            }
        } else if(v<k.getVal()){
            if(k.getLeft() == null){
                k.setLeft(new BNode(v));
            }
            else {
                add(v, k.getLeft());
            }
        }
    }

    @Override
    public String toString(){
        return ("["+treeString(root)+"]").replace(" ,]", "]");
    }

    public String treeString(BNode branch) {
        // output a string containing the BTree's values
        if (branch == null) {
            return "";
        } else {
            return treeString(branch.getLeft()) + branch.getVal() + " ," + treeString(branch.getRight());
        }
    }

    private int depth(BNode BN, int num, int currentDepth) {
        // it is a private method for public depth method.
        if (BN == null) {
            return -1;      // -1 is always smaller than currentDepth, which prevents bugs.
        } else if (BN.getVal() == num) {
            return currentDepth;
        } else {
            return Math.max(depth(BN.getRight(),num,currentDepth+1),depth(BN.getLeft(), num, currentDepth+1));  // return the larger value which should be the depth
        }
    }

    public int depth(int num) {
        // return the depth of the BNode with the value.
        return depth(root, num , 0);
    }

    public void display(){
        // it prints out the tree in order.
        System.out.println(("["+treeString(root)+"]").replace(" ,]", "]"));
    }

    private String treeStringPre(BNode branch) {
        // it is for display, which returns the tree's data in pre-order.
        if (branch == null) {
            return "";
        } else {
            return branch.getVal()  + " ," + treeStringPre(branch.getLeft()) + treeStringPre(branch.getRight()) ;
        }
    }

    private String treeStringPost(BNode branch) {
        // it is for display, which returns the tree's data in post-order.
        if (branch == null) {
            return "";
        } else {
            return treeStringPost(branch.getLeft()) + treeStringPost(branch.getRight()) + branch.getVal() + " ,";
        }
    }

    public void display(int state) {
        // it prints out the tree in certain
        if (state == IN) {          // print the tree in order.
            System.out.println(("["+treeString(root)+"]").replace(" ,]", "]"));
        } else if (state == PRE) {      // print the tree in pre-order.
            System.out.println(("["+treeStringPre(root)+"]").replace(" ,]", "]"));
        } else if (state == POST) {     // print the tree in post-order.
            System.out.println(("["+treeStringPost(root)+"]").replace(" ,]", "]"));
        }
    }

    private int countLeaves(BNode currentNode) {
        // this is a private recursive method that returns how many leaves the tree have.
        if (currentNode.getLeft() == null && currentNode.getRight() == null) {
            return 1;
        } else {
            int ans = 0;
            if (currentNode.getLeft() != null) {
                ans += countLeaves(currentNode.getLeft());
            }
            if (currentNode.getRight() != null) {
                ans += countLeaves(currentNode.getRight());
            }
            return ans;
        }
    }

    public int countLeaves(){
        // return how many leaves the tree have.
        return countLeaves(root);
    }

    private int height(BNode BN, int currentDepth) {
        // it is for public height, which is a recursive function that calculates the height of the tree.
        if (BN == null) {
            return currentDepth-1;      // -1 is because currentDepth should not increase when the node is null
        } else {
            return Math.max(height(BN.getRight(),currentDepth+1),height(BN.getLeft(), currentDepth+1));
        }
    }

    public int height() {
        // it returns the height of the tree
        return height(root,0);
    }

    private BNode findBNode(BNode start, int value) {
        // this function finds the BNode which has the value.
        if (start == null) {
            return null;
        } else if (start.getVal() == value) {
            return start;
        } else {
            return value < start.getVal() ? findBNode(start.getLeft(), value) : findBNode(start.getRight(), value);
        }
    }

    public boolean isAncestor(int ancestor, int child){
        // shall I use findPreviousNode instead to save some space overall in the class?
        BNode ancestorNode = findBNode(root, ancestor);
        if (findBNode(ancestorNode, child) != null) {
            return true;
        }
        return false;
    }

    private void graft(BNode currentNode, BNode addedNode){
        // it attaches a BNode to the tree.
        if(currentNode.getRight()==null){       // check if the BNode can be attach to the tree at this location.
            currentNode.setRight(addedNode);
        }
        else {
            graft(currentNode.getRight(), addedNode);   // if the location is occupied, find the next location.
        }
    }

    private void makeLeafNull(BNode current, int value) {
        // it is for delete method, which makes the leaf node null.
        BNode left = current.getLeft();
        BNode right = current.getRight();
        if (left != null) {                 // find the leaf node's previous node to set the leaf node null.
            if (left.getVal() == value) {
                current.setLeft(null);
            } else if(current.getVal()>value){
                makeLeafNull(left, value);  // recurse to find the node.
            }
        }

        if (right != null) {
            if (right.getVal() == value) {
                current.setRight(null);
            } else if(current.getVal()<value){
                makeLeafNull(right, value);
            }
        }
    }

    public void delete(int num){
        // this method delete a BNode.
        BNode theNode = findBNode(root, num);
        BNode left = theNode.getLeft();
        BNode right = theNode.getRight();
        if (left != null) {
            theNode.setVal(left.getVal());          // make the BNode become its left BNode to remove the BNode.
            theNode.setLeft(left.getLeft());
            theNode.setRight(left.getRight());
            if (right != null) {
                graft(theNode, right);              // add back the right Node to the tree.
            }
        } else if (right != null) {
            theNode.setVal(right.getVal());         // make the BNode become its right BNode to remove the BNode.
            theNode.setLeft(right.getLeft());
            theNode.setRight(right.getRight());
        } else {
            if (num == root.getVal()) {
                root = null;
            } else {
                makeLeafNull(root,num);            // when the BNode is a leaf and it should be removed, use the method to null
            }
        }
    }

    private int lowestHeight(BNode BN, int currentDepth) {
        // it is for isBalanced, which is a recursive function that calculates the lowest height of the tree.
        if (BN == null) {
            return currentDepth-1;      // -1 is because currentDepth should not increase when the node is null
        } else {
            return Math.min(height(BN.getRight(),currentDepth+1),height(BN.getLeft(), currentDepth+1));
        }
    }

    public boolean isBalanced(){
        // checks if the tree is balanced.
        int maxHeight = height();
        int minHeight = lowestHeight(root,0);
        if (maxHeight-minHeight<=1) {       // compare the largest difference in height between leaves.
            return true;
        } else {
            return false;
        }
    }

    private void addNode(BNode bn) {
        // it adds a node to this current node.
        if(bn != null){
            add(bn.getVal());       // add the node's value to current tree.
            addNode(bn.getLeft());      // add other linked nodes' values to current tree.
            addNode(bn.getRight());
        }
    }

    public void add(BTree bt) {
        // it takes a BTree as parameter and adds all its nodes to current tree.
        addNode(bt.root);
    }
}
