#!/bin/bash

_menu(){
    printf "\n\n----------------------------------------------------------------------------------------\n"
    printf "Elija una de las siguientes opciones:\n"
    printf "\t1) Ordenar los parámetros del programa de menor a mayor.\n"
    printf "\t2) Imprimir los procesos que se estén ejecutando y comiencen por determinada letra.\n"
    printf "\t3) Copiar los 5 primeros archivos de un directorio en otro directorio.\n"
    printf "\t4) Salir\n"
}


## numero de ficheros no valido
if [[ $# < 2 || $# > 4 ]]; then
	echo "ERROR. numero incorrecto de ficheros"
	exit 1
fi

_menu
read -p "elige opcion: " OPCION
printf "\n"
while [[ $OPCION != 4 ]]
do

	case $OPCION in
	
	1)
        	num_validos=0
        	
		for param in "$@";
        	do
                if [[ $param =~ ^[\+-]?[0-9]+(\[,][0-9]+)?$ ]]; then
                    echo $param >> $num_validos
                fi
        	done
		
        	num_sorted=$(sort -n $num_validos)

        	printf "Números válidos ordenados de menor a mayor:\n"
        	echo $num_sorted
		;;
		
	2)
		read -p "introducir letra:  " LETRA
		
		if [[ ! $LETRA =~ ^[a-zA-Z]$ ]]; then
			printf "error"
		else
			ps -e --format comm | egrep "^$LETRA" --color
		
		fi
		;;
	3)
		read -p "Introducir un directorio: " DIR_1
        	read -p "Introducir un segundo directorio: " DIR_2
        	
        	if [[ -r $DIR_1 ]]; then
        		echo "ok"
        	else
        		echo "no ok"
        	fi
        	
        	
		;;
esac

_menu
read -p "elige opcion: " OPCION
printf "\n"
done
exit 0
