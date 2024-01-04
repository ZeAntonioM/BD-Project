.mode columns
.headers ON
.nullvalue NULL

SELECT DISTINCT j.idJornada, j.idJogo, ECASA.nomeEquipa,(
	SELECT COUNT(*) FROM GOLO GCASA WHERE GCASA.idEvento = EVCASA.idEvento AND GCASA.idEquipa = ECASA.idEquipa) as GolosCasa,(
	SELECT COUNT(*) FROM GOLO GFORA WHERE GFORA.idEvento = EVFORA.idEvento AND GFORA.idEquipa = EFORA.idEquipa) as GolosFora,
	EFORA.nomeEquipa
FROM JOGO j
LEFT JOIN EQUIPA ECASA LEFT JOIN EQUIPA EFORA ON (ECASA.idEquipa = j.idEquipaCasa and EFORA.idEquipa = j.idEquipaFora)
LEFT JOIN EVENTO EVCASA LEFT JOIN EVENTO EVFORA ON (EVCASA.idJogo = j.idJogo and EVFORA.idJogo = j.idJogo)
WHERE j.idJornada LIKE "J32" AND (ECASA.idEquipa = 14 or EFORA.idEquipa = 14)

