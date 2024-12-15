emcc route_planner.cpp -o route_planner.js \
  -s WASM=1 \
  -s EXPORTED_FUNCTIONS='["_findShortestPath", "_freePath"]' \
  -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
  -s NO_EXIT_RUNTIME=1 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -O3