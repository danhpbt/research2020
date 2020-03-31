package com.xynotec.research2020;

import org.junit.Test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() {
        assertEquals(4, 2 + 2);

//        List<Integer> a = new ArrayList<>();
//        a.add(Integer.valueOf(2)); a.add(Integer.valueOf(4));
//        //a.add(Integer.valueOf(3)); a.add(Integer.valueOf(4));
//
//        List<Integer> b = new ArrayList<>();
//        b.add(Integer.valueOf(16)); b.add(Integer.valueOf(32)); b.add(Integer.valueOf(96));
//        //b.add(Integer.valueOf(24)); b.add(Integer.valueOf(48));
//        getTotalX(a, b);

        //int[] scores = new int[] {3, 4, 21, 36, 10, 28, 35, 5, 24, 42};
        //breakingRecords(scores);
        //int[] sample = new int[]{2, 5, 1, 3, 4, 4, 3, 5, 1, 1, 2, 1, 4, 1, 3, 3, 4, 2, 1}; //(s, 18, 7);
//        int[] sample = new int[]{4, 5, 4, 2, 4, 5, 2, 3, 2, 1, 1, 5, 4};
//        List<Integer> s = Arrays.stream(sample)		// IntStream
//                .boxed() 		// Stream<Integer>
//                .collect(Collectors.toList());
//        birthday(s, 15, 4);
//        int[] ar = new int[]{1, 3, 2, 6, 1, 2};
//        divisibleSumPairs(6, 3, ar);
//        int[] sample = new int[]{10, 20, 20, 10, 10, 30, 50, 10, 20};
//        sockMerchant(9, sample);

        int[] sample = new int[]{5, 1, 2, 3, 4, 5};
        List<Integer> s = Arrays.stream(sample)		// IntStream
                            .boxed() 		// Stream<Integer>
                            .collect(Collectors.toList());
        longestSubarray(s);
    }

    public static int longestSubarray(List<Integer> arr) {
        // Write your code here
        int maxlength = Integer.MIN_VALUE;
        int count = arr.size();
        Set<Integer> intSet = new HashSet<>();
        for(int i = 0; i < count - 1; i++)
        {
            Integer index0 = arr.get(i);
            intSet.clear();
            intSet.add(index0);
            for(int j = i + 1; j < count; j++)
            {
                int length = 0;
                Integer index1 = arr.get(j);
                if (Math.abs(index1.intValue() - index0.intValue()) > 1) {
                    break;
                }
                else
                {
                    if (intSet.size() == 2) {
                        length = j - i;
                        maxlength = length;
                    }
                    else
                    {
                        if (!intSet.contains(index1))
                            intSet.add(index1);
                    }
                }

            }
        }

        return maxlength;

//        int startIndex = 0;
//        int maxlength = Integer.MIN_VALUE;
//        for(int i = 0; i < count-1; i++) {
//            for (int j = i + 1; j < count; j++) {
//                if (Math.abs(nArr[j] - nArr[j - 1]) == 1)
//                {
//                    int length = j - i + 1;
//                    if (length > maxlength)
//                        maxlength = length;
//                }
//                else
//                    break;
//            }
//            if (maxlength == count - i)
//                break;
//        }
//
//        return maxlength;
    }

    static int sockMerchant(int n, int[] ar) {
        HashMap<Integer, Integer> counts = new HashMap<>();
        for(int i = 0; i < n; i++)
        {
            Integer val = Integer.valueOf(ar[i]);

            if (!counts.containsKey(val))
                counts.put(val, new Integer(1));
            else
                counts.put(val, new Integer(counts.get(val).intValue() + 1));
        }

        int count = 0;
        for (Map.Entry<Integer, Integer> entry : counts.entrySet()) {
            Integer val = entry.getValue();
            count += (val.intValue() / 2);
        }

        return count;

    }
    static void bonAppetit(List<Integer> bill, int k, int b) {
        int sum0k = 0;
        for(int i = 0; i < bill.size(); i++)
        {
            int val = bill.get(i).intValue();
            if (i != k)
                sum0k += val;
        }

        sum0k = sum0k / 2;
        if (sum0k == b)
            System.out.println("Bon Appetit");
        else
            System.out.println(b - sum0k);

    }

    static String dayOfProgrammer(int year) {
        if (year < 1918)
        {
            if (year % 4 == 0)
                return String.format("12.09.%d", year);
            else
                return String.format("13.09.%d", year);
        } else if (year > 1918)
        {
            if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
                return String.format("12.09.%d", year);
            else
                return String.format("13.09.%d", year);
        } else
        {
            return "26.09.1918";
        }

    }

    static int migratoryBirds(List<Integer> arr) {
        int size = arr.size();
        int[] nums = new int[size];
        for(int i = 0; i < size; i++)
            nums[arr.get(i).intValue()]++;

        int max = Integer.MIN_VALUE;
        int id = 0;
        for(int i = 0; i < size; i++)
        {
            int val = nums[i];
            if (val > max) {
                max = val;
                id = i;
            }
        }

        return id;



    }

    static int divisibleSumPairs(int n, int k, int[] ar) {
        int count = 0;
        for(int i = 0; i < n - 1; i++)
            for(int j = i + 1; j < n; j++)
            {
                int sum = ar[i] + ar[j];
                if (sum % k == 0)
                    count++;
            }
        return count;
    }

    static int birthday(List<Integer> s, int d, int m) {
        int size = s.size();
        int count = 0;
        for(int i = 0; i < size - m + 1; i++) {
            int sum = s.get(i).intValue();
            for (int j = i + 1; j < m + i; j++)
                sum += s.get(j).intValue();
            if (sum == d)
                count++;
        }
        return count;

    }


    static int[] breakingRecords(int[] scores) {
        int min = scores[0];
        int max = scores[0];

        int mincount = 0;
        int maxcount = 0;
        for(int i = 1; i < scores.length; i++)
        {
            if (min > scores[i])
            {
                mincount++;
                min = scores[i];

            }

            if (max < scores[i])
            {
                maxcount++;
                max = scores[i];
            }

        }

        return new int[] {mincount, maxcount};

    }

    public static int getTotalX(List<Integer> a, List<Integer> b) {
        // Write your code here
        int[] prime = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
        int alength = a.size();
        int blength = b.size();
        int bscnn = a.get(alength - 1);
        int limit = b.get(0);
        int loop = 0;
        int n_bscnn = bscnn;
        do {
            int i;
            for(i = 0; i < alength - 1; i++)
            {
                int numi = a.get(i);
                if (n_bscnn % numi != 0)
                    break;
            }
            if (i < alength - 1) {
                n_bscnn = bscnn*prime[loop];
                loop++;
            }
            else
                break;
        }
        while (n_bscnn <= limit);

        loop = 1;
        int count = 0;
        bscnn = n_bscnn;
        n_bscnn = bscnn;
        do {
            int i;
            for( i = 0; i < blength; i++)
            {
                int numi = b.get(i);
                if (numi % n_bscnn != 0)
                    break;
            }

            if (i == blength)
                count++;

            loop++;
            n_bscnn = bscnn*loop;
        }
        while (n_bscnn <= limit);

        return count;
    }

    static String kangaroo(int x1, int v1, int x2, int v2) {
        if (x1 == x2)
            return "YES";
        else
        {
            int pos1, pos2, loop;
            loop = 0;
            do {
                loop++;
                pos1 = x1 + v1*loop;
                pos2 = x2 + v2*loop;
                if (x1 < x2)
                {
                    if (v1 <= v2)
                        return "NO";

                    if (pos1 == pos2)
                        return "YES";
                    else if (pos1 > pos2)
                        return "NO";
                }
                else
                {
                    if (v1 >= v2)
                        return "NO";

                    if (pos1 == pos2)
                        return "YES";
                    else if (pos1 < pos2)
                        return "NO";
                }
            }
            while(true);

        }

    }

    static void countApplesAndOranges(int s, int t, int a, int b, int[] apples, int[] oranges) {
        int numA = apples.length;
        int countA = 0;
        for(int i = 0; i < numA; i++)
        {
            if ((a + apples[i] >= s) && (a + apples[i] <= t))
                countA ++;
        }

        int num0 = oranges.length;
        int countO = 0;
        for(int i = 0; i < num0; i++)
        {
            if ((b + oranges[i] >= s) && (b + oranges[i] <= t))
                countO ++;
        }

        System.out.println(countA);
        System.out.println(countO);
    }


    public static List<Integer> gradingStudents(List<Integer> grades) {
        // Write your code here

        List<Integer> result = new ArrayList<>();
        int length = grades.size();
        for(int i = 0; i < length; i++)
        {
            int val = grades.get(i).intValue();

            if (val >= 38)
            {
                int mod5 = val % 5;
                if (mod5 >= 3)
                    val = (val/5)*5 + 5;
            }

            result.add(Integer.valueOf(val));
        }

        return result;
    }


    static String timeConversion(String s) {
        /*
         * Write your code here.
         */

        String fmt = s.substring(8, 10);
        String time = s.substring(0, 8);
        String minsec = time.substring(2, 8);
        if (fmt.compareTo("AM") == 0)
        {
            String hourStr = s.substring(0, 2);
            int hour = Integer.valueOf(hourStr);
            if (hour == 12)
                return String.format("00%s", minsec);
            return time;
        }
        else
        {
            String hourStr = s.substring(0, 2);
            int hour = Integer.valueOf(hourStr);

            if (hour == 12)
                return String.format("12%s", minsec);
            else {
                hour += 12;
                return String.format("%d%s", hour, minsec);
            }

        }

    }
}