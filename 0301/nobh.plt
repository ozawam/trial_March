set title "collision Arp82(NGC2535+36) no Black hole dt=0.01 Y-10"
set title textcolor rgbcolor "white"
set view equal xyz
set ticslevel 0
set xrange[-6.0:6.0]
set yrange[-6.0:6.0]
set zrange[-6.0:6.0]
set grid lc rgb "white" lt 2
set xtics 1.0
set ytics 1.0
set ztics 1.0
set border lc rgb "white"
set obj rect behind from screen 0, screen 0 ,screen 0 to screen 1, screen 1,screen 1 fillcolor rgb "black"

set term gif animate delay 0.001
set out "arp82_nobh_10.gif"


load "arp82_no_Black_hole_plot.plt"


iE=0


set out
