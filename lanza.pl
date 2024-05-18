#!/usr/bin/perl
#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: J. Corredor
#     Fecha: Febrero 2024
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script automatización ejecución por lotes 
#****************************************************************/

$Path = `pwd`;         # Obtiene la ruta del directorio actual
chomp($Path);          # Elimina el carácter de nueva línea al final de la ruta del directorio

@Nombre_Ejecutable = ("MM_ejecutable","MM_transpuesta");          # Define los nombres de los ejecutables
@Size_Matriz = ("150","250","1000","2000","3000","4000");              # Define los tamaños de las matrices
@Num_Hilos = (1,2,4,6,8);          # Define el número de hilos
$Repeticiones = 30;          # Define el número de repeticiones

foreach $nombre (@Nombre_Ejecutable){          
	foreach $size (@Size_Matriz){  
		foreach $hilo (@Num_Hilos) {  
			$file = "$Path/$nombre-".$size."-Hilos-".$hilo.".dat";  # Define el nombre del archivo de salida
			for ($i=0; $i<$Repeticiones; $i++) {  
				system("$Path/$nombre $size $hilo  >> $file");          # Ejecuta el programa y redirige la salida al archivo
				# printf("$Path/$Nombre_Ejecutable $size $hilo \n");  
			}
			close($file);  # Cierra el archivo de salida
		$p=$p+1;  # Incrementa el contador
		}
	}
}

