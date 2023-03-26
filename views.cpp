//
// Created by hayann on 19/03/23.
//

#include <csignal>
#include "views.h"

void views::menu_inicial() {
    char opcao_inicial = 1;
    while (opcao_inicial != '0') {
        std::cout << "Calculadora IPv4" << std::endl;
        std::cout << "Redes de Computadores II" << std::endl;
        std::cout << "Aluno: Hayann Gonçalves Silva\n" << std::endl;

        std::cout << "Opções:" << std::endl;
        std::cout << "1 - Calcular IP com classe" << std::endl;
        std::cout << "2 - Calcular IP sem classe" << std::endl;
        std::cout << "0 - Sair" << std::endl;
        std::cout << "> Digite o número da opção desejada: ";

        std::cin >> opcao_inicial;

        system("clear");

        if (opcao_inicial == '1') {
            calcular_ip_com_classe();
        } else if (opcao_inicial == '2') {
            calcular_ip_sem_classe();
        } else if (opcao_inicial == '0') {
            std:std::cout << "> Programa finalizado, Até a próxima!" << std::endl;
            sleep(3);
            exit(0);
        } else {
            std::cout << "\n> Opção inválida!" << std::endl;
            sleep(2);
            system("clear");
        }
    }
}

void views::calcular_ip_com_classe() {
    std::string ip;
    std::cout << "Calculadora IPv4" << std::endl;
    std::cout << "Calcular IP com classe" << std::endl;
    while (ip != "0") {
        std::cout << "> Digite um IP válido (w.x.y.z) ou '0' pra voltar: ";
        std::cin >> ip;
        ip_com_classe calc(ip);

        if (ip == "0")
            break;
        if (calc.is_valid()) {
            char classe = calc.get_classe();
            std::string mascara_decimal = calc.get_mascara_decimal();
            std::string mascara_CIDR = calc.get_mascara_cidr();
            int quantidade_hosts = calc.get_quantidade_hosts();
            std::string endereco_rede = calc.get_primeiro_endereco();
            std::string endereco_broadcast = calc.get_ultimo_endereco();
            std::string primeiro_endereco_utilizavel = calc.get_primeiro_endereco_utilizavel();
            std::string ultimo_endereco_utilizavel = calc.get_ultimo_endereco_utilizavel();

            std::cout << get_mensagem("Endereco IP") << ip << std::endl;
            std::cout << get_mensagem("Classe") << classe << std::endl;
            if (classe == 'D' || classe == 'E') {
                std::cout << std::endl << std::endl;
                continue;
            }
            std::cout << get_mensagem("Mascara CIDR") << mascara_CIDR << std::endl;
            std::cout << get_mensagem("Mascara decimal") << mascara_decimal << std::endl;
            std::cout << get_mensagem("Quantidade de hosts") << quantidade_hosts << std::endl;
            std::cout << get_mensagem("Endereco da rede") << endereco_rede << std::endl;
            std::cout << get_mensagem("Endereco broadcast") << endereco_broadcast << std::endl;
            std::cout << get_mensagem("Primeiro endereco util") << primeiro_endereco_utilizavel << std::endl;
            std::cout << get_mensagem("Ultimo endereco util") << ultimo_endereco_utilizavel << std::endl;
            std::cout << std::endl << std::endl;
        } else {
            std::cout << "> IP digitado não é válido." << std::endl;
            std::cout << std::endl << std::endl;
        }
    }
    system("clear");
}

void views::calcular_ip_sem_classe() {
    std::string ip, mascara;
    std::cout << "Calculadora IPv4" << std::endl;
    std::cout << "Calcular IP sem classe" << std::endl;
    while (ip != "0") {
        std::cout << "> Digite um IP válido (n.n.n.n) ou '0' pra voltar: ";
        std::cin >> ip;

        if (ip == "0")
            break;

        ip_sem_classe calc;

        calc.build_ip(ip);
        if (!calc.ip_is_valid()) {
            std::cout << "> IP digitado não é válido." << std::endl << std::endl;
            continue;
        }

        std::cout << "> Digite uma máscara válida (/n ou n.n.n.n): ";
        std::cin >> mascara;

        calc.build_mascara(mascara);
        if (!calc.mascara_is_valid()) {
            std::cout << "> Máscara digitada não é válida." << std::endl << std::endl;
            continue;
        }

        std::string mascara_decimal = calc.get_mascara();
        std::string mascara_CIDR = calc.get_mascara_cidr();
        int quantidade_hosts = calc.get_quantidade_hosts();
        std::string endereco_rede = calc.get_rede();
        std::string endereco_broadcast = calc.get_broadcast();
        std::string primeiro_endereco_utilizavel = calc.get_primeiro_endereco_utilizavel();
        std::string ultimo_endereco_utilizavel = calc.get_ultimo_endereco_utilizavel();

        std::cout << get_mensagem("Endereco IP") << ip << std::endl;
        std::cout << get_mensagem("Mascara CIDR") << mascara_CIDR << std::endl;
        std::cout << get_mensagem("Mascara decimal") << mascara_decimal << std::endl;
        std::cout << get_mensagem("Quantidade de hosts") << quantidade_hosts << std::endl;
        std::cout << get_mensagem("Endereco da rede") << endereco_rede << std::endl;
        std::cout << get_mensagem("Endereco broadcast") << endereco_broadcast << std::endl;
        std::cout << get_mensagem("Primeiro endereco util") << primeiro_endereco_utilizavel << std::endl;
        std::cout << get_mensagem("Ultimo endereco util") << ultimo_endereco_utilizavel << std::endl;
        std::cout << std::endl << std::endl;
    }
    system("clear");
}

std::string views::get_mensagem(std::string mensagem) {
    int tam = 35, i = 0;
    std::string msg;
    for (i = 0; i < tam && i < mensagem.length(); i++) {
        msg += mensagem[i];
    }
    msg += ":";
    for (int j = i; j < tam; j++) {
        msg += " ";
    }
    return msg;
}
