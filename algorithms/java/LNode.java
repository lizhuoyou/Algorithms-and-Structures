// LNode.java
// by Lizhuo You
public class LNode {
    private int val;
    private LNode next;
    private LNode previous;
    public LNode(int v, LNode p, LNode n){
        val = v;
        previous = p;
        next = n;
    }

    public int getVal(){
        // get the LNode's value
        return val;
    }

    public void setVal(int v) {
        // reset the LNode's value.
        val = v;
    }

    public LNode getNext(){
        // return the next LNode ( sequence: head to tail)
        return next;
    }

    public void setNext(LNode n) {
        // reset the LNode's next LNode.
        next = n;
    }

    public LNode getPrevious(){
        // return the previous LNode ( sequence: head to tail)
        return previous;
    }

    public void setPrevious(LNode previous) {
        // reset the LNode's previous LNode.
        this.previous = previous;
    }
}
