//
// Created by hayann on 19/03/23.
//

#ifndef CALCULADORA_IP_IP_COM_CLASSE_H
#define CALCULADORA_IP_IP_COM_CLASSE_H


#include <string>
#include <bits/stdc++.h>

class ip_com_classe {
private:
    std::string ip;

    std::string get_first_octeto();

    std::string build_endereco(char classe, std::vector<std::string> octetos, bool primeiro_ou_ultimo);

    std::string build_endereco_util(char classe, std::vector<std::string> octetos, bool primeiro_ou_ultimo);
public:
    ip_com_classe(std::string ip);

    bool is_valid();

    char get_classe();

    std::vector<std::string> join_to_octeto(std::string ip);

    std::string get_mascara_decimal();

    std::string get_mascara_cidr();

    int get_quantidade_hosts();

    std::string get_primeiro_endereco();

    std::string get_ultimo_endereco();

    std::string get_primeiro_endereco_utilizavel();

    std::string get_ultimo_endereco_utilizavel();
};


#endif //CALCULADORA_IP_IP_COM_CLASSE_H
