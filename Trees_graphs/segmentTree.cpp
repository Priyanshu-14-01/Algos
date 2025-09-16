class SegmentTree{
    vector<int> seg;
    vector<int> Arr;
    int n;

    public:
    SegmentTree(vector<int> &Arr){
        this->Arr = Arr;
        n = Arr.size();
        seg.resize(4*n);
    }

    void build(int node, int start, int end){
        if(start ==end){
            seg[node] = Arr[start];
            return;
        }
        int mid = (start+end)/2;
        build(2*node-1,start,mid);
        build(2*node,mid+1,end);
        seg[node] = seg[2*node-1] + seg[2*node];
    }

    void pointUpdate(int node,int start, int end, int idx, int val){
        if(start == end){
            seg[node] = val;
            return;
        }
        int mid = (start+end)/2;
        if(idx <= mid){
            pointUpdate(2*node-1,start,mid,idx,val);
        }
        else{
            pointUpdate(2*node,mid+1,end,idx,val);
        }
        seg[node] = seg[2*node-1] + seg[2*node];
    }

    int rangeQuery(int node, int start, int end, int l, int r){
        if(start>r || end<l){
            return 0;
        }
        if(start>=l && end<=r){
            return seg[node];
        }
        int mid = (start+end)/2;
        int left = rangeQuery(2*node-1,start,mid,l,r);
        int right = rangeQuery(2*node,mid+1,end,l,r);
        return left + right;
    }
};

int main(){
    vector<int> Arr = {1,2,3,4,5};
    SegmentTree seg(Arr);
    seg.build(1,0,4);
    cout<<seg.rangeQuery(1,0,4,0,4)<<endl;
    seg.pointUpdate(1,0,4,2,10);
    cout<<seg.rangeQuery(1,0,4,0,4)<<endl;
    return 0;
}