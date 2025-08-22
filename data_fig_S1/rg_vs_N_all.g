set term postscript eps enhanced color font 'Helvetica,28'
set output "rg_vs_N_log.eps"
set rmargin 1.7
set tmargin 0.5
set bmargin 2.7
set lmargin 6.5
set xtics 0.2
#set ytics 0.1
set mytics 5
set mxtics 5
set key right bottom spacing 1.2 font 'Helvetica,28'
#set key at 2.52,1.9
set xrange [0.5:2.4]
set yrange [-0.35:0.25]
set label "(b)" at 0.6, 0.2 font 'Helvetica,32'
set xlabel "log N" offset 0,0.5
set ylabel "log(R_g) [nm]" offset 2.0, 0.0
f(x)=A*(x)+b
fit f(x) "rg_data_solvated" u (log10($1)):(log10($2)) via A,b
set style line 1 lw 4 linecolor rgb "orange" ps 2.5 pt 2
set style line 2 lw 4 linecolor rgb "sea-green" ps 2.5 pt 4
set style line 3 lw 4 linecolor rgb "magenta" ps 2.5 pt 6
set style line 4 lw 4 linecolor rgb "purple" ps 2.5 pt 8
set style line 5 lw 4 linecolor rgb "dark-turquoise" ps 2.5 pt 10
set style line 6 lw 4 linecolor rgb "blue" ps 2.5 pt 12
set style line 7 lw 4 linecolor rgb "brown" ps 2.5 pt 1
set style line 8 lw 4 linecolor rgb "dark-grey" ps 2.5 pt 14
p "rg_data_solvated" u (log10($1)):(log10($2)):(0.434*($3/$2)) w yerrorbars ls 1 title "PCL in water", "rg_PCL10_water_acetone_DiPasquale" u (log10($1)):(log10($2)):(0.434*($3/$2)) w yerrorbars ls 4 title "Di Pasquale, N=10","rg_PCL30_water_acetone_DiPasquale" u (log10($1)):(log10($2)):(0.434*($3/$2)) w yerrorbars ls 5 title "Di Pasquale, N=30", "rg_data_drenscko_membrane" u (log10($1)):(log10($2)):(0.434*($3/$2)) w yerrorbars ls 2 title "Drenscko", f(x) w l lt 0 lw 10 title 'Rg {/Symbol \176} N^{0.28}'

