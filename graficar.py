 #!/usr/bin/python
 # -*- coding: latin-1 -*-

import os
import sys
import subprocess

if len(sys.argv) != 2:
    print "Uso: ./graficar.py <archivo>"
    sys.exit(1)

comando = """set xlabel "Número de ciclo"
set ylabel "Costo"
set term gif
set output "%s"
plot "%s" using 1:2 title 'Real', \
     "%s" using 1:3 title 'Heurística'
"""

comando = comando % (sys.argv[1].split('.')[0] + ".gif", sys.argv[1], sys.argv[1])

f = open("graficar", "w")
f.write(comando)
f.close()

f = open("graficar")
process = subprocess.Popen('gnuplot', stdin=f)
