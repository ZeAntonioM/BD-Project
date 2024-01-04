#include "bits/stdc++.h"
using namespace std;

int main() {

    ofstream fileToWriteGames("jogos.sql", ios::trunc);
    ofstream fileToWriteEvents("eventos.sql", ios::trunc);
    ofstream fileToWriteConvocatoria("convocatoria.sql", ios::trunc);
    ofstream fileToWriteSubstituicao("subst.sql", ios::trunc);
    ofstream fileToWriteCartao("cartao.sql", ios::trunc);
    ofstream fileToWriteGolo("golo.sql", ios::trunc);
    //SCAPE AOS DADOS DO FICHEIRO PARA ORGANIZAR DEPOIS

    string filename = "Trabalho/dor.csv";
    ifstream file;
    file.open(filename);

    string line;
    getline(file,line);

    string word;
    stringstream s1(line);

    vector<vector<string>> scrape;

    while (file.good() && line.size()>0){

        getline(file, line);
        stringstream ss(line);
        vector<string> row;

        while (getline(ss, word, ',')){
            row.push_back(word);
        }
        scrape.push_back(row);
    }


    //BUSCAR AS PESSOAS PARA VERIFICAR MAIS TARDE E COLOCAR O ID

    string pessoasfile = "PESSOA.csv";
    ifstream file1;
    file1.open(pessoasfile);

    vector<vector<string>> pessoas;

    while (getline(file1, line)){

        stringstream ss(line);
        vector<string> rows;

        while (getline(ss, word, ',')){
            rows.push_back(word);
        }
       
        vector<string> select;
        select.push_back(rows[0]);
        select.push_back(rows[1]);
        pessoas.push_back(select);
        
    }

    //BUSCAR AS PESSOAS PARA VERIFICAR MAIS TARDE E COLOCAR O ID

    string jogadoresfile = "JOGADOR.csv";
    ifstream fileJ;
    fileJ.open(jogadoresfile);

    vector<vector<string>> jogadores;

    while (getline(fileJ, line)){

        stringstream ss(line);
        vector<string> rows;

        while (getline(ss, word, ',')){
            rows.push_back(word);
        }
       
        vector<string> select;
        select.push_back(rows[0]);
        select.push_back(rows[1]);
        jogadores.push_back(select);
        
    }

    //BUSCAR AS EQUIPAS PARA VERIFICAR MAIS TARDE E COLOCAR O ID
    string equipasfile = "EQUIPA.csv";
    ifstream fileE;
    fileE.open(equipasfile);

    vector<vector<string>> equipas;

    while (getline(fileE, line)){

        stringstream ss(line);
        vector<string> rows;

        while (getline(ss, word, ',')){
            rows.push_back(word);
        }
        
        vector<string> select;
        select.push_back(rows[0]);
        select.push_back(rows[1]);
        equipas.push_back(select);
        
    }

    //ORGANIZAR OS DADOS PARA DAR INSERT
    vector<vector<string>> jogos;
    vector<vector<string>> eventos;
    vector<vector<string>> convocatorias;
    vector<vector<string>> cartoes;
    vector<vector<string>> substituicoes;
    vector<vector<string>> golos;
    vector<vector<string>> saiu;
    vector<vector<string>> entrou;

    int quantjogo = 0;
    int quantevento = 1;

    int idx = 1;
    while (idx != scrape.size() && scrape[idx].size()!=0) {
        vector<string> l = scrape[idx];
        
        //Jogos
        vector<string> jogo;
        jogo.push_back(to_string(quantjogo+1));
        jogo.push_back(l[0]);
        jogo.push_back(l[3]);
        
        for (int j = 0; j < equipas.size(); j++) {
            if (l[1] == equipas[j][1]) {
                jogo.push_back(equipas[j][0]);
                break;
            }
        }

        for (int j = 0; j < equipas.size(); j++) {
            if (l[2] == equipas[j][1]) {
                jogo.push_back(equipas[j][0]);
                break;
            }
        }

        jogo.push_back(l[13]);

        if (jogos.size()==0) {
            quantjogo++;
            jogos.push_back(jogo);
        }

        else if ((jogos[jogos.size()-1][3] != jogo[3]) || (jogos[jogos.size()-1][4] != jogo[4])) {
            quantjogo++;
            
            for (int i = 0; i < saiu.size(); i++) {
                for (int j = 0; j < entrou.size(); j++) {
                    if (saiu[i][0] == entrou[j][0] && saiu[i][1] == entrou[j][1] && saiu[i][3] == entrou[j][3]) {
                        vector<string> evento;
                        evento.push_back(to_string(quantevento));
                        evento.push_back(saiu[i][0]);
                        evento.push_back(saiu[i][2]);
                        evento.push_back(saiu[i][1]);
                        eventos.push_back(evento);
                        
                        vector<string> substituicao;
                        substituicao.push_back(to_string(quantevento));
                        substituicao.push_back(entrou[j][2]);
                        substituicoes.push_back(substituicao);
                        quantevento++;
                        entrou.erase(entrou.begin()+j);
                        break;

                    }
                }
            }
            
            saiu.clear();
            entrou.clear();
            jogos.push_back(jogo);
        }
        
        
        //CONVOCATORIAS
        string idEquipa1;
        string idEquipa2;

        for (auto el : equipas) {
                if (el[1] == l[1]) {
                    idEquipa1 = el[0];
                }
                if (el[1] == l[2]) {
                    idEquipa2 = el[0];
                }
            }


        if (l[5] != "" && l[6] != "" ) {
            for (int j = 0; j < jogadores.size(); j++) {
                if ((l[5] == pessoas[j][1]) && (jogadores[j][1] == idEquipa1)) {
                    vector<string> touple;
                    touple.push_back(jogadores[j][0]);
                    touple.push_back(to_string(quantjogo));
                    convocatorias.push_back(touple);
                    break;
                }
            }
        }

        if (l[9] != "" && l[10] != "") {
            for (int j = 0; j < jogadores.size(); j++) {
                if ((l[9] == pessoas[j][1]) && (jogadores[j][1] == idEquipa2)) {
                    vector<string> touple;
                    touple.push_back(jogadores[j][0]);
                    touple.push_back(to_string(quantjogo));
                    convocatorias.push_back(touple);
                    break;
                }
            }
        }

        //EVENTOS
        vector<string> evento;
        vector<string> cartao;
        vector<string> golo;
        vector<string> sair;
        vector<string> entrar;

        string idjogador1;
        string idjogador2;

        for (int j = 0; j < jogadores.size(); j++) {
            if ((l[5] == pessoas[j][1]) && (jogadores[j][1] == idEquipa1)) {
                idjogador1 = jogadores[j][0];
            }
        }
        for (int j = 0; j < jogadores.size(); j++) {
            if ((l[9] == pessoas[j][1]) && (jogadores[j][1] == idEquipa2)) {
                idjogador2 = jogadores[j][0];
            }
        }       






        //EVENTOS EQUIPA 1
        if (l[6] != "") {
            istringstream ist(l[8]);
            while (getline(ist, word, '/')) {
                istringstream separator(word);
                string tipo;

                getline(separator, tipo, '-');

                int min;

                evento.clear();

                if (tipo == "Golo") {
                    string theRest;
                    getline(separator, theRest);
                    if (theRest.find("(p.b.)") == string::npos) {
                        istringstream aStream(theRest);
                        while (aStream >> min) {
                            evento.clear();
                            evento.push_back(to_string(quantevento));
                            evento.push_back(to_string(quantjogo));
                            evento.push_back(idjogador1);
                            evento.push_back(to_string(min));
                            eventos.push_back(evento);

                            golo.clear();
                            golo.push_back(to_string(quantevento));
                            golo.push_back(idEquipa1);
                            golos.push_back(golo);
                            quantevento++;
                        }
                    }
                    
                    else {
                        istringstream aStream(theRest);
                        while (aStream >> min) {
                            evento.clear();
                            evento.push_back(to_string(quantevento));
                            evento.push_back(to_string(quantjogo));
                            evento.push_back(idjogador1);
                            evento.push_back(to_string(min));
                            eventos.push_back(evento);

                            golo.clear();
                            golo.push_back(to_string(quantevento));
                            golo.push_back(idEquipa2);
                            golos.push_back(golo);
                            quantevento++;
                        }
                    }
                }
                
                else if (tipo == "Amarelo") {
                    while (separator >> min) {
                        evento.clear();
                        evento.push_back(to_string(quantevento));
                        evento.push_back(to_string(quantjogo));
                        evento.push_back(idjogador1);
                        evento.push_back(to_string(min));
                        eventos.push_back(evento);

                        cartao.clear();
                        cartao.push_back(to_string(quantevento));
                        cartao.push_back("Amarelo");
                        cartoes.push_back(cartao);
                        quantevento++;
                    }
                    
                }
                
                else if (tipo == "Vermelho") {
                    while (separator >> min) {
                        evento.clear();
                        evento.push_back(to_string(quantevento));
                        evento.push_back(to_string(quantjogo));
                        evento.push_back(idjogador1);
                        evento.push_back(to_string(min));
                        eventos.push_back(evento);

                        cartao.clear();
                        cartao.push_back(to_string(quantevento));
                        cartao.push_back("Vermelho");
                        cartoes.push_back(cartao);
                        quantevento++;
                    }
                    
                }
                
                else if (tipo == "Saiu") {
                    while (separator >> min) {
                        sair.push_back(to_string(quantjogo));
                        sair.push_back(to_string(min));
                        sair.push_back(idjogador1);
                        sair.push_back(idEquipa1);
                        saiu.push_back(sair);
                        
                    }
                }

                else if (tipo == "Entrou") {
                        while (separator >> min) {
                        entrar.push_back(to_string(quantjogo));
                        entrar.push_back(to_string(min));
                        if (idjogador1 == ""){
                            cout << "Erro" << endl;
                        }
                        entrar.push_back(idjogador1);
                        entrar.push_back(idEquipa1);
                        entrou.push_back(entrar);
                        
                    }
                }
                
            }
        
        }


        //EVENTOS EQUIPA 2
        if (l[10] != "") {
            istringstream st(l[12]);
            while (getline(st, word, '/')) {
                istringstream separator(word);
                string tipo;

                getline(separator, tipo, '-');

                int min;

                evento.clear();

                if (tipo == "Golo") {
                    string theRest;
                    getline(separator, theRest);
                    if (theRest.find("(p.b.)") == string::npos) {
                        istringstream aStream(theRest);
                        while (aStream >> min) {
                            evento.clear();               
                            evento.push_back(to_string(quantevento));
                            evento.push_back(to_string(quantjogo));
                            evento.push_back(idjogador2);
                            evento.push_back(to_string(min));
                            eventos.push_back(evento);

                            golo.clear();
                            golo.push_back(to_string(quantevento));
                            golo.push_back(idEquipa2);
                            golos.push_back(golo);
                            quantevento++;
                        }
                    }
                    
                    else {
                        istringstream aStream(theRest);
                        while (aStream >> min) {
                            evento.clear();
                            evento.push_back(to_string(quantevento));
                            evento.push_back(to_string(quantjogo));
                            evento.push_back(idjogador2);
                            evento.push_back(to_string(min));
                            eventos.push_back(evento);

                            golo.clear();
                            golo.push_back(to_string(quantevento));
                            golo.push_back(idEquipa1);
                            golos.push_back(golo);
                            quantevento++;
                        }
                    }
                }

                else if (tipo == "Amarelo") {
                    while (separator >> min) {
                        evento.clear();
                        evento.push_back(to_string(quantevento));
                        evento.push_back(to_string(quantjogo));
                        evento.push_back(idjogador2);
                        evento.push_back(to_string(min));
                        eventos.push_back(evento);

                        cartao.clear();
                        cartao.push_back(to_string(quantevento));
                        cartao.push_back("Amarelo");
                        cartoes.push_back(cartao);
                        quantevento++;
                    }
                    
                }
                
                else if (tipo == "Vermelho") {
                    while (separator >> min) {
                        evento.clear();
                        evento.push_back(to_string(quantevento));
                        evento.push_back(to_string(quantjogo));
                        evento.push_back(idjogador2);
                        evento.push_back(to_string(min));
                        eventos.push_back(evento);

                        cartao.clear();
                        cartao.push_back(to_string(quantevento));
                        cartao.push_back("Vermelho");
                        cartoes.push_back(cartao);
                        quantevento++;
                    }
                    
                }
                
                else if (tipo == "Saiu") {
                    while (separator >> min) {
                        sair.push_back(to_string(quantjogo));
                        sair.push_back(to_string(min));
                        sair.push_back(idjogador2);
                        sair.push_back(idEquipa2);
                        saiu.push_back(sair);
                        
                    }
                }

                else if (tipo == "Entrou") {
                        while (separator >> min) {
                        entrar.push_back(to_string(quantjogo));
                        entrar.push_back(to_string(min));
                        if (idjogador2 == ""){
                            cout << "Erro" << endl;
                        } 
                        entrar.push_back(idjogador2);
                        entrar.push_back(idEquipa2);
                        entrou.push_back(entrar);
                        
                    }
                }
                
            }
        }


    
        idx++;
    }

    for (int i = 0; i < saiu.size(); i++) {
        for (int j = 0; j < entrou.size(); j++) {
            if (saiu[i][0] == entrou[j][0] && saiu[i][1] == entrou[j][1] && saiu[i][3] == entrou[j][3]) {
                vector<string> evento;
                evento.push_back(to_string(quantevento));
                evento.push_back(saiu[i][0]);
                evento.push_back(saiu[i][2]);
                evento.push_back(saiu[i][1]);
                eventos.push_back(evento);
                
                vector<string> substituicao;
                substituicao.push_back(to_string(quantevento));
                substituicao.push_back(entrou[j][2]);
                substituicoes.push_back(substituicao);
                quantevento++;
                entrou.erase(entrou.begin()+j);
                break;

            }
        }
    }

    for (auto jogo: jogos) {
        fileToWriteGames << "INSERT INTO JOGO VALUES (" << jogo[0] << ", '" << jogo[1] << "', '" << jogo[2] << "', '" << jogo[4] << "', '" << jogo[3] << "', '"<< jogo[5] << "');" << endl;
    }

    for (auto convocatoria: convocatorias) {
        fileToWriteConvocatoria << "INSERT INTO CONVOCATORIA VALUES (" << convocatoria[0] << ", " << convocatoria[1] << ");" << endl;
    }

    for (auto evento: eventos) {
        fileToWriteEvents << "INSERT INTO EVENTO VALUES (" << evento[0] << ", " << evento[1] << ", " << evento[2] << ", " << evento[3] << ");" << endl;
    }
    
    for (auto golo: golos) {
        fileToWriteGolo << "INSERT INTO GOLO VALUES (" << golo[0] << ", " << golo[1] << ");" << endl;
    }

    for (auto cartao: cartoes) {
        fileToWriteCartao << "INSERT INTO CARTAO VALUES (" << cartao[0] << ", '" << cartao[1] << "');" << endl;
    }

    for (auto subs: substituicoes) {
        fileToWriteSubstituicao << "INSERT INTO SUBSTITUICAO VALUES (" << subs[0] << ", " << subs[1] << ");" << endl;
    }

    return 0;
}