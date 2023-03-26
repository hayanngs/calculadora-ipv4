//
// Created by hayann on 23/03/23.
//

#include "ip_sem_classe.h"

void ip_sem_classe::build_ip(const std::string &ip) {
    try {
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
    } catch (std::exception e) {
        ip_valid = false;
    }
}

void ip_sem_classe::build_mascara(std::string mascara) {
    try {
        ip_com_classe calc(get_endereco(octetos_ip));
        if (mascara.size() > 3) { // MONTA MASCARA NOTACAO DECIMAL
            std::vector<std::string> mascara_octetos_str = calc.join_to_octeto(mascara);
            if (mascara_octetos_str.size() < 4 || mascara_octetos_str.size() > 4) {
                mascara_valid = false;
                return;
            }
            int i;
            for (i = 0; i < mascara_octetos_str.size(); i++) {
                int octeto = std::stoi(mascara_octetos_str[i]);
                if (octeto < 0 || octeto > 255) {
                    mascara_valid = false;
                    return;
                }
                mascara_octetos.push_back(octeto);
                if (octeto > 0 && octeto < 255) {
                    posicao_octeto_quebrado_mascara = i;
                    quantidade_bits_octeto_quebrado_mascara = valida_octeto_quebrado(octeto);
                    if (quantidade_bits_octeto_quebrado_mascara == -1) {
                        mascara_valid = false;
                        return;
                    }
                    todos_bits_mascara = quantidade_bits_octeto_quebrado_mascara + (i * 8);
                    i++;
                    break;
                }
            }
            for (; i < mascara_octetos_str.size(); i++) {
                int octeto = std::stoi(mascara_octetos_str[i]);
                if (octeto > 0) {
                    mascara_valid = false;
                    return;
                }
                mascara_octetos.push_back(octeto);
            }
        } else { // MONTA MASCARA NOTACAO CIDR
            int mascara_dec = converte_mascara_stoi(mascara);
            if (mascara_dec < 1 || mascara_dec > 32) {
                mascara_valid = false;
                return;
            }

            posicao_octeto_quebrado_mascara = mascara_dec / 8;
            quantidade_bits_octeto_quebrado_mascara = mascara_dec % 8;
            todos_bits_mascara = mascara_dec;

            // MONTA A MASCARA
            int octeto_quebrado = converte_bin_to_dec(quantidade_bits_octeto_quebrado_mascara);
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
    } catch (std::exception e) {
        mascara_valid = false;
    }
}

std::string ip_sem_classe::get_mascara() {
    return get_endereco(mascara_octetos);
}

std::string ip_sem_classe::get_mascara_cidr() {
    return "/" + converte_int_to_str(todos_bits_mascara);
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

    std::vector<int> octetos_broadcast = get_vector_octetos(octeto_quebrado, 255);

    return get_endereco(octetos_broadcast);
}

std::string ip_sem_classe::get_rede() {
    int octeto_quebrado = mascara_octetos[posicao_octeto_quebrado_mascara] & octetos_ip[posicao_octeto_quebrado_mascara];

    std::vector<int> octetos_rede = get_vector_octetos(octeto_quebrado, 0);

    return get_endereco(octetos_rede);
}

std::string ip_sem_classe::get_primeiro_endereco_utilizavel() {
    int octeto_quebrado = mascara_octetos[posicao_octeto_quebrado_mascara] & octetos_ip[posicao_octeto_quebrado_mascara];

    std::vector<int> octetos_utilizavel = get_vector_octetos(octeto_quebrado, 0);

    octetos_utilizavel[3]++;

    return get_endereco(octetos_utilizavel);
}

std::string ip_sem_classe::get_ultimo_endereco_utilizavel() {
    int complemento = get_complemento_mascara();

    int octeto_quebrado = complemento | octetos_ip[posicao_octeto_quebrado_mascara];

    std::vector<int> octetos_ultimo_endereco_utilizavel = get_vector_octetos(octeto_quebrado, 255);

    octetos_ultimo_endereco_utilizavel[3]--;

    return get_endereco(octetos_ultimo_endereco_utilizavel);
}

int ip_sem_classe::get_complemento_mascara() {
    int complemento = 1, soma = 0;
    int diferenca = 8 - quantidade_bits_octeto_quebrado_mascara;
    for (int i = 0; i < diferenca; ++i) {
        soma += complemento;
        complemento *= 2;
    }
    return soma;
}

std::vector<int> ip_sem_classe::get_vector_octetos(int octeto_quebrado, int valores) {
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

    return octetos_utilizavel;
}

int ip_sem_classe::valida_octeto_quebrado(int octeto) {
    int valores_validos[8] = {0, 128, 192, 224, 240, 248, 252, 254};
    for (int i = 0; i < 8; i++) {
        if (valores_validos[i] == octeto) {
            return i;
        }
    }
    return -1;
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

std::string ip_sem_classe::converte_int_to_str(int number) {
    std::string mascara_cidr;
    while (number) {
        int digit = number % 10;
        number /= 10;
        mascara_cidr = char (digit + 48) + mascara_cidr;
    }
    return mascara_cidr;
}
