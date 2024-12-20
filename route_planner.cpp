#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);  // 禁用同步以提高性能
    cin.tie(nullptr);                  // 解除cin和cout的绑定
    
    //cout << "DEBUG: Program started\n" << flush;
    //cerr<< "DEBUG: Error stream test\n" << flush;
    
    int start, end;
    //cout << "DEBUG: Waiting for input in format: start_index end_index\n" << flush;
    //cout << "DEBUG: About to read input\n" << flush;
    
    cin >> start >> end;
    if (cin.fail()) {
        cout << "ERROR: Failed to read input\n" << flush;
        return 1;
    }
    //cout << "DEBUG: Got input: " << start << " " << end << "\n" << flush;
    
    // 验证范围
    const int MAX_LOCATIONS = 21;  // 根据实际地点数量设置
    if (start < 0 || end < 0 || start >= MAX_LOCATIONS || end >= MAX_LOCATIONS) {
        cout << "ERROR: Invalid input range. Valid range is 0-" << (MAX_LOCATIONS-1) << "\n" << flush;
        return 1;
    }
    //cout << "DEBUG: Input validation passed\n" << flush;

    const int n = 21;
    // 初始化距离数组
    double distances[21][21];
    //cout << "DEBUG: Initializing distances array\n" << flush;
    
    // 初始化为大值
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            distances[i][j] = 1e9;
        }
        distances[i][i] = 0;  // 自己到自己的距离为0
    }
    //cout << "DEBUG: Basic distance initialization done\n" << flush;

    // 东湖公园的连接 (0)
    distances[0][1] = distances[1][0] = 5.2;   // 成都东站
    distances[0][2] = distances[2][0] = 3.8;   // 川大望江
    distances[0][13] = distances[13][0] = 2.1; // 东郊记忆
    distances[0][10] = distances[10][0] = 4.3; // 四川科技馆
    distances[0][11] = distances[11][0] = 6.5; // 太古里

    // 成都东站的连接 (1)
    distances[1][12] = distances[12][1] = 7.2; // 春熙路
    distances[1][16] = distances[16][1] = 8.4; // 成都图书馆
    distances[1][10] = distances[10][1] = 6.2; // 四川科技馆
    distances[1][11] = distances[11][1] = 7.8; // 太古里
    distances[1][13] = distances[13][1] = 3.5; // 东郊记忆

    // 川大望江的连接 (2)
    distances[2][4] = distances[4][2] = 2.9;   // 成都动物园
    distances[2][15] = distances[15][2] = 4.1; // 川大华西
    distances[2][16] = distances[16][2] = 2.5; // 成都图书馆
    distances[2][17] = distances[17][2] = 4.8; // 万达

    // 杜甫草堂的连接 (3)
    distances[3][14] = distances[14][3] = 1.2; // 锦里
    distances[3][5] = distances[5][3] = 1.5;   // 文殊院
    distances[3][15] = distances[15][3] = 3.2; // 川大华西

    // 成都动物园的连接 (4)
    distances[4][16] = distances[16][4] = 1.8; // 成都图书馆
    distances[4][17] = distances[17][4] = 3.6; // 万达
    distances[4][15] = distances[15][4] = 3.3; // 川大华西
    distances[4][6] = distances[6][4] = 5.7;   // 青龙湖

    // 文殊院的连接 (5)
    distances[5][14] = distances[14][5] = 0.8; // 锦里
    distances[5][12] = distances[12][5] = 2.4; // 春熙路
    distances[5][9] = distances[9][5] = 2.1;   // 四川博物馆

    // 青龙湖的连接 (6)
    distances[6][20] = distances[20][6] = 5.1; // 天府公园
    distances[6][18] = distances[18][6] = 4.3; // 大悦城
    distances[6][17] = distances[17][6] = 3.7; // 万达
    distances[6][16] = distances[16][6] = 4.2; // 成都图书馆
    distances[6][10] = distances[10][6] = 6.3; // 四川科技馆

    // 川大江安的连接 (7)
    distances[7][19] = distances[19][7] = 15.2; // 都江堰
    distances[7][8] = distances[8][7] = 12.5;   // 双流机场
    distances[7][20] = distances[20][7] = 14.3; // 天府公园
    distances[7][16] = distances[16][7] = 13.1; // 成都图书馆

    // 双流机场的连接 (8)
    distances[8][20] = distances[20][8] = 8.9;  // 天府公园
    distances[8][18] = distances[18][8] = 10.3; // 大悦城
    distances[8][17] = distances[17][8] = 9.6;  // 万达
    distances[8][13] = distances[13][8] = 11.2; // 东郊记忆

    // 四川博物馆的连接 (9)
    distances[9][14] = distances[14][9] = 1.6; // 锦里
    distances[9][12] = distances[12][9] = 2.2; // 春熙路
    distances[9][11] = distances[11][9] = 2.0; // 太古里
    distances[9][13] = distances[13][9] = 4.8; // 东郊记忆

    // 天府公园的连接 (20)
    distances[20][19] = distances[19][20] = 18.5; // 都江堰
    distances[20][16] = distances[16][20] = 7.8;  // 成都图书馆
    distances[20][10] = distances[10][20] = 8.9;  // 四川科技馆

    // 太古里和春熙路的连接
    distances[11][12] = distances[12][11] = 0.5; // 太古里 <-> 春熙路
    distances[11][15] = distances[15][11] = 5.4; // 太古里 <-> 川大华西

    // 东郊记忆的连接
    distances[13][17] = distances[17][13] = 5.9; // 东郊记忆 <-> 万达

    // 锦里的连接
    distances[14][16] = distances[16][14] = 3.2; // 锦里 <-> 成都图书馆

    //cout << "DEBUG: Distance matrix initialized\n" << flush;

    // Dijkstra算法
    double dist[n];
    int prev[n];
    bool visited[n] = {false};

    for (int i = 0; i < n; i++) {
        dist[i] = 1e9;
        prev[i] = -1;
    }
    dist[start] = 0;

    //cout << "DEBUG: Starting Dijkstra algorithm\n" << flush;

    // Dijkstra主循环
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
        //cout << "DEBUG: Processing node " << u << "\n" << flush;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && distances[u][v] != 1e9 && 
                dist[u] + distances[u][v] < dist[v]) {
                dist[v] = dist[u] + distances[u][v];
                prev[v] = u;
                //cout << "DEBUG: Updated distance to node " << v << ": " << dist[v] << "\n" << flush;
            }
        }
    }

    //cout << "DEBUG: Dijkstra completed\n" << flush;

    if (prev[end] == -1) {
        cout << "No path found\n" << flush;
        return 0;
    }

    // 构建路径
    int path[MAX_LOCATIONS];
    int path_len = 0;
    for (int v = end; v != -1; v = prev[v]) {
        path[path_len++] = v;
    }

    //cout << "DEBUG: Path constructed\n" << flush;
    
    // 输出路径(只保留一个输出版本,使用箭头格式)
    cout << "Total nodes in path: " << path_len << "\n" << flush;
    cout << "PATH:";
    for (int i = path_len - 1; i >= 0; i--) {
        cout << " " << path[i];
        if (i > 0) {
            cout << " ->" << flush;
        }
    }
    cout << "\n" << flush;

    // 输出总距离
    cout << "DISTANCE: " << dist[end] << "\n" << flush;
    //cout << "DEBUG: Program completed\n" << flush;
    
    return 0;
}