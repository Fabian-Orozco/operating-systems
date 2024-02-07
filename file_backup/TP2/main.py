# Tarea programada 2 - respaldo lógico
# UCR | ECCI | Sistemas Operativos
# Fabián Orozco B95690 - Daniel Escobar C02748

from directorio import directorio
from archivo import archivo

MAX_ARCHIVOS = 11
MAX_DIRECTORIOS = 3
disco = []
respaldo = []
bitmap = []

# Genera la estructura inicial del disco (archivos y directorios)
# directorio 3 y archivo 4 modificados
def generarArchivos() -> None:
  raiz = directorio()
  raiz.indice = 0
  disco.append(raiz)
  for i in range(0, MAX_DIRECTORIOS):
    dir = directorio()
    dir.indice = i+1
    disco.append(dir)
  
  # asigna dos directorios hijos a la raiz
  raiz.indicesHijos.append(1)
  raiz.indicesHijos.append(2)

  # asigna un directorio 
  disco[1].indicesHijos.append(3)

  # crea 6 archivos
  for i in range(0,5):
    arch = archivo()
    arch.nombre = f"archivo_{i+4}"
    arch.indice = i+4
    disco.append(arch)

  # asigna directorios y archivos modificados.
  disco[3].modificado = True
  disco[4].modificado = True

  disco[1].indicesHijos.append(6)

  # hijo izquierdo
  disco[3].indicesHijos.append(4)
  disco[3].indicesHijos.append(5)
  # hijo derecho
  disco[2].indicesHijos.append(7)
  disco[2].indicesHijos.append(8)

# Crea el mapa de bits
def crearBitMap():
  bitmap.clear()
  for posicionDisco in disco:
    # FASE 1. marca en mapa de bits 1 si el archivo ha sido modificado o si es un directorio.
    bitmap.append(1 if posicionDisco.modificado or posicionDisco.clase == "directorio" else 0)

# Desmarca directorios que no ocupan respaldarse
def marcarBitMap():
  marcarDirectorio(disco[0])

# Recorre el bitmap y deja marcados solo los directorios que tienen elementos modificados bajo ellos.
def marcarDirectorio(elemento) -> bool:
  esModificado = 0
  for intHijo in elemento.indicesHijos:
    if (disco[intHijo].clase == "directorio"):
      resultado = marcarDirectorio(disco[intHijo])
      if (esModificado == 0):
        esModificado = resultado
    elif(disco[intHijo].modificado == 1):
      esModificado = 1
      return 1

  bitmap[elemento.indice] = esModificado
  return esModificado

# imprime el disco
def printEstructura(estructura):
  for i in range(len(estructura)):
    if (estructura[i] != None and estructura[i].clase == "directorio"):
      indices = estructura[i].indicesHijos
      estructura[i].imprimir()
      print("", end=":  ")
      for elemento in indices:
        if (estructura[i] != None):
          estructura[elemento].imprimir()
          print("", end="  ")
      print()
  print()
    
# Recorre el bitmap y dependiendo del tipo (directorio o archivo), lo respalda.
# Modifica la bandera de respaldo del archivo <modificado>, lo añade a la estructura de respaldo y actualiza el bitmap.
def respaldarDisco(elemento):
  for elem in range(len(bitmap)):
    if (bitmap[elem] == 1 and disco[elem].clase == elemento):
      # modifica la bandera de archivo.
      disco[elem].modificado = 0
      # mete el elemento a la estructura de respaldo
      respaldo[elem] = disco[elem]
      # respalda el archivo y actualiza bitmap
      bitmap[elem] = 0

# copia los archivos y directorios del disco original al disco de respaldo
def respaldoCompleto() :
  for i in disco:
    respaldo.append(i)

# imprime el bitmap
def printBitMap():
  print("Bitmap:" , bitmap)

# imprime el orden de los directorios y archivos como ayuda visual
def printEncabezado():
  print("Nombres:" + " "*7 + "[", end="")
  for i in disco:
    print(f"d{i.indice}" if i.clase == "directorio" else f"a{i.indice}", end="")
    if (i.indice != len(disco)-1):
      print("",end=" ")
  print("]")

# Ejecuta las fases del algoritmo de respaldo lógico
def ejecutarAlgoritmo(mensaje):
  print(mensaje)
  printEstructura(disco)

  printEncabezado()
  crearBitMap()
  
  # La salida muestra el resultado de aplicar cada fase
  print("FASE 1 ", end="")
  printBitMap()

  print("FASE 2 ", end="")
  marcarBitMap()
  printBitMap()

  print("FASE 3 ", end="")
  respaldarDisco("directorio")
  printBitMap()
  
  print("FASE 4 ", end="")
  respaldarDisco("archivo")
  printBitMap()

  print("\nDisco de respaldo:")
  printEstructura(respaldo)

def main():
  print("Tarea programada 2 - Respaldo lógico\n")
  print("* indica modificado\n")

  generarArchivos()
  # Realiza un respaldo completo del disco
  respaldoCompleto()

  ejecutarAlgoritmo("Disco inicial")

  print("#############################################\n")
  
  # Procede a modificar otro archivo
  disco[7].modificado = True
  ejecutarAlgoritmo("Disco luego de modificacion")

if __name__ == "__main__":
  main()