#include "include/client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, "Logger iniciado correctamente.");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	log_info(logger, "Iniciando configuración...");
	config = iniciar_config();

	if(config == NULL)
		terminar_programa(conexion, logger, config);

	log_info(logger, "Configuración realizada correctamente.");

	char * clave = config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "VALOR");


	log_info(logger, "La clave es: %s", clave);
	log_info(logger, "La ip es: %s", ip);
	log_info(logger, "La puerto es: %s", puerto);
	log_info(logger, "La valor es: %s", valor);

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */

	// leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	log_info(logger, "Creando conexión...");
	conexion = crear_conexion(ip, puerto);
	log_info(logger, "Conexión creada. Socket: %i", conexion);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	return 0;
	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("tp0.log", "tp0", 1, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("tp0.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	log_info(logger, "Esperando ingreso de datos por consola...");
	char* leido;
	leido = "void";
	bool ingresoActivado = 1;

	while(ingresoActivado){
		leido = readline("> ");
		log_info(logger, "Linea ingresada: %s", leido);

		if (strcmp(leido, "") == 0)
			ingresoActivado = 0; // Preguntar por ejemplo en la web. También, hay que liberar cuando es ""?

		free(leido);
	}
	// ¡No te olvides de liberar las lineas antes de regresar! // TODO Preguntar que onda esto.
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido = "1";
	t_paquete* paquete;
	paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
	agregar_a_paquete(paquete, leido, sizeof(int));
	enviar_paquete(paquete, conexion);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_info(logger, "Terminando programa.....");
	config_destroy(config);
	log_info(logger, "Memoria liberada correctamente");
	log_destroy(logger);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
