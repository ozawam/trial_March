if(exist("iE")==0||iE<0)iE=0


title(iE) = sprintf("t = %f *dt*interval",iE)
unset label
set label title(iE)  font 'Times,13'  at screen 0.7 ,screen 0.85 textcolor rgbcolor "white"

plot "arp271_right_nobh.dat" u 1:2 index iE w p lc rgb "light-salmon" pt 0 notitle ,\
"arp82_left_nobh.dat" u 1:2 index iE w p lc rgb "skyblue" pt 0 notitle

if(iE < 600) iE=iE+1; reread


