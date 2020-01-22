// LList.java
// by Lizhuo You
// this LList allows user to create a double linked list, which means each node connects to its previous node and its
// next node. The LList is a queue, which is a data structure that "first in first out". It has several methods for
// users to edit the data, including delete, deleteAt, sortedInsert, removeDuplicates, reverse and clone.
public class LList {
    private LNode head;
    private LNode tail;

    public LList(){
        head = null;        // set head and tail to null since the list is empty at the start.
        tail = null;
    }

    public void push(int n) {
        // add an element to the tail of the LList.
        LNode tmp = new LNode(n, tail, null);
        if(tmp.getPrevious() != null){
            tmp.getPrevious().setNext(tmp);     // add tmp to the tail.
        }
        tail = tmp;         // set tmp as tail.

        if (head == null) {     // if the LList is empty, set head.
            head = tmp;
        }
    }

    public int pop() {
        // it removes the head of the list and returns its value.
        int ans = head.getVal();    // get the return value
        head = head.getNext();      // reset head.

        if (head != null) {
            head.setPrevious(null);
        } else {
            tail = null;        // if there was only one LNode, then the list should be empty after pop.
        }

        return ans;
    }

    public void enqueue(int n) {
        // add an element to the tail of the LList.
        LNode tmp = new LNode(n, tail, null);
        if(tmp.getPrevious() != null){
            tmp.getPrevious().setNext(tmp);     // add tmp to the tail.
        }
        tail = tmp;         // set tmp as tail.

        if (head == null) {     // if the LList is empty, set head.
            head = tmp;
        }
    }

    public int dequeue() {
        // it removes the head of the list and returns its value.
        int ans = head.getVal();    // get the return value
        head = head.getNext();      // reset head.

        if (head != null) {
            head.setPrevious(null);
        } else {
            tail = null;        // if there was only one LNode, then the list should be empty after dequeue.
        }

        return ans;
    }

    @Override
    public String toString(){
        // it give a string that stores the list with punctuations like [] and ,
        String ans = "[";
        LNode tmp = head;

        while (tmp != null) {
            ans += tmp.getVal()+", ";           // add the integers to ans.
            tmp = tmp.getNext();
        }

        if (ans.length() > 1) {
            ans = ans.substring(0,ans.length()-2);      // remove the extra  ", "
        }

        return ans + "]";
    }

    private void delete(LNode ln) {
        // it takes a LNode reference and removes it from the list.
        // it is private because it is deliberately made for other methods.
        if(ln.getPrevious() != null){           // check if this LNode is the head.
            ln.getPrevious().setNext(ln.getNext());
        } else {
            head = head.getNext();
            head.setPrevious(null);
        }

        if (ln.getNext() != null) {             // check if this LNode is the tail.
            ln.getNext().setPrevious(ln.getPrevious());
        } else {
            tail = null;
        }
    }

    public void delete(int integer) {
        // takes an integer and remove the LNode with that integer value.

        LNode tmp = head;

        while (tmp.getVal() != integer) {
            tmp = tmp.getNext();        // find the LNode.
        }

        delete(tmp);
    }

    public void deleteAt(int position) {
        // takes the position of the element to delete it.
        // the position is counted from head to tail.
        LNode tmp = head;

        for (int i = 0; i < position-1; i++) {
            tmp = tmp.getNext();        // get the element
        }

        delete(tmp);
    }

    public void sortedInsert(int n, int position){
        // adds a new node into the correct position of the list (ascending from tail to head)
        if(tail!=null){         // check if the node is 0;
            LNode tmp = tail;
            for (int i = 0; i < position - 1; i++) {
                tmp = tmp.getPrevious();        // find the previous LNode for the
            }

            LNode nNode = new LNode(n , tmp.getPrevious(), tmp);    // add the node

            if (tmp.getPrevious() != null) {        // reset previous node
                tmp.getPrevious().setNext(nNode);
            }

            tmp.setPrevious(nNode);
        } else {
            enqueue(n);     // if the list is empty, the node will be enqueued.
        }
    }

    private void removeDuplicates(int n, LNode currentNode) {
        // this is for removeDuplicates.
        // It takes in a integer and remove the following LNodes in the list with the same value.
        while (currentNode != null) {       // null means it is the end

            if (currentNode.getVal() == n) {
                delete(currentNode);            // delete the LNode with same value.
            }

            currentNode = currentNode.getNext();
        }
    }

    public void  removeDuplicates(){
        // it removes the duplicates from the list.
        LNode tmp = head;
        while(tmp != null){     // go through the list
            removeDuplicates(tmp.getVal(), tmp.getNext());
            tmp = tmp.getNext();
        }
    }

    public void reverse() {
        // reverses the order of the nodes in the list
        LNode tmp = head;

        while (tmp != null) {
            LNode next = tmp.getNext();
            tmp.setNext(tmp.getPrevious());     // reverse each node
            tmp.setPrevious(next);
            tmp = next;
        }

        LNode oldHead = head;       // reverse head and tail.
        head = tail;
        tail = oldHead;
    }

    public LList clone(){
        // returns a new copy of the LList.
        LList ans = new LList();    // create a new LList.
        LNode tmp = head;
        while (tmp != null) {
            ans.enqueue(tmp.getVal());  // construct the new one with the LList's values
            tmp = tmp.getNext();
        }
        return ans;
    }
}
