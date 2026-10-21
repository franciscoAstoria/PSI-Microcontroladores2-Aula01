import sys
import re
import numpy as np
import matplotlib.pyplot as plt

def main():
    led0_jitter = 0
    led1_jitter = 0
    led0_tempos = []
    led0_jitter = []
    led1_tempos = []
    led1_jitter = []

    with open(sys.argv[1], "r") as f:
        linhas = f.readlines()
        l1 = linhas[1]
        l2 = linhas[2]
        led0_periodo = int(l1[l1.index("(")+1:l1.index("ms)")])
        led0_offset = int(l1[1:l1.index(" ms]")])
        led1_offset = int(l2[1:l2.index(" ms]")])
        led1_periodo = int(l2[l2.index("(")+1:l2.index("ms)")])

        for linha in linhas[3:]:
            if f"({led0_periodo}ms)" in linha:
                timestamp = int(linha[1:linha.index(" ms]")])
                led0_tempos.append(timestamp)
                erro = timestamp - (led0_periodo*(len(led0_tempos)) + led0_offset)
                led0_jitter.append(erro)

            elif f"({led1_periodo}ms)" in linha:
                timestamp = int(linha[1:linha.index(" ms]")])
                led1_tempos.append(timestamp)
                erro = timestamp - (led1_periodo*(len(led1_tempos)) + led1_offset)
                led1_jitter.append(erro)

        maior = max(led0_jitter)
        menor = abs(min(led0_jitter))
        print(f"led0 ({led0_periodo}ms):")
        print(f"Número de amostras do led0: {len(led0_jitter)}")
        print(f"Jitter maximo do led0: {maior if maior > menor else menor}ms")

        maior = max(led1_jitter)
        menor = abs(min(led1_jitter))
        print(f"led1 ({led1_periodo}ms):")
        print(f"Número de amostras do led1: {len(led1_jitter)}")
        print(f"Jitter maximo do led1 (): {maior if maior > menor  else menor}ms")

        plt.scatter(led0_tempos, led0_jitter, label = f"led0 ({led0_periodo}ms)")
        plt.legend()
        plt.scatter(led1_tempos, led1_jitter, label = f"led1 ({led1_periodo}ms)")
        plt.legend()
        plt.xlabel("Tempo (ms)")
        plt.ylabel("Jitter (ms)")
        plt.title("Jitter dos LEDs")
        nome = sys.argv[1][:-3] + "png"
        plt.savefig(nome)
    
if __name__ == "__main__":
    main()