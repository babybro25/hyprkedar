# hyprkedar
Tool for easily switch between workspaces and moving windows in multiple monitors setup in hyprland

# configuration
1. Open kedar.conf and start configuring<br>
2. Please keep in mind to write as much monitor name you have mention and similarly for the binding or shortcuts<br>
   monitor name = number of monitor<br>
   binding/shortcuts = number of workspaces<br>
3. Monitor name should be similar to the monitor name you get from running this in the terminal<br>
   command : hyprctl monitors -j | jq -r '.[].name'<br>
5. Enjoy

# how to use it
1. First go to the directory where it it cloned.
2. Make binary of the kedar.cxx<br>
   using : g++ -std=c++17 kedar.cxx -o kedar<br>
3. Run : "./kedar" in the terminal<br>
4. Open hyprland.conf file (generally located in ~/.config/hypr/hyprland.conf)
5. Add this line in <ins>**last**</ins> and delete all the predefined lines for workspaces or moving or switching<br>
   Line : source = "location of kedar1.conf"
   replace location of kedar1.conf<br>
   generally placed in the file where is cloned -> main_files -> kedar1.conf<br>
6. Do : hyprctl reload<br>
7. Enjoy

