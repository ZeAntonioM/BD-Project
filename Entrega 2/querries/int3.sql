.mode columns
.headers ON
.nullvalue NULL

SELECT e.nomeEquipa, count(j.idPessoa) as numJogadores
FROM EQUIPA e JOIN JOGADOR j
ON (j.idEquipa = e.idEquipa)
GROUP BY e.nomeEquipa
ORDER BY numJogadores DESC
LIMIT 5
