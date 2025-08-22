lines=`wc -l polystat.xvg | awk '{print $1}'`
lines=$((lines-28))
avg=`awk -v var=$lines '{if(NR>28)sum+=($3*$3)} END {print sum/var}' polystat.xvg`
awk -v a=$avg '{if(NR>28) print a, ($3*$3-a)*($3*$3-a)}' polystat.xvg > tmp
err=`awk -v var=$lines '{sum+=$2} END {print sqrt($1), 0.5*(1/sqrt($1))*sqrt(sum/var)}' tmp`
rm tmp
echo $err > avg_rg2
