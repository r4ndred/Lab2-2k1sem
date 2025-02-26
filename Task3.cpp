#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 100;

void findSubsets(vector<int>& nums, int targetSum, vector<vector<int>>& subsets, vector<int>& currentSubset, vector<bool>& used, int start) {
    if (targetSum == 0) {
        subsets.push_back(currentSubset);
        for (int num : currentSubset) {
            auto it = find(nums.begin(), nums.end(), num);
            if (it != nums.end()) *it = -1;
        }
        return;
    }

    for (int i = start; i < nums.size(); i++) {
        if (!used[i] && nums[i] != -1 && nums[i] <= targetSum) {
            used[i] = true;
            currentSubset.push_back(nums[i]);
            findSubsets(nums, targetSum - nums[i], subsets, currentSubset, used, i + 1);
            currentSubset.pop_back();
            used[i] = false;
        }
    }
}

bool partitionSet(vector<int>& nums, int subsetSum, vector<vector<int>>& subsets) {
    vector<bool> used(nums.size(), false);
    vector<int> currentSubset;
    
    while (true) {
        vector<int> tempSubset;
        findSubsets(nums, subsetSum, subsets, tempSubset, used, 0);
        bool found = false;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != -1) {
                found = true;
                break;
            }
        }
        
        if (!found) break;
    }
    
    return all_of(nums.begin(), nums.end(), [](int num) { return num == -1; });
}

int main() {
    vector<int> nums;
    int n, subsetSum;

    cout << "Введите количество элементов в множестве: ";
    cin >> n;

    nums.resize(n);
    cout << "Введите элементы множества: ";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    cout << "Введите сумму подмножества: ";
    cin >> subsetSum;

    vector<vector<int>> subsets;
    if (partitionSet(nums, subsetSum, subsets)) {
        cout << "Найдены подмножества с суммой " << subsetSum << ":" << endl;
        for (const auto& subset : subsets) {
            cout << "{ ";
            for (int num : subset) cout << num << " ";
            cout << "}" << endl;
        }
    } else {
        cout << "Ошибка: множество не может быть разбито на подмножества с равной суммой." << endl;
    }

    return 0;
}
