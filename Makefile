prepare: 
	mkdir -p build
	cp src/CMakeLists.txt build/
	cd build && cmake .$

c: 
	cd build && make$
	
clean:  
	rm -rf build/ bin/$

help:
	@echo ' '$
	@echo '---- COMANDOS -----'$
	@echo 'prepare: Cria os arquivos necessários para compilar'$
	@echo 'clean:	 Limpa arquivos de backup'$
	@echo 'c:	 Compila arquivos e executaveis'$
	@echo 'help:	 Mostar ajuda.'$
	@echo '-------------------'$