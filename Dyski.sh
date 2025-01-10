#!/bin/bash

# Sprawdzenie dostępnych dysków i partycji
available_disks=$(lsblk -o NAME,SIZE,TYPE,MOUNTPOINT | grep 'disk')

# Sprawdzenie miejsca na wybranej partycji 
partition="/dev/sda2"
partition_info=$(df -h | grep "$partition")

# Pobranie bieżącej daty i godziny w formacie YYYYMMdd-HHmmss
timestamp=$(date "+%Y%m%d-%H%M%S")

# Nazwa pliku wynikowego
filename="Report_${timestamp}.txt"

# Zapisanie wyników do pliku
{
    echo "Dostępne dyski i partycje:"
    echo "$available_disks"
    echo
    echo "Miejsce na wybranej partycji ($partition):"
    if [ -z "$partition_info" ]; then
        echo "Brak informacji o partycji $partition. Sprawdź, czy partycja istnieje i jest zamontowana."
    else
        echo "$partition_info"
    fi
} > "$filename"

# Informacja o zapisaniu pliku
echo "Plik o nazwie $filename został zapisany w $(pwd)."
