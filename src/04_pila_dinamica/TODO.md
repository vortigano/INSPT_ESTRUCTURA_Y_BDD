## TODO

### Lógica de juego
- [x] Inicializar pila y mostrarla
- [x] Turnos alternados (Jugador 1, Jugador 2 / CPU)
- [x] Animación de desapilado en tiempo real
- [x] CPU funcional con elección aleatoria
- [ ] **Limpiar buffer de entrada antes del turno del jugador**: Actualmente, si se presionan teclas durante la animación de la CPU, `scanf` las consume al iniciar el turno humano. Se debe drenar `stdin` justo antes de solicitar la cantidad para evitar pulsaciones fantasma.