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

    Program.prototype.processCout = function(line) {
        var parts = line.split("<<").slice(1);
        var output = "";
        for (var part of parts) {
            part = part.trim();
            if (part === "endl") {
                output += "\n";
            } else {
                output += part.replace(/[;"]/g, "");
            }
        }
        return output;
    };

    Program.prototype.processCin = function(line) {
        var match = line.match(/cin\s*>>\s*(\w+)/);
        if (match) {
            var varName = match[1];
            var inputParts = stdio.input.substr(stdio.inputPosition).trim().split(/\s+/);
            var value = inputParts[0];
            stdio.inputPosition += value.length + 1;
            this.memory.allocate(varName, parseInt(value) || 0);
            return value;
        }
    };

    Program.prototype.executeLine = function(line) {
        line = line.trim();
        
        if (line.startsWith("cout")) {
            var output = this.processCout(line);
            print(output);
        } else if (line.startsWith("cin")) {
            this.processCin(line);
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