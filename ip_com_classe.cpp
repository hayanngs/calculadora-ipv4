//
// Created by hayann on 19/03/23.
//

#include "ip_com_classe.h"

ip_com_classe::ip_com_classe(std::string ip) {
    this->ip = ip;
}

bool ip_com_classe::is_valid() {
    try {
        std::vector<std::string> octetos = join_to_octeto(ip);
        if (octetos.size() > 4) {
            return false;
        }
        for (const std::string& octeto: octetos) {
            int octetoFromStr = stoi(octeto, nullptr, 10);
            if (octetoFromStr > 255) {
                return false;
            }
        }
        return true;
    } catch (std::exception e) {
        return false;
    }
}

std::vector<std::string> ip_com_classe::join_to_octeto(std::string ip) {
    std::vector<std::string> octetos;
    int ultima_pos = 0, cont = 0;
    for (int i = 0; i < ip.length(); i++) {
        if (ip[i] == '.') {
            octetos.push_back(ip.substr(ultima_pos, cont));
            ultima_pos = i + 1;
            cont = 0;
        } else {
            cont++;
        }
    }
    octetos.push_back(ip.substr(ultima_pos, cont));
    return octetos;
}

char ip_com_classe::get_classe() {
    int first_octeto = stoi(get_first_octeto(), nullptr, 10);
    if (first_octeto >= 0 && first_octeto < 128)
        return 'A';
    else if (first_octeto >= 128 && first_octeto < 192)
        return 'B';
    else if (first_octeto >= 192 && first_octeto < 224)
        return 'C';
    else if (first_octeto >= 224 && first_octeto < 239)
        return 'D';
    else if (first_octeto >= 239 && first_octeto < 256)
        return 'E';
    else
        return '-';
}

std::string ip_com_classe::get_first_octeto() {
    std::string first_octeto;
    for (int i = 0; i < ip.length(); i++) {
        if (ip[i] == '.') {
            return first_octeto;
        } else {
            first_octeto += ip[i];
        }
    }
    return "";
}

std::string ip_com_classe::get_mascara_decimal() {
    char classe = get_classe();
    switch (classe) {
        case 'A':
            return "255.0.0.0";
        case 'B':
            return "255.255.0.0";
        case 'C':
            return "255.255.255.0";
        default:
            return "0.0.0.0";
    }
}

std::string ip_com_classe::get_mascara_cidr() {
    char classe = get_classe();
    switch (classe) {
        case 'A':
            return "/8";
        case 'B':
            return "/16";
        case 'C':
            return "/24";
        default:
            return "-";
    }
}

int ip_com_classe::get_quantidade_hosts() {
    char classe = get_classe();
    switch (classe) {
        case 'A':
            return 16777216 - 2;
        case 'B':
            return 65536 - 2;
        case 'C':
            return 256 - 2;
        default:
            return 268435456 - 2;
    }
    return 0;
}

std::string ip_com_classe::get_primeiro_endereco() {
    char classe = get_classe();
    std::vector<std::string> octetos = join_to_octeto(ip);
    std::string primeiro_endereco = build_endereco(classe, octetos, true);
    return primeiro_endereco;
}

std::string ip_com_classe::get_ultimo_endereco() {
    char classe = get_classe();
    std::vector<std::string> octetos = join_to_octeto(ip);
    std::string ultimo_endereco = build_endereco(classe, octetos, false);
    return ultimo_endereco;
}

std::string ip_com_classe::get_primeiro_endereco_utilizavel() {
    char classe = get_classe();
    std::vector<std::string> octetos = join_to_octeto(ip);
    std::string primeiro_endereco = build_endereco_util(classe, octetos, true);
    return primeiro_endereco;
}

std::string ip_com_classe::get_ultimo_endereco_utilizavel() {
    char classe = get_classe();
    std::vector<std::string> octetos = join_to_octeto(ip);
    std::string primeiro_endereco = build_endereco_util(classe, octetos, false);
    return primeiro_endereco;
}

std::string ip_com_classe::build_endereco_util(char classe, std::vector<std::string> octetos, bool primeiro_ou_ultimo) {
    std::string complemento_a = primeiro_ou_ultimo ? ".0.0.1" : ".255.255.254";
    std::string complemento_b = primeiro_ou_ultimo ? ".0.1" : ".255.254";
    std::string complemento_c = primeiro_ou_ultimo ? ".1" : ".254";
    switch (classe) {
        case 'A':
            return octetos.front() + complemento_a;
        case 'B': {
            std::string endereco_classe_b = octetos[0] + "." + octetos[1] + complemento_b;
            return endereco_classe_b;
        }
        case 'C': {
            std::string endereco_classe_c = octetos[0] + "." + octetos[1] + "." + octetos[2] + complemento_c;
            return endereco_classe_c;
        }
        default:
            return primeiro_ou_ultimo ? "0.0.0.0" : "255.255.255.255";;
    }
}


std::string ip_com_classe::build_endereco(char classe, std::vector<std::string> octetos, bool primeiro_ou_ultimo) {
    std::string complemento_a = primeiro_ou_ultimo ? ".0.0.0" : ".255.255.255";
    std::string complemento_b = primeiro_ou_ultimo ? ".0.0" : ".255.255";
    std::string complemento_c = primeiro_ou_ultimo ? ".0" : ".255";
    switch (classe) {
        case 'A':
            return octetos.front() + complemento_a;
        case 'B': {
            std::string endereco_classe_b = octetos[0] + "." + octetos[1] + complemento_b;
            return endereco_classe_b;
        }
        case 'C': {
            std::string endereco_classe_c = octetos[0] + "." + octetos[1] + "." + octetos[2] + complemento_c;
            return endereco_classe_c;
        }
        default:
            return primeiro_ou_ultimo ? "0.0.0.0" : "255.255.255.255";;
    }
}
