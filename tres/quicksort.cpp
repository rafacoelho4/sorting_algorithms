#include "quicksort.hpp"


void quick_sort_main(bool parametro, int quantidade){
    //Variáveis e inicializações
    //hsus
    Arquivo arquivo;
    Metrica m = inicializa_metrica();
    Item u;
    clock_t inicio, fim;
    int cont = 0;
    inicializando_ponteiros(&arquivo);
    
    inicio = clock();
    quick_sort_externo(&m, &arquivo, 1, quantidade);
    fim = clock();
    m.tempo = (double) (fim - inicio)/CLOCKS_PER_SEC;
    
    if(parametro){
        rewind(arquivo.leitura_inferior);
        while(fread(&u, sizeof(Item), 1, arquivo.leitura_inferior) == 1 && cont < quantidade){
            cout<<(cont+1)<<"\t"<<u.inscricao<<"\t"<<u.nota<<" "<<u.curso<<" "<<u.estado<<endl;
            cont++;
        }
    }

    imprimindo_resultados(m);
}
Metrica inicializa_metrica(){
    Metrica m;
    m.comparacoes = 0;
    m.escrita = 0;
    m.leitura = 0;
    return m;
}

void imprimindo_resultados( Metrica m ){
    cout<<color::rize( "                       RESULTADOS OBTIDOS QUICKSORT                       ", "Black" , "Light Cyan" )<<endl;
    printf(ANSI_COLOR_BLUE "\nCOMPARACOES: \t\t\t\t %lld" ANSI_COLOR_RESET, m.comparacoes);
    printf(ANSI_COLOR_BLUE "\nTRANSFERENCIAS DE LEITURA: \t\t %lld" ANSI_COLOR_RESET, m.leitura);
    printf(ANSI_COLOR_BLUE "\nTRANSFERENCIAS DE ESCRITA: \t\t %lld" ANSI_COLOR_RESET, m.escrita);
    printf(ANSI_COLOR_BLUE "\nTEMPO TOTAL: \t\t\t\t %lf segundos" ANSI_COLOR_RESET, m.tempo);
    printf("\n"); 
}

void inserir_area(Area* area, Item* ultimo_lido, int* tamanho_area){
    if(*tamanho_area < TAMANHO){
        (*tamanho_area)++;
        area[(*tamanho_area)-1] = (*ultimo_lido);  
        quick_sort(area, 0, (*tamanho_area)-1); 
    }
    
}


void ler_arquivo_texto(FILE** arquivo){
    //Caso ocorra algum problema na abertura do arquivo o programa finaliza
    if( (*arquivo = fopen("./entrada/PROVAO.bin", "r+b")) == NULL){
        cout<<"Erro na abertura do arquivo";
        exit(1);
    }
}

void inicializando_ponteiros(Arquivo* arquivo){
    //faz a leitura do ponteiro de escrita do subarquivo à esquerda
    ler_arquivo_texto(&arquivo->escrita_inferior);
    
    //faz a leitura do ponteiro de escrita do subarquivo à direita
    ler_arquivo_texto(&arquivo->escrita_superior);

    //faz a leitura do ponteiro de leitura do subarquivo à esquerda
    ler_arquivo_texto(&arquivo->leitura_inferior);

    //faz a leitura do ponteiro de leitura do subarquivo à direita
    ler_arquivo_texto(&arquivo->leitura_superior);
}

void quick_sort_externo(Metrica* m, Arquivo* arquivo, int esquerda, int direita){
   int i;
   int j;

    //Inicializa area de memória interna
    Area area[TAMANHO];    
    //Caso o tamanho do arquivo/ subarquivo seja menor que 1, finaliza
    if(direita - esquerda < 1 ){
        return;
    }

    particao( m, arquivo, area, esquerda, direita, &i, &j);
    fflush(arquivo->leitura_inferior);
    fflush(arquivo->leitura_superior);
    fflush(arquivo->escrita_inferior);
    fflush(arquivo->leitura_superior);

    if( (i - esquerda) < (direita - j)){
        //Caso o subarquivo a direita seja maior, a ordenação começa pela esquerda
        quick_sort_externo(m, arquivo, esquerda, i);
        quick_sort_externo(m, arquivo, j, direita);
    }
    else{
        //Caso o subarquivo a direita seja menor, a ordenação começa pela direita
        quick_sort_externo(m,arquivo, j, direita);
        quick_sort_externo(m,arquivo, esquerda, i);
       
    }

}


