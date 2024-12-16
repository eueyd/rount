(function(global) {
    'use strict';

    var config = {
        debug: false,
        warnings: true,
        quiet: false
    };

    var stdio = {
        output: "",
        input: "",
        inputPosition: 0
    };

    function resetStdio() {
        stdio.output = "";
        stdio.input = "";
        stdio.inputPosition = 0;
    }

    function print(text) {
        stdio.output += text;
    }

    var JSCPP = {
        run: function(code, input, options) {
            if (options) {
                config = Object.assign(config, options);
            }
            
            stdio.input = input || "";
            stdio.output = "";
            stdio.inputPosition = 0;
            
            try {
                var program = new Program(code);
                program.run();
                return stdio.output;
            } catch (e) {
                if (config.debug) {
                    console.error(e);
                }
                throw e;
            }
        }
    };

    function Program(code) {
        this.code = code;
        this.memory = new Memory();
        this.functions = {};
        this.parse();
    }

    Program.prototype.parse = function() {
        var lines = this.code.split("\n");
        var inFunction = false;
        var currentFunction = null;
        
        for (var i = 0; i < lines.length; i++) {
            var line = lines[i].trim();
            
            if (line.startsWith("#include")) {
                continue;
            }
            
            if (line.includes("int main")) {
                inFunction = true;
                currentFunction = "main";
                this.functions.main = [];
                continue;
            }
            
            if (inFunction) {
                if (line === "{") continue;
                if (line === "}") {
                    inFunction = false;
                    continue;
                }
                this.functions[currentFunction].push(line);
            }
        }
    };

    Program.prototype.run = function() {
        if (!this.functions.main) {
            throw new Error("No main function found");
        }
        
        var mainLines = this.functions.main;
        for (var i = 0; i < mainLines.length; i++) {
            this.executeLine(mainLines[i]);
        }
    };

    Program.prototype.processString = function(str) {
        // 处理字符串，移除引号
        return str.replace(/^["']|["']$/g, '');
    };

    Program.prototype.processPrintf = function(line) {
        var match = line.match(/printf\s*\((.*)\)/);
        if (match) {
            var args = match[1].split(',').map(arg => arg.trim());
            var format = this.processString(args[0]);
            args = args.slice(1);

            // 处理格式化字符串
            var output = format;
            for (var i = 0; i < args.length; i++) {
                var placeholder = /%[dfsc]/;
                output = output.replace(placeholder, args[i]);
            }
            
            print(output);
        }
    };

    Program.prototype.processScanf = function(line) {
        var match = line.match(/scanf\s*\((.*)\)/);
        if (match) {
            var args = match[1].split(',').map(arg => arg.trim());
            var format = this.processString(args[0]);
            var variables = args.slice(1).map(arg => arg.replace(/&/g, '').trim());
            
            var inputParts = stdio.input.substr(stdio.inputPosition).trim().split(/\s+/);
            for (var i = 0; i < variables.length; i++) {
                if (inputParts[i]) {
                    var value = inputParts[i];
                    stdio.inputPosition += value.length + 1;
                    this.memory.allocate(variables[i], parseFloat(value) || 0);
                }
            }
        }
    };

    Program.prototype.executeLine = function(line) {
        line = line.trim();
        
        if (line.startsWith("printf")) {
            this.processPrintf(line);
        } else if (line.startsWith("scanf")) {
            this.processScanf(line);
        } else if (line.startsWith("//") || line === "") {
            // 忽略注释和空行
            return;
        } else if (line.includes("=")) {
            // 处理赋值语句
            var parts = line.split("=").map(p => p.trim());
            var varName = parts[0];
            var value = parseFloat(parts[1]) || 0;
            this.memory.allocate(varName, value);
        }
    };

    function Memory() {
        this.variables = {};
    }

    Memory.prototype.allocate = function(name, value) {
        this.variables[name] = value;
    };

    Memory.prototype.get = function(name) {
        return this.variables[name];
    };

    // Export JSCPP
    if (typeof module !== 'undefined' && module.exports) {
        module.exports = JSCPP;
    } else {
        global.JSCPP = JSCPP;
    }

})(typeof window !== 'undefined' ? window : global);