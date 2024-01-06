
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
int n;
int mod=4;    //default is 4
vector<vector<int>> contorl(21,vector<int>());
vector<int> state(21,0);

int goal[21]={0};
vector<int> ans(100000,0);
map<vector<int>,vector<int>> prev_state; //记录前驱状态
bool check(vector<int> p){ //判断是否为目标状态
    int same=p[1];
    for(int i=1;i<=n;i++){
        if(p[i]!=same){
            return false;
        }
    }
    return true;
}
void go_back(vector<int> p){ //回溯
    if(prev_state.count(p)==0){
        return;
    }
    go_back(prev_state[p]);
    cout<<"点击石碑"<<p[0]<<"后状态：";
    for(int i=1;i<=n;i++){
        cout<<p[i]<<' ';
    }
    cout<<endl;
}
int bfs(int x){ //广度优先搜索
    int i,total=0;
    queue<vector<int>> Q;
    Q.push(state);
    while(!Q.empty()){
        total++;
        vector<int> p= Q.front();
        Q.pop();
        if(check(p)){ //判断是否为目标状态
            cout<<"总搜索步数："<<total<<endl;
            go_back(p);
            return total;
        }
        for(i=1;i<=n;i++){
            vector<int> p_copy(p);
            p_copy[0]=i;
            p_copy[p_copy[0]]++;p_copy[p_copy[0]]%=mod;
            for(int j=0;j<contorl[p_copy[0]].size();j++){
                p_copy[contorl[p_copy[0]][j]]++;
                p_copy[contorl[p_copy[0]][j]]%=mod;
            }
            if(prev_state.count(p_copy)==0){ //判断是否已经搜索过
                prev_state[p_copy]=p;
                Q.push(p_copy);
            }
        }
    }
    return 0;
}

void print(int t){
    int i=1;
    int mi=mod;
    while(t-mi>0){
        t-=mi;
        i++;
        mi*=mod;
    }
    int p,q;
    for(int j=i-1;j>=0;j--){
        p=t%mod;
        if(p==0){
            p=mod;
        }
        ans[j]=p;
        t=t/mod+1;
    }
    for(int j=0;j<i;j++){
        cout<<ans[j]<<' ';
    }
}

int main()
{
    int i,j,t;
    cout<<"输入石碑数：";
    cin>>n;
    cout<<"输入石碑状态数：";
    cin>>mod;
    
    cout<<"输入石碑控制关系："<<endl;
    for(i=0;i<=n;i++){
        char c;
        while ((c = getchar()) != '\n')
        {
            if (isdigit(c))
            {
                ungetc(c, stdin);
                cin>>t;
                contorl[i].push_back(t);
            }  
        }
    }
    cout<<"输入当前状态：";
    for(i=1;i<=n;i++){
        cin>>state[i];
    }
    bfs(0);

    return 0;
}
