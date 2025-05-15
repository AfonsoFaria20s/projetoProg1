@echo off
gcc main.c tecnico/tecnico.c admin/admin.c  incidentes/incidentes.c utils/utils.c -o main.exe
.\main.exe
