项目运行说明

1. C++程序编译和运行
   # 1. 在VSCode中打开项目文件夹
   # 2. 打开终端(Terminal)
   # 3. 编译C++文件
   gcc route_planner.cpp -o route_planner.exe
   # 4. 运行生成的可执行文件
   ./route_planner.exe

2. 项目文件结构说明
   ├── CODE/                    # 主项目目录
   │   ├── .dist               # 分发目录
   │   ├── .vscode/            # VSCode配置文件夹
   │   │   ├── c_cpp_properties.json
   │   │   ├── launch.json
   │   │   └── settings.json
   │   ├── lib/                # 库文件目录
   │   │   └── jscpp.js        # JavaScript C++接口文件
   │   ├── compile.sh          # 编译脚本
   │   ├── index.html          # 网页主界面
   │   ├── place.txt           # 地点数据文件
   │   ├── route_planner.cpp   # C++源代码
   │   └── route_planner.exe   # 编译后的可执行文件
   ├── compile.sh              # 根目录编译脚本
   └── readme.txt              # 说明文档

3. 网页界面运行（当前存在问题）
   # 1. 在VSCode中安装Live Server插件
   # 2. 右键index.html，选择"Open with Live Server"
   注意：目前网页端因缓冲区为空暂时无法正常使用

4. 已知问题
   - 网页界面当前无法正常运行（缓冲区为空）
   - WebAssembly和JavaScript集成部分待完善
   - 目前仅支持C++版本的直接运行

5. 后续更新计划
   - 解决网页端缓冲区问题
   - 完善WebAssembly集成
   - 优化用户界面交互

注意事项：
确保系统已安装gcc编译器和相关开发环境。
如遇问题请检查开发环境配置。