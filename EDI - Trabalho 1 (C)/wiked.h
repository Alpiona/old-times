#ifndef WIKED_H_INCLUDED
#define WIKED_H_INCLUDED
typedef struct link TipoLink;

typedef struct pagina TipoPagina;

typedef struct arquivo TipoArquivo;

typedef struct editor TipoEditor;

/*Inicializa lista de editores
* inputs:
* output: lista de editores
* pre-condicao: lista de editores existente
* pos-condicao: lista de editores é inicializada
*/

TipoEditor* iniciaEdi(void);

/*Inicializa lista de paginas
* inputs:
* output: lista de paginas
* pre-condicao: lista de paginas criada
* pos-condicao: lista de paginas inicializada
*/

TipoPagina* iniciaPag(void);

/*Adiciona uma nova pagina na lista
* inputs: ponteiro para log, lista de paginas, nome da pagina, e nome do arquivo da pagina
* output: lista de pagina
* pre-condicao: nome da pagina ausente na lista de paginas
* pos-condicao: pagina adicionada a lista de paginas
*/

TipoPagina* INSEREPAGINA (FILE *log, TipoPagina* pagina, char* nomePag, char* nomeArq);

/*Exclui uma página da lista de paginas
* inputs: log, lista de paginas, nome da pagina
* output: lista de paginas
* pre-condicao: pagina a ser retirada existente na lista de paginas
* pos-condicao: pagina é retirada da lista de paginas
*/

TipoPagina* RETIRAPAGINA (FILE *log, TipoPagina* pagina, char* nomePag);

/*Insere um editor a lista de editores
* inputs: log, lista de editores, nome do editor
* output: lista de editores
* pre-condicao: nome do editor ausente na lista de editores
* pos-condicao: nome do editor adicionado a lista de editores
*/

TipoEditor* INSEREEDITOR (FILE *log, TipoEditor* editor, char* nomeEdi);

/*Retira um editor a lista de editores
* inputs: log, lista de editores, nome do editor
* output: lista de editores
* pre-condicao: nome do editor existente na lista de editores
* pos-condicao: nome do editor retirado da lista de editores
*/

TipoEditor* RETIRAEDITOR (FILE *log, TipoEditor* editor, char* nome);

/*Insere uma contribuição
* inputs: log, lista de paginas, lista de editores, nome da pagina, nome do editor, arquivo da pagina
* output: lista de paginas
* pre-condicao: nome de editor existente na lista de editores, e nome da pagina existente na lista de paginas
* pos-condicao: contribuicao adicionado a lista de contribuicoes da pagina na lista de paginas
*/

TipoPagina* INSERECONTRIBUICAO (FILE *log, TipoPagina* listaPag, TipoEditor* listaEdi, char* pagina, char* editor, char* arquivo);

/*Retira uma contribuição
* inputs: log, lista de pagina, nome da pagina, nome do editor, nome do arquivo
* output: lista de pagina
* pre-condicao: nome da pagina existente na lista de paginas, arquivo da contribuicao existente na lista de contribuicoes,
                nome do editor ser o mesmo registrado a constribuicao q sera retirada
* pos-condicao: contribuicao é marcado como retirado
*/

TipoPagina* RETIRACONTRIBUICAO (FILE *log, TipoPagina* listaPag, char* pagina, char* editor, char* arquivo);

/*Insere um link em uma pagina para outra
* inputs: log, lista de paginas, pagina de origem e pagina de destino
* output: lista de paginas
* pre-condicao: ambas as paginas devem existir sem um link da pagina de origem para pagina de destino
* pos-condicao: pagina de origem com link para pagina de destino
*/

TipoPagina* INSERELINK (FILE *log, TipoPagina* listaPag, char* pagOri, char* pagDest);

/*Retira um link em uma pagina para outra
* inputs: log, lista de paginas, pagina de origem e pagina de destino
* output: lista de paginas
* pre-condicao: ambas as paginas devem existir, e possuir um link da pagina de origem para a pagina de destino
* pos-condicao: o link é retirado
*/

TipoPagina* RETIRALINK(FILE *log, TipoPagina* listaPag, char* pagOri, char* pagDest);

/*Verifica se há caminho na página origem para destino
* inputs: log, lista de paginas, pagina de origem e pagina de destino
* output:
* pre-condicao: ambas as paginas devem existir
* pos-condicao: escreve no arquivo de log se há link da pagina origem para destino
*/

void CAMINHO (FILE *log, TipoPagina* pagina, char* pagOri, char* pagDest);

/*Imprime e gera um arquivo de uma página
* inputs: log, lista de paginas, nome da pagina
* output:
* pre-condicao: pagina deve existir na lista de paginas
* pos-condicao: é criado um arquivo com a pagina
*/

void IMPRIMEPAGINA(FILE *log, TipoPagina* listaPag, char* pagina);

/*Imprime e gera arquivo de todas as páginas do wikied
* inputs: log, lista de paginas
* output:
* pre-condicao:
* pos-condicao: é criado arquivo de todas as paginas existentes na lista de paginas
*/

void IMPRIMEWIKED(FILE *log, TipoPagina* pagina);

/*Finaliza o programa
* inputs:
* output:
* pre-condicao:
* pos-condicao: memorias usadas sao liberadas e o programa é finalizado
*/

void FIM (TipoPagina* pagina, TipoEditor* editor, FILE* log, FILE* entrada);

#endif // WIKED_H_INCLUDED
