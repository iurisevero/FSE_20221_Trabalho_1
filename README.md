# FSE_20221_Trabalho_1
Repositório para desenvolvimento do trabalho 1 de Fundamentos de Sistemas Embarcados, semestre 1 de 2022. A descrição da atividade pode ser vista em https://gitlab.com/fse_fga/trabalhos-2022_1/trabalho-1-2022-1

## Servidores Distribuídos

Para utilização dos servidores distribuídos, basta rodar o comando ```make``` dentro da pasta ```distributedServer```. Para executar, utilize o comando ```make run``` com os argumentos ```CROSS=``` para indicar o cruzamento, ```PORT=``` para indicar a porta de conexão TCP, ```CENTRALSERVERIP=``` para indicar o Ip do servidor central e ```CENTRALSERVERPORT=``` para indicar a porta de acesso para o servidor central.

## Servidor Central

Para utilização dos servidores distribuídos, basta rodar o comando ```make``` dentro da pasta ```centralServer```. Antes de executar o programa é necesssário colocar as informações dos servidores distribuídos no arquivo ```.conf```. No arquivo ```.conf``` deve ser inserido um servidor distribuído por linha, seguindo o padrão IP:PORT. Por fim, para executar o servidor central utilize o comando ```make run``` com o argumento ```PORT=``` para indicar a porta de conexão TCP.