
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
    
    struct PairValuesAtSameIndex {
    int valueForSum{};
    int valueForMultiplication{};
    PairValuesAtSameIndex() = default;

    // Added for the sake of completeness, not used in the current algorithm.
    // The container holding the struct is set at an initial size=totalInputElements,
    // in order to avoid the overhead with resizing. 
    // The values for the instance variables are assigned after creation. 
    PairValuesAtSameIndex(int valueForSum, int valueForMultiplication) : 
                          valueForSum{valueForSum}, valueForMultiplication{valueForMultiplication}{}
    };
    
public:
    long long maxScore(const vector<int>& allValuesForSum, const vector<int>& allValuesForMultiplication, int subsequenceLength) const {
        size_t totalInputElements = allValuesForSum.size();
        vector<PairValuesAtSameIndex> pairValuesAtSameIndex(totalInputElements);
        for (int i = 0; i < totalInputElements; ++i) {
            pairValuesAtSameIndex[i].valueForSum = allValuesForSum[i];
            pairValuesAtSameIndex[i].valueForMultiplication = allValuesForMultiplication[i];
        }
        const auto compare = [](auto first, auto second) {
            return first.valueForMultiplication > second.valueForMultiplication;
        };
        sort(pairValuesAtSameIndex.begin(), pairValuesAtSameIndex.end(), compare);
        //C++20: std::ranges::sort(pairValuesAtSameIndex,compare);

        priority_queue<int, vector<int>, greater<>> minHeap;
        long sumSubsequence = 0;
        for (int i = 0; i < subsequenceLength; ++i) {
            minHeap.push(pairValuesAtSameIndex[i].valueForSum);
            sumSubsequence += pairValuesAtSameIndex[i].valueForSum;
        }

        long maxScore = sumSubsequence * pairValuesAtSameIndex[subsequenceLength - 1].valueForMultiplication;
        for (int i = subsequenceLength; i < totalInputElements; ++i) {
            sumSubsequence += -minHeap.top() + pairValuesAtSameIndex[i].valueForSum;
            minHeap.pop();
            minHeap.push(pairValuesAtSameIndex[i].valueForSum);
            maxScore = max(maxScore, sumSubsequence * pairValuesAtSameIndex[i].valueForMultiplication);
        }

        return maxScore;
    }
};
