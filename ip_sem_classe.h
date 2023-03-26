//
// Created by hayann on 23/03/23.
//

#ifndef CALCULADORA_IPV4_IP_SEM_CLASSE_H
#define CALCULADORA_IPV4_IP_SEM_CLASSE_H

#include <bits/stdc++.h>
#include "ip_com_classe.h"


class ip_sem_classe {
private:
    bool ip_valid = true;

    bool mascara_valid = true;

    int todos_bits_mascara = 0;

    int posicao_octeto_quebrado_mascara = 0;

    int quantidade_bits_octeto_quebrado_mascara = 0;

    int get_complemento_mascara();

    std::vector<int> get_vector_octetos(int octeto_quebrado, int valores);
public:
    std::vector<int> octetos_ip;

    std::vector<int> mascara_octetos;

    void build_ip(const std::string& ip);

    void build_mascara(std::string mascara);

    int converte_mascara_stoi(std::string mascara);

    int converte_bin_to_dec(int octeto);

    std::string get_mascara();

    std::string get_endereco(std::vector<int> octetos);

    bool ip_is_valid();

    bool mascara_is_valid();

    int get_quantidade_hosts();

    std::string get_broadcast();

    std::string get_rede();

    std::string get_primeiro_endereco_utilizavel();

    std::string get_ultimo_endereco_utilizavel();

    int valida_octeto_quebrado(int octeto);

    std::string get_mascara_cidr();

    std::string converte_int_to_str(int number);
};


#endif //CALCULADORA_IPV4_IP_SEM_CLASSE_H
