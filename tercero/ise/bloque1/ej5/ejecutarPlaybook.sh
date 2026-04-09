#!/bin/bash
# =========================================================
# Script de Despliegue de Servidores Web - Práctica ISE
# Autor: Juan
# =========================================================

echo "Iniciando el despliegue con Ansible..."
echo "----------------------------------------"

ansible-playbook -i inventory.ini configurar_servidores.yml >> output.txt

echo "----------------------------------------"
echo "Despliegue finalizado."
