.mode columns
.headers ON
.nullvalue NULL

SELECT p.nome, p.idade, p.nacionalidade, e.nomeEquipa
FROM JOGADOR j JOIN PESSOA p JOIN EQUIPA e
ON( j.idPessoa = p.idPessoa and j.idEquipa = e.idEquipa)
WHERE (
	p.nacionalidade NOT LIKE "Brasil"
    )
ORDER BY p.idade DESC
LIMIT 10;