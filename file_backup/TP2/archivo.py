# Tarea programada 2 - respaldo lógico
# UCR | ECCI | Sistemas Operativos
# Fabián Orozco B95690 - Daniel Escobar C02748

class archivo:
  def __init__(self):
    self.nombre = ""
    self.modificado = False  # Bandera de archivo. 0 si ha sido respaldado; 1 si necesita respaldarse
    self.clase = self.__class__.__name__  # da el tipo de archivo
    self.indice = -1

  def imprimir(self):
    if (self.modificado):
      print(f"a{self.indice}*",end="")
    else:
      print(f"a{self.indice}", end=" ")
