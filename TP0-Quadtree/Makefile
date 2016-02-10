######################################################################
# O conteúdo é livre para ser utilizados e editados, desde que citado 
# o autor original e que seja utilizado para fins não comerciais.
#
# Desenvolvido por: Bruno Maciel Peres - brunomperes@dcc.ufmg.br
# www.homepages.dcc.ufmg.br/~brunomperes/
######################################################################

# Lista dos objetos (arquivos .c, troca-se a extensão para .o) necessários para o programa final
OBJS = main.o quadtree.o

# Nome do executável
MAIN = tp0

# Argumentos para execução do programa
ARGS = -i input.txt -o output.txt

# Opções para execução do Valgrind
VALOPS = --leak-check=full --show-reachable=yes

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
	
valgrind: $(MAIN)
	valgrind $(VALOPS) ./$(MAIN) $(ARGS)

gprof: $(MAIN)
	./$(MAIN) $(ARGS)
	gprof -b -p $(MAIN)

