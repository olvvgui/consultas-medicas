#ifndef PACIENTE_H
#define PACIENTE_H

#include "structs.h"
#include "utilitarios.h"

// criação de conta
void cadastrarpaciente(cadastro_save cad, usuario *usr);

// login na conta
void login(usuario *usr);

// verifica se o email tem um domínio valido
int verificaEmail(char *email);

// verifica se o cpf já foi cadastrado 
int verificaCPF(char *cpf); 

#endif