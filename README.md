# hyprkedar
Tool for easily switch between workspaces and moving windows in multiple monitors setup in hyprland

# configuration
1. Open kedar.conf and start configuring
2. Please keep in mind to write as much monitor name you have mention and similarly for the binding or shortcuts
   monitor name = number of monitor
   binding/shortcuts = number of workspaces
3. Enjoy

# How to use it
1. First go to the directory where it it cloned.
2. Make binary of the kedar.cxx
   using : g++ -std=c++17 kedar.cxx -o kedar
3. Run : "./kedar" in the terminal
4. Open hyprland.conf file (generally located in ~/.config/hypr/hyprland.conf)
5. Add this line in last and delete all the predefined lines for workspaces or moving or switching
   Line : source "location of kedar1.sh"
   replace location of kedar1.sh

