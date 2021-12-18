O seguinte projeto tem como finalidade simular um timer Pomodoro.

*Sobre o timer*

Ele é constituído de 4 ciclos onde cada parte possui um tempo de 25 minutos de foco e um tempo de 5 minutos de pausa. No último ciclo a pausa é de 30 minutos.

*Sobre o projeto*
- Intruções

1. clone os arquivos numa pasta:
 `git clone https://github.com/taynaraMarcondes/pomodoro_timer.X.git`
2. Abra o software MPLAB X IDE (a versão que utilizei é v5.45)
3. Abra o software PicsimLab
4. No MPLAB abra o projeto que foi clonado no passo 1 e compile o projeto (comando F11)
5. No PicsimLab clique em File->Load Hex e abra o seguinte aquivo:
pomodoro_timer.X\dist\default\production\pomodoro_timer.X.production.hex

- Comandos

'U' - aumenta o tempo do timer em 1 segundo

'D' - diminui o tempo do timer em 1 segundo

'S' - Começa o timer

's' - pula para o próximo timer (que pode ser de estudo ou pausa, dependendo da parte do ciclo que está)

'L' - altera a meta de tempo de estudo
