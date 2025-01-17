@echo off
echo Compilando o programa...

:: Compilando os arquivos .c para .o
gcc -c mainTeste.c -o mainTeste.o
gcc -c EstruturaVetores.c -o EstruturaVetores.o

:: Criando o executável
gcc mainTeste.o EstruturaVetores.o -o programa.exe

:: Verifica se o executável foi criado com sucesso
if exist programa.exe (
    echo Compilado com sucesso!
    echo Executando o programa...
    programa.exe
) else (
    echo Falha na compilação.
)

pause
