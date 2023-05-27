
import java.util.Arrays;
import java.util.PriorityQueue;

public class Solution {

    private record PairValuesAtSameIndex(int valueForSum, int valueForMultiplication) {}

    public long maxScore(int[] allValuesForSum, int[] allValuesForMultiplication, int subsequenceLength) {
        int totalInputElements = allValuesForSum.length;
        PairValuesAtSameIndex[] pairValuesAtSameIndex = new PairValuesAtSameIndex[totalInputElements];
        for (int i = 0; i < totalInputElements; ++i) {
            pairValuesAtSameIndex[i] = new PairValuesAtSameIndex(allValuesForSum[i], allValuesForMultiplication[i]);
        }
        Arrays.sort(pairValuesAtSameIndex, (x, y) -> y.valueForMultiplication - x.valueForMultiplication);

        long sumSubsequence = 0;
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        for (int i = 0; i < subsequenceLength; ++i) {
            minHeap.add(pairValuesAtSameIndex[i].valueForSum);
            sumSubsequence += pairValuesAtSameIndex[i].valueForSum;
        }

        long maxScore = sumSubsequence * pairValuesAtSameIndex[subsequenceLength - 1].valueForMultiplication;
        for (int i = subsequenceLength; i < totalInputElements; ++i) {
            sumSubsequence += -minHeap.poll() + pairValuesAtSameIndex[i].valueForSum;
            minHeap.add(pairValuesAtSameIndex[i].valueForSum);
            maxScore = Math.max(maxScore, sumSubsequence * pairValuesAtSameIndex[i].valueForMultiplication);
        }

        return maxScore;
    }
}
