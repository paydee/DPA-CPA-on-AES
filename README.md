# DPA-CPA-on-AES

**Some basic DPA CPA on AES implemented in C**
___
Ref:
1. [DPA](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwj2zdbM5aT0AhW3QvEDHejuAioQFnoECAUQAQ&url=https%3A%2F%2Fpaulkocher.com%2Fdoc%2FDifferentialPowerAnalysis.pdf&usg=AOvVaw00fRfOSHbK1JArAuBTcKGE)
2. Correlation Power Analysis with a Leakage
   Mode,*Eric Brier, Christophe Clavier, and Francis Olivier*

The repo contains:
- **curves/** : power traces of 2000 AES encryption processes.
- **demo_input.txt**: 2000 inputs.
- **demo_output.txt**: 2000 corresponding outputs.
- **DPA.c**: Classic DPA with select function is the value of one bit of the first byte of the processing data right before enter the last round of AES.
- **DPA_HM.c**: DPA with select function is the HW of the first byte of the processing data right before enter the last round of AES.
- **CPA.c**: Classic CPA with Hamming weight model of power consumption.
- **CPA_HD_P.c**: CPA with Hamming distance model of power consumption, parallel programmed.
- **log_CPA.txt**, **CPA_parallel_log.txt** are execution log for *CPA.c* and *CPA_HD_P.c* repersively. Codes run on the same machine 4 cores, 1000000 clocks/secs
