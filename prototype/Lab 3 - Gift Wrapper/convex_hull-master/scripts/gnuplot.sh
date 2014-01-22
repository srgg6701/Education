#
#
# This script is expected to be executed from the root
# on the same directory where the makefile is
#
GNUPLOT=$(type -p "gnuplot")
PSMERGE=$(type -p "psmerge")
PLOTSCRIPT=scripts/plot.p
DATADIR=data
GEN=bin/main_chullgnuplot.out

for f in `ls ${DATADIR}/*dat`
do
    echo "${GEN} < ${f} > ${f}.chull"
    ${GEN} < ${f} > ${f}.chull
    echo "${GNUPLOT} -e \"pcloud=\'$f\';chull=\'$f.chull\';outfile=\'$f.ps\'\" ${PLOTSCRIPT}"
    ${GNUPLOT} -e "pcloud='$f';chull='$f.chull';outfile='$f.ps'" ${PLOTSCRIPT}
done

${PSMERGE} -oplots.ps data/*.ps

echo "Convex hull examples saved in plots.ps"

