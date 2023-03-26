//
// Created by hayann on 19/03/23.
//

#ifndef CALCULADORA_IP_VIEWS_H
#define CALCULADORA_IP_VIEWS_H

#include <iostream>
#include "ip_com_classe.h"
#include "ip_sem_classe.h"

class views {
private:
    std::string get_mensagem(std::string mensagem);
public:
    void menu_inicial();

    void calcular_ip_com_classe();

    void calcular_ip_sem_classe();
};

#endif //CALCULADORA_IP_VIEWS_H
