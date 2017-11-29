f(x) = a*(x**3)+b*(x**2)+c*x+d
fit f(x) "saida.dat" using 1:2 via a,b,c,d
plot f(x) smooth bezier lw 2, "saida.dat" using 1:2 with points 
set xlabel "Dimensão da Matriz"
set ylabel "Número de Interações da Decomposição LU"
set title "Interações x Dimensão"
set key below


