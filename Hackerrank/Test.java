import java.util.Arrays;
import java.util.List;

class Test {
    static int anagram(String s) {
        int l = s.length();
        int res = 0;
        if (l % 2 == 1) return -1;
        
        String first = s.substring(0, l/2);
        String last = s.substring(l/2, l);
        List<String> firstList = Arrays.asList(first.split(""));

        for(String a: firstList) {
            int index = last.indexOf(a);
            if (index == -1) {
                res += 1;
            } else {
                last = last.substring(0, index) + last.substring(index + 1);
            }
        }
        return res;
    }
    public static void main(String[] args) {

        String x = "1;2;3";
        System.out.println(x.split(";").length);
        
        List<String> a = Arrays.asList("0100101010100010110100100110110100011100111110101001011001110111110000101011011111011001111100011101".split("010"));

        System.out.println(a);
        System.out.println(a.size());
    }   
}

//010 010 1 010 100 010 11 010 010 011011 010 001110011111 010 10 010 11001110111110000101011011111011001111100011101
// dvosf         paall
// ffdhlvos    aafhllp
// => fdhlvos   afhlp

