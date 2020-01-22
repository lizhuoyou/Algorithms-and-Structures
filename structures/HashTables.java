public class HashTables {
    public static void main(String[] args) {
        HashTable<String> people = new HashTable<String>();
        people.setMaxLoad(0.1);
        people.add("Navjeet");
        people.add("Vithushan");
        people.add("Nafis");
        people.add("Nafis");
        people.add("Nithin");
        people.add("Farzna");
        people.add("666");
        people.add("233");
        people.add("244");
        System.out.println(people);
        people.remove("233");
        people.remove("FGH");
        System.out.println(people);
        System.out.println(people.getLoad());
    }
}
/*
Hash Tables are big o 1.
No order.
 */