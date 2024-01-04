.mode columns
.headers ON
.nullvalue NULL

SELECT e.nomeEquipa, COUNT(ev.idEvento) as numGolos
FROM EVENTO ev JOIN GOLO g ON (ev.idEvento = g.idEvento), 
	 EQUIPA e JOIN JOGADOR j ON (ev.idJogador = j.idPessoa and  e.idEquipa = j.idEquipa)
GROUP BY e.nomeEquipa
ORDER BY numGolos DESC

