// HashTable.java
// By Lizhuo You
// This is a data structure that stores values with index. List.
// The index depends on the size of the hashtable and the value's hash.
// In lots of situations the value can be accessed with O(1) efficiency.
import java.util.ArrayList;
import java.util.LinkedList;

public class HashTable<T> {
    private  ArrayList<LinkedList<T>> table;
    private int size;       // it accounts the num of the values.
    private int tableSize;      // it is the full size of the table.
    private double maxLoad;     // max load percentage
    public HashTable(){
        size = 0;
        tableSize = 10;
        maxLoad = 0.6;
        clear(10);
    }

    private void clear(int n){
        // it clears the table
        table = new ArrayList<LinkedList<T>>();
        for(int i = 0;i<n;i++){
            table.add(null);        // add spots for the table.
        }
    }

    public void add(T val){
        // add a value to the table.
        int pos = Math.abs(val.hashCode())%table.size();
        LinkedList<T>list = table.get(pos);

        if(list == null){           // ensure there is a LinkedList at the index to hold the value
            list = new LinkedList<T>();
            table.set(pos,list);
        }

        list.add(val);
        size++;

        if ((double) size / (double) tableSize > maxLoad) {     // check if the load amount is over max percent
            resize();
        }
    }

    public void resize() {
        // resize the table to increase its spots which allows more values to be entered.
        ArrayList<LinkedList<T>> tmp = table;
        size = 0;
        tableSize = table.size()*10;        // update the full size of the table
        clear(table.size() * 10);       // clear and increase the size of the table to hold more values.
        for (LinkedList<T> lst : tmp) {
            if(lst != null){
                for (T val : lst) {
                    add(val);       // add back all the values to the table
                }
            }
        }
    }

    public void remove(T val) {
        // it removes a val from the table
        if (contains(val)) {        // first ensure the value is in the table
            int pos = Math.abs(val.hashCode())%table.size();        // get position of the value
            LinkedList<T>list = table.get(pos);         // get the list in which the value is put

            if (list.size() == 1) {     // remove the value.
                table.set(pos, null);
            } else {
                list.remove(val);
            }

            size--;
        }
    }

    public boolean contains(T val) {
        // it checks if the val is in the table and returns true/false
        int pos = Math.abs(val.hashCode())%table.size();
        if (table.get(pos) == null) {
            return false;       // if there is nothing at the pos, the val is not in the table.
        }

        for (T n : table.get(pos)) {
            if (n.hashCode() == val.hashCode()) {       // check if the val actually exists.
                return true;
            }
        }

        return false;
    }

    public void setMaxLoad(double percent) {
        // set the max load of the table
        if (percent >= 0.1 && percent <= 0.8) {     // check if the new maxLoad is valid
            maxLoad = percent;
        }
    }

    public void setLoad(double percent) {
        // set the max load of the table and resize the table if the max load decreased
        if (percent >= 0.1 && percent <= 0.8) {     // check if the new maxLoad is valid
            if (percent < maxLoad) {
                if((double) size / (double) tableSize > percent) {  // check if it is necessary to resize the table.
                    resize();       // reset the hash table to force the load to be what was asked for
                }
            }
            maxLoad = percent;
        }
    }

    public double getLoad() {
        // return how full the hash table is
        return (double) size / (double) tableSize;
    }

    public ArrayList<T> toArray() {
        // return an ArrayList of the stored objects
        ArrayList<T> ans = new ArrayList<T>();      // answer
        for (LinkedList<T> lst : table) {
            if (lst != null) {
                for(T val: lst){
                    ans.add(val);   // store the val to the answer
                }
            }
        }

        return ans;     // return the answer.
    }

    @Override
    public String toString() {
        // returns a string with the contents of the table.
        String ans = "";
        for (LinkedList<T> lst : table) {
            if (lst != null) {
                for(T val: lst){
                    ans += " ," + val;
                }
            }
        }
        if (!ans.equals("")) {
            ans = ans.substring(2);
        }
        return ans;
    }
}