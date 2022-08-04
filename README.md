# FSE_20221_Trabalho_1
Repositório para desenvolvimento do trabalho 1 de Fundamentos de Sistemas Embarcados, semestre 1 de 2022. A descrição da atividade pode ser vista em https://gitlab.com/fse_fga/trabalhos-2022_1/trabalho-1-2022-1

## Servidores Distribuídos

Para utilização dos servidores distribuídos, basta rodar o comando ```make``` dentro da pasta ```distributedServer```. Para executar, utilize o comando ```make run``` com os argumentos ```CROSS=``` para indicar o cruzamento, ```PORT=``` para indicar a porta de conexão TCP, ```CENTRALSERVERIP=``` para indicar o Ip do servidor central e ```CENTRALSERVERPORT=``` para indicar a porta de acesso para o servidor central.

## Servidor Central

Para utilização dos servidores distribuídos, basta rodar o comando ```make``` dentro da pasta ```centralServer```. Antes de executar o programa é necesssário colocar as informações dos servidores distribuídos no arquivo ```.conf```. No arquivo ```.conf``` deve ser inserido um servidor distribuído por linha, seguindo o padrão IP:PORT. Por fim, para executar o servidor central utilize o comando ```make run``` com o argumento ```PORT=``` para indicar a porta de conexão TCP.

### Informações de Transito

As informações apresentadas correspondem a todos cruzamentos conectados. A quantidade de carros por via apresenta a soma da quantidade de carros em todos cruzamentos, enquanto a velocidade média da via principal e a média de carros por minuto faz a soma das informações dos cruzamentos e tira a média do resultado.

## Execução Geral

Para que o sistema funcione corretamente é necessário executar o servidor central com o arquivo .conf preenchido e, em seguida, executar os servidores. Não foi feito tratamento de erro para tentativa de conexão em servidores desativados, logo, o levantamento do sistema fora de ordem resulta em erro na conexão dos servidores distribuídos ```Broken pipe```.
