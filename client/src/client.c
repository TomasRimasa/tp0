#include "client.h"
#include <readline/readline.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	config = iniciar_config();

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "CLAVE");

	log_info(logger, "VALOR leido de config: %s", valor);

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	conexion = crear_conexion(ip, puerto);

	enviar_mensaje(valor, conexion);

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void) {
	t_log* nuevo_logger = log_create("cliente.log", "CLIENTE_LOGGER", 1 , LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void) {
	t_config* nuevo_config = config_create("cliente.config");

	if(nuevo_config == NULL) {
		perror("Error al intentar cargar el config");
		exit(EXIT_FAILURE);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger) {
	char* leido;

	leido = readline("> ");

	while (strcmp(leido, "") != 0){
		log_info(logger, "mensaje Leido: %s", leido);
		leido = readline("> ");
	}

	free(leido);

}

void paquete(int conexion) {
	char* leido;
	t_paquete* paquete = crear_paquete();

	leido = readline("> ");

	while (strcmp(leido, "") != 0){
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		free(leido);
		leido = readline("> ");
	}

	free(leido);

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config) {
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
	printf ("El programa Termino");
}
