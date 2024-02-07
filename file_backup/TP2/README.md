# Tarea programada 2 - Respaldo lógico

## Autores

- Fabián Orozco B95690
- Daniel Escobar C02748

## Ejecución

Introduzca el siguiente comando en terminal:  
`python main.py`


Ejemplo de salida esperada:

~~~bash
$ python main.py 
Tarea programada 2 - Respaldo lógico

* indica modificado

Disco inicial
d0 :  d1   d2
d1 :  d3*  a6
d2 :  a7   a8
d3*:  a4*  a5

Nombres:       [d0 d1 d2 d3 a4 a5 a6 a7 a8]
FASE 1 Bitmap: [1, 1, 1, 1, 1, 0, 0, 0, 0]
FASE 2 Bitmap: [1, 1, 0, 1, 1, 0, 0, 0, 0]
FASE 3 Bitmap: [0, 0, 0, 0, 1, 0, 0, 0, 0]
FASE 4 Bitmap: [0, 0, 0, 0, 0, 0, 0, 0, 0]

Disco de respaldo:
d0 :  d1   d2
d1 :  d3   a6
d2 :  a7   a8
d3 :  a4   a5

#############################################

Disco luego de modificacion
d0 :  d1   d2
d1 :  d3   a6
d2 :  a7*  a8
d3 :  a4   a5

Nombres:       [d0 d1 d2 d3 a4 a5 a6 a7 a8]
FASE 1 Bitmap: [1, 1, 1, 1, 0, 0, 0, 1, 0]
FASE 2 Bitmap: [1, 0, 1, 0, 0, 0, 0, 1, 0]
FASE 3 Bitmap: [0, 0, 0, 0, 0, 0, 0, 1, 0]
FASE 4 Bitmap: [0, 0, 0, 0, 0, 0, 0, 0, 0]

Disco de respaldo:
d0 :  d1   d2
d1 :  d3   a6
d2 :  a7   a8
d3 :  a4   a5
~~~
