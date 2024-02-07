# Tarea programada 2 - respaldo lógico
# UCR | ECCI | Sistemas Operativos
# Fabián Orozco B95690 - Daniel Escobar C02748

class directorio:
  def __init__(self):
    self.indicesHijos = []  # contiene a los elementos (directorios y archivos) que tiene dentro
    self.modificado = False  # Bandera de archivo. 0 si ha sido respaldado; 1 si necesita respaldarse
    self.clase = self.__class__.__name__ # indica la clase a la que pertenece el objeto
    self.indice = -1  # indica la posición en que se encuentra en disco

  def imprimir(self):
    if (self.modificado):
      print(f"d{self.indice}*", end="")
    else:
      print(f"d{self.indice}", end=" ")


