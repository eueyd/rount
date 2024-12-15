(function(global) {
    'use strict';

    var config = {
        debug: false,
        warnings: true,
        quiet: false
    };

    var stdio = {
        output: "",
        input: ""
    };

    function resetStdio() {
        stdio.output = "";
        stdio.input = "";
    }

    function print(text) {
        stdio.output += text;
    }

    // Main JSCPP object
    var JSCPP = {
        run: function(code, input, options) {
            if (options) {
                config = Object.assign(config, options);
            }
            
            stdio.input = input || "";
            stdio.output = "";
            
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

    // Program class
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