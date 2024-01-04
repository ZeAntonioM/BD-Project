.mode columns
.headers ON
.nullvalue NULL

SELECT p.nome as Jogador, count(g.idEvento) as Golos, count(s.idEvento) as Substituições, count(c.idEvento) as Cartões
FROM EVENTO e JOIN GOLO g JOIN SUBSTITUICAO s JOIN CARTAO c JOIN PESSOA p
ON ((e.idEvento = g.idEvento or e.idEvento = s.idEvento or e.idEvento = c.idEvento) and (e.idJogador = p.idpessoa))
WHERE e.idJogo = 195
GROUP BY p.idPessoa
ORDER BY e.idJogador ASC
