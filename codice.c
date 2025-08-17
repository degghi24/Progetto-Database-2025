#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dependencies/include/libpq-fe.h"

#define PG_HOST "localhost"
#define PG_USER "postgres"
#define PG_DB "local_server"
#define PG_PASS "" //nessuna password
#define PG_PORT 5432



//Funzione gestione errori
void checkCommand(PGresult *res, PGconn *conn)
{
	if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
    	printf("Comando fallito: %s\n", PQerrorMessage(conn));
    	PQclear(res);
    	PQfinish(conn);
    	exit(1);
	}
}

void checkResults(PGresult *res, PGconn *conn)
{
	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
    	printf("Risultati inconsistenti: %s\n", PQerrorMessage(conn));
    	PQclear(res);
    	PQfinish(conn);
    	exit(1);
	}
}

//Funzione per stampare output query
void printResult(int rows, int cols, PGresult *res)
{
	for (int i = 0; i < rows; i++)
	{
    	for (int j = 0; j < cols; j++)
    	{
        	printf("%s\t\t", PQgetvalue(res, i, j));
    	}
    	printf("\n");
	}
}

int main(int argc, char **argv)
{
	char conninfo[250];
	sprintf(conninfo, "user=%s password=%s dbname=%s host=%s port=%d",
        	PG_USER, PG_PASS, PG_DB, PG_HOST, PG_PORT);

	PGconn *conn = PQconnectdb(conninfo);

    // Verifico lo stato di connessione
	if (PQstatus(conn) != CONNECTION_OK)
	{
    	printf("Errore di connessione: %s\n", PQerrorMessage(conn));
    	PQfinish(conn);
    	exit(1);
	}
	printf("Connessione avvenuta correttamente", PG_DB);

}