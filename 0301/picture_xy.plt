set title "collision Arp82(NGC2535+36) no Black hole  dt=0.01 Y-30 "
set title textcolor rgbcolor "white"
set size square
set ticslevel 0
set xrange[-6.0:6.0]
set yrange[-6.0:6.0]

set grid lc rgb "white" lt 2
set xtics 1.0
set ytics 1.0

set border lc rgb "white"
set obj rect behind from screen 0, screen 0  to screen 1,screen 1 fillcolor rgb "black"

set term png
set out "Arp82_30_700.png"

plot "arp82_right_nobh_30.dat" u 1:2 index 700 w p lc rgb "light-salmon" pt 0 notitle ,\
"arp82_left_nobh_30.dat" u 1:2 index 700 w p lc rgb "skyblue" pt 0 notitle

set out
