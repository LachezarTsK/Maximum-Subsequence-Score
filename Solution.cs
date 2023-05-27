
using System;
using System.Collections.Generic;

public class Solution
{
    struct PairValuesAtSameIndex
    {
        public int valueForSum;
        public int valueForMultiplication;
        public PairValuesAtSameIndex(int valueForSum, int valueForMultiplication)
        {
            this.valueForSum = valueForSum;
            this.valueForMultiplication = valueForMultiplication;
        }
    }
    public long MaxScore(int[] allValuesForSum, int[] allValuesForMultiplication, int subsequenceLength)
    {
        int totalInputElements = allValuesForSum.Length;
        var pairValuesAtSameIndex = new PairValuesAtSameIndex[totalInputElements];
        for (int i = 0; i < totalInputElements; ++i)
        {
            pairValuesAtSameIndex[i] = new PairValuesAtSameIndex(allValuesForSum[i], allValuesForMultiplication[i]);
        }
        Array.Sort(pairValuesAtSameIndex, (x, y) => y.valueForMultiplication - x.valueForMultiplication);

        long sumSubsequence = 0;
        var minHeap = new PriorityQueue<int, int>();
        for (int i = 0; i < subsequenceLength; ++i)
        {
            minHeap.Enqueue(pairValuesAtSameIndex[i].valueForSum, pairValuesAtSameIndex[i].valueForSum);
            sumSubsequence += pairValuesAtSameIndex[i].valueForSum;
        }

        long maxScore = sumSubsequence * pairValuesAtSameIndex[subsequenceLength - 1].valueForMultiplication;
        for (int i = subsequenceLength; i < totalInputElements; ++i)
        {
            sumSubsequence += -minHeap.Dequeue() + pairValuesAtSameIndex[i].valueForSum;
            minHeap.Enqueue(pairValuesAtSameIndex[i].valueForSum, pairValuesAtSameIndex[i].valueForSum);
            maxScore = Math.Max(maxScore, sumSubsequence * pairValuesAtSameIndex[i].valueForMultiplication);
        }

        return maxScore;
    }
}
