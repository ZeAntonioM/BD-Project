.mode columns
.headers ON
.nullvalue NULL

SELECT p.nome, p.idade, e.nomeEquipa, j.numCamisola
FROM JOGADOR j JOIN PESSOA p JOIN EQUIPA e
ON (j.idPessoa = p.idPessoa and j.idEquipa = e.idEquipa)
WHERE(
	p.idade >= 18 and p.idade <= 23
	)
ORDER BY p.idade ASC;