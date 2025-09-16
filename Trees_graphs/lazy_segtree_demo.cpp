#include <bits/stdc++.h>
using namespace std;

class LazySegmentTree{
    vector<long long> seg;
    vector<long long> lazy;
    vector<int> Arr;
    int n;

    public:
    LazySegmentTree(vector<int> &Arr){
        this->Arr = Arr;
        n = Arr.size();
        seg.resize(4*n);
        lazy.resize(4*n, 0);
    }

    void build(int node, int start, int end){
        if(start == end){
            seg[node] = Arr[start];
            return;
        }
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node + 1, mid + 1, end);
        seg[node] = seg[2*node] + seg[2*node + 1];
    }

    void push(int node, int start, int end){
        if(lazy[node] != 0){
            seg[node] += lazy[node] * (end - start + 1);
            if(start != end){
                lazy[2*node] += lazy[node];
                lazy[2*node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void rangeUpdate(int node, int start, int end, int l, int r, int val){
        push(node, start, end);
        
        if(start > r || end < l){
            return;
        }
        
        if(start >= l && end <= r){
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        
        int mid = (start + end) / 2;
        rangeUpdate(2*node, start, mid, l, r, val);
        rangeUpdate(2*node + 1, mid + 1, end, l, r, val);
        
        push(2*node, start, mid);
        push(2*node + 1, mid + 1, end);
        seg[node] = seg[2*node] + seg[2*node + 1];
    }

    long long rangeQuery(int node, int start, int end, int l, int r){
        push(node, start, end);
        
        if(start > r || end < l){
            return 0;
        }
        
        if(start >= l && end <= r){
            return seg[node];
        }
        
        int mid = (start + end) / 2;
        long long left = rangeQuery(2*node, start, mid, l, r);
        long long right = rangeQuery(2*node + 1, mid + 1, end, l, r);
        return left + right;
    }

    void pointUpdate(int node, int start, int end, int idx, int val){
        push(node, start, end);
        
        if(start == end){
            seg[node] = val;
            return;
        }
        
        int mid = (start + end) / 2;
        if(idx <= mid){
            pointUpdate(2*node, start, mid, idx, val);
        } else {
            pointUpdate(2*node + 1, mid + 1, end, idx, val);
        }
        
        push(2*node, start, mid);
        push(2*node + 1, mid + 1, end);
        seg[node] = seg[2*node] + seg[2*node + 1];
    }
};

void printArray(vector<int>& arr, string label){
    cout << label << ": ";
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    cout << "=== Lazy Propagation Segment Tree Demo ===" << endl << endl;
    
    // Test Case 1: Basic functionality
    cout << "Test Case 1: Basic Range Update and Query" << endl;
    vector<int> Arr1 = {1, 2, 3, 4, 5, 6, 7, 8};
    int n1 = Arr1.size();
    LazySegmentTree seg1(Arr1);
    seg1.build(1, 0, n1-1);
    
    printArray(Arr1, "Initial array");
    cout << "Sum of range [0, 7]: " << seg1.rangeQuery(1, 0, n1-1, 0, 7) << endl;
    cout << "Sum of range [2, 5]: " << seg1.rangeQuery(1, 0, n1-1, 2, 5) << endl;
    
    cout << "\nAdding 10 to range [1, 4]..." << endl;
    seg1.rangeUpdate(1, 0, n1-1, 1, 4, 10);
    cout << "Sum of range [0, 7] after update: " << seg1.rangeQuery(1, 0, n1-1, 0, 7) << endl;
    cout << "Sum of range [2, 5] after update: " << seg1.rangeQuery(1, 0, n1-1, 2, 5) << endl;
    
    cout << "\n" << string(50, '=') << endl << endl;
    
    // Test Case 2: Multiple overlapping updates
    cout << "Test Case 2: Multiple Overlapping Range Updates" << endl;
    vector<int> Arr2 = {0, 0, 0, 0, 0, 0, 0, 0};
    int n2 = Arr2.size();
    LazySegmentTree seg2(Arr2);
    seg2.build(1, 0, n2-1);
    
    printArray(Arr2, "Initial array");
    cout << "Sum of range [0, 7]: " << seg2.rangeQuery(1, 0, n2-1, 0, 7) << endl;
    
    cout << "\nAdding 5 to range [0, 3]..." << endl;
    seg2.rangeUpdate(1, 0, n2-1, 0, 3, 5);
    cout << "Sum of range [0, 7]: " << seg2.rangeQuery(1, 0, n2-1, 0, 7) << endl;
    
    cout << "\nAdding 3 to range [2, 5]..." << endl;
    seg2.rangeUpdate(1, 0, n2-1, 2, 5, 3);
    cout << "Sum of range [0, 7]: " << seg2.rangeQuery(1, 0, n2-1, 0, 7) << endl;
    
    cout << "\nAdding 2 to range [1, 6]..." << endl;
    seg2.rangeUpdate(1, 0, n2-1, 1, 6, 2);
    cout << "Sum of range [0, 7]: " << seg2.rangeQuery(1, 0, n2-1, 0, 7) << endl;
    cout << "Sum of range [2, 4]: " << seg2.rangeQuery(1, 0, n2-1, 2, 4) << endl;
    
    cout << "\n" << string(50, '=') << endl << endl;
    
    // Test Case 3: Point updates
    cout << "Test Case 3: Point Updates with Range Updates" << endl;
    vector<int> Arr3 = {10, 20, 30, 40, 50};
    int n3 = Arr3.size();
    LazySegmentTree seg3(Arr3);
    seg3.build(1, 0, n3-1);
    
    printArray(Arr3, "Initial array");
    cout << "Sum of range [0, 4]: " << seg3.rangeQuery(1, 0, n3-1, 0, 4) << endl;
    
    cout << "\nAdding 5 to range [1, 3]..." << endl;
    seg3.rangeUpdate(1, 0, n3-1, 1, 3, 5);
    cout << "Sum of range [0, 4]: " << seg3.rangeQuery(1, 0, n3-1, 0, 4) << endl;
    
    cout << "\nSetting element at index 2 to 100..." << endl;
    seg3.pointUpdate(1, 0, n3-1, 2, 100);
    cout << "Sum of range [0, 4]: " << seg3.rangeQuery(1, 0, n3-1, 0, 4) << endl;
    cout << "Sum of range [1, 3]: " << seg3.rangeQuery(1, 0, n3-1, 1, 3) << endl;
    
    cout << "\n" << string(50, '=') << endl << endl;
    
    // Test Case 4: Large array
    cout << "Test Case 4: Large Array Operations" << endl;
    vector<int> Arr4(16, 1); // Array of 16 ones
    int n4 = Arr4.size();
    LazySegmentTree seg4(Arr4);
    seg4.build(1, 0, n4-1);
    
    cout << "Array size: " << n4 << " (all elements are 1)" << endl;
    cout << "Sum of range [0, 15]: " << seg4.rangeQuery(1, 0, n4-1, 0, 15) << endl;
    
    cout << "\nAdding 10 to entire array [0, 15]..." << endl;
    seg4.rangeUpdate(1, 0, n4-1, 0, 15, 10);
    cout << "Sum of range [0, 15]: " << seg4.rangeQuery(1, 0, n4-1, 0, 15) << endl;
    
    cout << "\nAdding 5 to range [4, 11]..." << endl;
    seg4.rangeUpdate(1, 0, n4-1, 4, 11, 5);
    cout << "Sum of range [0, 15]: " << seg4.rangeQuery(1, 0, n4-1, 0, 15) << endl;
    cout << "Sum of range [4, 11]: " << seg4.rangeQuery(1, 0, n4-1, 4, 11) << endl;
    
    cout << "\n=== Demo Complete ===" << endl;
    
    return 0;
}
