#!/bin/bash

printf "Seleccione opcion: \n 1) Sumar números enteros \n 2) Restar números enteros \n 3) Multiplicar números enteros \n 4) Salir \n"

read REPLY

while (($REPLY != 4))
do

	case "$REPLY" in 
		1) read n1; read n2; echo "$n1 + $n2 = $((n1+n2))" ;;
		2) read n1; read n2; echo "$n1 - $n2 = $((n1-n2))" ;;
		3) read n1; read n2; echo "$n1 * $n2 = $((n1*n2))" ;;
		4) exit ;;
		*) echo "opcion no contemplada" ;;
	esac
	
	printf "Seleccione opcion: \n 1) Sumar números enteros \n 2) Restar números enteros \n 3) Multiplicar números enteros \n 4) Salir \n"

	read REPLY
done
