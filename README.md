Implemetancion del algoritmo que soluciona el problema 1 de la tarea 6 de la materia CI5651 Diseño de algoritmos

Considere un arreglo A[1..N], representando una permutación de los números
de 1 a N.
Se desea que ejecute N acciones de la forma multiswap(a, b). Esta acción consite en:
(a) Intercambiar el valor en la posición a con el valor en la posición b.
(b) Invocar multiswap(a+1,b+1)
(c) El proceso termina cuando b se sale del rango del arreglo o a alcanza el primer valor
de b utilizado.
A continuación se presenta una implementación en pseudo–Python para multiswap(a,b):
def multiswap(A, a, b):
i, j = a, b
while i < b and j <= N:
swap(A, i, j)
i += 1
j += 1
Si A inicia como la permutación identidad (números del 1 al N, de menor a mayor) y se
ejecutan N operaciones multiswap(ai, bi) (donde los valores para ai y bi vienen dados
en una lista de tuplas), se desea que imprima el arreglo resultado.
Diseñe un algoritmo que pueda ejecutar esta acción en tiempo promedio O(N log N), usando
memoria adicional O(N).
