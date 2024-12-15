#include <iostream>
using namespace std;

int main() {
  // 从标准输入读取起点和终点
  int start, end;
  // 简化输入获取
  cin >> start;
  cin >> end;

  // 在 main 函数内，设置距离矩阵的部分
  const int n = 21;             // 21个地点
  double distances[n][n] = {0}; // 初始化为0

  // 设置实际距离值 (单位：公里)
  // 东湖公园的连接
  distances[0][1] = 5.2;  // 东湖公园 -> 成都东站
  distances[0][2] = 3.8;  // 东湖公园 -> 川大望江
  distances[0][13] = 2.1; // 东湖公园 -> 东郊记忆
  distances[0][10] = 4.3; // 东湖公园 -> 四川科技馆

  // 成都东站的连接
  distances[1][0] = 5.2;  // 成都东站 -> 东湖公园
  distances[1][13] = 3.5; // 成都东站 -> 东郊记忆
  distances[1][10] = 6.2; // 成都东站 -> 四川科技馆
  distances[1][11] = 7.8; // 成都东站 -> 太古里

  // 川大望江的连接
  distances[2][0] = 3.8;  // 川大望江 -> 东湖公园
  distances[2][4] = 2.9;  // 川大望江 -> 成都动物园
  distances[2][15] = 4.1; // 川大望江 -> 川大华西
  distances[2][16] = 2.5; // 川大望江 -> 成都图书馆

  // 杜甫草堂的连接
  distances[3][14] = 1.2; // 杜甫草堂 -> 锦里
  distances[3][5] = 1.5;  // 杜甫草堂 -> 文殊院
  distances[3][15] = 3.2; // 杜甫草堂 -> 川大华西

  // 成都动物园的连接
  distances[4][2] = 2.9;  // 成都动物园 -> 川大望江
  distances[4][16] = 1.8; // 成都动物园 -> 成都图书馆
  distances[4][17] = 3.6; // 成都动物园 -> 万达

  // 文殊院的连接
  distances[5][3] = 1.5;  // 文殊院 -> 杜甫草堂
  distances[5][14] = 0.8; // 文殊院 -> 锦里
  distances[5][12] = 2.4; // 文殊院 -> 春熙路

  // 青龙湖的连接
  distances[6][20] = 5.1; // 青龙湖 -> 天府公园
  distances[6][18] = 4.3; // 青龙湖 -> 大悦城
  distances[6][17] = 3.7; // 青龙湖 -> 万达

  // 川大江安的连接
  distances[7][19] = 15.2; // 川大江安 -> 都江堰
  distances[7][8] = 12.5;  // 川大江安 -> 双流机场

  // 双流机场的连接
  distances[8][7] = 12.5;  // 双流机场 -> 川大江安
  distances[8][20] = 8.9;  // 双流机场 -> 天府公园
  distances[8][18] = 10.3; // 双流机场 -> 大悦城

  // 四川博物馆的连接
  distances[9][14] = 1.6; // 四川博物馆 -> 锦里
  distances[9][12] = 2.2; // 四川博物馆 -> 春熙路
  distances[9][11] = 2.0; // 四川博物馆 -> 太古里

  // 四川科技馆的连接
  distances[10][0] = 4.3;  // 四川科技馆 -> 东湖公园
  distances[10][1] = 6.2;  // 四川科技馆 -> 成都东站
  distances[10][13] = 3.1; // 四川科技馆 -> 东郊记忆

  // 太古里的连接
  distances[11][12] = 0.5; // 太古里 -> 春熙路
  distances[11][9] = 2.0;  // 太古里 -> 四川博物馆
  distances[11][1] = 7.8;  // 太古里 -> 成都东站

  // 春熙路的连接
  distances[12][11] = 0.5; // 春熙路 -> 太古里
  distances[12][9] = 2.2;  // 春熙路 -> 四川博物馆
  distances[12][5] = 2.4;  // 春熙路 -> 文殊院

  // 东郊记忆的连接
  distances[13][0] = 2.1;  // 东郊记忆 -> 东湖公园
  distances[13][1] = 3.5;  // 东郊记忆 -> 成都东站
  distances[13][10] = 3.1; // 东郊记忆 -> 四川科技馆

  // 锦里的连接
  distances[14][3] = 1.2; // 锦里 -> 杜甫草堂
  distances[14][5] = 0.8; // 锦里 -> 文殊院
  distances[14][9] = 1.6; // 锦里 -> 四川博物馆

  // 川大华西的连接
  distances[15][2] = 4.1;  // 川大华西 -> 川大望江
  distances[15][3] = 3.2;  // 川大华西 -> 杜甫草堂
  distances[15][16] = 2.7; // 川大华西 -> 成都图书馆

  // 成都图书馆的连接
  distances[16][2] = 2.5;  // 成都图书馆 -> 川大望江
  distances[16][4] = 1.8;  // 成都图书馆 -> 成都动物园
  distances[16][15] = 2.7; // 成都图书馆 -> 川大华西

  // 万达的连接
  distances[17][4] = 3.6;  // 万达 -> 成都动物园
  distances[17][6] = 3.7;  // 万达 -> 青龙湖
  distances[17][18] = 2.9; // 万达 -> 大悦城

  // 大悦城的连接
  distances[18][17] = 2.9; // 大悦城 -> 万达
  distances[18][6] = 4.3;  // 大悦城 -> 青龙湖
  distances[18][8] = 10.3; // 大悦城 -> 双流机场

  // 都江堰的连接
  distances[19][7] = 15.2;  // 都江堰 -> 川大江安
  distances[19][20] = 18.5; // 都江堰 -> 天府公园

  // 天府公园的连接
  distances[20][6] = 5.1;   // 天府公园 -> 青龙湖
  distances[20][8] = 8.9;   // 天府公园 -> 双流机场
  distances[20][19] = 18.5; // 天府公园 -> 都江堰

  /* 地点对照表：
  0: 东湖公园     1: 成都东站     2: 川大望江     3: 杜甫草堂     4: 成都动物园
  5: 文殊院       6: 青龙湖       7: 川大江安     8: 双流机场     9: 四川博物馆
  10: 四川科技馆  11: 太古里      12: 春熙路      13: 东郊记忆    14: 锦里
  15: 川大华西    16: 成都图书馆  17: 万达        18: 大悦城      19: 都江堰
  20: 天府公园
  */

  // 初始化辅助数组
  double dist[n];
  int prev[n];
  bool visited[n];

  // 初始化距离数组
  for (int i = 0; i < n; i++) {
    dist[i] = 1e9; // 用一个很大的数代替INFINITY
    prev[i] = -1;
    visited[i] = false;
  }
  dist[start] = 0;

  // Dijkstra算法主循环
  for (int i = 0; i < n; i++) {
    // 找到最近的未访问节点
    int u = -1;
    double minDist = 1e9;
    for (int j = 0; j < n; j++) {
      if (!visited[j] && dist[j] < minDist) {
        minDist = dist[j];
        u = j;
      }
    }

    if (u == -1)
      break;
    visited[u] = true;

    // 更新邻居节点的距离
    for (int v = 0; v < n; v++) {
      if (distances[u][v] > 0 && !visited[v] &&
          dist[u] + distances[u][v] < dist[v]) {
        dist[v] = dist[u] + distances[u][v];
        prev[v] = u;
      }
    }
  }

  // 构建并输出路径
  int path[n];
  int pathLen = 0;
  for (int v = end; v != -1; v = prev[v]) {
    path[pathLen++] = v;
  }

  // 反转并输出路径
  for (int i = pathLen - 1; i >= 0; i--) {
    cout << path[i];
    if (i > 0)
      cout << " ";
  }
  cout << endl;

  return 0;
}