void particao(Metrica* m, Arquivo *arquivo, Area* area, int esquerda, int direita, int* i, int* j){


    int ls = direita; // leitura superior
    int es = direita; // apontador de escrita superior
    int li = esquerda; // leitura inferior
    int ei = esquerda; // apontador de escrita inferior
    int tamanho_area = 0; // tamanho da area
    double limite_inf = DBL_MIN; // limite inferior
    double limite_sup = DBL_MAX; // limite superior
    bool lido = true; // variavel que verifica se o item foi lido
    Item ultimo_lido;
    Item aux;
  
    //Definindo posições dos ponteiros de leitura e escrita do subarquivo à esquerda
    fseek(arquivo->leitura_inferior, (li - 1)*sizeof(Item), SEEK_SET);
    fseek(arquivo->escrita_inferior, (ei - 1)*sizeof(Item), SEEK_SET);
    
    //Definindo posições dos ponteiros de leitura e escrita do subarquivo à direita
    fseek(arquivo->leitura_superior, (ls - 1)*sizeof(Item), SEEK_SET);
    fseek(arquivo->escrita_superior, (es - 1)*sizeof(Item), SEEK_SET); 

    *i = esquerda-1;
    *j = direita+1;

    while (ls >= li){
       
        //se a are de memoria principal não estiver cheia
        if (tamanho_area < TAMANHO - 1)
        {
        
            if(lido){
                ler_limite_superior(&m->leitura, arquivo->leitura_superior , &ultimo_lido, &ls, &lido);
         
            } else {
                ler_limite_inferior(&m->leitura, arquivo->leitura_inferior, &ultimo_lido, &li, &lido);
               
            }
            inserir_area(area, &ultimo_lido, &tamanho_area);
            continue; 
        }
 
      //Caso seja necessario quebrar a sequencia de leitura alternada
        if(ls == es){
            ler_limite_superior(&m->leitura, arquivo->leitura_superior, &ultimo_lido, &ls, &lido);
        }
        else if(li == ei){
            ler_limite_inferior(&m->leitura, arquivo->leitura_inferior, &ultimo_lido, &li, &lido);
      
        }
        else if(lido){
            ler_limite_superior(&m->leitura, arquivo->leitura_superior, &ultimo_lido, &ls, &lido);
        }else{
            ler_limite_inferior(&m->leitura, arquivo->leitura_inferior, &ultimo_lido, &li, &lido);
        }

        
        if(ultimo_lido.nota > limite_sup){
            (m->comparacoes)++;
            *j = es;
            escreve_max(&m->escrita, &arquivo->escrita_superior, ultimo_lido, &es);
            continue;
        }
        
        if(ultimo_lido.nota < limite_inf){
            (m->comparacoes)+=2;
            *i = ei;
            escreve_min(&m->escrita, &arquivo->escrita_inferior, ultimo_lido, &ei);
            continue;
        }

        inserir_area(area, &ultimo_lido, &tamanho_area);

         //Caso seja a area de memoria esteja cheia
        if(ei - esquerda < direita - es){
            retira_min(area, &aux, &tamanho_area);
            escreve_min(&m->escrita, &arquivo->escrita_inferior, aux, &ei);
            limite_inf = aux.nota;
        } else {
            retira_max(area, &aux, &tamanho_area);
            escreve_max(&m->escrita, &arquivo->escrita_superior, aux, &es);
            limite_sup = aux.nota;
        } 
    }
    fflush(arquivo->leitura_inferior);
    fflush(arquivo->leitura_superior);
    fflush(arquivo->escrita_inferior);
    fflush(arquivo->leitura_superior);
     while (ei <= es){
        retira_min(area, &aux, &tamanho_area);
        escreve_min(&m->escrita, &arquivo->escrita_inferior, aux, &ei);
    }   


}

void quick_sort(Area* v, int esquerda, int direita){
   
    int i, j;
    double x;
    Item y;
     
    i = esquerda;
    j = direita;
    x = (v)[(esquerda + direita) / 2].nota;

    while (i <= j) {
        while ((v)[i].nota < x && i < direita) {
            i++;
        }
        while ((v)[j].nota > x && j > esquerda) {
            j--;
        }
        if (i <= j) {
            y = (v)[i];
            (v)[i] = (v)[j];
            (v)[j] = y;
            i++;
            j--;
        }
    }

    if (j > esquerda) {
        quick_sort(v, esquerda, j);
    }
    if (i < direita) {
        quick_sort(v, i, direita);
    }
}

void retira_primeiro(Area* area, Item* primeiro){
    (*primeiro)= area[0];
}

void retira_min(Area* area, Item* aux, int* tamanho_area){
     if((*tamanho_area) == 0)
        return;

    retira_primeiro(area, aux );
       for(int i = 1; i < (*tamanho_area); i++){
    	area[i - 1] = area[i];
    }

    (*tamanho_area)--;
}

void retira_ultimo(Area* area, Item* ultimo){
    (*ultimo) = area[TAMANHO-1];
}
void retira_max(Area* area, Item* aux, int* tamanho_area){
    if((*tamanho_area) == 0)
        return;
    retira_ultimo(area, aux );
    (*tamanho_area)--;
}

void ler_limite_inferior(unsigned long long int* leitura, FILE* arquivo, Item* u, int* li, bool* lido){
    fread(u, sizeof(Item), 1, arquivo); 

    (*li)++;
    (*leitura)++;
    (*lido) = true;
}

void ler_limite_superior(unsigned long long int* leitura, FILE* arquivo, Item* u, int* ls, bool* lido){
    fread(u, sizeof(Item), 1, arquivo); 
    (*ls)--;
    (*lido) = false;
    (*leitura)++;
    fseek(arquivo, ((*ls)-1)*sizeof(Item), SEEK_SET);
}

void escreve_max(unsigned long long int* escrita, FILE** arquivo, Item aux, int* es){
    fwrite(&aux, sizeof(Item), 1, *arquivo);
    (*es)--;
    (*escrita)++;
    fseek(*arquivo, ((*es)-1)*sizeof(Item), SEEK_SET);
}

void escreve_min(unsigned long long int* escrita, FILE** arquivo, Item aux, int* ei){
    fwrite(&aux, sizeof(Item), 1, *arquivo);
    (*escrita)++;
    (*ei)++;
}