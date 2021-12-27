#---------------------------------------------------------------------------
# This is a basic gnuplot script to generate a performance comparison
# graph. This example requires an "output.dat" file, which is
# generated by running:
#
#     ./hw1_perf > output.dat
#
# To run this script type the following at the command line
#
#     gnuplot -c plot_script.gp
#
# After running the above two commands, the file simple-sort-perf.png
# will be generated. 
#---------------------------------------------------------------------------

infile = "output.dat"
outfile = "simple-sort-perf.png"

# Set the terminal for PNG output and aspect ratio
set terminal pngcairo enhanced font 'Verdana, 10'
set size ratio 0.75

# Save the graph in the given file name (e.g., "graph.png")
set output outfile

# Set the title and each axis label
set xlabel "Input Size (n)"
set ylabel "Time (msec)"

# Move the key to the left of the graph
set key left

# color scheme
RED = "#e6194B"
GREEN = "#3cb44b"
YELLOW = "#ffe119"
BLUE = "#4363d8"
ORANGE = "#f58231"
PURPLE = "#911eb4"
CYAN = "#42d4f4"
MAGENTA = "#f032e6"
LIME = "#bfef45"
PINK = "#fabed4"
TEAL = "#469990"
LAVENDER = "#dcbeff"
BROWN = "#9A6324"
BEIGE = "#fffac8"
MAROON = "#800000"
MINT = "#aaffc3"
OLIVE = "#808000"
APRICOT = "#ffd8b1"
NAVY = "#000075"
GREY = "#a9a9a9"

# Plot the data
set title "Simple Sort Performance Comparison";
plot  infile u 1:2 t "Bubble, Sorted" w linespoints lw 3 lc rgb MAGENTA pointtype 6, \
      infile u 1:3 t "Bubble, Reversed" w linespoints lw 3 lc rgb RED pointtype 6, \
      infile u 1:4 t "Bubble, Shuffled" w linespoints lw 3 lc rgb PURPLE pointtype 6, \
      infile u 1:5 t "Insertion, Sorted" w linespoints lw 2 lc rgb CYAN pointtype 6, \
      infile u 1:6 t "Insertion, Reversed" w linespoints lw 2 lc rgb BLUE pointtype 6, \
      infile u 1:7 t "Insertion, Shuffled" w linespoints lw 2 lc rgb NAVY pointtype 6, \
      infile u 1:8 t "Selection, Sorted" w linespoints lw 4 lc rgb ORANGE pointtype 6, \
      infile u 1:9 t "Selection, Reversed" w linespoints lw 3 lc rgb GREEN pointtype 6, \
      infile u 1:10 t "Selection, Shuffled" w linespoints lw 2 lc rgb MAROON pointtype 6;




