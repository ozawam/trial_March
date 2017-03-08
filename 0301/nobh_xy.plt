set title "collision Arp271 no Black hole  dt=0.001"
set title textcolor rgbcolor "white"
set size square
set ticslevel 0
set xrange[-7.0:7.0]
set yrange[-7.0:7.0]

set grid lc rgb "white" lt 2
set xtics 1.0
set ytics 1.0

set border lc rgb "white"
set obj rect behind from screen 0, screen 0  to screen 1, screen 1 fillcolor rgb "black"

set term gif animate delay 0.001
set out "arp271_1_xy.gif"


load "nobh_xy_plot.plt"


iE=0


set out
