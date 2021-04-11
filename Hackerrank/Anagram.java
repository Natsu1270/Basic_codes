import java.util.*;

public class Anagram {
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
}
