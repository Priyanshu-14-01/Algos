#include <bits/stdc++.h>
using namespace std;

class FenwickTree{
    vector<int> bit;
    int n;
    public:
    FenwickTree(int n){
        this->n = n;
        bit.resize(n+1);
    }

    void update(int idx, int val){
        while(idx <= n){
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int sum(int idx){
        int sum = 0;
        while(idx>0){
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

    int rangeSum(int l,int r){
        return sum(r) - sum(l-1);
    }

    void rangeUpdate(int l,int r,int val){
        update(l,val);
        update(r+1,-val);
    }
};

int main(){
    int n;
    cin>>n;
    FenwickTree fenwick(n);
    fenwick.update(1,1);
    fenwick.update(2,2);
    fenwick.update(3,3);
    cout<<fenwick.sum(3)<<endl;
    return 0;
}