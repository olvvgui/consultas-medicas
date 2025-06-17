#ifndef MAIN_H
#define MAIN_H

#include "lib/consultas.h"
#include "lib/menu.h"
#include "lib/paciente.h"
#include "lib/structs.h"
#include "lib/utilitarios.h"

void cadastrar(usuario *usr);

void agendar(usuario *usr);

void buscar(usuario *usr);

void cancelar(usuario *usr);

void reagendar(usuario *usr);

void medOudia();

#endif