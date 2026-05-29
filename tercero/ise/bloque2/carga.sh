#!/bin/bash

# 1. Obtenemos la fecha y hora con el formato solicitado
FECHA=$(date "+%d/%m/%Y %H:%M:%S")

# 2. Extraemos la carga de 1 minuto del comando uptime limpiando el texto
CARGA=$(uptime | awk -F'load average: ' '{print $2}' | awk '{print $1}' | sed 's/,$//')

# 3. Enviamos el mensaje al log del sistema con la etiqueta "ISE"
logger -t ISE "JRA: $FECHA - $CARGA %"
