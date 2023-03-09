all: main.o balanceada.o files.o blocos.o blocosSelecao.o intercalacao.o sort.o quicksort.o gerador.o
	g++ main.o balanceada.o files.o blocos.o blocosSelecao.o intercalacao.o sort.o quicksort.o gerador.o -o ordena

main.o: main.cpp
	g++ -c main.cpp

# BALANCEADA
files.o: ./um/files.cpp
	g++ -c ./um/files.cpp

balanceada.o: balanceada.cpp
	g++ -c balanceada.cpp

## UM
blocos.o: ./um/blocos.cpp
	g++ -c ./um/blocos.cpp

intercalacao.o: ./um/intercalacao.cpp
	g++ -c ./um/intercalacao.cpp

sort.o: ./um/sort.cpp
	g++ -c ./um/sort.cpp

## DOIS
blocosSelecao.o: ./dois/blocosSelecao.cpp
	g++ -c ./dois/blocosSelecao.cpp

## TRES
quicksort.o: ./tres/quicksort.cpp
	g++ -c ./tres/quicksort.cpp

gerador.o: ./gerador/gerador.cpp
	g++ -c ./gerador/gerador.cpp

# DELETAR/LIMPAR
clean:
	del -f *.o ordena.exe

remove:
	rm -f *.o ordena.exe

# Em windows, usar comando make clean
# Em linux, comando make remove