#!/bin/bash
"Los archivos del directorio $1 que han sido accedidos en los últimos numero $2 días son:"
find $1 -type f -atime -$2
