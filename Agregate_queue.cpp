#include <bits/stdc++.h>
using namespace std;

/*
Core Idea:
---------
We want the minimum of every sliding window of size k, and finally
the minimum among all those window minimums.

To do this in O(n) time, we simulate a queue using TWO stacks.
Each stack is a "MinStack", meaning:
- Every element stores (value, minimum_so_far_in_this_stack)

Stacks:
-------
1) inStack  -> holds newly added elements (right side of window)
2) outStack -> holds older elements to be removed (left side of window)

Key Insight:
------------
At any time, the sliding window is split between inStack and outStack.
So the minimum of the current window is:

    min(inStack.min, outStack.min)

Why this works:
---------------
- Each element is pushed once into inStack
- Moved at most once to outStack
- Popped once from outStack

=> Total operations are O(n), amortized O(1) per element.
*/

struct MinStack {
    // Each element stores {value, minimum up to this point}
    stack<pair<int,int>> st;

    void push(int x) {
        int mn = st.empty() ? x : min(x, st.top().second);
        st.push({x, mn});
    }

    void pop() {
        st.pop();
    }

    int top() {
        return st.top().first;
    }

    int getMin() {
        return st.top().second;
    }

    bool empty() {
        return st.empty();
    }
};

int minOfAllWindowMinimums(vector<int>& arr, int k) {
    MinStack inStack, outStack;
    int globalMin = INT_MAX;

    for (int i = 0; i < arr.size(); i++) {

        // Step 1: Add new element to the window
        inStack.push(arr[i]);

        // Step 2: Remove element if window size exceeded
        if (i >= k) {
            // If outStack is empty, transfer all elements from inStack
            // This reverses order and exposes the oldest element on top
            if (outStack.empty()) {
                while (!inStack.empty()) {
                    outStack.push(inStack.top());
                    inStack.pop();
                }
            }
            // Remove the outgoing (oldest) element
            outStack.pop();
        }

        // Step 3: Window is valid, compute window minimum
        if (i >= k - 1) {
            int windowMin;
            if (inStack.empty())
                windowMin = outStack.getMin();
            else if (outStack.empty())
                windowMin = inStack.getMin();
            else
                windowMin = min(inStack.getMin(), outStack.getMin());

            // Track minimum among all window minimums
            globalMin = min(globalMin, windowMin);
        }
    }

    return globalMin;
}

int main() {
    vector<int> arr = {2, 1, 3, 4, 6, 3, 8, 9, 10, 12, 56};
    int k = 4;

    cout << minOfAllWindowMinimums(arr, k);
    return 0;
}
