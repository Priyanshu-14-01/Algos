class Trie {
    vector<vector<int>> nxt;
    map<int,int> is_terminal;
    int N;
public:
    Trie() {
        N=0;
        nxt.resize(100005, vector<int>(30, -1));
    }
    
    void insert(string word) {
        int root = 0;
        int cur = root;
        int n = word.length();
        for(int i = 0;i<n;i++){
            char c = word[i];
            if(nxt[cur][c-'a'] == -1){
                nxt[cur][c-'a'] = ++N;
            }
            cur = nxt[cur][c-'a'];
        }
        is_terminal[cur] = 1;
    }
    
    bool search(string word) {
        int root = 0;
        int cur = root;
        for(auto c: word){
            if(nxt[cur][c-'a'] == -1){
                return false;
            }
            cur = nxt[cur][c-'a'];
        }
        if(!is_terminal[cur])return false;
        return true;
    }
    
    bool startsWith(string prexfix) {
        int root = 0;
        int cur = root;
        for(auto c: prexfix){
            if(nxt[cur][c-'a'] == -1){
                return false;
            }
            cur = nxt[cur][c-'a'];
        }
        return true;
    }
};