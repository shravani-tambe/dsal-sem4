// shell sort heap sort exp e21

import java.util.Arrays;
import java.util.Scanner;

public class Sort {

    public static void shell(int[] a) {
        int increment = a.length / 2;
        while (increment > 0) {
            for (int i = increment; i < a.length; i++) {
                int temp = a[i];
                int j = i;
                while (j >= increment && a[j - increment] > temp) {
                    a[j] = a[j - increment];
                    j -= increment;
                }
                a[j] = temp;
            }
            if (increment == 2)
                increment = 1;
            else
                increment *= 5.0 / 11;
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        final int SIZE = 10;
        int[] n = new int[SIZE];

        System.out.println("Enter " + SIZE + " Elements:");
        for (int i = 0; i < SIZE; i++) {
            n[i] = sc.nextInt();
        }

        System.out.println("Original Array:");
        System.out.println(Arrays.toString(n));

        Sort.shell(n);

        System.out.println("Sorted Array:");
        System.out.println(Arrays.toString(n));
    }
}
