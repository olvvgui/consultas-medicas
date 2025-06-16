#ifndef CONSULTAS_H
#define CONSULTAS_H

#include "utilitarios.h"
#include "structs.h"

// funcao para selecionar o medico
void selecionar(char selecao[50], char med1[50], char med2[50], char nome_medico[50]);

// implementação dos lembretes
void lembrete(int *dia, int hora, char *medico, char *email);

// Funcao para buscar consultas já agendadas.
void buscar_consulta(const char *nome, const char *cpf);

// Funcao ara cancelar consultas.
void cancelar_consulta(const char *cpf);

// Funcao para reagendar consulta.
void reagendar_consulta(const char *cpf);

// Funcao para ver todas as consultas agendadas de determinado medico.
void ver_consultas_medico();

// Funcao para ver todas as consultas agendadas em determinado dia.
void ver_consultas_no_dia();



#endif
