.mode columns
.headers ON
.nullvalue NULL

/*
SELECT e.nomeEquipa as "Equipa", SUM(CASE 
             WHEN (SELECT COUNT(*) FROM GOLO GCASA WHERE GCASA.idEvento = ECASA.idEvento AND GCASA.idEquipa = ec.idEquipa) > 
                  (SELECT COUNT(*) FROM GOLO GFORA WHERE GFORA.idEvento = EFORA.idEvento AND GFORA.idEquipa = ef.idEquipa) THEN 3
             WHEN (SELECT COUNT(*) FROM GOLO GCASA WHERE GCASA.idEvento = ECASA.idEvento AND GCASA.idEquipa = ec.idEquipa) = 
                  (SELECT COUNT(*) FROM GOLO GFORA WHERE GFORA.idEvento = EFORA.idEvento AND GFORA.idEquipa = ef.idEquipa) THEN 1
             ELSE 0
           END) as Pontos, 
           RANK() OVER(ORDER BY 
           		 SUM(CASE 
			     WHEN (SELECT COUNT(*) FROM GOLO GCASA WHERE GCASA.idEvento = ECASA.idEvento AND GCASA.idEquipa = ec.idEquipa) > 
				  (SELECT COUNT(*) FROM GOLO GFORA WHERE GFORA.idEvento = EFORA.idEvento AND GFORA.idEquipa = ef.idEquipa) THEN 3
			     WHEN (SELECT COUNT(*) FROM GOLO GCASA WHERE GCASA.idEvento = ECASA.idEvento AND GCASA.idEquipa = ec.idEquipa) = 
				  (SELECT COUNT(*) FROM GOLO GFORA WHERE GFORA.idEvento = EFORA.idEvento AND GFORA.idEquipa = ef.idEquipa) THEN 1
			     ELSE 0
			     END) DESC, e.nomeEquipa ASC) as Lugar
FROM JOGO j
JOIN EQUIPA e ON e.idEquipa = j.idEquipaCasa OR e.idEquipa = j.idEquipaFora
LEFT JOIN EVENTO ECASA ON ECASA.idJogo = j.idJogo
LEFT JOIN EVENTO EFORA ON EFORA.idJogo = j.idJogo
JOIN EQUIPA ec ON ec.idEquipa = j.idEquipaCasa
JOIN EQUIPA ef ON ef.idEquipa = j.idEquipaFora
WHERE (CAST(SUBSTR(j.idJornada, 2) AS INTEGER) <= 32 /* Aqui fica a jornada desejada
GROUP BY e.idEquipa
ORDER BY Lugar ASC; 
*/

SELECT 
  e.nomeEquipa AS 'Equipa',
  SUM(CASE WHEN g.idEquipa = e.idEquipa THEN 1 ELSE 0 END) AS 'Golos Marcados',
  SUM(CASE WHEN g.idEquipa <> e.idEquipa AND g.idEquipa IS NOT NULL THEN 1 ELSE 0 END) AS 'Golos Sofridos',
  SUM(CASE WHEN g.idEquipa = e.idEquipa THEN 1 ELSE -1 END) AS 'Saldo de Golos',
  SUM(
  (SELECT 
 	CASE
 	    WHEN ((SELECT COUNT(*) FROM GOLO GCASA WHERE GCASA.idEvento = EVCASA.idEvento AND GCASA.idEquipa = ECASA.idEquipa) > (SELECT COUNT(*) FROM GOLO GFORA WHERE GFORA.idEvento = EVFORA.idEvento AND GFORA.idEquipa = EFORA.idEquipa)) THEN 3
 	    WHEN ((SELECT COUNT(*) FROM GOLO GCASA WHERE GCASA.idEvento = EVCASA.idEvento AND GCASA.idEquipa = ECASA.idEquipa) = (SELECT COUNT(*) FROM GOLO GFORA WHERE GFORA.idEvento = EVFORA.idEvento AND GFORA.idEquipa = EFORA.idEquipa)) THEN 1
 	    ELSE 0
 	    END
 	FROM EQUIPA e
	LEFT JOIN EQUIPA ECASA LEFT JOIN EQUIPA EFORA ON (ECASA.idEquipa = j.idEquipaCasa and EFORA.idEquipa = j.idEquipaFora)
	LEFT JOIN EVENTO EVCASA LEFT JOIN EVENTO EVFORA ON (EVCASA.idJogo = j.idJogo and EVFORA.idJogo = j.idJogo)
	JOIN JOGO j 
	ON j.idJogo = EVCASA.idJogo AND j.idJogo = EVFORA.idJogo AND EFORA.idEquipa = j.idEquipaFora AND ECASA.idEquipa = j.idEquipaCasa
	WHERE CAST(SUBSTR(j.idJornada, 2) AS INTEGER) <= 38
	GROUP BY e.idEquipa)) AS 'Pontos'

FROM EQUIPA e
LEFT JOIN GOLO g
JOIN EVENTO ev ON ev.idEvento = g.idEvento
JOIN JOGO j ON j.idJogo = ev.idJogo AND (e.idEquipa = j.idEquipaFora or e.idEquipa = j.idEquipaCasa)
WHERE CAST(SUBSTR(j.idJornada, 2) AS INTEGER) <= 38
GROUP BY e.idEquipa
ORDER BY Pontos DESC, 'Saldo de Golos' DESC, 'Golos Marcados' DESC;





