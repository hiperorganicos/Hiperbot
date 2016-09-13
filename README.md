# Hiperbot
Monitoramento com Arduino com envio de dados para servidor remoto.

Usar o arquivo arduino/hiperbot/hiperbot.ino em conjunto com o arquivo pd/terrario2014.pd para enviar os dados do
monitoramento para um servidor remoto OSC.

O arquivo hiperbot_yun não necessita de um arquivo PD, pois envia diretamente os dados para o servidor.
Para enviá-los através do utilitário OscGroups, é necessário enviar para um outro computador rodando o utilitário na mesma rede
do Arduino Yun.

A pasta old contém arquivos antigos de sonificação usando Max e de arduino.
