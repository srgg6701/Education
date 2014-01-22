#Expects to receive pcloud, chull and outfile from the command line

set term postscript color portrait
set output outfile
set autoscale
#set xrange [-125:125]
#set yrange [-125:125]
plot pcloud title "points", \
        chull title "chull" with lines
