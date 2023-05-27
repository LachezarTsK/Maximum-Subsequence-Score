
/**
 * @param {number[]} allValuesForSum
 * @param {number[]} allValuesForMultiplication
 * @param {number} subsequenceLength
 * @return {number}
 */
var maxScore = function (allValuesForSum, allValuesForMultiplication, subsequenceLength) {
    let totalInputElements = allValuesForSum.length;
    const pairValuesAtSameIndex = new Array(totalInputElements);
    for (let i = 0; i < totalInputElements; ++i) {
        pairValuesAtSameIndex[i] = new PairValuesAtSameIndex(allValuesForSum[i], allValuesForMultiplication[i]);
    }
    pairValuesAtSameIndex.sort((x, y) => y.valueForMultiplication - x.valueForMultiplication);

    //const {MinPriorityQueue} = require('@datastructures-js/priority-queue');
    //MinPriorityQueue<number>
    const minHeap = new MinPriorityQueue({compare: (x, y) => x - y});
    let sumSubsequence = 0;
    for (let i = 0; i < subsequenceLength; ++i) {
        minHeap.enqueue(pairValuesAtSameIndex[i].valueForSum);
        sumSubsequence += pairValuesAtSameIndex[i].valueForSum;
    }

    let maxScore = sumSubsequence * pairValuesAtSameIndex[subsequenceLength - 1].valueForMultiplication;
    for (let i = subsequenceLength; i < totalInputElements; ++i) {
        sumSubsequence += -minHeap.dequeue() + pairValuesAtSameIndex[i].valueForSum;
        minHeap.enqueue(pairValuesAtSameIndex[i].valueForSum);
        maxScore = Math.max(maxScore, sumSubsequence * pairValuesAtSameIndex[i].valueForMultiplication);
    }

    return maxScore;
};

/**
 * @param {number} valueForSum
 * @param {number} valueForMultiplication
 */
function PairValuesAtSameIndex(valueForSum, valueForMultiplication) {
    this.valueForSum = valueForSum;
    this.valueForMultiplication = valueForMultiplication;
}
