.mode columns
.headers ON
.nullvalue NULL

SELECT e.idJogo, e.minuto, e.idJogador
FROM EVENTO e JOIN CARTAO c
ON (e.idEvento = c.idEvento)
WHERE (c.cor = "Vermelho")
