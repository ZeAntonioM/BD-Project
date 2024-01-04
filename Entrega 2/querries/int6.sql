.mode columns
.headers ON
.nullvalue NULL

SELECT j.idJogo, count(e.idEvento) AS numGolos
FROM JOGO j JOIN EVENTO e JOIN GOLO g
ON (j.idJogo = e.idJogo and e.idEvento = g.idEvento)
ORDER BY numGolos DESC
GROUP BY j.idJogo
LIMIT 5
