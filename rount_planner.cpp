#include <iostream>
using namespace std;

int main() {
    // 从标准输入读取起点和终点
    int start, end;
    cin >> start >> end;
    
    // 硬编码的测试图（相邻点之间的距离）
    const int n = 21;  // 21个地点
    double distances[n][n] = {0};  // 初始化为0
    
    // 设置一些测试距离（这里只是示例，您需要设置实际的距离）
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                // 设置一个默认距离，实际应用中需要使用真实距离
                distances[i][j] = 1.0;  // 或者其他合适的默认值
            }
        }
    }
    
    // 初始化辅助数组
    double dist[n];
    int prev[n];
    bool visited[n];
    
    // 初始化距离数组
    for(int i = 0; i < n; i++) {
        dist[i] = 1e9;  // 用一个很大的数代替INFINITY
        prev[i] = -1;
        visited[i] = false;
    }
    dist[start] = 0;
    
    // Dijkstra算法主循环
    for(int i = 0; i < n; i++) {
        // 找到最近的未访问节点
        int u = -1;
        double minDist = 1e9;
        for(int j = 0; j < n; j++) {
            if(!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        
        if(u == -1) break;
        visited[u] = true;
        
        // 更新邻居节点的距离
        for(int v = 0; v < n; v++) {
            if(distances[u][v] > 0 && !visited[v] && 
               dist[u] + distances[u][v] < dist[v]) {
                dist[v] = dist[u] + distances[u][v];
                prev[v] = u;
            }
        }
    }
    
    // 构建并输出路径
    int path[n];
    int pathLen = 0;
    for(int v = end; v != -1; v = prev[v]) {
        path[pathLen++] = v;
    }
    
    // 反转并输出路径
    for(int i = pathLen - 1; i >= 0; i--) {
        cout << path[i];
        if(i > 0) cout << " ";
    }
    cout << endl;
    
    return 0;
}