# Lista dos objetos (arquivos .c, troca-se a extensão para .o) necessários para o programa final
OBJS = main.o quadtree.o

# Nome do executável
MAIN = tp0

# Argumentos para execução do programa
ARGS = -i input.txt -o output.txt

# Especifica o compilador
CC = gcc

# Especifica as opções do compilador, habilita aviso sobre erros
CFLAGS = -Wall -pg -g3

# Comando terminal para limpar sem confirmação
RM = rm -f

# Compilação do programa e passos das ligações de dependências
$(MAIN): $(OBJS)
	@echo ""
	@echo " --- COMPILANDO PROGRAMA ---"
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $(MAIN)
	@echo ""

%.o: %.c %.h
	@echo ""
	@echo " --- COMPILANDO OBJETO \"$@\""
	@$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o
	$(RM) gmon.out

run: $(MAIN)
	./$(MAIN) $(ARGS)
