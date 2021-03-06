#define pb push_back
typedef pair<int, int> pii;
#define f first
#define s second
#define mp make_pair

vector<vector<string> > output;

int change(string &a, string &b){
    int n = a.length();
    int num = 0;
    for(int i = 0; i < n; i++){
        if(a[i] != b[i]) num++;
    }
    return num;
}

int bfs(int u, int n, vector<int> **graph, bool *IsVisited){
    queue<pii> q;
    q.push(mp(n-1, 1));
    IsVisited[n-1] = true;
    
    int cur, v, h;
    while(!q.empty()){
        cur = q.front().f;
        h = q.front().s;
        if(cur == u) return h;
        q.pop();
        
        for(int i = 0; i < graph[cur]->size(); i++){
            v = graph[cur]->at(i);
            if(!IsVisited[v]){
                q.push(mp(v, h+1));
                IsVisited[v] = true;
            }
        }
    }
    return 0;
}

int ladderLength(string start, string end, vector<string> &dictV) {
    if(start == end) return 1;
    
    dictV.pb(start);
    dictV.pb(end);
    int n = dictV.size();
    
    vector<int> **graph = new vector<int> *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new vector<int>;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(change(dictV[i], dictV[j]) == 1){
                graph[i]->pb(j);
                graph[j]->pb(i);
            }
        }
    }
    
    bool *IsVisited = new bool[n];
    for(int i = 0; i < n; i++) IsVisited[i] = false;
    return bfs(n-2, n, graph, IsVisited);
}

void dfs(int u, int n, vector<int> **graph, bool *IsVisited, vector<string> &dict, vector<string> &helper, int min){
    if(u == n-1){
        if(min == 1) output.pb(helper);
        return;
    }
    
    IsVisited[u] = true;
    int v;
    for(int i = 0; i < graph[u]->size(); i++){
        v = graph[u]->at(i);
        if(!IsVisited[v]){
            helper.pb(dict[v]);
            dfs(v, n, graph, IsVisited, dict, helper, min-1);
            helper.pop_back();
        }
    }
    
    IsVisited[u] = false;
}

vector<vector<string> > Solution::findLadders(string start, string end, vector<string> &dict) {
    output.clear();
    
    int min = ladderLength(start, end, dict);
    
    set<string> st;
    int n = dict.size();
    for(int i = 0; i < n; i++) st.insert(dict[i]);
    
    vector<string> NewDict;
    for(auto s : st){
        if(s != start && s != end) NewDict.pb(s); 
    }
    NewDict.pb(start);
    NewDict.pb(end);
    n = NewDict.size();
    
    vector<int> **graph = new vector<int> *[n];
    for(int i = 0; i < n; i++){
        graph[i] = new vector<int>;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(change(NewDict[i], NewDict[j]) == 1){
                graph[i]->pb(j);
                graph[j]->pb(i);
            }
        }
    }
    
    bool *IsVisited = new bool[n];
    for(int i = 0; i < n; i++) IsVisited[i] = false;
    
    vector<string> helper;
    helper.pb(NewDict[n-2]);
    if(start == end){
        output.pb(helper);
    }
    dfs(n-2, n, graph, IsVisited, NewDict, helper, min);
    return output;
}
