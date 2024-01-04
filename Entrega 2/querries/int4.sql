.mode columns
.headers ON
.nullvalue NULL

SELECT j.idJogo, T.nomeEquipa, F.nomeEquipa, j.nomeEstadio
FROM JOGO j
	LEFT JOIN EQUIPA T ON T.idEquipa = j.idEquipaCasa
	LEFT JOIN EQUIPA F ON F.idEquipa = j.idEquipaFora
WHERE j.idJornada LIKE "J15";
