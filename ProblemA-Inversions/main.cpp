#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll merge(vector<ll>& arr, int left, int mid, int right){
    vector<ll> temp;
    ll inv=0;
    int i= left;
    int j= mid + 1;
    
    while (i <= mid && j <= right){
        if (arr[i] <= arr[j]){
            temp.push_back(arr[i]);
            i++;
        }else{
            inv += (mid - i + 1);
            temp.push_back(arr[j]);
            j++;
        }
    }

    while(i <= mid){
        temp.push_back(arr[i]);
        i++;
    }

    while(j <= right){
        temp.push_back(arr[j]);
        j++;
    }

    for (int k = 0; k < (int)temp.size(); k++){
        arr[left + k] = temp[k];
    }

    return inv;
}

ll mergeSortCount(vector<ll>& arr, int left, int right){
    if (left >= right){
        return 0;
    }

    int mid = left + (right - left)/2;

    ll invLeft = mergeSortCount(arr, left, mid);
    ll invRight = mergeSortCount(arr, mid + 1, right);
    ll invSplit = merge(arr, left, mid, right);

    return invLeft + invRight + invSplit;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // TODO: implement efficient inversion counting
    // Print the number of inversions as a 64-bit integer.
    ll inv = mergeSortCount(a, 0, n - 1);
    cout << inv << "\n";
    return 0;
}