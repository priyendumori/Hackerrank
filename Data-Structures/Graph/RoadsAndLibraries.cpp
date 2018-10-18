#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

void DFS(long s, vector<bool> &visited, vector<vector<long> > &adj, long* count){
    visited[s]=true;
    (*count)++;
    
    // cout<<"s "<<s<<endl;
    // cout<<"CC "<<*count<<endl;
    for(auto a:adj[s]){
        // cout<<"a "<<a<<endl;
        if(!visited[a])
            DFS(a,visited,adj, count);
    }
}

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(long n, long c_lib, long c_road, vector<vector<int>> cities) {
    if(c_lib <= c_road) return n*c_lib;
    
    vector<vector<long> > adj(n+1);
    for(long i=0;i<cities.size();i++){
        adj[cities[i][0]].push_back(cities[i][1]);
        adj[cities[i][1]].push_back(cities[i][0]);
    }
    
    vector<bool> visited(n+1, false);
    
    long library=0;
    long count=0;

    long total=0;
    for(long i=1;i<=n;i++){
        if(!visited[i]){
            DFS(i, visited, adj, &count);
            cout<<"c "<<count<<endl;
            total+=(count-1)*c_road;
            count=0;
            library++;
        }
    }

    // cout<<library<<endl;
    
    return library*c_lib + total;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
