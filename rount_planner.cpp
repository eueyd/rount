#include <stdlib.h>
#include <math.h>

// 避免使用 emscripten/bind.h，改用纯C接口
extern "C" {

// 使用简单的C数组代替vector
int* findShortestPath(double* distances, int n, int start, int end, int* pathLength) {
    // 初始化辅助数组
    double* dist = (double*)malloc(n * sizeof(double));
    int* prev = (int*)malloc(n * sizeof(int));
    bool* visited = (bool*)malloc(n * sizeof(bool));
    
    // 初始化距离数组
    for(int i = 0; i < n; i++) {
        dist[i] = INFINITY;
        prev[i] = -1;
        visited[i] = false;
    }
    dist[start] = 0;
    
    // Dijkstra算法主循环
    for(int i = 0; i < n; i++) {
        // 找到最近的未访问节点
        int u = -1;
        double minDist = INFINITY;
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
            double weight = distances[u * n + v];
            if(weight > 0 && !visited[v] && 
               dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
            }
        }
    }
    
    // 构建路径
    int maxLength = n;
    int* tempPath = (int*)malloc(maxLength * sizeof(int));
    int pathIdx = 0;
    
    // 从终点回溯到起点
    for(int v = end; v != -1; v = prev[v]) {
        tempPath[pathIdx++] = v;
    }
    
    // 反转路径
    int* path = (int*)malloc(pathIdx * sizeof(int));
    for(int i = 0; i < pathIdx; i++) {
        path[i] = tempPath[pathIdx - 1 - i];
    }
    
    // 清理内存
    free(dist);
    free(prev);
    free(visited);
    free(tempPath);
    
    *pathLength = pathIdx;
    return path;
}

// 释放路径内存
void freePath(int* path) {
    free(path);
}

} // extern "C"