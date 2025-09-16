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

int main(){
    vector<int> Arr = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = Arr.size();
    LazySegmentTree seg(Arr);
    seg.build(1, 0, n-1);
    
    cout << "Initial array: ";
    for(int i = 0; i < n; i++){
        cout << Arr[i] << " ";
    }
    cout << endl;
    
    cout << "Sum of range [0, 7]: " << seg.rangeQuery(1, 0, n-1, 0, 7) << endl;
    cout << "Sum of range [2, 5]: " << seg.rangeQuery(1, 0, n-1, 2, 5) << endl;
    
    // Range update: add 10 to elements from index 1 to 4
    cout << "\nAdding 10 to range [1, 4]..." << endl;
    seg.rangeUpdate(1, 0, n-1, 1, 4, 10);
    
    cout << "Sum of range [0, 7] after update: " << seg.rangeQuery(1, 0, n-1, 0, 7) << endl;
    cout << "Sum of range [2, 5] after update: " << seg.rangeQuery(1, 0, n-1, 2, 5) << endl;
    cout << "Sum of range [0, 1] after update: " << seg.rangeQuery(1, 0, n-1, 0, 1) << endl;
    
    // Another range update: add 5 to elements from index 3 to 6
    cout << "\nAdding 5 to range [3, 6]..." << endl;
    seg.rangeUpdate(1, 0, n-1, 3, 6, 5);
    
    cout << "Sum of range [0, 7] after second update: " << seg.rangeQuery(1, 0, n-1, 0, 7) << endl;
    cout << "Sum of range [3, 6] after second update: " << seg.rangeQuery(1, 0, n-1, 3, 6) << endl;
    
    // Point update
    cout << "\nSetting element at index 2 to 100..." << endl;
    seg.pointUpdate(1, 0, n-1, 2, 100);
    cout << "Sum of range [0, 7] after point update: " << seg.rangeQuery(1, 0, n-1, 0, 7) << endl;
    
    return 0;
}