# Planejamento de Testes: Atividade Baremetal

Placa: FRDM-KL25Z | Branch: `baremetal`

### T1: Build limpo

- **Objetivo:** garantir que o projeto compila do zero.
- **Procedimento:**
  1. `west build -p auto -b frdm_kl25z`
- **Resultado esperado:** build termina sem erros e sem warnings do código da aplicação (`src/main.c`).
- **Critério:** código de saída 0.

### T2: Gravação

- **Objetivo:** garantir que o firmware é gravado na placa.
- **Procedimento:**
  1. `west flash -r pyocd`
- **Resultado esperado:** flash conclui sem erro e a placa reinicia sozinha.
- **Critério:** nenhuma mensagem de erro; LEDs começam a piscar após a gravação.

### T3: Mensagem de boot

- **Objetivo:** confirmar que a saída serial funciona.
- **Procedimento:**
  1. Abrir `python -m serial.tools.miniterm /dev/ttyACM0 115200`.
  2. Apertar o botão **reset** da placa.
- **Resultado esperado:** aparece a mensagem de início (`Iniciando`).
- **Critério:** mensagem visível em até 2 s após o reset.

### T4: Verificação visual

- **Objetivo:** confirmar que o comportamento físico bate com o log.
- **Procedimento:**
  1. Reset na placa.
  2. Observar (ou gravar em vídeo) por 10 s, contando mudanças de estado de cada LED.
- **Resultado esperado:** LED A muda de estado 10 vezes, LED B 20 vezes em 10 s.
- **Critério:** contagem dentro de ±1 toggle.

### T5: Verificação pelo log

- **Objetivo:** confirmar que cada LED piscou no instante certo, de acordo com seu período configurado.
- **Procedimento:**
  1. Abrir `demo_log.txt` (ou `desafio_log.txt`, para o desafio) e observar os timestamps `[xx ms]` de cada linha.
- **Resultado esperado:** os timestamps de cada LED crescem de forma consistente com o período configurado para ele (ex: ~500ms entre toggles do `led0` e ~1000ms entre toggles do `led1` no `demo_log.txt`).
- **Critério:** nenhum desvio grosseiro entre timestamps consecutivos do mesmo LED em relação ao período esperado.

## Registro de execução

| Teste | Resultado (Aprovado/Reprovado) 
|-------|-------------------------------|
| T1 | | | |
| T2 | | | |
| T3 | | | |
| T4 | | | |
| T5 | | | |

## Validação pelo par

O avaliador deve executar os testes acima, preencher a tabela de registro em um comentário do PR e registrar explicitamente que a validação foi realizada, mesmo que tudo passe.
