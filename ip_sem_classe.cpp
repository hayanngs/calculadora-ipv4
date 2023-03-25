//
// Created by hayann on 23/03/23.
//

#include "ip_sem_classe.h"

void ip_sem_classe::build_ip(const std::string &ip) {
    ip_com_classe calc(ip);

    // SEPARA O IP EM OCTETOS
    std::vector<std::string> octetos_str = calc.join_to_octeto(ip);
    if (octetos_str.size() < 4 || octetos_str.size() > 4)
        ip_valid = false;

    // CONVERTE CADA OCTETO EM INTEIRO
    for (int i = 0; i < octetos_str.size(); i++) {
        octetos_ip.push_back(std::stoi(octetos_str[i]));
        if (octetos_ip[i] < 0 || octetos_ip[i] > 255)
            ip_valid = false;
    }
}

void ip_sem_classe::build_mascara(std::string mascara) {
    int mascara_dec = converte_mascara_stoi(mascara);
    if (mascara_dec < 1 || mascara_dec > 32)
        mascara_valid = false;

    posicao_octeto_quebrado_mascara = mascara_dec / 8;
    cont_bits_octeto_quebrado_mascara = mascara_dec % 8;
    todos_bits_mascara = mascara_dec;

    // MONTA A MASCARA
    int octeto_quebrado = converte_bin_to_dec(cont_bits_octeto_quebrado_mascara);
    int i;
    for (i = 0; i < posicao_octeto_quebrado_mascara; i++) {
        mascara_octetos.push_back(255);
    }
    i++;
    mascara_octetos.push_back(octeto_quebrado);
    for (; i < 4; i++) {
        mascara_octetos.push_back(0);
    }
}

int ip_sem_classe::converte_mascara_stoi(std::string mascara) {
    int mascara_dec = 0, pot = 1;

    // CONVERTER A MASCARA DA NOTACAO /n DE STRING PARA INTEIRO
    for (int i = mascara.length() - 1; i >= 0; i--) {
        int caracter_dec = mascara[i] - 48;
        if (caracter_dec >= 0 && caracter_dec <= 9) {
            mascara_dec += caracter_dec * pot;
            pot *= 10;
        }
    }

    return mascara_dec;
}

int ip_sem_classe::converte_bin_to_dec(int octeto) {
    int bit = 128;
    int octeto_dec = 0;
    for (int i = 0; i < octeto; i++) {
        octeto_dec += bit;
        bit /= 2;
    }
    return octeto_dec;
}

std::string ip_sem_classe::get_mascara() {
    return get_endereco(mascara_octetos);
}

std::string ip_sem_classe::get_endereco(std::vector<int> octetos_param) {
    return std::to_string(octetos_param[0]) +
           "." +
           std::to_string(octetos_param[1]) +
           "." +
           std::to_string(octetos_param[2]) +
           "." +
           std::to_string(octetos_param[3]);
}

int ip_sem_classe::get_quantidade_hosts() {
    int total_hosts = 1;
    int bits = 32 - todos_bits_mascara;
    for (int i = 0; i < bits; ++i) {
        total_hosts *= 2;
    }
    return total_hosts - 2;
}

bool ip_sem_classe::ip_is_valid() {
    return ip_valid;
}

bool ip_sem_classe::mascara_is_valid() {
    return mascara_valid;
}

std::string ip_sem_classe::get_broadcast() {
    int complemento = get_complemento_mascara();

    int octeto_quebrado = complemento | octetos_ip[posicao_octeto_quebrado_mascara];

    std::vector<int> octetos_broadcast = get_vector_octetos(octeto_quebrado, 255, 255);

    return get_endereco(octetos_broadcast);
}

std::string ip_sem_classe::get_rede() {
    int octeto_quebrado = mascara_octetos[posicao_octeto_quebrado_mascara] & octetos_ip[posicao_octeto_quebrado_mascara];

    std::vector<int> octetos_rede = get_vector_octetos(octeto_quebrado, 0, 0);

    return get_endereco(octetos_rede);
}

std::string ip_sem_classe::get_primeiro_endereco_utilizavel() {
    int octeto_quebrado = mascara_octetos[posicao_octeto_quebrado_mascara] & octetos_ip[posicao_octeto_quebrado_mascara];

    std::vector<int> octetos_utilizavel = get_vector_octetos(octeto_quebrado, 0, 1);

    return get_endereco(octetos_utilizavel);
}

std::string ip_sem_classe::get_ultimo_endereco_utilizavel() {
    int complemento = get_complemento_mascara();

    int octeto_quebrado = complemento | octetos_ip[posicao_octeto_quebrado_mascara];

    std::vector<int> octetos_ultimo_endereco_utilizavel = get_vector_octetos(octeto_quebrado, 255, 254);

    return get_endereco(octetos_ultimo_endereco_utilizavel);
}

int ip_sem_classe::get_complemento_mascara() {
    int complemento = 1, soma = 0;
    int diferenca = 8 - cont_bits_octeto_quebrado_mascara;
    for (int i = 0; i < diferenca; ++i) {
        soma += complemento;
        complemento *= 2;
    }
    return soma;
}

std::vector<int> ip_sem_classe::get_vector_octetos(int octeto_quebrado, int valores, int ultimo_valor) {
    std::vector<int> octetos_utilizavel;

    int i;
    for (i = 0; i < posicao_octeto_quebrado_mascara; i++) {
        octetos_utilizavel.push_back(octetos_ip[i]);
    }
    i++;
    octetos_utilizavel.push_back(octeto_quebrado);
    for (; i < 4; i++) {
        octetos_utilizavel.push_back(valores);
    }
    octetos_utilizavel[3] = ultimo_valor;

    return octetos_utilizavel;
}
