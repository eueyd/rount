#include <iostream>
using namespace std;

int main() {
    int start, end;
    cin >> start >> end;
    
    cout << "Input: " << start << " " << end << endl;
    
    const int n = 21;
    double distances[n][n] = {0};

    // 东湖公园的连接 (0)
    distances[0][1] = distances[1][0] = 5.2;  // 东湖公园 <-> 成都东站
    distances[0][2] = distances[2][0] = 3.8;  // 东湖公园 <-> 川大望江
    distances[0][13] = distances[13][0] = 2.1; // 东湖公园 <-> 东郊记忆
    distances[0][10] = distances[10][0] = 4.3; // 东湖公园 <-> 四川科技馆
    distances[0][11] = distances[11][0] = 6.5; // 东湖公园 <-> 太古里

    // 成都东站的连接 (1)
    distances[1][12] = distances[12][1] = 7.2; // 成都东站 <-> 春熙路
    distances[1][16] = distances[16][1] = 8.4; // 成都东站 <-> 成都图书馆
    distances[1][10] = distances[10][1] = 6.2; // 成都东站 <-> 四川科技馆
    distances[1][11] = distances[11][1] = 7.8; // 成都东站 <-> 太古里
    distances[1][13] = distances[13][1] = 3.5; // 成都东站 <-> 东郊记忆

    // 川大望江的连接 (2)
    distances[2][4] = distances[4][2] = 2.9;  // 川大望江 <-> 成都动物园
    distances[2][15] = distances[15][2] = 4.1; // 川大望江 <-> 川大华西
    distances[2][16] = distances[16][2] = 2.5; // 川大望江 <-> 成都图书馆
    distances[2][17] = distances[17][2] = 4.8; // 川大望江 <-> 万达

    // 杜甫草堂的连接 (3)
    distances[3][14] = distances[14][3] = 1.2; // 杜甫草堂 <-> 锦里
    distances[3][5] = distances[5][3] = 1.5;   // 杜甫草堂 <-> 文殊院
    distances[3][15] = distances[15][3] = 3.2; // 杜甫草堂 <-> 川大华西

    // 成都动物园的连接 (4)
    distances[4][16] = distances[16][4] = 1.8; // 成都动物园 <-> 成都图书馆
    distances[4][17] = distances[17][4] = 3.6; // 成都动物园 <-> 万达
    distances[4][15] = distances[15][4] = 3.3; // 成都动物园 <-> 川大华西
    distances[4][6] = distances[6][4] = 5.7;   // 成都动物园 <-> 青龙湖

    // 文殊院的连接 (5)
    distances[5][14] = distances[14][5] = 0.8; // 文殊院 <-> 锦里
    distances[5][12] = distances[12][5] = 2.4; // 文殊院 <-> 春熙路
    distances[5][9] = distances[9][5] = 2.1;   // 文殊院 <-> 四川博物馆

    // 青龙湖的连接 (6)
    distances[6][20] = distances[20][6] = 5.1; // 青龙湖 <-> 天府公园
    distances[6][18] = distances[18][6] = 4.3; // 青龙湖 <-> 大悦城
    distances[6][17] = distances[17][6] = 3.7; // 青龙湖 <-> 万达
    distances[6][16] = distances[16][6] = 4.2; // 青龙湖 <-> 成都图书馆
    distances[6][10] = distances[10][6] = 6.3; // 青龙湖 <-> 四川科技馆

    // 川大江安的连接 (7)
    distances[7][19] = distances[19][7] = 15.2; // 川大江安 <-> 都江堰
    distances[7][8] = distances[8][7] = 12.5;   // 川大江安 <-> 双流机场
    distances[7][20] = distances[20][7] = 14.3; // 川大江安 <-> 天府公园
    distances[7][16] = distances[16][7] = 13.1; // 川大江安 <-> 成都图书馆

    // 双流机场的连接 (8)
    distances[8][20] = distances[20][8] = 8.9;  // 双流机场 <-> 天府公园
    distances[8][18] = distances[18][8] = 10.3; // 双流机场 <-> 大悦城
    distances[8][17] = distances[17][8] = 9.6;  // 双流机场 <-> 万达
    distances[8][13] = distances[13][8] = 11.2; // 双流机场 <-> 东郊记忆

    // 四川博物馆的连接 (9)
    distances[9][14] = distances[14][9] = 1.6; // 四川博物馆 <-> 锦里
    distances[9][12] = distances[12][9] = 2.2; // 四川博物馆 <-> 春熙路
    distances[9][11] = distances[11][9] = 2.0; // 四川博物馆 <-> 太古里
    distances[9][13] = distances[13][9] = 4.8; // 四川博物馆 <-> 东郊记忆

    // 四川科技馆的连接 (10)
    distances[10][13] = distances[13][10] = 3.1; // 四川科技馆 <-> 东郊记忆
    distances[10][20] = distances[20][10] = 8.9; // 四川科技馆 <-> 天府公园

    // 太古里的连接 (11)
    distances[11][12] = distances[12][11] = 0.5; // 太古里 <-> 春熙路
    distances[11][15] = distances[15][11] = 5.4; // 太古里 <-> 川大华西

    // 东郊记忆的连接 (13)
    distances[13][17] = distances[17][13] = 5.9; // 东郊记忆 <-> 万达

    // 锦里的连接 (14)
    distances[14][16] = distances[16][14] = 3.2; // 锦里 <-> 成都图书馆

    // 天府公园的连接 (20)
    distances[20][19] = distances[19][20] = 18.5; // 天府公园 <-> 都江堰
    distances[20][16] = distances[16][20] = 7.8;  // 天府公园 <-> 成都图书馆

    // Dijkstra算法数组
    double dist[n];
    int prev[n];
    bool visited[n] = {false};

    // 初始化
    for (int i = 0; i < n; i++) {
        dist[i] = 1e9;
        prev[i] = -1;
    }
    dist[start] = 0;

    // Dijkstra算法
    for (int i = 0; i < n - 1; i++) {
        double min_dist = 1e9;
        int u = -1;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        
        visited[u] = true;
        cout << "Visiting: " << u << endl;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && distances[u][v] > 0 && 
                dist[u] + distances[u][v] < dist[v]) {
                dist[v] = dist[u] + distances[u][v];
                prev[v] = u;
            }
        }
    }

    if (prev[end] == -1) {
        cout << "NO_PATH" << endl;
        return 0;
    }

    // 构建路径
    int path[n];
    int path_len = 0;
    for (int v = end; v != -1; v = prev[v]) {
        path[path_len++] = v;
    }

    // 输出路径
    cout << "PATH: ";
    for (int i = path_len - 1; i >= 0; i--) {
        cout << path[i];
        if (i > 0) cout << " ";
    }
    cout << endl;

    cout << "DISTANCE: " << dist[end] << endl;

    return 0;
}