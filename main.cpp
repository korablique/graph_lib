#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct BFSreturn{
    std::vector<int> ret_vector;
    int ret_int;
    bool is_path;
};
BFSreturn BFS(std::vector<std::vector<bool>> graph, int start, int End){
    std::queue<int> vertix; //очередь ближайших вершин
    vertix.push (start);
    std::vector<bool> painted (graph.size()); //вектор покрашенных вершин
    for (int i = 0; i < graph.size(); i++){
        painted[i] = false;
    }
    painted[start] = true;
    std::vector<int> distance (graph.size()); // расстояние до данной вершины
    std::vector<std::vector<int>> path (graph.size()); // путь до данной вершин
    while (!vertix.empty()) {
        int current_vertix = vertix.front();
        vertix.pop();
        for (int i=0; i<graph.size(); i++) {
            if ((!painted[i]) && (graph[current_vertix][i] == true)) { //проверка смежной вершины на непокрашенность
                painted[i] = true;
                vertix.push(i); // добавление в очередь
                distance[i] = distance[current_vertix]++; // подсчет расстояния до этой вершины
                for (int j = 0; j < path[current_vertix].size(); j++) {
                    path[i].push_back(path[current_vertix][j]); // построение пути
                }
                path[i].push_back(current_vertix);
                if (i == End) {
                }
            }
            }
        }

    if (painted[End] == false) {
        BFSreturn result;
        result.ret_int = distance[End];
        result.ret_vector = path[End];
        result.is_path = false;
        return result;


    }
    else {
        reverse(path.begin(), path.end());
        BFSreturn result;
        result.ret_int = distance[End];
        result.ret_vector = path[End];
        result.is_path = true;
        return result;
        //


    }

}


int main() {
    std::vector<std::vector<bool>> graphs;
    std::vector <bool> used (graphs.size());
    uint64_t start;
    int end;
    BFSreturn bfs_result;
    bfs_result = BFS(graphs, start, end);
    return 0;
}
