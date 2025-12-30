#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Triming whitespace from both ends
std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

int main() {
    // Reading the config file
    std::ifstream file("kedar.conf");
    if (!file) {
        std::cerr << "Failed to open kedar.conf\n";
        return 1;
    }

    std::map<std::string, std::string> config;
    std::string line;

    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        config[line.substr(0,pos)] = trim(line.substr(pos+1));
    }

    // Extract monitors and workspaces
    int number_of_monitors = std::stoi(config["number_of_monitors"]);
    int number_of_workspaces = std::stoi(config["number_of_workspaces"]);

    std::vector<std::string> monitors, switch_binds, move_binds;
    for (int i = 1; i <= number_of_monitors; i++) monitors.push_back(config["mon_" + std::to_string(i)]);
    for (int i = 1; i <= number_of_workspaces; i++) switch_binds.push_back(config["switch_bind_" + std::to_string(i)]);
    for (int i = 1; i <= number_of_workspaces; i++) move_binds.push_back(config["move_bind_" + std::to_string(i)]);

    // generate kedar1.conf
    std::ofstream out1("kedar1.conf");
    if (!out1) {
        std::cerr << "Failed to create kedar1.conf\n";
        return 1;
    }

    for (int i = 0; i < number_of_monitors; i++) {
        out1 << "# monitor_" << i + 1 << " workspaces [" 
             << i*number_of_workspaces + 1 << "-" 
             << i*number_of_workspaces + number_of_workspaces << "]\n";

        for (int j = 1; j <= number_of_workspaces; j++) {
            out1 << "workspace = " << (j + i * number_of_workspaces)
                 << ", monitor:" << monitors[i] << "\n";
        }
        out1 << "\n";
    }

    out1 << "# Bindings for switching workspaces\n";
    for (int i = 0; i < number_of_workspaces; i++) {
        out1 << "bind = " << switch_binds[i] 
             << " exec /kedar2.sh " 
             << i + 1 << " switch\n";
    }
    out1 << "\n# Bindings for moving windows\n";
    for (int i = 0; i < number_of_workspaces; i++) {
        out1 << "bind = " << move_binds[i] 
             << " exec /kedar2.sh " 
             << i + 1 << " move\n";
    }

    // generate kedar2.sh
    std::ofstream out2("kedar2.sh");
    if (!out2) {
        std::cerr << "Failed to create kedar2.sh\n";
        return 1;
    }

    out2 << "#!/usr/bin/env bash\n\n";
    out2 << "n=$1  # workspace number\n";
    out2 << "mode=$2  # optional: move\n\n";
    out2 << "mon=$(hyprctl activeworkspace -j | jq -r '.monitor')\n\n";

    out2 << "case \"$mon\" in\n";
    for (int i = 0; i < number_of_monitors; i++) {
        out2 << "    \"" << monitors[i] << "\") base=" 
             << i*number_of_workspaces << " ;;\n";
    }
    out2 << "    *) base=0 ;;\n";
    out2 << "esac\n\n";

    out2 << "target=$((base + n))\n\n";
    out2 << "if [[ \"$mode\" == \"move\" ]]; then\n";
    out2 << "    hyprctl dispatch movetoworkspace \"$target\"\n";
    out2 << "else\n";
    out2 << "    hyprctl dispatch focusworkspaceoncurrentmonitor \"$target\"\n";
    out2 << "fi\n";

    std::cout << "Generated kedar1.conf and kedar2.sh successfully!\n";
    return 0;
}

